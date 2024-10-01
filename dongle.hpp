#ifndef CATZ_SETTINGS_DONGLE_HPP
#define CATZ_SETTINGS_DONGLE_HPP

#include <cstdint>
#include <expected>
#include <string>
#include <vector>

#include <hidapi.h>

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


}  // namespace catz

#endif  // CATZ_SETTINGS_DONGLE_HPP
