#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <string>
#include <cctype>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_TIMER(wxID_ANY, MainFrame::updatevalues)  // Bind the timer event
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title,wxDefaultPosition,wxDefaultSize,wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)),timer(this) {
	wxPanel* panel = new wxPanel(this);
	wxButton* Button = new wxButton(panel, wxID_ANY, "Run", wxPoint(590, 455), wxSize(100, 35)); // Button config
	wxButton* Button2 = new wxButton(panel, wxID_ANY, "Clear Memory", wxPoint(490, 455), wxSize(100, 35));
	wxButton* Button3 = new wxButton(panel, wxID_ANY, "Clear Register", wxPoint(390, 455), wxSize(100, 35));
	wxButton* Button4 = new wxButton(panel, wxID_ANY, "Import", wxPoint(290, 455), wxSize(100, 35));
	wxButton* Button5 = new wxButton(panel, wxID_ANY, "Run one Step", wxPoint(190, 455), wxSize(100, 35));
	MemoryList = new wxListCtrl(panel, wxID_ANY, wxPoint(20,20), wxSize(200, 400), wxLC_REPORT | wxLC_SINGLE_SEL);
	RegisterList = new wxListCtrl(panel, wxID_ANY, wxPoint(450,20), wxSize(200, 340), wxLC_REPORT | wxLC_SINGLE_SEL);
	Pc = new wxStaticText(panel,wxID_ANY,"Program Counter",wxPoint(292,-1),wxSize(100,15));
	PcCount = new wxTextCtrl(panel,wxID_ANY,"", wxPoint(312, 20), wxSize(50, -1));
	iRtxt = new wxStaticText(panel,wxID_ANY,"Instruction Register",wxPoint(288,60));
	iR = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(312,80),wxSize(50,-1));
	gauge = new wxGauge(panel, wxID_ANY, 100, wxPoint(20, 455),wxSize(100,-1));
	gauge->Show(false);
	Pc->SetBackgroundColour(*wxLIGHT_GREY);
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
	
	timer.Start(100);
	Button->Bind(wxEVT_BUTTON, &MainFrame::RunButtonClicked, this);
	Button2->Bind(wxEVT_BUTTON, &MainFrame::ClearMButtonClicked, this);
	Button3->Bind(wxEVT_BUTTON, &MainFrame::ClearRButtonClicked, this);
	Button4->Bind(wxEVT_BUTTON, &MainFrame::ImportButtonClicked, this);
	Button5->Bind(wxEVT_BUTTON, &MainFrame::StepButtonClicked, this);
	
	CreateStatusBar();
	
}

void MainFrame::RunButtonClicked(wxCommandEvent& evt){
	gauge->Show(true); // Show the gauge
	gauge->SetValue(0);
	Program.getCpu().Import("Text.txt");

	// loading by incrementing the gauge's value
	for (int i = 0; i <= 100; i++) {
		gauge->SetValue(i);
		wxYield(); 
		wxMilliSleep(20); 
	}
	wxLogStatus("Loading complete!");
	gauge->Show(false); // Hide the gauge after loading
	Program.getCpu().RunCode();
}

void MainFrame::StepButtonClicked(wxCommandEvent& evt){
	iR->SetValue(Program.getCpu().getIR());
	Program.getCpu().Step();
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
}
void MainFrame::ImportButtonClicked(wxCommandEvent& evt){
	Program.getCpu().Import("Text.txt");

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

	RegValues();
	MemValues();
}
