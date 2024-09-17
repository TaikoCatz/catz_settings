#include <iostream>
#include <span>

#include <hidapi.h>

constexpr int kMaxStrDescLen = 255;

void panic(std::wstring_view msg)
{
    std::wcerr << L"Error: " << msg << L'\n';
    hid_exit();
    exit(1);
}

void send_data(hid_device* handle, std::span<unsigned char> buf)
{
    int res = hid_write(handle, buf.data(), buf.size());
    if (res < 0) panic(hid_error(handle));
    std::wcout << L"Written bytes: " << res << L'\n';
}

int main(int argc, char* argv[])
{
    int res;
    unsigned char buf[65];
    wchar_t wstr[kMaxStrDescLen];
    hid_device* handle;
    int i;

    res = hid_init();

    handle = hid_open(0x16c0, 0x27d9, nullptr);
    if (!handle) panic(hid_error(nullptr));

    res = hid_get_manufacturer_string(handle, wstr, kMaxStrDescLen);
    if (res < 0) panic(hid_error(handle));
    std::wcout << L"Manufacturer String: " << wstr << L'\n';

    res = hid_get_product_string(handle, wstr, kMaxStrDescLen);
    if (res < 0) panic(hid_error(handle));
    std::wcout << L"Product String: " << wstr << L'\n';

    res = hid_get_serial_number_string(handle, wstr, kMaxStrDescLen);
    if (res < 0) panic(hid_error(handle));
    std::wcout << L"Serial Number String: " << wstr << L'\n';

    res = hid_read(handle, buf, 64);
    if (res < 0) panic(hid_error(handle));

    std::wcout << L"Received bytes: " << res << L'\n';
    for (i = 0; i < 16; i++)
        std::wcout << L"buf[" << i << L"]: " << static_cast<int>(buf[i]) << L'\n';
    
    if (res == 32) {
        // Write back.
        send_data(handle, {buf, 32});

        // Write short.
        send_data(handle, {buf, 31});

        // Write single byte.
        send_data(handle, {buf, 1});

        // Write corrupted.
        buf[1] = 'x';
        send_data(handle, {buf, 32});

        // Write wrong report.
        buf[0] = 42;
        send_data(handle, {buf, 32});
    }

    hid_close(handle);

    res = hid_exit();

    return 0;
}
