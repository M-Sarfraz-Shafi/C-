#include <wx/wx.h>
#include <wx/utils.h> 
#include <iostream>
using namespace std;

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame{
   public:
       MyFrame();
       ~MyFrame();
    private:
        wxButton *myButton;
        void OnButtonClick(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};
enum{
    ID_BUTTON = 1
};
wxBEGIN_EVENT_TABLE(MyFrame,wxFrame)
    EVT_BUTTON(ID_BUTTON, MyFrame::OnButtonClick)
wxEND_EVENT_TABLE()


MyFrame::MyFrame() : wxFrame(nullptr,wxID_ANY,"Simple Button",wxPoint(30,30),wxSize(800,600))
{
    myButton = new wxButton(this,ID_BUTTON,"My Button",wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,wxButtonNameStr );
}

MyFrame::~MyFrame()
{

}

        
void MyFrame::OnButtonClick(wxCommandEvent& event )
{
    cout<<"Hello World"<<endl;
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