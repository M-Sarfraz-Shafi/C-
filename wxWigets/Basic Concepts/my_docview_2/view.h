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
    void split_window(wxFrame *subframe);
    void create_Button(wxWindow *left_window);
    void OnButtonClicked(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
private:
    MyCanvas *m_canvas;
    DrawingView *myView;
};

