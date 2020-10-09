/*
    Split window into two using wxPanel
*/

#include <wx/wx.h>
#include <wx/utils.h> 
#include <wx/log.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
#include <iostream>
using namespace std;

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame{
   public:
       MyFrame();
       ~MyFrame();
       wxSplitterWindow *splitter;
       void OnSplitWindow(wxSplitterEvent& event);
};

MyFrame::MyFrame() : wxFrame(nullptr,wxID_ANY,"Splitter Window",wxPoint(30,30),wxSize(800,600))
{
    splitter = new wxSplitterWindow(this,wxID_ANY,wxDefaultPosition,wxDefaultSize, wxSP_3D,"splitterWindow");	
    splitter->SetSashGravity(0.5);
    splitter->SetMinimumPaneSize(20);
    
    wxPanel * panel1;
    wxPanel * panel2;

    panel1 = new wxPanel(splitter,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL,wxPanelNameStr );
    panel1->SetBackgroundColour(*wxBLACK);
    panel2 = new wxPanel(splitter,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTAB_TRAVERSAL,wxPanelNameStr );
    panel2->SetBackgroundColour(*wxBLUE);

    splitter->SplitVertically(panel1,panel2);
    

}

MyFrame::~MyFrame()
{

}

//-----------------------------My Frame End-----------------------------//

class MyApp:public wxApp
{
    public:
        MyApp();
        ~MyApp();
        virtual bool OnInit();
    private:
        MyFrame* m_frame = NULL;
        
};

MyApp::MyApp()
{
   
}

MyApp::~MyApp()
{

}

bool MyApp:: OnInit()
{
   m_frame = new MyFrame();
   m_frame->Show();
   return true;
}

wxIMPLEMENT_APP(MyApp);