#include "wx/wxprec.h"

// #ifdef __BORLANDC__
// #pragma hdrstop
// #endif

// #if !wxUSE_DOC_VIEW_ARCHITECTURE
// #error You must set wxUSE_DOC_VIEW_ARCHITECTURE to 1 in setup.h!
// #endif

// #ifndef WX_PRECOMP
// #include "wx/wx.h"
// #endif

// #if wxUSE_STD_IOSTREAM
#include <iostream>
using namespace std;
// #else
// #include "wx/txtstrm.h"
// #endif
#include "wx/wfstream.h"

#include <string.h>
#include <stdlib.h>
#include "doc.h"
#include "view.h"
#include <wx/utils.h>

enum
{
    ID_BUTTON =1
};

BEGIN_EVENT_TABLE(MyImageCanvas, wxScrolledWindow)
EVT_LEFT_DOWN(MyImageCanvas::OnLeftClick)
EVT_MOTION(MyImageCanvas::OnDragging)
EVT_BUTTON(ID_BUTTON,MyImageCanvas::OnButtonClicked)
END_EVENT_TABLE()

DrawingDocument::DrawingDocument()
{
}

MyImageCanvas::MyImageCanvas(wxWindow *parent) : wxScrolledWindow(parent)
{
    wxString filename = "/home/msarfrazshafi/wxWidgets/samples/my_docview_2/image.jpg";
    //wxString filename = wxFileSelector(_T("Select file"), _T(""), _T(""), _T(""), _T("All files (*.*)|*.*"));

    image.LoadFile(filename, wxBITMAP_TYPE_ANY, -1);

    if (image.IsOk())
    {
        w = image.GetWidth();
        h = image.GetHeight();
        if (w > 500)
        {
            w = 500;
            image.Rescale(w, h);
            if (h > 500)
            {
                h = 500;
                image.Rescale(w, h);
            }
        }
        else if (h > 500)
        {
            h = 500;
            image.Rescale(w, h);
        }

        this->SetSize(0, 0, w, h);
    }
    else
    {
        cout << "Not load  image" << endl;
    }
    
  

}

void MyImageCanvas::Draw_image()
{
    wxClientDC dc(this);
    wxBitmap image_map(image);
    dc.DrawBitmap(image_map, 0, 0, false);
}

void MyImageCanvas::OnDraw(wxDC &dc)
{
    wxBitmap image_map(image);
    dc.DrawBitmap(image_map, 0, 0, false);

 /*   if (axis1 == true & axis2 == true)
    {
        wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
        dc.SetPen(*wxBLACK);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawRectangle(mouseX1, mouseY1, w, h);
    }*/
}

void MyImageCanvas::OnLeftClick(wxMouseEvent &event)
{
    if (event.LeftIsDown())
    {
        wxClientDC dc(this);
        DoPrepareDC(dc);
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

void MyImageCanvas::OnDragging(wxMouseEvent &event)
{
    wxPoint pt2;
    if (event.Dragging())
    {
        if (axis1 == true)
        {
            wxClientDC dc(this);
            DoPrepareDC(dc);
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

void MyImageCanvas::create_Button(wxWindow *left_window)
{
    
    wxButton *myButton, *myButton2;
    myButton = new wxButton(left_window, ID_BUTTON, "new Button");
}

void MyImageCanvas::OnButtonClicked(wxCommandEvent& event)
{
    cout<<"Button Clicked"<<endl;
}







