<<<<<<< HEAD
#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "InstInput.h"
#include <string>
#include <cctype>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_TIMER(wxID_ANY, MainFrame::updatevalues)  // Bind the timer event
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title,wxDefaultPosition,wxDefaultSize,wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)),timer(this) {
	wxPanel* panel = new wxPanel(this);
	// Buttons
	wxButton* Run = new wxButton(panel, wxID_ANY, "Run", wxPoint(590, 505), wxSize(100, 35)); // Button config
	wxButton* ClearM = new wxButton(panel, wxID_ANY, "Clear Memory", wxPoint(490, 505), wxSize(100, 35));
	wxButton* ClearR = new wxButton(panel, wxID_ANY, "Clear Register", wxPoint(390, 505), wxSize(100, 35));
	wxButton* Import = new wxButton(panel, wxID_ANY, "Import", wxPoint(290, 505), wxSize(100, 35));
	wxButton* Step = new wxButton(panel, wxID_ANY, "Run one Step", wxPoint(190, 505), wxSize(100, 35));
	wxButton* Reset = new wxButton(panel, wxID_ANY, "Reset Counter", wxPoint(90, 505), wxSize(100, 35));
	// ===============================================================================
	// List Controls
	MemoryList = new wxListCtrl(panel, wxID_ANY, wxPoint(20,20), wxSize(200, 400), wxLC_REPORT | wxLC_SINGLE_SEL);
	RegisterList = new wxListCtrl(panel, wxID_ANY, wxPoint(450,20), wxSize(200, 340), wxLC_REPORT | wxLC_SINGLE_SEL);
	   // config
	RegisterList->AppendColumn("Register", wxLIST_FORMAT_LEFT, 100);
	for (int i = 0; i < 16; i++) {  // Address column
		wxString item = wxString(wxDecToHex(i));
		RegisterList->InsertItem(i, item);
	}
	RegisterList->AppendColumn("Value", wxLIST_FORMAT_LEFT, 100);
	

	MemoryList->AppendColumn("Address",wxLIST_FORMAT_LEFT,100);
	for (int i = 0;i < 256;i++) { // Address column
		wxString item = wxString(wxDecToHex(i));
		MemoryList->InsertItem(i, item);
	}
	MemoryList->AppendColumn("Value", wxLIST_FORMAT_LEFT, 100);
	// ========================================================================
	// Static Text
	Pc = new wxStaticText(panel,wxID_ANY,"Program Counter",wxPoint(292,-1),wxSize(100,15));
	wxStaticText* MainMemory = new wxStaticText(panel,wxID_ANY,"Main Memory",wxPoint(20,4),wxSize(100,15));
	iRtxt = new wxStaticText(panel,wxID_ANY,"Instruction Register",wxPoint(288,60));
	wxStaticText* Central_Processing = new wxStaticText(panel,wxID_ANY,"CPU",wxPoint(455,4),wxSize(50,15));
	outputScreen = new wxStaticText(panel,wxID_ANY,"",wxPoint(370,400),wxSize(250,90));
	wxStaticText* output = new wxStaticText(panel,wxID_ANY,"Console",wxPoint(370,380));
	// config
	Pc->SetBackgroundColour(*wxLIGHT_GREY);
	MainMemory->SetBackgroundColour(*wxLIGHT_GREY);
	Central_Processing->SetBackgroundColour(*wxLIGHT_GREY);
	outputScreen->SetBackgroundColour(*wxWHITE);
	outputScreen->SetFont(outputScreen->GetFont().Scale(1.1));
	output->SetFont(output->GetFont().Scale(1.2));

	// ========================================================================
	// Text Control
	PcCount = new wxTextCtrl(panel,wxID_ANY,"00", wxPoint(312, 20), wxSize(50, -1), wxTE_READONLY);
	iR = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(312,80),wxSize(50,-1), wxTE_READONLY);
	PcCount_Value = wxHexToDec(PcCount->GetValue());

	// =====================================================================
	// Gauge
	gauge = new wxGauge(panel, wxID_ANY, 100, wxPoint(20, 455),wxSize(100,-1));
	gauge->Show(false);
	
	timer.Start(100);
	Run->Bind(wxEVT_BUTTON, &MainFrame::RunButtonClicked, this);
	ClearM->Bind(wxEVT_BUTTON, &MainFrame::ClearMButtonClicked, this);
	ClearR->Bind(wxEVT_BUTTON, &MainFrame::ClearRButtonClicked, this);
	Import->Bind(wxEVT_BUTTON, &MainFrame::ImportButtonClicked, this);
	Step->Bind(wxEVT_BUTTON, &MainFrame::StepButtonClicked, this);
	Reset->Bind(wxEVT_BUTTON, &MainFrame::OnResetButtonCliked, this);
	
	CreateStatusBar();
	
}

