#include <wx/wx.h>
#include "wx/docview.h"

class DrawingDocument : public wxDocument
{
public:
    DrawingDocument();
};

class MyImageCanvas : public wxScrolledWindow
{
private:
    wxImage image;
    int w,h;
    int mouseX1, mouseY1, mouseX2, mouseY2;
    wxPoint pt;
    bool axis1, axis2;
    DECLARE_EVENT_TABLE()

public:
    MyImageCanvas(wxWindow *parent);
    void OnDraw(wxDC &dc);
    void Draw_image();
    void OnLeftClick(wxMouseEvent &event);
    void OnDragging(wxMouseEvent &event);
    void create_Button(wxWindow *left_window);
    void OnButtonClicked(wxCommandEvent& event);
};
