#include "InstInput.h"


InstInput::InstInput(wxWindow* parent, const wxString& title)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(450, 300)) {

    wxPanel* panel = new wxPanel(this);

    
    instructions = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 20), wxSize(350, 200), wxTE_MULTILINE);

    wxStaticText* txt = new wxStaticText(panel,wxID_ANY,"Start at Address:",wxPoint(20,230));
    memAdd = new wxTextCtrl(panel, wxID_ANY, "0A", wxPoint(115, 230), wxSize(50, 20));

    
    wxButton* addCodeButton = new wxButton(panel, wxID_OK, "Add Instructions", wxPoint(300, 230));  
    Bind(wxEVT_CLOSE_WINDOW, [&](wxCloseEvent& evt) {
        EndModal(wxID_CANCEL);
    });
}


