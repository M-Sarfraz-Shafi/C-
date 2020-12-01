#ifndef _WX_SAMPLES_DOCVIEW_DOC_H_
#define _WX_SAMPLES_DOCVIEW_DOC_H_

#include "wx/docview.h"
#include "wx/cmdproc.h"
#include "wx/vector.h"
#include "wx/image.h"
#include <iostream>
using namespace std;

#if wxUSE_STD_IOSTREAM
    typedef wxSTD istream DocumentIstream;
    typedef wxSTD ostream DocumentOstream;
#else // !wxUSE_STD_IOSTREAM
    typedef wxInputStream DocumentIstream;
    typedef wxOutputStream DocumentOstream;
#endif // wxUSE_STD_IOSTREAM/!wxUSE_STD_IOSTREAM


class ImageDocument : public wxDocument
{
  public:
    ImageDocument() : wxDocument() { 
        cout<<"Step 1"<<endl;
    }

    virtual bool OnOpenDocument(const wxString& file) wxOVERRIDE;

    wxImage GetImage() const { return m_image; }
    int ImageX();
    int ImageY();
    wxImage myImage;
protected:
    virtual bool DoOpenDocument(const wxString& file) wxOVERRIDE;

private:
    wxImage m_image;

    wxDECLARE_NO_COPY_CLASS(ImageDocument);
    wxDECLARE_DYNAMIC_CLASS(ImageDocument);

};


#endif // _WX_SAMPLES_DOCVIEW_DOC_H_