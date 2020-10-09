#include <wx/utils.h> 
class MyCanvas : public wxPanel
{
    private:
        wxImage image;
        wxBitmapButton *myButton_bm;
        int w,h;
    public:
        MyCanvas(wxFrame* parent);
       
};