void MainFrame::RunButtonClicked(wxCommandEvent& evt){
	gauge->Show(true); // Show the gauge
	gauge->SetValue(0);

	// loading by incrementing the gauge's value
	for (int i = 0; i <= 100; i++) {
		gauge->SetValue(i);
		wxYield(); 
		wxMilliSleep(20); 
	}
	wxLogStatus("Loading complete!");
	gauge->Show(false); // Hide the gauge after loading
	Program.getCpu().RunCode();
	PcCount->SetValue(wxDecToHex(Program.getCpu().getPc()));
}

void MainFrame::StepButtonClicked(wxCommandEvent& evt){
	Program.getCpu().Step();
	iR->SetValue(Program.getCpu().getIR2());
	//Program.getCpu().setPc(PcCount_Value);
	PcCount->SetValue(wxDecToHex(Program.getCpu().getPc()));


}

void MainFrame::ClearMButtonClicked(wxCommandEvent& evt){
	wxMessageDialog sure(this, "Are you sure you want to clear Memory?", "Clear Memory", wxYES_NO | wxICON_QUESTION);

	int response = sure.ShowModal();

	if (response == wxID_YES) {
		Program.getCpu().getMem().Reset();
		wxLogStatus("Memory Cleared!"); 
	}
	
	
}

void MainFrame::ClearRButtonClicked(wxCommandEvent& evt){
	wxMessageDialog sure(this, "Are you sure you want to clear Registers?", "Clear Memory", wxYES_NO | wxICON_QUESTION);

	int response = sure.ShowModal();

	if (response == wxID_YES) {
		Program.getCpu().getReg().Reset();
		
		wxLogStatus("Register Cleared!");
	}
	Program.getCpu().getO().clear();
}
void MainFrame::ImportButtonClicked(wxCommandEvent& evt){

	InstInput dialog(this, "Enter Instructions");
	
	wxString userInput;
	string start;
	if (dialog.ShowModal() == wxID_OK) { 
		userInput = dialog.GetInst();  // get the input from the dialog
		
		start = string(dialog.GetAdd()); // get the address to start at

		string textToSave = string(userInput.mb_str());

		
		ofstream file("Text.txt");
		if (file.is_open()) {
			file << textToSave;  
			file.close();
			wxLogStatus("Instructions saved");
			Program.getCpu().getPc() = Program.getCpu().getALU().HexToDec(string(dialog.GetAdd()));
		}
		else {
			wxLogStatus("Failed to open the file for writing.\nPlease try again");
		}
	}
	else return;
	Program.getCpu().Import("Text.txt",Program.getCpu().getALU().HexToDec(start));

}
void MainFrame::RegValues(){
	for (int i = 0; i < 16; i++) {
		wxString item = wxString(Program.getCpu().getReg().GetValues(i));
		RegisterList->SetItem(i, 1, item);
	}

}
void MainFrame::MemValues(){
	for (int i = 0; i < 256; i++) {
		wxString item = wxString(Program.getCpu().getMem().Get_Value(i));
		MemoryList->SetItem(i, 1, item);
	}
}

void MainFrame::updatevalues(wxTimerEvent& evt) {
	outputScreen->SetLabel(Program.getCpu().getO());
	PcCount->SetValue(wxDecToHex(Program.getCpu().getPc()));
	RegValues();
	MemValues();
}

