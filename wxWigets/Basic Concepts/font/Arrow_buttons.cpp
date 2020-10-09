/*
    Arrow buttons
*/

#include <wx/wx.h>
#include <wx/utils.h> 
#include <iostream>
using namespace std;

//-----------------------------My Image Load Start-----------------------------//
class MyCanvas : public wxPanel
{
    private:
        wxImage image_right,image_left,image_up,image_down;
        wxBitmapButton *button_right, *button_left, *button_up, *button_down;
        int w,h;
    public:
        MyCanvas(wxFrame* parent, wxBitmapType format);
        void OnButtonClick(wxCommandEvent& event);
        void CreateButton();
        DECLARE_EVENT_TABLE()
};

enum{
    ID_BTN_RIGHT = 1,
    ID_BTN_LEFT = 2,
    ID_BTN_UP = 3,
    ID_BTN_DOWN = 4
};

BEGIN_EVENT_TABLE(MyCanvas, wxPanel)
    EVT_BUTTON(ID_BTN_RIGHT, MyCanvas::OnButtonClick)
    EVT_BUTTON(ID_BTN_LEFT, MyCanvas::OnButtonClick)
    EVT_BUTTON(ID_BTN_UP, MyCanvas::OnButtonClick)
    EVT_BUTTON(ID_BTN_DOWN, MyCanvas::OnButtonClick)

END_EVENT_TABLE()

MyCanvas::MyCanvas(wxFrame* parent, wxBitmapType format) : wxPanel(parent)
{
    image_right.LoadFile("/home/msarfrazshafi/Desktop/arrow_right.jpg", format,-1); 
    image_left.LoadFile("/home/msarfrazshafi/Desktop/arrow_left.jpg", format,-1); 
    image_up.LoadFile("/home/msarfrazshafi/Desktop/up_arrow.jpeg", format,-1); 
    image_down.LoadFile("/home/msarfrazshafi/Desktop/down_arrow.png", format,-1); 
}


void MyCanvas::OnButtonClick(wxCommandEvent& event)
{
    cout<<"Button Clicked"<<endl;
}

void MyCanvas::CreateButton()
{
    wxBitmap btn_right(image_right.Rescale(100, 100)), btn_left(image_left.Rescale(100, 100)), btn_up(image_up.Rescale(100, 100)), btn_down(image_down.Rescale(100, 100));

    button_left = new wxBitmapButton(this,ID_BTN_LEFT,btn_left,wxPoint (100,200),wxSize(100,100),0,wxDefaultValidator,wxButtonNameStr );
    button_right = new wxBitmapButton(this,ID_BTN_RIGHT,btn_right,wxPoint (300,200),wxSize(100,100),0,wxDefaultValidator,wxButtonNameStr );

    button_up = new wxBitmapButton(this,ID_BTN_UP,btn_up,wxPoint (200,100),wxSize(100,100),0,wxDefaultValidator,wxButtonNameStr );
    button_down = new wxBitmapButton(this,ID_BTN_DOWN,btn_down,wxPoint (200,300),wxSize(100,100),0,wxDefaultValidator,wxButtonNameStr );
}

//-----------------------------My Image Load End-----------------------------//

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame{
   public:
       MyFrame();
       ~MyFrame();
};

MyFrame::MyFrame() : wxFrame(nullptr,wxID_ANY,"Load Image",wxPoint(30,30),wxSize(800,600))
{
   
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
        MyCanvas * drawPane;
};

MyApp::MyApp()
{
   
}

MyApp::~MyApp()
{

}

bool MyApp:: OnInit()
{
   wxInitAllImageHandlers();
   m_frame = new MyFrame();
   //wxString filename = wxFileSelector(_T("Select file"),_T(""),_T(""),_T(""), _T("All files (*.*)|*.*") );

   drawPane = new MyCanvas( m_frame, wxBITMAP_TYPE_ANY);
   drawPane->CreateButton();
   m_frame->Show();
   return true;
}

wxIMPLEMENT_APP(MyApp);