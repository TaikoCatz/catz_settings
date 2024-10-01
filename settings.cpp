#include "settings.hpp"

#include <algorithm>
#include <expected>

#include "constants.hpp"

namespace catz {

std::vector<unsigned char> Settings::serialize() const
{
    std::vector<unsigned char> result;
    // TODO
    return result;
}

std::expected<Settings, std::wstring> Settings::deserialize(std::span<const unsigned char> data)
{
    if (data.size() != kSettingsPayloadSize) {
        return std::unexpected<std::wstring>(L"Invalid payload size.");
    }

    if (!std::ranges::equal(data.first(std::size(kSettingsHeader)), kSettingsHeader)) {
        return std::unexpected<std::wstring>(L"Invalid header.");
    }

    // TODO: Check CRC.

    Settings result;
    // TODO
    return result;
}

}  // namespace catz
