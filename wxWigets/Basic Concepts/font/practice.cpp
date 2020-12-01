/*
    Bitmap Button with function
    Drawing 
    2 separte panels    
*/

#include <wx/wx.h>

//-----------------------------My Frame Start-----------------------------//

class MyFrame : public wxFrame
{
public:
    MyFrame();
    ~MyFrame();
    wxImage image;
    virtual void OnDraw(wxDC &dc);
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Button with wxView", wxPoint(30, 30), wxSize(800, 600))
{
    wxString filename = wxFileSelector(_T("Select file"), _T(""), _T(""), _T(""), _T("All files (*.*)|*.*"));
    bool isLoaded = image.LoadFile(filename, wxBITMAP_TYPE_ANY, -1);
}

void MyFrame::OnDraw(wxDC &dc)
{
    wxBitmap image_map(image);
    dc.DrawBitmap(image_map, 0, 0, false);
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
    //m_frame->OnDraw(dc);
    return true;
}

wxIMPLEMENT_APP(MyApp);