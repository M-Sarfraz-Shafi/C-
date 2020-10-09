/*
    Load Image using Menu bar 
    need to change frame once to display image
*/                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
#include <wx/wx.h>
#include <wx/utils.h> 

#include <iostream>
using namespace std;

//-----------------------------Load Image Panel Start-----------------------------//
class wxImagePanel : public wxPanel
{
    wxBitmap image;
    public:
        wxImagePanel(wxFrame* parent,wxString file, wxBitmapType format);
        void OnPaint(wxPaintEvent & evt);
        DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
    EVT_PAINT(wxImagePanel::OnPaint)
END_EVENT_TABLE()

wxImagePanel::wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format) : wxPanel(parent)
{
    image.LoadFile(file,format);
}

void wxImagePanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    dc.DrawBitmap(image,0,0,false);
}

//-----------------------------Load Image Panel End-----------------------------//

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame{
   public:
       MyFrame();
       ~MyFrame();
    private:
       void OnOpenImage(wxCommandEvent& event);
       wxImagePanel* image_panel;
       DECLARE_EVENT_TABLE()
};

enum{
    ID_LOAD_IMAGE = 1
};

BEGIN_EVENT_TABLE(MyFrame,wxFrame)
    EVT_MENU(ID_LOAD_IMAGE,  MyFrame::OnOpenImage)
END_EVENT_TABLE()

MyFrame::MyFrame() : wxFrame(nullptr,wxID_ANY,"Load Image 3",wxPoint(30,30),wxSize(800,600))
{
   wxMenu * file_menu= new wxMenu();
   file_menu ->Append(ID_LOAD_IMAGE, "&Select Image\tCtrl+o");

   wxMenuBar * menuBar = new wxMenuBar();
   menuBar->Append(file_menu,"&File");
   SetMenuBar(menuBar);
}

MyFrame::~MyFrame()
{

}

void MyFrame::OnOpenImage(wxCommandEvent& event)
{
    cout<<"Inside open imae function"<<endl;
    wxString filename = wxFileSelector(_T("Please select a Image"),_T(""),_T(""),_T(""),_T("All files (*.*)|*.*"));
    image_panel = new wxImagePanel(this,filename,wxBITMAP_TYPE_ANY);
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
        //wxImagePanel* image_panel;
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
   //wxString filename = wxFileSelector(_T("Please select a Image"),_T(""),_T(""),_T(""),_T("All files (*.*)|*.*"));
   //image_panel = new wxImagePanel(m_frame,filename,wxBITMAP_TYPE_ANY);
   m_frame->Show();
   return true;
}

wxIMPLEMENT_APP(MyApp);