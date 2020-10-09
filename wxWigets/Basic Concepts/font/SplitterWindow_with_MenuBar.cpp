/*
    Split window into two
*/

#include <wx/wx.h>
#include <wx/utils.h>
#include <wx/log.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>
#include <wx/sizer.h>

#include <iostream>
using namespace std;

enum
{
    ID_Hello = 1,
    ID_Hello_w1 = 2
};

//-----------------------------My Window Start------------------------------//
class MyWindow : public wxWindow
{
public:
    MyWindow(wxSplitterWindow *parent, wxWindowID id);
};
MyWindow::MyWindow(wxSplitterWindow *parent, wxWindowID id) : wxWindow(parent, id)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello_w1, "&W1\tCtrl-w", "Help string shown in status bar for this menu item");
   
    wxMenuBar *menuBar1 = new wxMenuBar;
    menuBar1 ->Append(menuFile,"&Myfile");
    //SetMenuBar(menuBar1); --> not allowed  
}

//-----------------------------My Window End------------------------------//

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame
{
public:
    MyFrame();
    ~MyFrame();
    wxSplitterWindow *splitter;
    MyWindow *window11;
    MyWindow *window22;

private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello, MyFrame::OnHello)
        EVT_MENU(wxID_EXIT, MyFrame::OnExit)
            EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
                wxEND_EVENT_TABLE()
                    
MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Splitter Window", wxPoint(30, 30), wxSize(800, 600))
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D, "splitterWindow");
    splitter->SetSashGravity(0.5);
    splitter->SetMinimumPaneSize(20);

    /*wxWindow *window1 = new wxWindow(splitter,wxID_ANY,wxDefaultPosition,wxDefaultSize);
    wxWindow *window2 = new wxWindow(splitter,wxID_ANY,wxDefaultPosition,wxDefaultSize);
    wxSize windowSize = window1->GetSize();
    window1->SetBackgroundColour(*wxBLACK);
    window2->SetBackgroundColour(*wxBLUE);*/
    window11 = new MyWindow(splitter, wxID_ANY);
    window22 = new MyWindow(splitter, wxID_ANY);

    window11->SetBackgroundColour(*wxLIGHT_GREY);
    window22->SetBackgroundColour(*wxCYAN);

    splitter->SplitVertically(window11, window22);
}

MyFrame::~MyFrame()
{
}

void MyFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets' Hello world sample",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

//-----------------------------My Frame End-----------------------------//

class MyApp : public wxApp
{
public:
    MyApp();
    ~MyApp();
    virtual bool OnInit();

private:
    MyFrame *m_frame = NULL;
};

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

bool MyApp::OnInit()
{
    m_frame = new MyFrame();
    m_frame->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);