void MainFrame::OnResetButtonCliked(wxCommandEvent& evt){
	Program.getCpu().getPc() = 0;
	PcCount->SetValue(wxDecToHex(Program.getCpu().getPc()));
}
=======
#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "InstInput.h"
#include <string>
#include <cctype>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_TIMER(wxID_ANY, MainFrame::updatevalues)  // Bind the timer event
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title,wxDefaultPosition,wxDefaultSize,wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)),timer(this) {
	wxPanel* panel = new wxPanel(this);
	// Buttons
	wxButton* Run = new wxButton(panel, wxID_ANY, "Run", wxPoint(590, 505), wxSize(100, 35)); // Button config
	wxButton* ClearM = new wxButton(panel, wxID_ANY, "Clear Memory", wxPoint(490, 505), wxSize(100, 35));
	wxButton* ClearR = new wxButton(panel, wxID_ANY, "Clear Register", wxPoint(390, 505), wxSize(100, 35));
	wxButton* Import = new wxButton(panel, wxID_ANY, "Import", wxPoint(290, 505), wxSize(100, 35));
	wxButton* Step = new wxButton(panel, wxID_ANY, "Run one Step", wxPoint(190, 505), wxSize(100, 35));
	wxButton* Reset = new wxButton(panel, wxID_ANY, "Reset Counter", wxPoint(90, 505), wxSize(100, 35));
	// ===============================================================================
	// List Controls
	MemoryList = new wxListCtrl(panel, wxID_ANY, wxPoint(20,20), wxSize(200, 400), wxLC_REPORT | wxLC_SINGLE_SEL);
	RegisterList = new wxListCtrl(panel, wxID_ANY, wxPoint(450,20), wxSize(200, 340), wxLC_REPORT | wxLC_SINGLE_SEL);
	   // config
	RegisterList->AppendColumn("Register", wxLIST_FORMAT_LEFT, 100);
	for (int i = 0; i < 16; i++) {  // Address column
		wxString item = wxString(wxDecToHex(i));
		RegisterList->InsertItem(i, item);
	}
	RegisterList->AppendColumn("Value", wxLIST_FORMAT_LEFT, 100);
	

	MemoryList->AppendColumn("Address",wxLIST_FORMAT_LEFT,100);
	for (int i = 0;i < 256;i++) { // Address column
		wxString item = wxString(wxDecToHex(i));
		MemoryList->InsertItem(i, item);
	}
	MemoryList->AppendColumn("Value", wxLIST_FORMAT_LEFT, 100);
	// ========================================================================
	// Static Text
	Pc = new wxStaticText(panel,wxID_ANY,"Program Counter",wxPoint(292,-1),wxSize(100,15));
	wxStaticText* MainMemory = new wxStaticText(panel,wxID_ANY,"Main Memory",wxPoint(20,4),wxSize(100,15));
	iRtxt = new wxStaticText(panel,wxID_ANY,"Instruction Register",wxPoint(288,60));
	wxStaticText* Central_Processing = new wxStaticText(panel,wxID_ANY,"CPU",wxPoint(455,4),wxSize(50,15));
	outputScreen = new wxStaticText(panel,wxID_ANY,"",wxPoint(370,400),wxSize(250,90));
	wxStaticText* output = new wxStaticText(panel,wxID_ANY,"Console",wxPoint(370,380));
	// config
	Pc->SetBackgroundColour(*wxLIGHT_GREY);
	MainMemory->SetBackgroundColour(*wxLIGHT_GREY);
	Central_Processing->SetBackgroundColour(*wxLIGHT_GREY);
	outputScreen->SetBackgroundColour(*wxWHITE);
	outputScreen->SetFont(outputScreen->GetFont().Scale(1.1));
	output->SetFont(output->GetFont().Scale(1.2));

	// ========================================================================
	// Text Control
	PcCount = new wxTextCtrl(panel,wxID_ANY,"00", wxPoint(312, 20), wxSize(50, -1), wxTE_READONLY);
	iR = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(312,80),wxSize(50,-1), wxTE_READONLY);
	PcCount_Value = wxHexToDec(PcCount->GetValue());

	// =====================================================================
	// Gauge
	gauge = new wxGauge(panel, wxID_ANY, 100, wxPoint(20, 455),wxSize(100,-1));
	gauge->Show(false);
	
	timer.Start(100);
	Run->Bind(wxEVT_BUTTON, &MainFrame::RunButtonClicked, this);
	ClearM->Bind(wxEVT_BUTTON, &MainFrame::ClearMButtonClicked, this);
	ClearR->Bind(wxEVT_BUTTON, &MainFrame::ClearRButtonClicked, this);
	Import->Bind(wxEVT_BUTTON, &MainFrame::ImportButtonClicked, this);
	Step->Bind(wxEVT_BUTTON, &MainFrame::StepButtonClicked, this);
	Reset->Bind(wxEVT_BUTTON, &MainFrame::OnResetButtonCliked, this);
	
	CreateStatusBar();
	
}

