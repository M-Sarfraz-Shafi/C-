#ifndef _WX_SAMPLES_DOCVIEW_DOCVIEW_H_
#define _WX_SAMPLES_DOCVIEW_DOCVIEW_H_

#include "wx/docview.h"
#include "wx/vector.h"
#include <wx/splitter.h>
#include <wx/sizer.h>
class MyCanvas;
class DrawingView;
// Define a new application
class MyApp : public wxApp
{
public:
    MyApp();
    virtual bool OnInit() wxOVERRIDE;
    wxFrame *CreateChildFrame(wxView *view, bool isCanvas);

private:
    wxSplitterWindow *splitter;
    MyCanvas *m_canvas;
    DrawingView *myView;
    void split_window(wxFrame *subframe);
    void OnButtonClicked(wxCommandEvent &event);
};

wxDECLARE_APP(MyApp);

#endif // _WX_SAMPLES_DOCVIEW_DOCVIEW_H_
