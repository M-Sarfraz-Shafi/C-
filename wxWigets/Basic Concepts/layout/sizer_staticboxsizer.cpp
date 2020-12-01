/*
    wxStaticBoxSizer 
        +
    Two button in center
*/
#include <wx/wx.h>
#include <wx/utils.h>
#include <wx/sizer.h>
enum
{
    ID_btn_1 = 1,
    ID_btn_2 = 2
};

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame
{
public:
    MyFrame();
    ~MyFrame();

private:
    wxButton *button_1, *button_2;
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Button with Sizer", wxPoint(30, 30), wxSize(800, 600))
{
    button_1 = new wxButton(this, ID_btn_1, "Button 1", wxDefaultPosition, wxDefaultSize);//wxSize(10, 10));
    button_2 = new wxButton(this, ID_btn_2, "Button 2", wxDefaultPosition, wxDefaultSize);//wxSize(100, 100));

    wxPanel *panel = new wxPanel(this);
    wxStaticBoxSizer *sz = new wxStaticBoxSizer(wxVERTICAL, this, "Box");
    sz->Add(button_1, wxSizerFlags().FixedMinSize().Proportion(1).Shaped());
  

    sz->Add(button_2);
    SetSizerAndFit(sz);
}

MyFrame::~MyFrame()
{
    
}

//-----------------------------My Frame End-----------------------------//

class MyApp : public wxApp
{
public:
    MyApp();
    ~MyApp();
    virtual bool OnInit();

private:
    MyFrame *m_frame = NULL;
};

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();


    m_frame = new MyFrame();
    
    m_frame->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);