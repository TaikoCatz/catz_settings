#include <cassert>
#include <cstdlib>
#include <optional>

#include <hidapi.h>
#include <wx/wx.h>

#ifdef _WIN32
#include <locale.h>
#endif  // _WIN32

#include "dongle.hpp"
#include "ui/CatzSettingsUi.h"

using namespace catz;

class SelectDeviceDialogImpl final : public SelectDeviceDialog {
public:
	SelectDeviceDialogImpl(wxWindow* parent, std::optional<DongleHidInfo>& dongle_hid_info)
            : SelectDeviceDialog(parent),
            dongle_hid_info_(dongle_hid_info) {
        dongle_hid_info_ = std::nullopt;
        doRefresh();
    }

    void handleBtnRefresh(wxCommandEvent& event) override {
        doRefresh();
    }

    void handleBtnChoose(wxCommandEvent& event) override {
        const auto selection = m_listBox_devices->GetSelection();
        if (selection == wxNOT_FOUND || selection < 0 || selection >= std::ssize(dongles_)) {
            wxMessageBox("Please select a valid device.", "Error", wxICON_ERROR);
            return;
        }

        dongle_hid_info_ = dongles_[selection];
        EndModal(wxID_OK);
    }

private:
    void doRefresh() {
        m_listBox_devices->Clear();
        m_listBox_devices->Disable();
        dongles_.clear();

        auto enumerated = DongleEnumerator::enumerate();
        if (!enumerated) {
            m_listBox_devices->Append("No dongle device found.");
            wxMessageBox(enumerated.error(), "Error", wxICON_ERROR);
            return;
        }

        dongles_ = std::move(enumerated.value());
        for (const auto& dongle : dongles_) {
            m_listBox_devices->Append(dongle.serial);
        }
        enableSelection();
    }

    void enableSelection() {
        m_listBox_devices->Enable();
        m_button_choose->Enable();
    }

    std::optional<DongleHidInfo>& dongle_hid_info_;
    std::vector<DongleHidInfo> dongles_;
};

class MainWindowImpl final : public MainWindow {
public:
	MainWindowImpl() : MainWindow(nullptr) {}

	void handleBtnSelectDevice(wxCommandEvent& event) override
	{
        std::optional<DongleHidInfo> dongle_info;
		auto* select_device_dialog = new SelectDeviceDialogImpl(this, dongle_info);
		select_device_dialog->ShowModal();

        if (dongle_info) {
            handleDeviceSelected(*dongle_info);
        }
	}

    void handleBtnHelp(wxCommandEvent& event) override
    {
        auto* help_dialog = new HelpDialog(this);
        help_dialog->ShowModal();
    }

private:
    void handleDeviceSelected(const DongleHidInfo& dongle_info) {
        dongle_.reset();
        dongle_.emplace(dongle_info.path);

        auto state = dongle_->state();
        if (state == Dongle::kOk) {
            wxMessageBox("Device state is OK.", "Success", wxICON_INFORMATION);
        } else if (state == Dongle::kCorrupted) {
            wxMessageBox("Device reports its stored setting is corrupted. Saving a new setting may fix it.", "Info", wxICON_INFORMATION);
        } else {
            wxMessageBox(dongle_->getLog(), "Error", wxICON_ERROR);
        }
    }

    std::optional<Dongle> dongle_;
};

class MyApp final : public wxApp
{
public:
    bool OnInit() override {
#ifdef _WIN32
        // On Windows, set locale to utf-8.
        setlocale(LC_ALL, ".UTF-8");
#endif  // _WIN32
        hid_init();
        std::atexit([](){ hid_exit(); });

        auto* main_window = new MainWindowImpl();
        main_window->Show(true);

        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
