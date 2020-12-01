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
    wxImagePanel(wxFrame *parent, wxString file, wxBitmapType format);
    void OnPaint(wxPaintEvent &event);
    int getWidth();
    int getHight();
    void OnMouseClicked(wxMouseEvent &event);
    DECLARE_EVENT_TABLE()
private:
    int w, h, mouseX1, mouseY1;
    wxPoint pt;
};

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
EVT_PAINT(wxImagePanel::OnPaint)
EVT_LEFT_DOWN(wxImagePanel::OnMouseClicked)
END_EVENT_TABLE()

void wxImagePanel::OnMouseClicked(wxMouseEvent &event)
{
    wxClientDC dc(this);
    pt = event.GetLogicalPosition(dc);
    mouseX1 = pt.x;
    mouseY1 = pt.y;
    cout << "x: " << mouseX1 << "    y: " << mouseY1 << endl;
}

wxImagePanel::wxImagePanel(wxFrame *parent, wxString file, wxBitmapType format) : wxPanel(parent)
{
    image.LoadFile(file, format);
    w = image.GetWidth();
    h = image.GetHeight();
}

void wxImagePanel::OnPaint(wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    dc.DrawBitmap(image, 0, 0, false);
}

int wxImagePanel::getWidth()
{
    return w;
}

int wxImagePanel::getHight()
{
    return h;
}

//-----------------------------My Image Load End-----------------------------//

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame
{
public:
    MyFrame();
    ~MyFrame();
    void SetStatusBar(int width, int hight);
};

void MyFrame::SetStatusBar(int width, int hight)
{
    CreateStatusBar();

    SetStatusText("Welcome to wxWidgets");

}

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Load Image", wxPoint(30, 30), wxSize(800, 600))
{
    
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
    wxImagePanel *drawPane;
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
    wxString filename = wxFileSelector(_T("Select file"), _T(""), _T(""), _T(""), _T("All files (*.*)|*.*"));

    drawPane = new wxImagePanel(m_frame, filename, wxBITMAP_TYPE_ANY);
    int width = drawPane->getWidth();
    int hight = drawPane->getHight();
    m_frame->SetSize(width, hight);
  //  m_frame->SetStatusBar();
    m_frame->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);