#include "wx/wxprec.h"
#include "wx/wx.h"
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

// ----------------------------------------------------------------------------
// DrawingView implementation
// ----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(DrawingView, wxView)
enum
{
    ID_BUTTON = 1,
    ID_BUTTON2 = 2
};

wxBEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
    EVT_LEFT_DOWN(MyCanvas::OnLeftClick)
        EVT_MOTION(MyCanvas::OnDragging)
            wxEND_EVENT_TABLE()

                DrawingView::DrawingView() : wxView()
{
    m_canvas = new MyCanvas();
}

void DrawingView::split_window(wxFrame *subframe)
{
    wxSplitterWindow *splitter;
    splitter = new wxSplitterWindow(subframe, wxID_ANY);
    splitter->SetSashGravity(0.5);
    splitter->SetMinimumPaneSize(20);

    //------using Panel-------------//
    /*
    wxPanel * panel1;
    wxPanel * panel2;
    panel1 = new wxPanel(splitter,wxID_ANY);
    panel1->SetBackgroundColour(*wxBLACK);
    panel2 = new wxPanel(splitter,wxID_ANY);
    panel2->SetBackgroundColour(*wxBLUE);
    splitter->SplitVertically(panel1,panel2);*/

    //-----------Using wxWindow------------//

    wxWindow *left_window = new wxWindow(splitter, wxID_ANY, wxDefaultPosition, wxSize(30, 50));
    wxWindow *right_window = new wxWindow(splitter, wxID_ANY, wxDefaultPosition, wxSize(30, 50));
    left_window->SetBackgroundColour(*wxBLACK);
    right_window->SetBackgroundColour(*wxBLUE);
    splitter->SplitVertically(left_window, right_window);

    create_Button(left_window);
    //-----------------Button create---------------//
    // wxButton *myButton, *myButton2;
    // myButton = new wxButton(left_window, ID_BUTTON, "My Button");
    // myButton2 = new wxButton(left_window, ID_BUTTON, "My Button 2");

    // wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    // sizer->Add(myButton, wxSizerFlags().Center());
    // sizer->Add(myButton2, wxSizerFlags().Center());
    // left_window->SetSizerAndFit(sizer);

    //Bind(wxEVT_BUTTON, &DrawingView::OnButtonClick, this, ID_BUTTON,wxID_ANY);
    //-----------------Button create---------------//

    MyImageCanvas *myImage;
    myImage = new MyImageCanvas(right_window);
    // myImage->create_Button(right_window);
}

void DrawingView::create_Button(wxWindow *left_window)
{
    // wxPanel * panel;
    // wxPoint p = left_window->GetPosition();
    // wxSize s = left_window->GetSize();

    // panel = new wxPanel(left_window,wxID_ANY,wxDefaultPosition,wxSize (300,300));
    // panel->SetBackgroundColour(*wxCYAN);
    wxButton *myButton;
    myButton = new wxButton(left_window, ID_BUTTON, "My Button");

    myButton->SetDefault();
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(myButton, wxSizerFlags().Center());

    left_window->SetSizerAndFit(sizer);

    //Bind(myButton->GetId(),wxEVT_COMMAND_BUTTON_CLICKED,OnButtonClick);
    // Bind(wxEVT_BUTTON,&DrawingView::OnButtonClick, this, ID_BUTTON);
    //Bind(EVT_BUTTON,&DrawingView::OnButtonClick);
}

void DrawingView::OnButtonClicked(wxCommandEvent &event)
{
    cout << "Button Clicked" << endl;
}

void DrawingView::OnDraw(wxDC &dc)
{

    if (m_canvas->axis1 == true & m_canvas->axis2 == true)
    {

        wxCoord w = m_canvas->mouseX2 - m_canvas->mouseX1, h = m_canvas->mouseY2 - m_canvas->mouseY1;
        dc.SetPen(*wxBLACK);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawRectangle(m_canvas->mouseX1, m_canvas->mouseY1, w, h);
    }
}

MyCanvas::MyCanvas()
{
}
void MyCanvas::OnLeftClick(wxMouseEvent &event)
{
    if (event.LeftIsDown())
    {
        wxClientDC dc(this);

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

void MyCanvas::OnDragging(wxMouseEvent &event)
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
}

void MyCanvas::OnDraw(wxDC &dc)
{

    if (axis1 == true & axis2 == true)
    {
        wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
        dc.SetPen(*wxBLACK);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawRectangle(mouseX1, mouseY1, w, h);
    }
}
