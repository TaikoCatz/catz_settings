#include "settings.hpp"

#include <algorithm>
#include <expected>

#include <wx/wx.h>

#include "constants.hpp"

namespace catz {

namespace {

constexpr int kSettingsPayloadSize = 32;
constexpr int kCrcRegionBegin = 16;
constexpr int kCrcOffset = 12;

// CRC32 (Ethernet, ZIP, etc.)
constexpr uint32_t crc32(std::span<const unsigned char> data)
{
    uint32_t crc = 0xffff'ffff;
    for (unsigned char byte : data) {
        crc ^= byte;
        for (int i = 0; i < 8; i++) {
            crc = (crc >> 1) ^ (0xedb8'8320 & -(crc & 1));
        }
    }
    return ~crc;
}

// Read little-endian value, max 32 bits.
uint32_t readLe(std::span<const unsigned char> data)
{
    uint32_t result = 0;
    for (int i = 0; i < std::size(data); i++) {
        result |= uint32_t{data[i]} << (i * 8);
    }
    return result;
}

// Write little-endian value, max 32 bits.
void writeLe(uint32_t value, std::span<unsigned char> data)
{
    for (int i = 0; i < std::size(data); i++) {
        data[i] = value >> (i * 8);
    }
}

}  // namespace

std::vector<unsigned char> Settings::serialize() const
{
    wxCHECK(isValid(), {});

    std::vector<unsigned char> result(kSettingsPayloadSize, 0);

    // Header.
    std::ranges::copy(kSettingsHeader, result.begin());

    // Body.
    auto body = std::span(result).subspan(kCrcRegionBegin);
    body[0] = 0x01;
    body[2] = keyboard_altkey;
    body[3] = keypress_duration;
    for (int i = 0; i < 4; i++) {
        body[8 + i] = sensitivity[i];
    }
    body[12] = overall_sensitivity;
    body[13] = drumroll_level;

    // CRC.
    uint32_t crc = crc32(body);
    writeLe(crc, std::span(result).subspan(kCrcOffset, 4));

    return result;
}

std::expected<Settings, std::wstring> Settings::deserialize(std::span<const unsigned char> data)
{
    // Size.
    if (data.size() != kSettingsPayloadSize) {
        return std::unexpected<std::wstring>(L"Invalid payload size.");
    }

    // Header.
    if (!std::ranges::equal(data.first(std::size(kSettingsHeader)), kSettingsHeader)) {
        return std::unexpected<std::wstring>(L"Invalid header.");
    }

    // CRC.
    auto body = data.subspan(kCrcRegionBegin);
    uint32_t calc_crc = crc32(body);
    uint32_t reported_crc = readLe(data.subspan(kCrcOffset, 4));
    if (calc_crc != reported_crc) {
        return std::unexpected<std::wstring>(L"CRC corrupted.");
    }

    Settings result;
    auto fail_at = [](int offset) {
        return std::unexpected<std::wstring>(L"Off " + std::to_wstring(offset));
    };

    // Parse body.
    if (body[0] != 0x01) return fail_at(0);
    if (body[1] != 0x00) return fail_at(1);
    result.keyboard_altkey = body[2];
    result.keypress_duration = body[3];
    if (body[4] != 0x00) return fail_at(4);
    if (body[5] != 0x00) return fail_at(5);
    if (body[6] != 0x00) return fail_at(6);
    if (body[7] != 0x00) return fail_at(7);

    for (int i = 0; i < 4; i++) {
        result.sensitivity[i] = body[8 + i];
    }
    result.overall_sensitivity = body[12];
    result.drumroll_level = body[13];
    if (body[14] != 0x00) return fail_at(14);
    if (body[15] != 0x00) return fail_at(15);

    if (!result.isValid()) {
        return std::unexpected<std::wstring>(L"Out of range.");
    }
    return result;
}

}  // namespace catz
