/*
    Bitmap Button +
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
    private:
        wxImage image;
        wxBitmapButton *myButton_bm;
        int w,h;
    public:
        MyCanvas(wxFrame* parent, wxString file, wxBitmapType format);
        void OnPaint(wxPaintEvent & evt);
        void OnButtonClick(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};

enum{
    ID_BUTTON_BM = 1
};

BEGIN_EVENT_TABLE(MyCanvas, wxPanel)
    EVT_PAINT(MyCanvas::OnPaint)
    EVT_BUTTON(ID_BUTTON_BM, MyCanvas::OnButtonClick)
END_EVENT_TABLE()

MyCanvas::MyCanvas(wxFrame* parent, wxString file, wxBitmapType format) : wxPanel(parent)
{
    image.LoadFile(file, format,-1); 
    w = image.GetWidth();
    h = image.GetHeight();
    cout<<"w: "<<w<<endl<<"h: "<<h<<endl;
    wxBitmap button_image(image);
    myButton_bm = new wxBitmapButton(this,ID_BUTTON_BM,button_image,wxPoint (w/2,h+10),wxDefaultSize,0,wxDefaultValidator,wxButtonNameStr );
}

void MyCanvas::OnPaint(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    wxBitmap image_map(image);
    dc.DrawBitmap( image_map, 0, 0, false );
}

void MyCanvas::OnButtonClick(wxCommandEvent& event)
{
    cout<<"Button Clicked"<<endl;
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