#include "dongle.hpp"

#include <hidapi.h>
#include <wx/wx.h>

namespace catz {

namespace {
constexpr uint16_t kVendorId = 0x16c0;
constexpr uint16_t kProductId = 0x27d9;
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

}  // namespace catz
