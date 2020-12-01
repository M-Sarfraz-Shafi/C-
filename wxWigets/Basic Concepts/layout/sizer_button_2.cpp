/*
    
*/

#include <wx/wx.h>
#include <wx/utils.h>
#include <wx/sizer.h>
enum
{
    ID_btn_1 = 1,
    ID_btn_2 = 2,
    ID_btn_3 = 3
};

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame
{
public:
    MyFrame();
    ~MyFrame();

private:
    wxButton *button_1, *button_2, *button_3;
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Button with Sizer", wxPoint(30, 30), wxSize(800, 600))
{
    button_1 = new wxButton(this, ID_btn_1, "1", wxDefaultPosition, wxDefaultSize);
    button_2 = new wxButton(this, ID_btn_2, "2", wxDefaultPosition, wxDefaultSize);
    button_3 = new wxButton(this, ID_btn_3, "3", wxDefaultPosition, wxDefaultSize);
    

    wxBoxSizer *top_sizer = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *first_sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *second_sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *third_sizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *h_1st = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *h_2nd = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *h_3rd = new wxBoxSizer(wxHORIZONTAL);

    top_sizer->Add(first_sizer);
    top_sizer->Add(second_sizer);
    top_sizer->Add(third_sizer);
    
    first_sizer->Add(h_1st);
    second_sizer->Add(h_2nd);
    third_sizer->Add(h_3rd);
    
    h_1st->Add(button_1);
   h_1st->Add(0,0,1);
    h_1st->Add(button_2); 
    h_1st->Add(0,0,1);
    h_1st->Add(button_3); 
    
    SetSizerAndFit(top_sizer);
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