#ifndef _WX_SAMPLES_DOCVIEW_VIEW_H_
#define _WX_SAMPLES_DOCVIEW_VIEW_H_

#include <wx/splitter.h>
#include <wx/sizer.h>

class MyCanvas : public wxScrolledWindow
{
public:
    MyCanvas();
    void OnLeftClick(wxMouseEvent &event);
    void OnDragging(wxMouseEvent &event);
    virtual void OnDraw(wxDC &dc) wxOVERRIDE;

    int mouseX1, mouseY1, mouseX2, mouseY2;
    int w, h;
    bool axis1, axis2;
    DECLARE_EVENT_TABLE()
private:
    wxPoint pt;
};

// The view using MyCanvas to show its contents
class DrawingView : public wxView
{
public:
    void OnDraw(wxDC &dc);

    DrawingView();
    void split_window(wxFrame *subframe);
    void create_Button(wxWindow *left_window);
    void OnButtonClicked(wxCommandEvent &event);

    int w, h;

private:
    MyCanvas *m_canvas;
    DrawingView *myView;
    wxDECLARE_DYNAMIC_CLASS(DrawingView);
};

#endif // _WX_SAMPLES_DOCVIEW_VIEW_H_
