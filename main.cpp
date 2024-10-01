#ifdef _WIN32
#include <locale.h>
#endif  // _WIN32

#include <wx/wx.h>

#include "ui/CatzSettingsUi.h"

class SelectDeviceDialogImpl final : public SelectDeviceDialog {
public:
	SelectDeviceDialogImpl(wxWindow* parent) : SelectDeviceDialog(parent) {}
};

class MainWindowImpl final : public MainWindow {
public:
	MainWindowImpl() : MainWindow(nullptr) {}

	void handleBtnSelectDevice(wxCommandEvent& event) override
	{
		auto* select_device_dialog = new SelectDeviceDialogImpl(this);
		select_device_dialog->ShowModal();
	}
};

class MyApp final : public wxApp
{
public:
    bool OnInit() override {
#ifdef _WIN32
        // On Windows, set locale to utf-8.
        setlocale(LC_ALL, ".UTF-8");
#endif  // _WIN32

        auto* main_window = new MainWindowImpl();
        main_window->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
