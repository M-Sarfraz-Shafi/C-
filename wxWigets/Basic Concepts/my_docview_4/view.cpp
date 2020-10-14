#include <iostream>
using namespace std;
#include "wx/wxprec.h"

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
ImageCanvas::ImageCanvas(wxView *view, wxWindow *parent) : wxScrolledWindow(parent)
{


    //wxDocument *doc = view->GetDocument();

    this->SetSize(500,500);
    m_view = view;

    cout << "Step 5" << endl;
}

// Define the repainting behaviour
void ImageCanvas::OnDraw(wxDC &dc)
{
    if (m_view)
        m_view->OnDraw(&dc);
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
    cout << "Frame size is x: " << size.x << " Y: " << size.y << endl;
     wxASSERT(frame == GetFrame());

    wxSplitterWindow *splitter;
    splitter = new wxSplitterWindow(frame, wxID_ANY);
    splitter->SetSashGravity(0.5);

    wxWindow *left_window, *right_window;

    left_window = new wxWindow(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    right_window = new wxWindow(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    left_window->SetBackgroundColour(*wxBLUE);
    right_window->SetBackgroundColour(*wxBLACK);
    splitter->SplitVertically(left_window, right_window);

    
    // x_axis = GetDocument()->ImageX();
    // y_axis = GetDocument()->ImageY();


   // splitter->SetSize(x_axis*2, y_axis);

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

// void ImageView :: MyFun()
// {
//     int a =1;
// }
