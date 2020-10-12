
#include "wx/wxprec.h"
#include <wx/wx.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include "wx/stockitem.h"
#endif

#if !wxUSE_DOC_VIEW_ARCHITECTURE
#error You must set wxUSE_DOC_VIEW_ARCHITECTURE to 1 in setup.h!
#endif

#include "wx/docview.h"
#include "wx/docmdi.h"

#if wxUSE_AUI
#include "wx/aui/tabmdi.h"
#endif // wxUSE_AUI

#include "docview.h"
#include "doc.h"
#include "view.h"

#include "wx/cmdline.h"
#include "wx/config.h"

#ifdef __WXMAC__
#include "wx/filename.h"
#endif

#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "doc.xpm"
#include "chart.xpm"
#include "notepad.xpm"
#endif
#include <wx/utils.h>
#include <iostream>
 using namespace std;
// ----------------------------------------------------------------------------
// MyApp implementation
// ----------------------------------------------------------------------------

wxIMPLEMENT_APP(MyApp);
enum
{
    ID_BUTTON = 1
};

MyApp::MyApp()
{
    myView == NULL;
}

bool MyApp::OnInit()
{
    wxDocManager *docManager = new wxDocManager;
    new wxDocTemplate(docManager, "Drawings", "*.txt;*.drw", "", "drw",
                      "Drawing Doc", "Drawing View",
                      CLASSINFO(DrawingDocument), CLASSINFO(DrawingView));

    wxFrame *frame = NULL;
    frame = new wxDocMDIParentFrame(docManager, NULL, wxID_ANY,
                                    GetAppDisplayName(),
                                    wxDefaultPosition,
                                    wxSize(500, 400));

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN);

    wxMenuBar *menubar = new wxMenuBar;
    menubar->Append(menuFile, "&File");
    frame->SetMenuBar(menubar);
    frame->Centre();
    frame->Show();
    //--------------------------Child Frame--------------------//
    wxDocument *doc;
    wxFrame *subframe = NULL;
    wxView *view;

    subframe = new wxDocMDIChildFrame(doc, view, wxStaticCast(GetTopWindow(), wxDocMDIParentFrame), wxID_ANY,
                                      "Child Frame", wxDefaultPosition, wxSize(300, 300));
    split_window(subframe);
    subframe->Centre();
    subframe->Show();
    //--------------------Splitter Window----------------//

    //wxSplitterWindow *splitter;
    return true;
}

void MyApp::split_window(wxFrame *subframe)
{
    splitter = new wxSplitterWindow(subframe, wxID_ANY);
    splitter->SetSashGravity(0.5);
    splitter->SetMinimumPaneSize(20);

    //------using Panel-------------//
   
    wxPanel * panel1;
    wxPanel * panel2;
    panel1 = new wxPanel(splitter,wxID_ANY);
    panel1->SetBackgroundColour(*wxBLACK);
    panel2 = new wxPanel(splitter,wxID_ANY);
    panel2->SetBackgroundColour(*wxBLUE);
    splitter->SplitVertically(panel1,panel2);

    //-----------Using wxWindow------------//
    wxWindow *left_window = new wxWindow(splitter, wxID_ANY);
    wxWindow *right_window = new wxWindow(splitter, wxID_ANY);
    left_window->SetBackgroundColour(*wxBLACK);
    right_window->SetBackgroundColour(*wxBLUE);
    splitter->SplitVertically(left_window, right_window);

    wxButton *myButton;
    myButton = new wxButton(left_window, ID_BUTTON, "My Button");

    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(myButton, wxSizerFlags().Center());
    left_window->SetSizerAndFit(sizer);
    
   // Bind(wxEVT_BUTTON, &MyApp::OnButtonClicked,ID_BUTTON);
}

void MyApp::OnButtonClicked(wxCommandEvent& event)
{
    cout<<"Button Clicked"<<endl;
}

wxFrame *MyApp::CreateChildFrame(wxView *view, bool isCanvas)
{
    // create a child frame of appropriate class for the current mode
    wxFrame *subframe = NULL;
    wxDocument *doc = view->GetDocument();
    subframe = new wxDocMDIChildFrame(
        doc,
        view,
        wxStaticCast(GetTopWindow(), wxDocMDIParentFrame),
        wxID_ANY,
        "Child Frame",
        wxDefaultPosition,
        wxSize(300, 300));
    subframe->Centre();

    subframe->SetIcon(isCanvas ? wxICON(chrt) : wxICON(notepad));

    return subframe;
}
