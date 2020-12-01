#include <iostream>
using namespace std;
#include "wx/wxprec.h"
#include <wx/splitter.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#if !wxUSE_DOC_VIEW_ARCHITECTURE
#error You must set wxUSE_DOC_VIEW_ARCHITECTURE to 1 in setup.h!
#endif

#include <iostream>
using namespace std;

#include "docview.h"
#include "doc.h"
#include "view.h"
#include <wx/splitter.h>
//wxIMPLEMENT_DYNAMIC_CLASS(ImageView, wxView);

int draw_clear = 0;

enum
{
    ID_btn_right = 1,
    ID_btn_left = 2,
    ID_btn_up = 3,
    ID_btn_down = 4
};
//----------------------Image Canvas----------------------------//
wxBEGIN_EVENT_TABLE(ImageCanvas, wxScrolledWindow)
    EVT_LEFT_DOWN(ImageCanvas::OnLeftClick)
        EVT_MOTION(ImageCanvas::OnDragging)
            wxEND_EVENT_TABLE()
                ImageCanvas::ImageCanvas(wxView *view, wxWindow *parent) : wxScrolledWindow(parent)
{

    //wxDocument *doc = view->GetDocument();

    this->SetSize(500, 500);
    m_view = view;

    cout << "Step 5" << endl;
}

void ImageCanvas::OnLeftClick(wxMouseEvent &event)
{
    if (event.LeftIsDown())
    {
        wxClientDC dc(this);
        //DoPrepareDC(dc);
        pt = event.GetLogicalPosition(dc);
        mouseX1 = pt.x;
        mouseY1 = pt.y;
        axis1 = true;
        cout << mouseX1 << " : " << mouseY1 << endl;
    }
    else
    {
        axis1 = false;
    }
}

