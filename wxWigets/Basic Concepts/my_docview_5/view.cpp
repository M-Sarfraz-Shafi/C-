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

wxIMPLEMENT_DYNAMIC_CLASS(ImageView, wxView);
ImageCanvas::ImageCanvas(wxView *view) : wxScrolledWindow(view->GetFrame())
{
    m_view = view;
    SetScrollRate(10, 10);
}

// Define the repainting behaviour
void ImageCanvas::OnDraw(wxDC &dc)
{
    if (m_view)
        m_view->OnDraw(&dc);
}

//wxIMPLEMENT_DYNAMIC_CLASS(ImageView, wxView);

ImageDocument *ImageView::GetDocument()
{
    return wxStaticCast(wxView::GetDocument(), ImageDocument);
}

bool ImageView::OnCreate(wxDocument *doc, long flags)
{
    if (!wxView::OnCreate(doc, flags))
        return false;

    wxFrame *frame = wxGetApp().CreateChildFrame(this, false); //-------TODO Later on
    wxASSERT(frame == GetFrame());
    m_canvas = new ImageCanvas(this);
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
