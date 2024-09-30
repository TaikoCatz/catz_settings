///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6a)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/choice.h>
#include <wx/statbox.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/listbox.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainWindow
///////////////////////////////////////////////////////////////////////////////
class MainWindow : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText12;
		wxStaticText* m_staticText13;
		wxSlider* m_slider_lk;
		wxSlider* m_slider_ld;
		wxSlider* m_slider_rd;
		wxSlider* m_slider_rk;
		wxStaticText* m_staticText131;
		wxChoice* m_choice_overall_sensi;
		wxChoice* m_choice_drumroll;
		wxCheckBox* m_keypress_dur_override;
		wxSlider* m_slider_keypress;
		wxStaticText* m_text_keypress_ms;
		wxStaticText* m_staticText8;
		wxChoice* m_choice_keyboard;
		wxButton* m_button_help;
		wxButton* m_button_seldev;
		wxButton* m_button_save;
		wxStatusBar* m_statusBar1;

		// Virtual event handlers, override them in your derived class
		virtual void handleBtnSelectDevice( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("TaikoCatz I/O Dongle v4 Settings Tool"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,400 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

		~MainWindow();

};

///////////////////////////////////////////////////////////////////////////////
/// Class SelectDeviceWindow
///////////////////////////////////////////////////////////////////////////////
class SelectDeviceWindow : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText23;
		wxListBox* m_listBox_devices;
		wxButton* m_button_refresh;
		wxButton* m_button_choose;

	public:

		SelectDeviceWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select device"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 240,360 ), long style = wxCAPTION|wxCLOSE_BOX|wxSTAY_ON_TOP|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

		~SelectDeviceWindow();

};

