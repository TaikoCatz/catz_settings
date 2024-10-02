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
        log_ << L"Open: " << hid_error(nullptr) << L"\n";
        return;
    }
    log_ << L"Open: OK.\n";

    readFeatureReport();
}

Dongle::~Dongle()
{
    if (device_) {
        hid_close(device_);
    }
}

void Dongle::readFeatureReport()
{
    unsigned char buf[kFeatureReportBufferSize] = {};

    buf[0] = kFeatureReportId;
    const auto res = hid_get_feature_report(device_, buf, sizeof(buf));

    if (res < 0) {
        log_ << L"GetFeature: " << hid_error(device_) << L"\n";
        state_ = State::kInitFail;
        return;
    }
    log_ << L"GetFeature: " << logifyPayload({buf, size_t(res)}) << L"\n";

    processFeatureReport({buf, size_t(res)});
}

void Dongle::sendSettings(const Settings& settings)
{
    assert(state_ == kCorrupted || state_ == kOk);

    // TODO: really send the settings.
}

void Dongle::processFeatureReport(std::span<const unsigned char> feature)
{
    if (state_ == State::kInitFail) {
        processInitialRead(feature);
    } else if (state_ == State::kCorrupted || state_ == State::kOk) {
        // TODO: see if write is ongoing.
    } else if (state_ == State::kSaving) {
        // TODO: see if device has transited to rebooting.
    } else if (state_ == State::kRebooting) {
        // Do nothing, wait for reboot.
    } else if (state_ == State::kInternalError) {
        // Do nothing.
    }
}

void Dongle::processInitialRead(std::span<const unsigned char> feature)
{
    state_ = State::kInitFail;  // By default.

    if (feature.size() < std::size(kMagic)) {
        log_ << L"Init: short (" << feature.size() << ")\n";
        return;
    }

    if (feature.size() == std::size(kStorageInvalidPayload)
            && std::ranges::equal(feature, kStorageInvalidPayload)) {
        state_ = State::kCorrupted;
        log_ << L"Init: corrupted.\n";
        return;
    }

    // Check if the magic matches.
    if (!std::ranges::equal(feature.first(std::size(kMagic)), kMagic)) {
        log_ << L"Init: magic mismatch.\n";
        return;
    }

    // Check if device version matches.
    if (feature[4] != '4' || feature[5] != ' ' || feature[6] != ' ' || feature[7] != ' ') {
        log_ << L"Init: unknown dev.\n";
        state_ = State::kUnsupported;
        return;
    }

    // Check if protocol version matches.
    if (feature[8] != 0x00 || feature[9] != 0x00) {
        log_ << L"Init: unknown proto.\n";
        state_ = State::kUnsupported;
        return;
    }

    // OK, deserialize the settings.
    auto des = Settings::deserialize(feature);
    if (!des) {
        log_ << L"Init: deser babble.\n";
        log_ << L"Deser: " << des.error() << L"\n";
        return;
    }

    // Settings are valid.
    settings_ = des.value();
    state_ = State::kOk;
}


}  // namespace catz
