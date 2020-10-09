/*
    Splitter Window +
    Bitmap Button 4 -> arrows+
    Image load 
*/
#include <wx/splitter.h>
#include <wx/wx.h>
#include <wx/utils.h>
#include <iostream>
using namespace std;

//-----------------------------My Image Load Start-----------------------------//
class MyCanvas : public wxPanel
{
public:
    MyCanvas(wxSplitterWindow *splitter);
    void OnPaint(wxPaintEvent &evt);
    DECLARE_EVENT_TABLE()
private:
    wxImage image;
    wxBitmapButton *MyRegion_bm;
};

BEGIN_EVENT_TABLE(MyCanvas, wxPanel)
EVT_PAINT(MyCanvas::OnPaint)
END_EVENT_TABLE()

MyCanvas::MyCanvas(wxSplitterWindow *splitter) : wxPanel(splitter)
{
    SetBackgroundColour(*wxBLACK);
    wxString filename = wxFileSelector(_T("Select file"),_T(""),_T(""),_T(""), _T("All files (*.*)|*.*") );
    image.LoadFile(filename, wxBITMAP_TYPE_ANY,-1);
}

void MyCanvas::OnPaint(wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    wxBitmap image_map(image);
    dc.DrawBitmap(image_map, 0, 0, false);
}
//-----------------------------My Image Load End-----------------------------//

//-----------------------------My Bitmap Button Start-----------------------------//

class MyRegion : public wxPanel
{
public:
    MyRegion(wxSplitterWindow *splitter);
    void CreateButton();
    void OnButtonClick(wxCommandEvent& event);
private:
    wxImage image_right,image_left,image_up,image_down;
    wxBitmapButton *button_right, *button_left, *button_up, *button_down;

};

enum{
    ID_BTN_RIGHT = 1,
    ID_BTN_LEFT = 2,
    ID_BTN_UP = 3,
    ID_BTN_DOWN = 4
};



MyRegion::MyRegion(wxSplitterWindow *splitter) : wxPanel(splitter)
{
    SetBackgroundColour(*wxBLUE);
    image_right.LoadFile("/home/msarfrazshafi/Desktop/arrow_right.jpg", wxBITMAP_TYPE_ANY,-1); 
    image_left.LoadFile("/home/msarfrazshafi/Desktop/arrow_left.jpg", wxBITMAP_TYPE_ANY,-1); 
    image_up.LoadFile("/home/msarfrazshafi/Desktop/up_arrow.jpeg", wxBITMAP_TYPE_ANY,-1); 
    image_down.LoadFile("/home/msarfrazshafi/Desktop/down_arrow.png", wxBITMAP_TYPE_ANY,-1); 
    CreateButton();
}

void MyRegion::CreateButton()
{
    wxBitmap btn_right(image_right.Rescale(100, 100)), btn_left(image_left.Rescale(100, 100)), btn_up(image_up.Rescale(100, 100)), btn_down(image_down.Rescale(100, 100));

    button_left = new wxBitmapButton(this,ID_BTN_LEFT,btn_left,wxPoint (100,200),wxSize(100,100),0,wxDefaultValidator,wxButtonNameStr );
    button_right = new wxBitmapButton(this,ID_BTN_RIGHT,btn_right,wxPoint (300,200),wxSize(100,100),0,wxDefaultValidator,wxButtonNameStr );

    button_up = new wxBitmapButton(this,ID_BTN_UP,btn_up,wxPoint (200,100),wxSize(100,100),0,wxDefaultValidator,wxButtonNameStr );
    button_down = new wxBitmapButton(this,ID_BTN_DOWN,btn_down,wxPoint (200,300),wxSize(100,100),0,wxDefaultValidator,wxButtonNameStr );

}

void MyRegion::OnButtonClick(wxCommandEvent& event)
{
    cout<<"Hello World"<<endl;
}
//-----------------------------My Bitmap Button End-----------------------------//

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame
{
public:
    MyFrame();
    ~MyFrame();

private:
    MyCanvas *drawPane;
    MyRegion *drawButton;
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Load Image", wxPoint(30, 30), wxSize(800, 600))
{
    wxSplitterWindow *splitter;
    splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D, "splitterWindow");
    splitter->SetSashGravity(0.5);
    //splitter->SetMinimumPaneSize(30);

    wxPanel *panel1;
    drawPane = new MyCanvas(splitter);
    drawButton = new MyRegion(splitter);

    splitter->SplitVertically( drawButton,drawPane);
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
    return true;
}

wxIMPLEMENT_APP(MyApp);