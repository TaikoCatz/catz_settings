#ifndef CATZ_SETTINGS_SETTINGS_HPP
#define CATZ_SETTINGS_SETTINGS_HPP

#include <expected>
#include <span>
#include <string>
#include <vector>

namespace catz {

struct Settings {
    int sensitivity[4] = { 16, 16, 16, 16 };  // 8-16.
    int overall_sensitivity = 1;  // 1-5.

    int drumroll_level = 2;  // 0-4.
    int keypress_duration = 0;  // 2-30, or 0 for use default.

    int keyboard_altkey = 0;  // 0 = DF-JK, 1 = ZX-CV.

    bool isValid() const {
        if (overall_sensitivity < 1 || overall_sensitivity > 5) return false;
        if (drumroll_level < 0 || drumroll_level > 4) return false;
        if (keypress_duration != 0 && (keypress_duration < 2 || keypress_duration > 30)) return false;
        if (keyboard_altkey < 0 || keyboard_altkey > 1) return false;
        for (int i = 0; i < 4; ++i) {
            if (sensitivity[i] < 8 || sensitivity[i] > 16) return false;
        }
        return true;
    }

    std::vector<unsigned char> serialize() const;

    static std::expected<Settings, std::wstring> deserialize(std::span<const unsigned char>);
};

}  // namespace catz

#endif  // CATZ_SETTINGS_SETTINGS_HPP
