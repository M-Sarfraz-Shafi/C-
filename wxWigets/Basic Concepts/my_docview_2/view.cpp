#include "wx/wxprec.h"
#include "wx/wx.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#if !wxUSE_DOC_VIEW_ARCHITECTURE
#error You must set wxUSE_DOC_VIEW_ARCHITECTURE to 1 in setup.h!
#endif

#include <iostream>
using namespace std;
#include "docview.h"
#include "doc.h"
#include "view.h"

// ----------------------------------------------------------------------------
// DrawingView implementation
// ----------------------------------------------------------------------------

enum
{
    ID_BUTTON = 1,
    ID_BUTTON2 = 2
};
//DrawingView : public wxView
wxBEGIN_EVENT_TABLE(DrawingView, wxView)
    EVT_BUTTON(ID_BUTTON, DrawingView::OnButtonClicked)
        wxEND_EVENT_TABLE()

            DrawingView::DrawingView() : wxView()
{
    m_canvas = NULL;
}

void DrawingView::split_window(wxFrame *subframe)
{
    wxSplitterWindow *splitter;
    splitter = new wxSplitterWindow(subframe, wxID_ANY);
    splitter->SetSashGravity(0.5);
    splitter->SetMinimumPaneSize(20);

    //------using Panel-------------//
    /*
    wxPanel * panel1;
    wxPanel * panel2;
    panel1 = new wxPanel(splitter,wxID_ANY);
    panel1->SetBackgroundColour(*wxBLACK);
    panel2 = new wxPanel(splitter,wxID_ANY);
    panel2->SetBackgroundColour(*wxBLUE);
    splitter->SplitVertically(panel1,panel2);*/

    //-----------Using wxWindow------------//
 
    wxWindow *left_window = new wxWindow(splitter, wxID_ANY, wxDefaultPosition, wxSize(30, 50));
    wxWindow *right_window = new wxWindow(splitter, wxID_ANY, wxDefaultPosition, wxSize(30, 50));
     left_window->SetBackgroundColour(*wxBLACK);
     right_window->SetBackgroundColour(*wxBLUE);
     splitter->SplitVertically(left_window, right_window);

    
    


    create_Button(left_window);
    //-----------------Button create---------------//
    // wxButton *myButton, *myButton2;
    // myButton = new wxButton(left_window, ID_BUTTON, "My Button");
    // myButton2 = new wxButton(left_window, ID_BUTTON, "My Button 2");

    // wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    // sizer->Add(myButton, wxSizerFlags().Center());
    // sizer->Add(myButton2, wxSizerFlags().Center());
    // left_window->SetSizerAndFit(sizer);

    //Bind(wxEVT_BUTTON, &DrawingView::OnButtonClick, this, ID_BUTTON,wxID_ANY);
    //-----------------Button create---------------//

   MyImageCanvas *myImage;
    myImage = new MyImageCanvas(right_window);
   // myImage->create_Button(right_window);

}

void DrawingView::create_Button(wxWindow *left_window)
{
    // wxPanel * panel;
    // wxPoint p = left_window->GetPosition();
    // wxSize s = left_window->GetSize();

    // panel = new wxPanel(left_window,wxID_ANY,wxDefaultPosition,wxSize (300,300));
    // panel->SetBackgroundColour(*wxCYAN);
    wxButton *myButton, *myButton2;
    myButton = new wxButton(left_window, ID_BUTTON, "My Button");
    myButton2 = new wxButton(left_window, ID_BUTTON, "My Button 2");

    myButton->SetDefault();
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(myButton, wxSizerFlags().Center());
    sizer->Add(myButton2, wxSizerFlags().Center());
    left_window->SetSizerAndFit(sizer);
    
    //Bind(myButton->GetId(),wxEVT_COMMAND_BUTTON_CLICKED,OnButtonClick);
    // Bind(wxEVT_BUTTON,&DrawingView::OnButtonClick, this, ID_BUTTON);
    //Bind(EVT_BUTTON,&DrawingView::OnButtonClick);
}

void DrawingView::OnButtonClicked(wxCommandEvent& event)
{
    cout << "Button Clicked" << endl;
}








