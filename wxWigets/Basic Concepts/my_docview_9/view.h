#ifndef _WX_SAMPLES_DOCVIEW_VIEW_H_
#define _WX_SAMPLES_DOCVIEW_VIEW_H_

#include "wx/docview.h"
#include <wx/splitter.h>
#include <iostream>
using namespace std;


class ImageCanvas : public wxScrolledWindow
{
public:
    ImageCanvas(wxView *view, wxSplitterWindow *parent);
    ImageCanvas();
    virtual void OnDraw(wxDC &dc) wxOVERRIDE;
    void OnLeftClick(wxMouseEvent &event);
    void OnDragging(wxMouseEvent &event);
    void left_move(wxDC &dc);
    void right_move(wxDC &dc);
    void up_move(wxDC &dc);
    void down_move(wxDC &dc);
    void clearImage();
    void DrawImage();
    void Refresh_Window();
    void OnEventSize(wxSizeEvent &event);
    void OnMaximize(wxMaximizeEvent &event);
    void OnIonized(wxIconizeEvent& event);
   
    wxDECLARE_EVENT_TABLE();

private:
    wxView *m_view;
    
    int w, h;
    int mouseX1, mouseY1, mouseX2, mouseY2;
    wxPoint pt;
    bool axis1, axis2;
};

class MyWindow : public wxWindow
{
public:
    MyWindow(wxSplitterWindow *parent);
    void CreateButton(wxString name, int id, wxPoint *pt);
    void OnButtonClicked(wxCommandEvent &event);
    void OnleftClicked(wxCommandEvent &event);
    void OnRightClicked(wxCommandEvent &event);
    void OnUpClicked(wxCommandEvent &event);
    void OnDownClicked(wxCommandEvent &event);
 
       wxDECLARE_EVENT_TABLE();
private:
ImageCanvas * myImageCanvas;

};

class MyImageWindow : public wxWindow
{
    MyImageWindow(wxSplitterWindow *parent);
};

class ImageView : public wxView
{
public:
    ImageView() : wxView()
    {
        cout << "Step 2" << endl;
    }

    virtual bool OnCreate(wxDocument *, long flags) wxOVERRIDE;
    virtual void OnDraw(wxDC *) wxOVERRIDE;
    virtual bool OnClose(bool deleteWindow = true) wxOVERRIDE;
    virtual void OnUpdate(wxView *sender, wxObject *hint = NULL) wxOVERRIDE;
    
    ImageDocument *GetDocument();

    int x_axis = 0, y_axis = 0;
    
private:
    ImageCanvas *m_canvas;

    wxDECLARE_DYNAMIC_CLASS(ImageView);
};

#endif // _WX_SAMPLES_DOCVIEW_VIEW_H_