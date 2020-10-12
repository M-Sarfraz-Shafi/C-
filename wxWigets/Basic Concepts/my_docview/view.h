#include <wx/splitter.h>
#include <wx/sizer.h>

class MyCanvas : public wxScrolledWindow
{
public:
    MyCanvas(wxView *view, wxWindow *parent = NULL);
};

// The view using MyCanvas to show its contents
class DrawingView : public wxView
{
public:
    DrawingView();
private: 
    MyCanvas *m_canvas;
};
