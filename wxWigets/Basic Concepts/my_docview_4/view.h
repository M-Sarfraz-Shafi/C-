#ifndef _WX_SAMPLES_DOCVIEW_VIEW_H_
#define _WX_SAMPLES_DOCVIEW_VIEW_H_

#include "wx/docview.h"
#include <iostream>
using namespace std;

class ImageCanvas : public wxScrolledWindow
{
public:
    ImageCanvas(wxView* view, wxWindow * parent);

    virtual void OnDraw(wxDC& dc) wxOVERRIDE;
private:
    wxView *m_view;
};


class ImageView : public wxView
{
public:
    ImageView() : wxView() {
        cout<<"Step 2"<<endl;
    }

    virtual bool OnCreate(wxDocument*, long flags) wxOVERRIDE;
    virtual void OnDraw(wxDC*) wxOVERRIDE;
    virtual bool OnClose(bool deleteWindow = true) wxOVERRIDE;
    virtual void OnUpdate(wxView *sender, wxObject *hint = NULL) wxOVERRIDE;

    ImageDocument* GetDocument();

    int x_axis =0, y_axis =0;
private:
    ImageCanvas* m_canvas;

    wxDECLARE_DYNAMIC_CLASS(ImageView);
};



#endif // _WX_SAMPLES_DOCVIEW_VIEW_H_