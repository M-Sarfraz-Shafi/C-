/*
    Splitter Window +
    Bitmap Button 4 -> arrows+
    Image load 
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
    wxButton *myButton, *myButton2;
};

enum
{
    ID_BUTTON = 1,
    ID_BUTTON2 = 2
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Box Sizer", wxPoint(30, 30), wxSize(800, 600))
{
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    myButton = new wxButton(this, ID_BUTTON, "Button1", wxPoint(50, 50), wxSize(100, 100), 0, wxDefaultValidator, wxButtonNameStr);
    myButton2 = new wxButton(this, ID_BUTTON2, "Button2", wxPoint(100, 200), wxSize(100, 100), 0, wxDefaultValidator, wxButtonNameStr);
    sizer->Add(myButton, wxSizerFlags().Center());

    //sizer->Add(myButton2, wxSizerFlags().Centre());
    SetSizerAndFit(sizer);
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
    wxInitAllImageHandlers();
    m_frame = new MyFrame();

    m_frame->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);