void ImageCanvas::OnDragging(wxMouseEvent &event)
{

    wxPoint pt2;
    if (event.Dragging())
    {
        if (axis1 == true)
        {
            wxClientDC dc(this);
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

void ImageCanvas::clearImage()
{

    // wxDC &dc;
    wxClientDC dc(ImageCanvas);
    //dc = *GetHandle();

    // dc.Clear();
    // Draw_Image();
}

void ImageCanvas::OnDraw(wxDC &dc)
{
    if (m_view)
    {
        dc.SetPen(*wxBLACK);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        m_view->OnDraw(&dc);
        if (draw_clear == 0)
        {
            if (axis1 == true & axis2 == true)
            {
                cout << "X1 : " << mouseX1 << " , Y1 : " << mouseY1 << endl;
                cout << "X2 : " << mouseX2 << " , Y2 : " << mouseY2 << endl;

                wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
                cout << "w: " << w << " h : " << h << endl;
                dc.DrawRectangle(mouseX1, mouseY1, w, h);
            }
        }
        else if (draw_clear == 1)
        {      //left move
            mouseX1 -= 2;
            mouseX2 -= 2;

            cout << "X1 : " << mouseX1 << " , Y1 : " << mouseY1 << endl;
            cout << "X2 : " << mouseX2 << " , Y2 : " << mouseY2 << endl;
            wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
            cout << "w: " << w << " h : " << h << endl;

            dc.DrawRectangle(mouseX1, mouseY1, w, h);
        }
        else if (draw_clear ==2)
        {
            //right move
            mouseX1 += 2;
            mouseX2 += 2;
            wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
            dc.DrawRectangle(mouseX1, mouseY1, w, h);
        }
        else if (draw_clear==3)
        {
            //up move 
            mouseY1 -= 2;
            mouseY2 -= 2;
            wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
            dc.DrawRectangle(mouseX1, mouseY1, w, h);
        }
        else
        {
            //down move
            mouseY1 += 2;
            mouseY2 += 2;
            wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
            dc.DrawRectangle(mouseX1, mouseY1, w, h);
        }
        
    }

    cout << "Clean Draw : " << draw_clear << endl;
}

//----------------------Image View----------------------------//

wxIMPLEMENT_DYNAMIC_CLASS(ImageView, wxView);

ImageDocument *ImageView::GetDocument()
{
    return wxStaticCast(wxView::GetDocument(), ImageDocument);
}

bool ImageView::OnCreate(wxDocument *doc, long flags)
{
    std::cout << "Step 3" << endl;
    if (!wxView::OnCreate(doc, flags))
        return false;

    wxWindow *frame = wxGetApp().CreateChildFrame(this, false); //-------TODO Later on

    wxSize size = frame->GetSize();
    wxASSERT(frame == GetFrame());
    wxSplitterWindow *splitter;
    splitter = new wxSplitterWindow(frame, wxID_ANY);
    splitter->SetSashGravity(0.5);
    MyWindow *left_window, *right_window;
    left_window = new MyWindow(splitter);
    right_window = new MyWindow(splitter);
    right_window->SetBackgroundColour(*wxBLUE);

    left_window->CreateButton("Up", ID_btn_up, new wxPoint(100, 30));
    left_window->CreateButton("Left", ID_btn_left, new wxPoint(0, 60));
    left_window->CreateButton("Right", ID_btn_right, new wxPoint(200, 60));
    left_window->CreateButton("Down", ID_btn_down, new wxPoint(100, 90));

    splitter->SplitVertically(left_window, right_window);

    m_canvas = new ImageCanvas(this, right_window);
    frame->Show();

    return true;
}

void ImageView::OnUpdate(wxView *sender, wxObject *hint)
{
    wxView::OnUpdate(sender, hint);
    wxImage image = GetDocument()->GetImage();
    if (image.IsOk())
    {
        m_canvas->SetVirtualSize(image.GetWidth(), image.GetHeight());
    }
}

void ImageView::OnDraw(wxDC *dc)
{
    cout << "Inside ImageView:ondraw()" << endl;
    wxImage image = GetDocument()->GetImage();
    if (image.IsOk())
    {

        dc->DrawBitmap(wxBitmap(image), 0, 0, true /* use mask */);
    }
}

bool ImageView::OnClose(bool deleteWindow)
{
    if (!wxView::OnClose(deleteWindow))
        return false;

    Activate(false);

    if (deleteWindow)
    {
        GetFrame()->Destroy();
        SetFrame(NULL);
    }

    return true;
}

//----------------------MyWindow----------------------------//
wxBEGIN_EVENT_TABLE(MyWindow, wxWindow)
    //  EVT_BUTTON(ID_btn_up, MyWindow::OnButtonClicked)
    EVT_BUTTON(ID_btn_left, MyWindow::OnleftClicked)
    EVT_BUTTON(ID_btn_right, MyWindow::OnRightClicked)
    EVT_BUTTON(ID_btn_up, MyWindow::OnUpClicked)
    EVT_BUTTON(ID_btn_down, MyWindow::OnDownClicked)
wxEND_EVENT_TABLE()

                        MyWindow::MyWindow(wxSplitterWindow *parent) : wxWindow(parent, wxID_ANY)
{
    draw_clear = 0;
    //Bind( EVT_BUTTON,MyWindow::OnButtonClicked,ID_mybutton);
}

void MyWindow::CreateButton(wxString name, int id, wxPoint *pt)
{
    wxButton *myButton = new wxButton(this, id, name);
    myButton->SetPosition(*pt);
}

void MyWindow::OnButtonClicked(wxCommandEvent &event)
{
    cout << "-------------------------------" << endl;
    cout << "Button Clicked" << endl;

    draw_clear = 1;
    cout << "Clean Draw on button click : " << draw_clear << endl;
    ///  myImageCanvas =new  ImageCanvas(wxView *view, wxWindow *parent)
    // DoPrepareDC(dc);
    // RefreshRect(wxRect(0,0,500,500));
    // wxWindow::Update();
    wxWindow *sibling = GetNextSibling();
    if (sibling != NULL)
    {
        cout << "Next window get" << endl;
        sibling->Refresh();
    }
    //sibling.Refresh();
    //myImageCanvas->clearImage();
}

void MyWindow::OnleftClicked(wxCommandEvent &event)
{
    cout << "Left clilcked" << endl;
    draw_clear = 1;
    wxWindow *sibling = GetNextSibling();
    if (sibling != NULL)
    {
        cout << "Next window get" << endl;
        sibling->Refresh();
    }
}

void MyWindow::OnRightClicked(wxCommandEvent &event)
{
    cout << "Right clicked" << endl;
    draw_clear = 2;
    wxWindow *sibling = GetNextSibling();
    if (sibling != NULL)
    {
        cout << "Next window get" << endl;
        sibling->Refresh();
    }
}

void MyWindow::OnUpClicked(wxCommandEvent &event)
{
    cout << "Up clicked" << endl;
    draw_clear = 3;
    wxWindow *sibling = GetNextSibling();
    if (sibling != NULL)
    {
        cout << "Next window get" << endl;
        sibling->Refresh();
    }
}

void MyWindow::OnDownClicked(wxCommandEvent &event)
{
    cout << "Down Clicked" << endl;
    draw_clear = 4;
    wxWindow *sibling = GetNextSibling();
    if (sibling != NULL)
    {
        cout << "Next window get" << endl;
        sibling->Refresh();
    }
}
