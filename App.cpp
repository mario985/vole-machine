<<<<<<< HEAD
#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);
bool App::OnInit() {

	MainFrame* mainFrame = new MainFrame("Machintosh");
	mainFrame->SetClientSize(700, 550);
	mainFrame->Center();
	mainFrame->Show();
	return true;
=======
#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);
bool App::OnInit() {

	MainFrame* mainFrame = new MainFrame("Machintosh");
	mainFrame->SetClientSize(700, 550);
	mainFrame->Center();
	mainFrame->Show();
	return true;
>>>>>>> ccb3b64d80a319ab1d95b8035a67d9771c43620a
}