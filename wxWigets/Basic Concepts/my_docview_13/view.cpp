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
#include <wx/defs.h>
int draw_clear = 0;
int n = 0, m = 0;

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
            EVT_SIZE(ImageCanvas::OnEventSize)
                EVT_MAXIMIZE(ImageCanvas::OnMaximize)
                    EVT_ICONIZE(ImageCanvas::OnIonized)
                        wxEND_EVENT_TABLE()

                            ImageCanvas::ImageCanvas(wxView *view, wxSplitterWindow *parent) : wxScrolledWindow(parent)
{

    //wxDocument *doc = view->GetDocument();

    this->SetSize(500, 500);
    this->SetWindowStyle(wxFULL_REPAINT_ON_RESIZE);
    m_view = view;

    cout << "Step 5" << endl;
}

ImageCanvas::ImageCanvas()
{
}

void ImageCanvas::OnEventSize(wxSizeEvent &event)
{
    axis1 = true;
    axis2 = true;
}

void ImageCanvas::OnMaximize(wxMaximizeEvent &event)
{
    cout << "Maximized event call" << endl;
    axis1 = true;
    axis2 = true;
}

void ImageCanvas::OnIonized(wxIconizeEvent &event)
{
    cout << "ionized event call" << endl;
    axis1 = true;
    axis2 = true;
}

void ImageCanvas::OnLeftClick(wxMouseEvent &event)
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
            //OnDraw(dc);
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

void ImageCanvas::left_move(wxDC &dc)
{
    mouseX1 -= 2;
    mouseX2 -= 2;
    wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
    dc.DrawRectangle(mouseX1, mouseY1, w, h);
    draw_clear = 0;
}

void ImageCanvas::right_move(wxDC &dc)
{
    mouseX1 += 2;
    mouseX2 += 2;
    wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
    dc.DrawRectangle(mouseX1, mouseY1, w, h);
    draw_clear = 0;
}

void ImageCanvas::up_move(wxDC &dc)
{
    mouseY1 -= 2;
    mouseY2 -= 2;
    wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
    dc.DrawRectangle(mouseX1, mouseY1, w, h);
    draw_clear = 0;
}

void ImageCanvas::down_move(wxDC &dc)
{
    mouseY1 += 2;
    mouseY2 += 2;
    wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
    dc.DrawRectangle(mouseX1, mouseY1, w, h);
    draw_clear = 0;
}

void ImageCanvas::OnDraw(wxDC &dc)
{
    if (m_view)
    {

        dc.SetPen(*wxRED);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        m_view->OnDraw(&dc);

        m = m + 1;
    }

    cout << "Clean Draw : " << draw_clear << endl;
}

void ImageCanvas::Refresh_Window()
{
    draw_clear = 4;
    cout << "draw clear : " << draw_clear << endl;
    wxWindow::Refresh();
}
// {
//     //Refresh
// }
//----------------------Image View----------------------------//

void ImageCanvas::GetAxis(int *X1, int *Y1, int *X2, int *Y2, bool *ax1, bool *ax2)
{
    *X1 = mouseX1;
    *X2 = mouseX2;
    *Y1 = mouseY1;
    *Y2 = mouseY2;
    *ax1 = axis1;
    *ax2 = axis2;
}

//----------------------Image View----------------------------//
wxIMPLEMENT_DYNAMIC_CLASS(ImageView, wxView);

ImageDocument *ImageView::GetDocument()
{
    return wxStaticCast(wxView::GetDocument(), ImageDocument);
}
/*
MyWindow *ImageView::GetWindow()
{
    return wxStaticCast(&m_canvas,MyWindow);
}
*/
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
    MyWindow *left_window; //, *right_window;
    left_window = new MyWindow(splitter);
    //right_window = new MyWindow(splitter);
    //right_window->SetBackgroundColour(*wxBLUE);

    m_canvas = new ImageCanvas(this, splitter);

    left_window->CreateButton("Up", ID_btn_up, new wxPoint(100, 30));
    left_window->CreateButton("Left", ID_btn_left, new wxPoint(0, 60));
    left_window->CreateButton("Right", ID_btn_right, new wxPoint(200, 60));
    left_window->CreateButton("Down", ID_btn_down, new wxPoint(100, 90));

    splitter->SplitVertically(left_window, m_canvas);

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

