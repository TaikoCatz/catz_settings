#ifndef CATZ_SETTINGS_CONSTANTS_HPP
#define CATZ_SETTINGS_CONSTANTS_HPP

#include <cstdint>

namespace catz {

constexpr uint16_t kVendorId = 0x16c0;
constexpr uint16_t kProductId = 0x27d9;
constexpr int kFeatureReportBufferSize = 64;
constexpr int kFeatureReportId = 0x01;

constexpr int kDefaultKeypressDurationMsByLevel[] = {
    16, 16, 10, 8, 6,
};

constexpr unsigned char kMagic[] = {
    kFeatureReportId, 'S', 'd', 'T',
};
constexpr unsigned char kSettingsHeader[] = {
    kFeatureReportId, 'S', 'd', 'T', '4', ' ', ' ', ' ',
    0x00, 0x00,
    0x01, 0x00,
};

constexpr unsigned char kStorageInvalidPayload[] = {
    kFeatureReportId, 'S', 'd', 'T', '4', ' ', ' ', ' ',
    0x00, 0x00,
    0x01, 0xff,
    0x00, 0x00, 0x00, 0x00,
};
constexpr unsigned char kWriteOngoingPayload[] = {
    kFeatureReportId, 'S', 'd', 'T', '4', ' ', ' ', ' ',
    0x00, 0x00,
    0x02, 0xff,
    0x00, 0x00, 0x00, 0x00,
};
constexpr unsigned char kWriteSuccessPayload[] = {
    kFeatureReportId, 'S', 'd', 'T', '4', ' ', ' ', ' ',
    0x00, 0x00,
    0x03, 0xff,
    0x00, 0x00, 0x00, 0x00,
};

}  // namespace catz

#endif  // CATZ_SETTINGS_CONSTANTS_HPP