void MainFrame::RunButtonClicked(wxCommandEvent& evt){
	gauge->Show(true); // Show the gauge
	gauge->SetValue(0);

	// loading by incrementing the gauge's value
	for (int i = 0; i <= 100; i++) {
		gauge->SetValue(i);
		wxYield(); 
		wxMilliSleep(20); 
	}
	wxLogStatus("Loading complete!");
	gauge->Show(false); // Hide the gauge after loading
	Program.getCpu().RunCode();
	PcCount->SetValue(wxDecToHex(Program.getCpu().getPc()));
}

void MainFrame::StepButtonClicked(wxCommandEvent& evt){
	Program.getCpu().Step();
	iR->SetValue(Program.getCpu().getIR2());
	//Program.getCpu().setPc(PcCount_Value);
	PcCount->SetValue(wxDecToHex(Program.getCpu().getPc()));


}

void MainFrame::ClearMButtonClicked(wxCommandEvent& evt){
	wxMessageDialog sure(this, "Are you sure you want to clear Memory?", "Clear Memory", wxYES_NO | wxICON_QUESTION);

	int response = sure.ShowModal();

	if (response == wxID_YES) {
		Program.getCpu().getMem().Reset();
		wxLogStatus("Memory Cleared!"); 
	}
	
	
}

void MainFrame::ClearRButtonClicked(wxCommandEvent& evt){
	wxMessageDialog sure(this, "Are you sure you want to clear Registers?", "Clear Memory", wxYES_NO | wxICON_QUESTION);

	int response = sure.ShowModal();

	if (response == wxID_YES) {
		Program.getCpu().getReg().Reset();
		
		wxLogStatus("Register Cleared!");
	}
	Program.getCpu().getO().clear();
}
void MainFrame::ImportButtonClicked(wxCommandEvent& evt){

	InstInput dialog(this, "Enter Instructions");
	
	wxString userInput;
	string start;
	if (dialog.ShowModal() == wxID_OK) { 
		userInput = dialog.GetInst();  // get the input from the dialog
		
		start = string(dialog.GetAdd()); // get the address to start at

		string textToSave = string(userInput.mb_str());

		
		ofstream file("Text.txt");
		if (file.is_open()) {
			file << textToSave;  
			file.close();
			wxLogStatus("Instructions saved");
			Program.getCpu().getPc() = Program.getCpu().getALU().HexToDec(string(dialog.GetAdd()));
		}
		else {
			wxLogStatus("Failed to open the file for writing.\nPlease try again");
		}
	}
	else return;
	Program.getCpu().Import("Text.txt",Program.getCpu().getALU().HexToDec(start));

}
void MainFrame::RegValues(){
	for (int i = 0; i < 16; i++) {
		wxString item = wxString(Program.getCpu().getReg().GetValues(i));
		RegisterList->SetItem(i, 1, item);
	}

}
void MainFrame::MemValues(){
	for (int i = 0; i < 256; i++) {
		wxString item = wxString(Program.getCpu().getMem().Get_Value(i));
		MemoryList->SetItem(i, 1, item);
	}
}

void MainFrame::updatevalues(wxTimerEvent& evt) {
	outputScreen->SetLabel(Program.getCpu().getO());
	PcCount->SetValue(wxDecToHex(Program.getCpu().getPc()));
	RegValues();
	MemValues();
}

void MainFrame::OnResetButtonCliked(wxCommandEvent& evt){
	Program.getCpu().getPc() = 0;
	PcCount->SetValue(wxDecToHex(Program.getCpu().getPc()));
}
>>>>>>> ccb3b64d80a319ab1d95b8035a67d9771c43620a
