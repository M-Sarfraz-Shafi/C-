/*
    Load image using 
    wxImage
    wxBitmap
    wxDrawBitmap
*/

#include <wx/wx.h>
#include <wx/utils.h> 
#include <iostream>
using namespace std;

//-----------------------------My Image Load Start-----------------------------//
class MyCanvas : public wxPanel
{
    wxImage image;
    public:
        MyCanvas(wxFrame* parent, wxString file, wxBitmapType format);
        void OnPaint(wxPaintEvent & evt);
        DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyCanvas, wxPanel)
    //EVT_PAINT(MyCanvas::OnPaint)
END_EVENT_TABLE()

MyCanvas::MyCanvas(wxFrame* parent, wxString file, wxBitmapType format) : wxPanel(parent)
{
     
    wxClientDC dc(this);
    wxBitmap image_map(image);
    dc.DrawBitmap( image_map, 0, 0, false );
}

void MyCanvas::OnPaint(wxPaintEvent & evt)
{
    image.LoadFile(file, format,-1);0
    wxPaintDC dc(this);
    wxBitmap image_map(image);
    dc.DrawBitmap( image_map, 0, 0, false );
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
   m_frame->Show();
   return true;
}

wxIMPLEMENT_APP(MyApp);