/*
    Grid Sizer
*/
#include <wx/splitter.h>
#include <wx/wx.h>
#include <wx/utils.h>
#include <iostream>
using namespace std;

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame
{
public:
    MyFrame();
    ~MyFrame();
    wxButton *myButton, *myButton2, *myButton3, *myButton4;
};

enum
{
    ID_BUTTON = 1,
    ID_BUTTON2 = 2,
    ID_BUTTON3 = 3,
    ID_BUTTON4 = 4
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Box Sizer", wxPoint(30, 30), wxSize(800, 600))
{
    //myButton = new wxButton(this,wxID_ANY,"Button 1",wxDefaultPosition,wxSize(100,100));
    myButton = new wxButton(this, ID_BUTTON, "Button1", wxPoint(50, 50), wxSize(100, 100), 0, wxDefaultValidator, wxButtonNameStr);
    myButton2 = new wxButton(this,ID_BUTTON2,"Button 2",wxDefaultPosition,wxSize(100,100), 0, wxDefaultValidator, wxButtonNameStr);
    myButton3 = new wxButton(this,ID_BUTTON3,"Button 3",wxDefaultPosition,wxSize(100,100), 0, wxDefaultValidator, wxButtonNameStr);
    myButton4 = new wxButton(this,ID_BUTTON4,"Button 4",wxDefaultPosition,wxSize(100,100), 0, wxDefaultValidator, wxButtonNameStr);

    wxGridSizer * gs = new wxGridSizer(2,10,0);
    
   // gs->Add(myButton,0,wxEXPAND,0);
    //gs->Add(myButton,wxSizerFlags().Expand().Border(wxALL, 50));
    gs->Add(myButton,wxSizerFlags().FixedMinSize().Centre());
    
    gs->Add(myButton2,wxSizerFlags().FixedMinSize().Centre());
    gs->Add(myButton3,wxSizerFlags().FixedMinSize().Centre());
    gs->Add(myButton4,wxSizerFlags().FixedMinSize().Centre());

    SetSizer(gs);
}

MyFrame::~MyFrame()
{
    
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