/*
    Bitmap Button only with function
    No image load
*/

#include <wx/wx.h>
#include <wx/utils.h> 
#include <iostream>
using namespace std;

//-----------------------------My Image Load Start-----------------------------//
class MyCanvas : public wxPanel
{
    private:
        wxImage image;
        wxBitmapButton *myButton_bm;
        int w,h;
    public:
        MyCanvas(wxFrame* parent, wxString file, wxBitmapType format);
        void OnButtonClick(wxCommandEvent& event);
        void CreateButton();
        DECLARE_EVENT_TABLE()
};

enum{
    ID_BUTTON_BM = 1
};

BEGIN_EVENT_TABLE(MyCanvas, wxPanel)
    EVT_BUTTON(ID_BUTTON_BM, MyCanvas::OnButtonClick)
END_EVENT_TABLE()

MyCanvas::MyCanvas(wxFrame* parent, wxString file, wxBitmapType format) : wxPanel(parent)
{
    image.LoadFile(file, format,-1); 
}


void MyCanvas::OnButtonClick(wxCommandEvent& event)
{
    cout<<"Button Clicked"<<endl;
}

void MyCanvas::CreateButton()
{
    w = image.GetWidth();
    h = image.GetHeight();
    wxBitmap button_image(image);
    myButton_bm = new wxBitmapButton(this,ID_BUTTON_BM,button_image,wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,wxButtonNameStr );

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
   wxString filename = wxFileSelector(_T("Select file"),_T(""),_T(""),_T(""), _T("All files (*.*)|*.*") );

   drawPane = new MyCanvas( m_frame, filename, wxBITMAP_TYPE_ANY);
   drawPane->CreateButton();
   m_frame->Show();
   return true;
}

wxIMPLEMENT_APP(MyApp);