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
    ID_mybutton = 1
};

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

// void ImageCanvas::DrawImage()
// {
//     wxClientDC dc(this);
//     m_view->OnDraw(&dc);
// }

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
    cout << "Inside ImageCanvas:ondraw()" << endl;

    if (draw_clear == 1)
    {

        cout << "DC cleared" << endl;
        dc.Clear();
        m_view->OnDraw(&dc);
        draw_clear = 0;
    }
    else
    {
        cout << "Not cleared" << endl;

        if (m_view)
        {
            m_view->OnDraw(&dc);

            if (axis1 == true & axis2 == true)
            {
                wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
                dc.SetPen(*wxBLACK);
                dc.SetBrush(*wxTRANSPARENT_BRUSH);
                dc.DrawRectangle(mouseX1, mouseY1, w, h);
            }
        }
    }

    cout<<"Clean Draw : "<<draw_clear<<endl;
}

wxIMPLEMENT_DYNAMIC_CLASS(ImageView, wxView);

ImageDocument *ImageView::GetDocument()
{
    return wxStaticCast(wxView::GetDocument(), ImageDocument);
}

bool ImageView::OnCreate(wxDocument *doc, long flags)
{
    cout << "Step 3" << endl;
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
    left_window->CreateButton();

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

wxBEGIN_EVENT_TABLE(MyWindow, wxWindow)
    EVT_BUTTON(ID_mybutton, MyWindow::OnButtonClicked)
        wxEND_EVENT_TABLE()

            MyWindow::MyWindow(wxSplitterWindow *parent) : wxWindow(parent, wxID_ANY)
{
    draw_clear = 0;
    //Bind( EVT_BUTTON,MyWindow::OnButtonClicked,ID_mybutton);
}

void MyWindow::CreateButton()
{
    wxButton *myButton = new wxButton(this, ID_mybutton, "My Button");
}

void MyWindow::OnButtonClicked(wxCommandEvent &event)
{
    cout<<"-------------------------------"<<endl;
    cout << "Button Clicked" << endl;

    draw_clear = 1;
    cout<<"Clean Draw on button click : "<<draw_clear<<endl;
    ///  myImageCanvas =new  ImageCanvas(wxView *view, wxWindow *parent)
    // DoPrepareDC(dc);
   // RefreshRect(wxRect(0,0,500,500));
   // wxWindow::Update();
   wxWindow *sibling = GetNextSibling();
   if(sibling!=NULL)
   {
       cout<<"Next window get"<<endl;
       sibling->Refresh();
   }
    //sibling.Refresh();
    //myImageCanvas->clearImage();
}
