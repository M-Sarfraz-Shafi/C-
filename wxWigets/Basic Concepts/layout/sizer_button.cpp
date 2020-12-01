/*
    wxBoxSizer 
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

    button_1 = new wxButton(this, ID_btn_1, "Button 1", wxDefaultPosition, wxSize(100, 100));
    button_2 = new wxButton(this, ID_btn_2, "Button 2", wxDefaultPosition, wxSize(100, 100));

    wxBoxSizer *first_sizer = new wxBoxSizer(wxVERTICAL);
    //   wxBoxSizer *second_sizer = new wxBoxSizer(wxVERTICAL);
    // wxBoxSizer *top_sizer = new wxBoxSizer(wxHORIZONTAL);
    //   top_sizer->Add(first_sizer);
    //   top_sizer->Add(second_sizer);
    //  SetSizerAndFit(top_sizer);
    first_sizer->Add(button_2, wxSizerFlags().Center().Shaped().Expand());
    first_sizer->Add(0, 0, 1);
    first_sizer->Add(button_1, wxSizerFlags().Center().Shaped().Expand()); //

    // third_1->Add(button_1,wxSHAPED);
    // third_2->Add(button_2,wxSHAPED);
    // second_sizer->Add(button_1,wxSHAPED); //,wxSHAPED
    // second_sizer->Add(button_2,wxSHAPED);

    // first_sizer->Fit(this);
    // first_sizer->SetSizeHints(this);
   SetSizerAndFit(first_sizer);
    //SetSizerAndFit(second_sizer);

    // SetSizerAndFit(third_1);
    // SetSizerAndFit(third_2);
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
    // wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    // topSizer->Add(this,wxALL);
    //SetSizerAndFit(topSizer);

    m_frame->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);