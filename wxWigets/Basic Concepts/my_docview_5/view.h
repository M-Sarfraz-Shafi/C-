#ifndef _WX_SAMPLES_DOCVIEW_VIEW_H_
#define _WX_SAMPLES_DOCVIEW_VIEW_H_

#include "wx/docview.h"


class ImageCanvas : public wxScrolledWindow
{
public:
    ImageCanvas(wxView* view);

    virtual void OnDraw(wxDC& dc) wxOVERRIDE;
private:
    wxView *m_view;
};


class ImageView : public wxView
{
public:
    ImageView() : wxView() {}

    virtual bool OnCreate(wxDocument*, long flags) wxOVERRIDE;
    virtual void OnDraw(wxDC*) wxOVERRIDE;
    virtual bool OnClose(bool deleteWindow = true) wxOVERRIDE;
    virtual void OnUpdate(wxView *sender, wxObject *hint = NULL) wxOVERRIDE;

    ImageDocument* GetDocument();

private:
    ImageCanvas* m_canvas;

    wxDECLARE_DYNAMIC_CLASS(ImageView);
};



#endif // _WX_SAMPLES_DOCVIEW_VIEW_H_