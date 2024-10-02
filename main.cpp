#include <cstdlib>
#include <optional>

#include <hidapi.h>
#include <wx/wx.h>

#ifdef _WIN32
#include <locale.h>
#endif  // _WIN32

#include "constants.hpp"
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
	MainWindowImpl() : MainWindow(nullptr) {
        settingsToUi(Settings{});  // Default settings.
        doSelectDeviceDialog();  // Select the first device.
    }

	void handleBtnSelectDevice(wxCommandEvent& event) override {
        doSelectDeviceDialog();
	}

    void handleBtnHelp(wxCommandEvent& event) override {
        auto* help_dialog = new HelpDialog(this);
        help_dialog->ShowModal();
    }

    void handleBtnSave(wxCommandEvent& event) override {
        setSaveButtonEnabled(false);
        setStatusBarStatus(L"Saving settings to dongle...");

        auto settings = uiToSettings();
        dongle_->sendSettings(settings);

        auto state = dongle_->state();
        if (state == Dongle::kRebooting) {
            wxMessageBox("Settings saved. Device is rebooting.", "Info", wxICON_INFORMATION);
            wxMessageBox(L"Debug log:\n" + dongle_->getLog(), "Debug log", wxICON_INFORMATION);
            setStatusBarStatus(L"Saved...");
            // Now select another device.
            doSelectDeviceDialog();
            return;
        } else if (state == Dongle::kInternalError) {
            wxMessageBox(dongle_->getErrorMsg(), "Error", wxICON_ERROR);
            wxMessageBox(L"Debug log:\n" + dongle_->getLog(), "Debug log", wxICON_INFORMATION);
            handleDeviceSelected(std::nullopt);
        } else {
            // Should not reach here.
            wxCHECK(false, );
        }
    }

    void handleDurOverrideCheckbox(wxCommandEvent& event) override {
        uiUpdate();
    }

    void handleChoiceLevel(wxCommandEvent& event) override {
        uiUpdate();
    }

    void handleSliderKeypressDur(wxScrollEvent& event) override {
        uiUpdate();
    }

private:
    void doSelectDeviceDialog() {
        setSaveButtonEnabled(false);

        std::optional<DongleHidInfo> dongle_info;
		auto* select_device_dialog = new SelectDeviceDialogImpl(this, dongle_info);
		select_device_dialog->ShowModal();

        handleDeviceSelected(dongle_info);
    }

    void handleDeviceSelected(const std::optional<DongleHidInfo>& dongle_info) {
        setSaveButtonEnabled(false);
        dongle_.reset();

        if (!dongle_info) {
            setStatusBarDevice(L"");
            setStatusBarStatus(L"No device selected.");
            return;
        }

        dongle_.emplace(dongle_info->path);
        auto state = dongle_->state();
        if (state == Dongle::kOk) {
            settingsToUi(dongle_->getSettings());
            setSaveButtonEnabled(true);
            setStatusBarDevice(dongle_info->serial);
            setStatusBarStatus(L"Settings loaded.");
        } else if (state == Dongle::kCorrupted) {
            wxMessageBox("Device reports its stored setting is corrupted. Saving a new setting may fix it.", "Info", wxICON_INFORMATION);
            settingsToUi(Settings{});  // Default settings.
            setSaveButtonEnabled(true);
            setStatusBarDevice(dongle_info->serial);
            setStatusBarStatus(L"Corrupted settings.");
        } else {
            wxMessageBox(dongle_->getErrorMsg(), "Error", wxICON_ERROR);
            wxMessageBox(L"Debug log:\n" + dongle_->getLog(), "Debug log", wxICON_INFORMATION);
            handleDeviceSelected(std::nullopt);
        }
    }

    void setSaveButtonEnabled(bool enabled) {
        m_button_save->Enable(enabled);
    }

    void setStatusBarDevice(const auto& serial) {
        m_statusBar->SetStatusText(serial, 1);
        setStatusBarStatus(L"");
    }
    void setStatusBarStatus(const auto& status) {
        m_statusBar->SetStatusText(status, 0);
    }

    void settingsToUi(const Settings& settings) {
        wxCHECK(settings.isValid(), );

        m_choice_overall_sensi->SetSelection(settings.overall_sensitivity - 1);
        m_slider_lk->SetValue(settings.sensitivity[0]);
        m_slider_ld->SetValue(settings.sensitivity[1]);
        m_slider_rd->SetValue(settings.sensitivity[2]);
        m_slider_rk->SetValue(settings.sensitivity[3]);

        m_choice_drumroll->SetSelection(settings.drumroll_level);
        if (settings.keypress_duration == 0) {
            m_check_keypress_dur_default->SetValue(true);
            m_slider_keypress->SetValue(kDefaultKeypressDurationMsByLevel[settings.drumroll_level]);
        } else {
            m_check_keypress_dur_default->SetValue(false);
            m_slider_keypress->SetValue(settings.keypress_duration);
        }

        m_choice_keyboard->SetSelection(settings.keyboard_altkey);

        uiUpdate();
    }

    Settings uiToSettings() {
        Settings settings;

        settings.overall_sensitivity = m_choice_overall_sensi->GetSelection() + 1;
        settings.sensitivity[0] = m_slider_lk->GetValue();
        settings.sensitivity[1] = m_slider_ld->GetValue();
        settings.sensitivity[2] = m_slider_rd->GetValue();
        settings.sensitivity[3] = m_slider_rk->GetValue();

        settings.drumroll_level = m_choice_drumroll->GetSelection();
        if (m_check_keypress_dur_default->IsChecked()) {
            settings.keypress_duration = 0;
        } else {
            settings.keypress_duration = m_slider_keypress->GetValue();
        }

        settings.keyboard_altkey = m_choice_keyboard->GetSelection();

        wxCHECK(settings.isValid(), {});
        return settings;
    }

    void uiUpdate() {
        if (m_check_keypress_dur_default->IsChecked()) {
            m_slider_keypress->Disable();
            int level = m_choice_drumroll->GetSelection();
            wxCHECK(level >= 0 && level < std::ssize(kDefaultKeypressDurationMsByLevel), );
            auto ms = kDefaultKeypressDurationMsByLevel[level];
            m_slider_keypress->SetValue(ms);
            m_text_keypress_ms->SetLabel(std::to_wstring(ms) + L"ms (default)");
        } else {
            m_slider_keypress->Enable();
            m_text_keypress_ms->SetLabel(std::to_wstring(m_slider_keypress->GetValue()) + L"ms (override)");
        }
        m_text_keypress_ms->GetContainingSizer()->Layout();
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
