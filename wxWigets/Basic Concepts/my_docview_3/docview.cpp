
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

MyApp::MyApp()
{
    
}

bool MyApp::OnInit()
{
    DrawingView * myView;
    wxInitAllImageHandlers();
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
   
    myView->split_window(subframe);
    subframe->Centre();
    subframe->Show();

    
    //--------------------Splitter Window----------------//

    
    //wxSplitterWindow *splitter;
    return true;
}
