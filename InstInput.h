
#ifndef INSTINPUT_H
#define INSTINPUT_H

#include <wx/wx.h>
#include <string>

class InstInput : public wxDialog{
	wxTextCtrl* instructions;
	wxTextCtrl* memAdd;

public:
	InstInput(wxWindow* parent,const wxString& title);
	wxString GetInst() {
		return instructions->GetValue();
	}
	wxString GetAdd() {
		return memAdd->GetValue();
	}

};
#endif // !INSTINPUT_H
#ifndef INSTINPUT_H
#define INSTINPUT_H

#include <wx/wx.h>
#include <string>

class InstInput : public wxDialog{
	wxTextCtrl* instructions;
	wxTextCtrl* memAdd;

public:
	InstInput(wxWindow* parent,const wxString& title);
	wxString GetInst() {
		return instructions->GetValue();
	}
	wxString GetAdd() {
		return memAdd->GetValue();
	}

};
#endif // !INSTINPUT_H
