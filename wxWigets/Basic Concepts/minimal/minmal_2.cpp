#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>

enum
{
    ID_QUIT = 1,
    ID_ABOUT,
	ID_LOAD,
	ID_SAVE,
	ID_PROCESS,
	ID_BEST_SIZE
};
class MyCanvas: public wxPanel
//------------------------------------------------------------------------
{
public:
    MyCanvas( wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size ) ;
    ~MyCanvas() ;
	void LoadImage(wxString fileName) ;
	void SaveImage(wxString fileName) ;
	void ProcessImage() ;
	void BestSize() ;

private:
	int m_imageWidth ;
	int m_imageHeight ;
    wxBitmap m_imageBitmap ;	// used to display the image
	wxImage *m_imageRGB ;		// used to load the image
    unsigned char* m_myImage ;	// used to process the image

    void OnPaint(wxPaintEvent &event) ;

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyCanvas, wxPanel)
	EVT_PAINT(MyCanvas::OnPaint)
END_EVENT_TABLE()
MyCanvas::MyCanvas( wxWindow *parent, wxWindowID id,
                    const wxPoint &pos, const wxSize &size )
        : wxPanel( parent, id, pos, size, wxSUNKEN_BORDER)
//------------------------------------------------------------------------
{
    m_myImage=NULL;
	m_imageRGB = NULL ;
}

MyCanvas::~MyCanvas()
//------------------------------------------------------------------------
{
	if (m_myImage)
		free(m_myImage) ;
	if (m_imageRGB)
		delete m_imageRGB ;
}
void MyCanvas::LoadImage(wxString fileName)
//------------------------------------------------------------------------
{
	if (m_myImage)
		free (m_myImage) ;
	if (m_imageRGB)
		delete m_imageRGB ;

// open image dialog box
	m_imageRGB = new wxImage(fileName, wxBITMAP_TYPE_ANY, -1); // ANY => can load many image formats
	m_imageBitmap = wxBitmap(*m_imageRGB, -1); // ...to get the corresponding bitmap

	m_imageWidth = m_imageRGB->GetWidth() ;
	m_imageHeight = m_imageRGB->GetHeight() ;

	m_myImage = (unsigned char*)malloc(m_imageWidth * m_imageHeight * 3) ;
	memcpy(m_myImage, m_imageRGB->GetData(), m_imageWidth * m_imageHeight * 3) ;

// update GUI size
	SetSize(m_imageWidth, m_imageHeight) ;
	GetParent()->SetClientSize(GetSize()) ;

// update display
	Refresh(false) ;
}
class MyFrame: public wxFrame
//------------------------------------------------------------------------
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

protected:
	void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void OnOpenImage(wxCommandEvent& WXUNUSED(event) ) ;
	void OnSaveImage(wxCommandEvent & WXUNUSED(event)) ;
	void OnProcessImage(wxCommandEvent& WXUNUSED(event) ) ;
	void OnClose(wxCloseEvent& event) ;
	void OnBestSize(wxCommandEvent& WXUNUSED(event)) ;

    MyCanvas *m_canvas; // the canvas inside the main frame
	bool m_imageLoaded ;
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(ID_LOAD,  MyFrame::OnOpenImage)
	

END_EVENT_TABLE()
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
//------------------------------------------------------------------------
{
	wxMenu *file_menu = new wxMenu();
	file_menu->Append(ID_LOAD, _T("&Open image..."));


	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(file_menu, _T("&File"));
	SetMenuBar( menuBar );

// create the canvas that will manage the image
	m_canvas = new MyCanvas( this, -1, wxDefaultPosition, wxDefaultSize);
	m_imageLoaded = false ;
	Centre() ;
}