/*
    Parent Frame +/ Child Frame
        +

    Splitter in Child window 
        +
    Image in right window

*/

#include "wx/wxprec.h"

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

// ----------------------------------------------------------------------------
// MyApp implementation
// ----------------------------------------------------------------------------

wxIMPLEMENT_APP(MyApp);

MyApp::MyApp()
{
}

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    wxDocManager *docManager = new wxDocManager;
    //-------------continue below----------------//

    new wxDocTemplate(docManager, "Image", "*.jpg", "", "png;jpg",
                      "Image Doc", "Image View",
                      CLASSINFO(ImageDocument), CLASSINFO(ImageView));

    //ImageView *myview = new ImageView();

    wxFrame *frame = NULL;
    frame = new wxDocMDIParentFrame(docManager, NULL, wxID_ANY,
                                    GetAppDisplayName(),
                                    wxDefaultPosition,
                                    wxSize(400, 500)); //

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN);

    wxMenuBar *menubar = new wxMenuBar;
    menubar->Append(menuFile, "&File");
    frame->SetMenuBar(menubar);
    frame->Centre();
    frame->Show();

    //docManager->CreateNewDocument();

    return true;
}

wxWindow *MyApp::CreateChildFrame(wxView *view, bool isCanvas) //
{
    cout << "Step 4" << endl;
    // create a child frame of appropriate class for the current mode
    wxWindow *subframe = NULL;

    wxDocument *doc = view->GetDocument();
    wxSize size;
    subframe = new wxDocMDIChildFrame(
        doc,
        view,
        wxStaticCast(GetTopWindow(), wxDocMDIParentFrame),
        wxID_ANY,
        "Child Frame",
        wxDefaultPosition,
        wxDefaultSize);

    subframe->Centre();
    // subframe->SetSize(100,100);
    subframe->Show();

    size= subframe->GetSize();

    cout << "Subframe x: " << size.x << " Y: " << size.y << endl;
    subframe->SetBackgroundColour(*wxYELLOW);
    return subframe;
}
