/*
    Bitmap Button with function
    Drawing 
    2 separte panels    
*/
#include <wx/docview.h>
#include <wx/wx.h>
#include "myheader.h"
using namespace std;

enum
{
    ID_BUTTON = 1
};

class MyView : public wxView
{
    public:
    MyView();
};

MyView::MyView(): wxView()
{
    //wxButton * myButton;
    //myButton = new wxButton(this,ID_BUTTON,"My Button",wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,wxButtonNameStr );

}
//-----------------------------My Frame Start-----------------------------//


enum
{
    ID_BUTTON_2 = 1
};

void MyFrame::OnButtonClicked(wxCommandEvent& event)
{
    cout<<"Button clicked"<<endl;
}


MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Button with wxView", wxPoint(30, 30), wxSize(800, 600))
{
    wxButton *mybutton;
    mybutton = new wxButton(this,ID_BUTTON_2,"mybutton");
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MyFrame::OnButtonClicked,this,ID_BUTTON_2);
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