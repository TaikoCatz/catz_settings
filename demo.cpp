#include <chrono>
#include <clocale>
#include <format>
#include <iostream>
#include <span>
#include <thread>

#include <hidapi.h>

constexpr int kMaxStrDescLen = 255;
constexpr int kReportSize = 64;

void panic(std::wstring_view msg)
{
    std::wcerr << L"Error: " << msg << L'\n';
    hid_exit();
    exit(1);
}

void send_feature(hid_device* handle, std::span<unsigned char> buf)
{
    int res = hid_send_feature_report(handle, buf.data(), buf.size());
    if (res < 0) {
        std::wcerr << L"Error: " << hid_error(handle) << L'\n';
    } else {
        std::wcerr << L"Written bytes: " << res << L'\n';
    }
}

int main(int argc, char* argv[])
{
    std::locale loc("");
    std::wcerr.imbue(loc);

    int res;
    unsigned char buf[kReportSize];
    wchar_t wstr[kMaxStrDescLen];

    res = hid_init();

    hid_device* handle = hid_open(0x16c0, 0x27d9, nullptr);
    if (!handle) panic(hid_error(nullptr));

    res = hid_get_manufacturer_string(handle, wstr, kMaxStrDescLen);
    if (res < 0) panic(hid_error(handle));
    std::wcerr << L"Manufacturer String: " << wstr << L'\n';

    res = hid_get_product_string(handle, wstr, kMaxStrDescLen);
    if (res < 0) panic(hid_error(handle));
    std::wcerr << L"Product String: " << wstr << L'\n';

    res = hid_get_serial_number_string(handle, wstr, kMaxStrDescLen);
    if (res < 0) panic(hid_error(handle));
    std::wcerr << L"Serial Number String: " << wstr << L'\n';

    buf[0] = 0x01;
    res = hid_get_feature_report(handle, buf, 64);
    if (res < 0) panic(hid_error(handle));

    std::wcerr << L"Received bytes: " << res << L'\n';
    for (int i = 0; i < res; i++) {
        std::wcerr << std::format(L"{:02x}{}", buf[i], i == res - 1 ? L'\n' : L' ');
    }

    if (res == 32) {
        // Write short.
        send_feature(handle, {buf, kReportSize - 1});

        // Write single byte.
        send_feature(handle, {buf, 1});

        auto recover = buf[1];
        // Write corrupted.
        buf[1] = 'x';
        send_feature(handle, {buf, kReportSize});

        // Write wrong report.
        buf[0] = 42;
        send_feature(handle, {buf, kReportSize});

        // Write back.
        buf[0] = 0x01;
        buf[1] = recover;
        send_feature(handle, {buf, kReportSize});
    }

    // Continue get status.
    for (int i = 0; i < 25; ++i) {
        res = hid_get_feature_report(handle, buf, kReportSize);
        if (res < 0) panic(hid_error(handle));

        std::wcerr << L"Received bytes: " << res << L'\n';
        for (int i = 0; i < res; i++) {
            std::wcerr << std::format(L"{:02x}{}", buf[i], i == res - 1 ? L'\n' : L' ');
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    hid_close(handle);

    res = hid_exit();

    return 0;
}
