#ifndef CATZ_SETTINGS_DONGLE_HPP
#define CATZ_SETTINGS_DONGLE_HPP

#include <cstdint>
#include <expected>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include <hidapi.h>

#include "settings.hpp"

namespace catz {

struct DongleHidInfo {
    uint16_t vendor_id;
    uint16_t product_id;
    std::wstring serial;
    std::string path;
};

class DongleEnumerator {
public:
    using EnumerateResult = std::expected<std::vector<DongleHidInfo>, std::wstring>;
    static EnumerateResult enumerate();

private:
    DongleEnumerator();
    ~DongleEnumerator();

    EnumerateResult getDevices();

    hid_device_info* list_ = nullptr;
};

class Dongle {
public:
    enum State {
        kInitFail = 0,  // Failed to initiate communication with the dongle.
        kCorrupted = 1,  // Dongle says its storage is corrupted, may be fixed by sending new settings.
        kOk = 2,  // Settings are loaded and valid.
        kSaving = 3,  // Settings are being saved.
        kRebooting = 4,  // Device is rebooting after saving settings.
        kInternalError = 5,  // Internal error, check error log.
        kUnsupported = 6,  // Version reported by the dongle is not supported.
    };

    Dongle(std::string_view path);
    ~Dongle();

    // Read a new feature report from the dongle, update the state.
    void readFeatureReport();

    // Send settings to the dongle. Read the response and update the state.
    // Settings must be valid.
    void sendSettings(const Settings& settings);

    // Get the current state.
    State state() const { return state_; }

    // Get log messages.
    std::wstring getLog() const { return log_.str(); }

private:
    void processFeatureReport(std::span<const unsigned char> feature);
    void processInitialRead(std::span<const unsigned char> feature);

    hid_device* device_ = nullptr;
    State state_ = kInitFail;
    std::wostringstream log_;

    Settings settings_;
};

}  // namespace catz

#endif  // CATZ_SETTINGS_DONGLE_HPP