void ImageView::Get_axis()
{
    m_canvas->GetAxis(&X1, &Y1, &X2, &Y2, &ax1, &ax2);
}

void ImageView::left_move(wxDC *dc)
{
    X1 -= 2;
    X2 -= 2;
    wxCoord w = X2 - X1, h = Y2 - Y1;
    dc->DrawRectangle(X1, Y1, w, h);
    draw_clear = 0;
}

void ImageView::right_move(wxDC *dc)
{
    X1 += 2;
    X2 += 2;
    wxCoord w = X2 - X1, h = Y2 - Y1;
    dc->DrawRectangle(X1, Y1, w, h);
    draw_clear = 0;
}

void ImageView::up_move(wxDC *dc)
{
    Y1 -= 2;
    Y2 -= 2;
    wxCoord w = X2 - X1, h = Y2 - Y1;
    dc->DrawRectangle(X1, Y1, w, h);
    draw_clear = 0;
}

void ImageView::down_move(wxDC *dc)
{
    Y1 += 2;
    Y2 += 2;
    wxCoord w = X2 - X1, h = Y2 - Y1;
    dc->DrawRectangle(X1, Y1, w, h);
    draw_clear = 0;
}

void ImageView::Draw_mini_rect(wxDC *dc)
{
    x_values[0] = 0;

    float x_points = 18;
    for (int i = 0; i < x_points + 1; i++)
    {
        x_values[i + 1] = x_values[i] + w / x_points;
        cout << "Total x_values are" << i << " : " << x_values[i] << endl;
    }

    y_values[0] = 0;
    float y_points = 12;
    for (int j = 0; j < y_points + 1; j++)
    {
        y_values[j + 1] = y_values[j] + h / y_points;
    }

    wxCoord w1 = x_values[1] - x_values[0], h1 = y_values[1] - y_values[0];

    cout << "Width is : " << w << endl;
    cout << "Hight is : " << h << endl;
    for (int row = 0; row < 4; row++)
    {

        for (int col = 0; col < 6; col++)
        {
            cout << "x" << (col * 3) + 1 << " : " << x_values[col * 3 + 1] << endl;

            dc->DrawRectangle(X1 + x_values[col * 3 + 1], Y1 + (y_values[row * 3 + 1]), w1, h1);
        }
    }
}

void ImageView::OnDraw(wxDC *dc)
{
    wxImage image = GetDocument()->GetImage();
    if (image.IsOk())
    {
        dc->DrawBitmap(wxBitmap(image), 0, 0, true /* use mask */);
    }

    if (draw_clear == 0)
    {
        Get_axis();
        if (ax1 == true & ax2 == true)
        {
            w = X2 - X1;
            h = Y2 - Y1;
            //cout << "Draw 1" << endl;
            dc->DrawRectangle(X1, Y1, w, h);
            Draw_mini_rect(dc);
            //cout << "Draw 2" << endl;
            // dc->DrawRectangle(X1 + 15, Y1 + 15, w, h);
        }
    }
    else if (draw_clear == 1)
    {
        left_move(dc);
        Draw_mini_rect(dc);
    }
    else if (draw_clear == 2)
    {
        right_move(dc);
        Draw_mini_rect(dc);
    }
    else if (draw_clear == 3)
    {
        up_move(dc);
        Draw_mini_rect(dc);
    }
    else
    {
        down_move(dc);
        Draw_mini_rect(dc);
    }

    n = n + 1;
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
    parentSplitter = parent;
    //Bind( EVT_BUTTON,MyWindow::OnButtonClicked,ID_mybutton);
}

ImageCanvas *MyWindow::Get_Scrolled_window()
{
    // return wxStaticCast(, ImageCanvas);
}

MyWindow *MyWindow::Get_ScrolledWindow()
{
    //return wxStaticCast(ImageView->m_canvas,MyWindow);
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
    draw_clear = 4;

    if ((wxStaticCast(parentSplitter->GetWindow2(), MyWindow)) != NULL)
    {
        ImageCanvas *ptrMyWin = wxStaticCast(parentSplitter->GetWindow2(), ImageCanvas);
        ptrMyWin->Refresh_Window();
    }
}
