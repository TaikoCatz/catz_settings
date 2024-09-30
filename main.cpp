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
        auto* main_window = new MainWindowImpl();
        main_window->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
