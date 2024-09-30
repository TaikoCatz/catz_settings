#ifdef _WIN32
#include <locale.h>
#endif  // _WIN32

#include <wx/wx.h>

#include "ui/CatzSettingsUi.h"

class SelectDeviceWindowImpl : public SelectDeviceWindow {
public:
	SelectDeviceWindowImpl(wxWindow* parent) : SelectDeviceWindow(parent) {}

private:
	wxWindowDisabler disable_parent_{this};
};

class MainWindowImpl : public MainWindow {
public:
	MainWindowImpl() : MainWindow(nullptr) {}

	void handleBtnSelectDevice(wxCommandEvent& event) override
	{
		auto* select_device_window = new SelectDeviceWindowImpl(this);
		select_device_window->Show(true);
	}
};

class MyApp : public wxApp
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
