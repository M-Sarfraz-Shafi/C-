#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#if !wxUSE_DOC_VIEW_ARCHITECTURE
#error You must set wxUSE_DOC_VIEW_ARCHITECTURE to 1 in setup.h!
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#if wxUSE_STD_IOSTREAM
#include <iostream>
#else
#include "wx/txtstrm.h"
#endif
#include "wx/wfstream.h"

#include "doc.h"
#include "view.h"

wxIMPLEMENT_DYNAMIC_CLASS(ImageDocument, wxDocument); //TODO --> Define this line of code inside the class

bool ImageDocument::DoOpenDocument(const wxString &file)
{
    return m_image.LoadFile(file);
}

bool ImageDocument::OnOpenDocument(const wxString &filename)
{
    if (!wxDocument::OnOpenDocument(filename))
        return false;

    // we don't have a wxDocTemplate for the image details document as it's
    // never created by wxWidgets automatically, instead just do it manually
  /*  ImageDetailsDocument *const docDetails = new ImageDetailsDocument(this);
    docDetails->SetFilename(filename);

    new ImageDetailsView(docDetails);*/ ////----------TODO uncomment later on

    return true;
}
