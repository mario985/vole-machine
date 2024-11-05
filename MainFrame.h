<<<<<<< HEAD
#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/timer.h>
#include <string>
#include "Machine.h"

class MainFrame : public wxFrame{
private:
	wxListCtrl* MemoryList;
	wxListCtrl* RegisterList;
	wxStaticText* Pc;
	wxTextCtrl* PcCount;
	wxStaticText* iRtxt;
	wxTextCtrl* iR;
	wxGauge* gauge;
	Machine Program;
	wxStaticText* outputScreen;

	int PcCount_Value;

	wxTimer timer;
	wxDECLARE_EVENT_TABLE();

	void RunButtonClicked(wxCommandEvent& evt);
	void StepButtonClicked(wxCommandEvent& evt);
	void ClearMButtonClicked(wxCommandEvent& evt);
	void ClearRButtonClicked(wxCommandEvent& evt);
	void ImportButtonClicked(wxCommandEvent& evt);
	void RegValues();
	void MemValues();
	void updatevalues(wxTimerEvent& evt);
	void OnResetButtonCliked(wxCommandEvent& evt);
public:
	MainFrame(const wxString& title);
    
};

=======
#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/timer.h>
#include <string>
#include "Machine.h"

class MainFrame : public wxFrame{
private:
	wxListCtrl* MemoryList;
	wxListCtrl* RegisterList;
	wxStaticText* Pc;
	wxTextCtrl* PcCount;
	wxStaticText* iRtxt;
	wxTextCtrl* iR;
	wxGauge* gauge;
	Machine Program;
	wxStaticText* outputScreen;

	int PcCount_Value;

	wxTimer timer;
	wxDECLARE_EVENT_TABLE();

	void RunButtonClicked(wxCommandEvent& evt);
	void StepButtonClicked(wxCommandEvent& evt);
	void ClearMButtonClicked(wxCommandEvent& evt);
	void ClearRButtonClicked(wxCommandEvent& evt);
	void ImportButtonClicked(wxCommandEvent& evt);
	void RegValues();
	void MemValues();
	void updatevalues(wxTimerEvent& evt);
	void OnResetButtonCliked(wxCommandEvent& evt);
public:
	MainFrame(const wxString& title);
    
};

>>>>>>> ccb3b64d80a319ab1d95b8035a67d9771c43620a
