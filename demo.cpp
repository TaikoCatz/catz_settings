#include <iostream>

#include <hidapi.h>

constexpr int kMaxStrDescLen = 255;

void panic(std::wstring_view msg)
{
    std::wcerr << L"Error: " << msg << L'\n';
    hid_exit();
    exit(1);
}

int main(int argc, char* argv[])
{
    int res;
    unsigned char buf[65];
    wchar_t wstr[kMaxStrDescLen];
    hid_device *handle;
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
    for (i = 0; i < 4; i++)
        std::wcout << L"buf[" << i << L"]: " << static_cast<int>(buf[i]) << L'\n';

    hid_close(handle);

    res = hid_exit();

    return 0;
}
