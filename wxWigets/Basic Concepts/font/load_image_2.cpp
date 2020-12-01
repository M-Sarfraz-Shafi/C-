/*
    Load image Only using
    wxBitmap
    wxDrawBitmap
*/

#include <wx/wx.h>
#include <wx/utils.h> 
#include <iostream>
using namespace std;

//-----------------------------My Image Load Start-----------------------------//
class wxImagePanel : public wxPanel
{
    wxBitmap image;
    public:
        wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format);
        void OnPaint(wxPaintEvent & evt);
        void paintNow();
        void render(wxDC& dc);
        
        DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
    EVT_PAINT(wxImagePanel::OnPaint)
END_EVENT_TABLE()

wxImagePanel::wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format) :
wxPanel(parent)
{
    image.LoadFile(file, format);
}

void wxImagePanel::OnPaint(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    dc.DrawBitmap( image, 0, 0, false );
}


void wxImagePanel::render(wxDC&  dc)
{
    dc.DrawBitmap( image, 0, 0, false );
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
        wxImagePanel * drawPane;
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

   drawPane = new wxImagePanel( m_frame, filename, wxBITMAP_TYPE_JPEG);
   m_frame->Show();
   return true;
}

wxIMPLEMENT_APP(MyApp);