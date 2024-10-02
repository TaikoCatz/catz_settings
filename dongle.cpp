#include "dongle.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>

#include <hidapi.h>
#include <wx/wx.h>

#include "constants.hpp"
#include "settings.hpp"

namespace catz {

namespace {

std::wstring logifyPayload(std::span<const unsigned char> payload)
{
    std::wostringstream ss;
    ss << L'(' << payload.size() << L')';
    for (const auto byte : payload) {
        ss << L' ' << std::hex << std::setw(2) << std::setfill(L'0') << int{byte};
    }
    return ss.str();
}

}  // namespace

auto DongleEnumerator::enumerate() -> EnumerateResult
{
    return DongleEnumerator().getDevices();
}

DongleEnumerator::DongleEnumerator()
{
    list_ = hid_enumerate(kVendorId, kProductId);
}

DongleEnumerator::~DongleEnumerator()
{
    if (list_) {
        hid_free_enumeration(list_);
    }
}

auto DongleEnumerator::getDevices() -> EnumerateResult
{
    if (!list_) {
        return std::unexpected<std::wstring>(hid_error(nullptr));
    }

    std::vector<DongleHidInfo> result;
    for (auto* dev = list_; dev; dev = dev->next) {
        result.push_back({
            .vendor_id = dev->vendor_id,
            .product_id = dev->product_id,
            .serial = dev->serial_number,
            .path = dev->path,
        });
    }
    return result;
}

Dongle::Dongle(std::string_view path)
{
    device_ = hid_open_path(path.data());
    if (!device_) {
        state_ = State::kInitFail;
        error_msg_ = std::wstring{L"Failed to open device: "} + hid_error(nullptr);
        log_ << L"Open: " << hid_error(nullptr) << L"\n";
        return;
    }
    log_ << L"Open: OK.\n";

    readAndProcessFeatureReport();
}

Dongle::~Dongle()
{
    if (device_) {
        hid_close(device_);
    }
}

void Dongle::readAndProcessFeatureReport()
{
    processFeatureReport(readFeatureReport());
}

void Dongle::sendSettings(const Settings& settings)
{
    wxCHECK(state_ == kCorrupted || state_ == kOk, );

    auto payload = settings.serialize();
    log_ << L"Save: " << logifyPayload(payload) << L"\n";

    const auto res = hid_send_feature_report(device_, payload.data(), payload.size());
    if (res < 0) {
        state_ = State::kInternalError;
        error_msg_ = L"Could not send settings.";
        log_ << L"SendFeature: " << hid_error(device_) << L"\n";
        return;
    }

    // Settings sent. Read back feature report.
    auto timeout = std::chrono::steady_clock::now() + kSendSettingsTimeout;
    bool log_once_ongoing = false;
    while (true) {
        if (std::chrono::steady_clock::now() > timeout) {
            state_ = State::kInternalError;
            error_msg_ = L"Device timeout when saving settings.";
            log_ << L"Save: timeout.\n";
            break;
        }

        auto response = readFeatureReport();
        if (std::ranges::equal(response, kWriteOngoingPayload)) {
            state_ = State::kSaving;
            if (!log_once_ongoing) {
                log_ << L"Save: ongoing.\n";
                log_once_ongoing = true;
            }
            // The only branch to continue.
        } else if (std::ranges::equal(response, kWriteSuccessPayload)) {
            state_ = State::kRebooting;
            log_ << L"Save: rebooting.\n";
            break;
        } else {
            // Babble.
            state_ = State::kInternalError;
            error_msg_ = L"Could not understand device response during saving.";
            log_ << L"Save: babble, " << logifyPayload(response) << L"\n";
            break;
        }
    }
}

std::vector<unsigned char> Dongle::readFeatureReport()
{
    std::vector<unsigned char> buf(kFeatureReportBufferSize, 0);

    buf[0] = kFeatureReportId;
    const auto res = hid_get_feature_report(device_, buf.data(), buf.size());

    if (res < 0) {
        state_ = State::kInitFail;
        error_msg_ = std::wstring{L"Failed to communicate: "} + hid_error(device_);
        log_ << L"GetFeature: " << hid_error(device_) << L"\n";
        return {};
    }

    buf.resize(res);
    log_ << L"GetFeature: " << logifyPayload(buf) << L"\n";
    return buf;
}

void Dongle::processFeatureReport(std::span<const unsigned char> feature)
{
    if (state_ == State::kInitFail) {
        // Initial read.
        processInitialRead(feature);
    } else {
        // Any other case should not reach here.
        wxCHECK(false, );
    }
}

void Dongle::processInitialRead(std::span<const unsigned char> feature)
{
    state_ = State::kInitFail;  // By default.

    if (feature.size() < std::size(kMagic)) {
        error_msg_ = L"Could not understand device response: too short.";
        log_ << L"Init: short (" << feature.size() << ")\n";
        return;
    }

    if (std::ranges::equal(feature, kStorageInvalidPayload)) {
        state_ = State::kCorrupted;
        log_ << L"Init: corrupted.\n";
        return;
    }

    // Check if the magic matches.
    if (!std::ranges::equal(feature.first(std::size(kMagic)), kMagic)) {
        error_msg_ = L"Could not understand device response: magic mismatch.";
        log_ << L"Init: magic mismatch.\n";
        return;
    }

    // Check if device version matches.
    if (feature[4] != '4' || feature[5] != ' ' || feature[6] != ' ' || feature[7] != ' ') {
        state_ = State::kUnsupported;
        error_msg_ = L"Unsupported device version. Only \"Apricot's Taiko I/O Dongle v4\" is supported.";
        log_ << L"Init: unknown dev.\n";
        return;
    }

    // Check if protocol version matches.
    if (feature[8] != 0x00 || feature[9] != 0x00) {
        state_ = State::kUnsupported;
        error_msg_ = L"Unsupported protocol version. Please download the latest version of this tool.";
        log_ << L"Init: unknown proto.\n";
        return;
    }

    // OK, deserialize the settings.
    auto des = Settings::deserialize(feature);
    if (!des) {
        error_msg_ = L"Could not understand device reported settings.";
        log_ << L"Init: deser babble.\n";
        log_ << L"Deser: " << des.error() << L"\n";
        return;
    }

    // Settings are valid.
    settings_ = des.value();
    state_ = State::kOk;
}

}  // namespace catz
