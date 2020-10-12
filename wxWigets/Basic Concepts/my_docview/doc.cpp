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

DrawingDocument::DrawingDocument()
{
    
}