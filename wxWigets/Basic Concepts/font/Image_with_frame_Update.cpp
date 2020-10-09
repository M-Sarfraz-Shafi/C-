/*
    Bitmap Button with function
    Drawing 
    2 separte panels    
*/

#include <wx/wx.h>
#include <wx/utils.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

enum
{
    ID_BUTTON_BM = 1
};
//-----------------------------My Image Load Start-----------------------------//
class MyCanvas : public wxScrolledWindow
{
private:
    wxImage image;
    wxBitmapButton *myButton_bm;
    int w, h;
    int mouseX1, mouseY1, mouseX2, mouseY2;
    bool axis1, axis2;
    wxPoint pt;
    wxPoint pt2;

public:
    MyCanvas(wxFrame *parent, wxString file, wxBitmapType format);
    void OnButtonClick(wxCommandEvent &event);
    void CreateButton();
    void Draw_Rectangular();
    void Draw_Image();
    void OnDraw(wxDC &dc);
    void OnPaint(wxPaintEvent &evt);
    void OnLeftClick(wxMouseEvent &event);
    void OnDragging(wxMouseEvent &event);
    void OnMotion(wxMouseEvent &event);
    void OnSetSize();
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
EVT_LEFT_DOWN(MyCanvas::OnLeftClick)
EVT_MOTION(MyCanvas::OnDragging)
EVT_BUTTON(ID_BUTTON_BM, MyCanvas::OnButtonClick)
END_EVENT_TABLE()

MyCanvas::MyCanvas(wxFrame *parent, wxString file, wxBitmapType format) : wxScrolledWindow(parent)
{
    this->SetBackgroundColour(wxColor(*wxRED)); //(255,11,11)
    image.LoadFile(file, format, -1);
    w = image.GetWidth();
    h = image.GetHeight();
    
    //GetParent()->SetClientSize();
    // this->SetSize(startX, startY, w, h);
    axis1 = false;
    axis2 = false;
}

void MyCanvas::OnSetSize()
{
    cout<<"OnSetSize function"<<endl;
    wxSize size = GetParent()->GetSize();
    image.Rescale(size.x, size.y);
    //GetParent()->SetClientSize(size.x,size.y);
}

void MyCanvas::OnLeftClick(wxMouseEvent &event)
{
    if (event.LeftIsDown())
    {
        // wxPaintDC dc(this);
        wxClientDC dc(this);
        //DoPrepareDC(dc);

        pt = event.GetLogicalPosition(dc);
        mouseX1 = pt.x;
        mouseY1 = pt.y;
        axis1 = true;
        wxWindow::Refresh();
    }
    else
    {
        axis1 = false;
    }
    
}

void MyCanvas::OnDragging(wxMouseEvent &event)
{
    wxPoint pt2;
    if (event.Dragging())
    {
        if (axis1 == true)
        {
            // wxPaintDC dc(this);
            wxClientDC dc(this);
            //DoPrepareDC(dc);
            pt2 = event.GetLogicalPosition(dc);
            mouseX2 = pt2.x;
            mouseY2 = pt2.y;
            cout << "x2: " << mouseX2 << endl;
            cout << "y2: " << mouseY2 << endl;
            axis2 = true;
            wxWindow::Refresh();
        }
        else
        {
            cout << "Please click Left mouse first" << endl;
        }
    }
    else
    {
        axis1 = false;
        axis2 = false;
    }
    
}

void MyCanvas::Draw_Rectangular()
{
    wxPaintDC dc(this);
    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    if (axis1 == true & axis2 == true)
    {
        wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
        cout << "Inside paint function" << endl;
        dc.DrawRectangle(mouseX1, mouseY1, w, h);
    }
}

void MyCanvas::Draw_Image()
{
    wxClientDC dc(this);
    wxBitmap image_map(image);
    dc.DrawBitmap(image_map, 0, 0, false);
}

void MyCanvas::OnDraw(wxDC &dc)
{
    wxBitmap image_map(image);
    dc.DrawBitmap(image_map, 0, 0, false);

    wxSize mySize(w, h);
    wxRect myRect(mySize);
    dc.SetClippingRegion(myRect);
    cout << "OnDraw function" << endl;

    wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;

    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    if (axis1 == true & axis2 == true)
    {
        dc.DrawRectangle(mouseX1, mouseY1, w, h);
    }
    
    OnSetSize();
}

void MyCanvas::OnButtonClick(wxCommandEvent &event)
{
    wxClientDC dc(this);
    dc.Clear();
    Draw_Image();
}

void MyCanvas::CreateButton()
{
    wxImage image2 = image;
    wxBitmap button_image(image2.Rescale(100, 100));
    myButton_bm = new wxBitmapButton(this, ID_BUTTON_BM, button_image, wxPoint(w / 2, h + 10), wxSize(100, 100), 0, wxDefaultValidator, wxButtonNameStr);
}

//-----------------------------My Image Load End-----------------------------//

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame
{
public:
    MyFrame();
    ~MyFrame();
    private:
     MyCanvas *drawPane;
    void OnSize(wxSizeEvent &event);
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
//EVT_SIZE(MyFrame::OnSize)
wxEND_EVENT_TABLE()

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Load Image", wxPoint(30, 30), wxSize(800, 600))
{
    wxString filename = "//home//msarfrazshafi//Desktop//image.png"; //image2.jpg
    drawPane = new MyCanvas(this, filename, wxBITMAP_TYPE_ANY);
}

MyFrame::~MyFrame()
{
}

void MyFrame::OnSize(wxSizeEvent &event)
{
    // cout << "Size event is working" << endl;
    //drawPane->OnSetSize();//  OnSetSize();
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