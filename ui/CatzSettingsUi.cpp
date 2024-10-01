///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6a)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "CatzSettingsUi.h"

///////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Sensitivity") ), wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("<Katsu"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText1->Wrap( -1 );
	bSizer4->Add( m_staticText1, 1, wxALL, 5 );

	m_staticText11 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("<Don"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText11->Wrap( -1 );
	bSizer4->Add( m_staticText11, 1, wxALL, 5 );

	m_staticText12 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Don>"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText12->Wrap( -1 );
	bSizer4->Add( m_staticText12, 1, wxALL, 5 );

	m_staticText13 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Katsu>"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText13->Wrap( -1 );
	bSizer4->Add( m_staticText13, 1, wxALL, 5 );


	bSizer3->Add( bSizer4, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	m_slider_lk = new wxSlider( sbSizer4->GetStaticBox(), wxID_ANY, 16, 8, 16, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_VALUE_LABEL|wxSL_VERTICAL );
	bSizer2->Add( m_slider_lk, 1, wxALL|wxEXPAND, 5 );

	m_slider_ld = new wxSlider( sbSizer4->GetStaticBox(), wxID_ANY, 16, 8, 16, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_VALUE_LABEL|wxSL_VERTICAL );
	bSizer2->Add( m_slider_ld, 1, wxALL|wxEXPAND, 5 );

	m_slider_rd = new wxSlider( sbSizer4->GetStaticBox(), wxID_ANY, 16, 8, 16, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_VALUE_LABEL|wxSL_VERTICAL );
	bSizer2->Add( m_slider_rd, 1, wxALL|wxEXPAND, 5 );

	m_slider_rk = new wxSlider( sbSizer4->GetStaticBox(), wxID_ANY, 16, 8, 16, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_VALUE_LABEL|wxSL_VERTICAL );
	bSizer2->Add( m_slider_rk, 1, wxALL|wxEXPAND, 5 );


	bSizer3->Add( bSizer2, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText131 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Overall Sensitivity:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText131->Wrap( -1 );
	bSizer5->Add( m_staticText131, 0, wxALL, 5 );

	wxString m_choice_overall_sensiChoices[] = { _("Low (0.7x)"), _("Medium (1.0x)"), _("High (1.4x)"), _("Extreme (2.0x)") };
	int m_choice_overall_sensiNChoices = sizeof( m_choice_overall_sensiChoices ) / sizeof( wxString );
	m_choice_overall_sensi = new wxChoice( sbSizer4->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_overall_sensiNChoices, m_choice_overall_sensiChoices, 0 );
	m_choice_overall_sensi->SetSelection( 1 );
	bSizer5->Add( m_choice_overall_sensi, 1, wxALL, 5 );


	bSizer3->Add( bSizer5, 0, wxEXPAND, 5 );


	sbSizer4->Add( bSizer3, 1, wxEXPAND, 5 );


	bSizer1->Add( sbSizer4, 0, wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Performance") ), wxVERTICAL );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( sbSizer5->GetStaticBox(), wxID_ANY, _("Drum-roll level") ), wxVERTICAL );

	wxString m_choice_drumrollChoices[] = { _("Fallback (Reliability++, Roll--, press 16ms)"), _("Level 1 (Reliability+, Roll-, press 16ms)"), _("Level 2 (Balanced, press 10ms)"), _("Level 3 (Reliability-, Roll+, press 8ms)"), _("Level 4 (Reliability--, Roll++, press 6ms)") };
	int m_choice_drumrollNChoices = sizeof( m_choice_drumrollChoices ) / sizeof( wxString );
	m_choice_drumroll = new wxChoice( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_drumrollNChoices, m_choice_drumrollChoices, 0 );
	m_choice_drumroll->SetSelection( 2 );
	sbSizer3->Add( m_choice_drumroll, 0, wxALL|wxEXPAND, 5 );


	sbSizer5->Add( sbSizer3, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer41;
	sbSizer41 = new wxStaticBoxSizer( new wxStaticBox( sbSizer5->GetStaticBox(), wxID_ANY, _("Key press duration (ms)") ), wxVERTICAL );

	m_keypress_dur_override = new wxCheckBox( sbSizer41->GetStaticBox(), wxID_ANY, _("Use default duration by drum-roll level"), wxDefaultPosition, wxDefaultSize, 0 );
	m_keypress_dur_override->SetValue(true);
	sbSizer41->Add( m_keypress_dur_override, 0, wxALL, 5 );

	m_slider_keypress = new wxSlider( sbSizer41->GetStaticBox(), wxID_ANY, 10, 2, 30, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_HORIZONTAL );
	sbSizer41->Add( m_slider_keypress, 0, wxALL|wxEXPAND, 5 );

	m_text_keypress_ms = new wxStaticText( sbSizer41->GetStaticBox(), wxID_ANY, _("10ms"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_text_keypress_ms->Wrap( -1 );
	sbSizer41->Add( m_text_keypress_ms, 0, wxALL|wxEXPAND, 5 );


	sbSizer5->Add( sbSizer41, 0, wxEXPAND, 5 );


	bSizer8->Add( sbSizer5, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer51;
	sbSizer51 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Others") ), wxVERTICAL );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText8 = new wxStaticText( sbSizer51->GetStaticBox(), wxID_ANY, _("Keyboard keys:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer9->Add( m_staticText8, 0, wxALL, 5 );

	wxString m_choice_keyboardChoices[] = { _("DF - JK"), _("ZX - CV") };
	int m_choice_keyboardNChoices = sizeof( m_choice_keyboardChoices ) / sizeof( wxString );
	m_choice_keyboard = new wxChoice( sbSizer51->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_keyboardNChoices, m_choice_keyboardChoices, 0 );
	m_choice_keyboard->SetSelection( 0 );
	bSizer9->Add( m_choice_keyboard, 1, wxALL, 5 );


	sbSizer51->Add( bSizer9, 0, wxEXPAND, 5 );


	bSizer8->Add( sbSizer51, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Actions") ), wxHORIZONTAL );

	m_button_help = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, _("Help..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer6->Add( m_button_help, 1, wxALL|wxEXPAND, 5 );

	m_button_seldev = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, _("Select device..."), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer6->Add( m_button_seldev, 1, wxALL|wxEXPAND, 5 );

	m_button_save = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, _("<b>Save!</b>"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button_save->SetLabelMarkup( _("<b>Save!</b>") );
	m_button_save->Enable( false );

	sbSizer6->Add( m_button_save, 1, wxALL|wxEXPAND, 5 );


	bSizer8->Add( sbSizer6, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer8, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	m_button_help->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::handleBtnHelp ), NULL, this );
	m_button_seldev->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::handleBtnSelectDevice ), NULL, this );
}

MainWindow::~MainWindow()
{
}

SelectDeviceDialog::SelectDeviceDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );

	m_staticText23 = new wxStaticText( this, wxID_ANY, _("Devices connected:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	bSizer26->Add( m_staticText23, 0, wxALL, 5 );

	m_listBox_devices = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer26->Add( m_listBox_devices, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );

	m_button_refresh = new wxButton( this, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer27->Add( m_button_refresh, 1, wxALL, 5 );

	m_button_choose = new wxButton( this, wxID_ANY, _("<b>Choose</b>"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button_choose->SetLabelMarkup( _("<b>Choose</b>") );
	m_button_choose->Enable( false );

	bSizer27->Add( m_button_choose, 1, wxALL, 5 );


	bSizer26->Add( bSizer27, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer26 );
	this->Layout();

	this->Centre( wxBOTH );
}

SelectDeviceDialog::~SelectDeviceDialog()
{
}

HelpDialog::HelpDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );


	bSizer11->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText9 = new wxStaticText( this, wxID_ANY, _("TaikoCatz I/O Dongle v4 Settings Tool"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText9->Wrap( -1 );
	m_staticText9->SetFont( wxFont( 18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Helvetica") ) );

	bSizer11->Add( m_staticText9, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );


	bSizer26->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText27 = new wxStaticText( this, wxID_ANY, _("Help and more info:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	bSizer26->Add( m_staticText27, 0, wxALL, 5 );

	m_hyperlink1 = new wxHyperlinkCtrl( this, wxID_ANY, _("taikocatz.com"), wxT("https://taikocatz.com"), wxDefaultPosition, wxDefaultSize, wxHL_ALIGN_CENTRE|wxHL_DEFAULT_STYLE );
	bSizer26->Add( m_hyperlink1, 0, wxALL, 5 );


	bSizer26->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer11->Add( bSizer26, 0, wxEXPAND, 5 );


	bSizer11->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText91 = new wxStaticText( this, wxID_ANY, _("Copyright (c) 2024 Zheng Lyu"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText91->Wrap( -1 );
	bSizer11->Add( m_staticText91, 0, wxALL|wxEXPAND, 5 );

	m_staticText911 = new wxStaticText( this, wxID_ANY, _("The TaikoCatz logo is a registered trademark in China,"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText911->Wrap( -1 );
	bSizer11->Add( m_staticText911, 0, wxALL|wxEXPAND, 5 );

	m_staticText9111 = new wxStaticText( this, wxID_ANY, _("owned by TaikoCatz team."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText9111->Wrap( -1 );
	bSizer11->Add( m_staticText9111, 0, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer11 );
	this->Layout();

	this->Centre( wxBOTH );
}

HelpDialog::~HelpDialog()
{
}
