#ifndef _WX_SAMPLES_DOCVIEW_DOCVIEW_H_
#define _WX_SAMPLES_DOCVIEW_DOCVIEW_H_

#include "wx/docview.h"
#include "wx/vector.h"

//class MyCanvas;
//class DrawingView;

// Define a new application
class MyApp : public wxApp
{
public:
    MyApp();
    virtual bool OnInit() wxOVERRIDE;
    wxFrame *CreateChildFrame(wxView *view, bool isCanvas); // ------TODO why using bool isCanvas

};

wxDECLARE_APP(MyApp);

#endif // _WX_SAMPLES_DOCVIEW_DOCVIEW_H_
