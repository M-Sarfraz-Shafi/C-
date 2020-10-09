/*#include <wx/wx.h>
#include <wx/utils.h> 
#include <iostream>
#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>
#include <iostream>*/
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>
#include <iostream>

using namespace std;

//-----------------------------My Canvas Start-----------------------------//
class MyCanvas: public wxPanel
{
public:
    MyCanvas( wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size ) ;
    ~MyCanvas() ;
	void OnLeftClick(wxMouseEvent& event);
	void OnDragging(wxMouseEvent& event);
	void OnPaint(wxPaintEvent &event) ;
    void LoadImage(wxString fileName) ;
private:
	int mouseX1;
	int mouseY1;
	int mouseX2;
	int mouseY2;
	bool axis1;
	bool axis2;	
	wxPoint pt;
    int m_imageWidth ;
	int m_imageHeight ;
    wxBitmap m_imageBitmap ;	
	wxImage *m_imageRGB ;		
    unsigned char* m_myImage ;	
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyCanvas, wxPanel)
	EVT_PAINT(MyCanvas::OnPaint)
	EVT_LEFT_DOWN(MyCanvas::OnLeftClick)
	EVT_MOTION(MyCanvas::OnDragging)
END_EVENT_TABLE()


MyCanvas::MyCanvas( wxWindow *parent, wxWindowID id,const wxPoint &pos, const wxSize &size )
        : wxPanel( parent, id, pos, size, wxSUNKEN_BORDER)
{
    m_myImage=NULL;
	m_imageRGB = NULL ;
	axis1 = false;
	axis2 = false;
	//this->SetBackgroundColour((11,11,11));
}

MyCanvas::~MyCanvas()
{
	if (m_myImage)
		free(m_myImage) ;
	if (m_imageRGB)
		delete m_imageRGB ;
}

void MyCanvas::OnLeftClick(wxMouseEvent& event)
{
   cout<<"Inside Onleft click"<<endl;
   if(event.LeftDown())
   {
        wxClientDC dc(this);
        pt = event.GetLogicalPosition(dc);
        mouseX1= pt.x ;
        mouseY1 = pt.y;
        axis1 = true;
        wxWindow::Refresh();
   }
}

void MyCanvas::OnDragging(wxMouseEvent& event)
{
	wxPoint pt2;
   	if(event.Dragging())
   	{
		if(axis1 == true)
        {
			wxClientDC dc(this);
    		pt2 = event.GetLogicalPosition(dc);
			mouseX2= pt2.x;	
			mouseY2 = pt2.y;
			cout<<"x2: "<<mouseX2<<endl;
			cout<<"y2: "<<mouseY2<<endl;
			axis2=true;
            wxWindow::Refresh();
		}
		else
		{
			cout<<"Please click Left mouse first"<<endl;
		}
     }
}

void MyCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    wxPaintDC dc(this);
    wxImage* tempImage;  
	if (m_myImage)
	{
		tempImage = new wxImage(m_imageWidth, m_imageHeight, m_myImage, true); 
		m_imageBitmap = wxBitmap(*tempImage, -1); 
		delete(tempImage) ;	
		dc.DrawBitmap(m_imageBitmap, 0, 0);
	}
    //------------------------------
    //wxPaintDC dc(this);
    dc.SetPen(*wxBLACK_PEN);
    if(axis1==true & axis2==true)
    {   
        wxCoord w =mouseX2-mouseX1, h = mouseY2-mouseY1;
        wxCoord a = 50, b = 50;
        wxSize size(500,100) ;
        dc.DrawRectangle(mouseX1,mouseY1,w,h);
    }
}


void MyCanvas::LoadImage(wxString fileName)
{
	if (m_myImage)
    {
		free (m_myImage) ;
    }
    if (m_imageRGB)
    {
    	delete m_imageRGB ;
    }
	m_imageRGB = new wxImage(fileName, wxBITMAP_TYPE_ANY, -1); // ANY => can load many image formats
	m_imageBitmap = wxBitmap(*m_imageRGB, wxBITMAP_SCREEN_DEPTH);//-1); // ...to get the corresponding bitmap
	
	m_imageWidth = m_imageRGB->GetWidth() ;
	m_imageHeight = m_imageRGB->GetHeight() ;

	m_myImage = (unsigned char*)malloc(m_imageWidth * m_imageHeight* 3) ;
	memcpy(m_myImage, m_imageRGB->GetData(), m_imageWidth * m_imageHeight* 3) ;


	SetSize(m_imageWidth, m_imageHeight) ;
	GetParent()->SetClientSize(GetSize()) ;
    
    // update display
	Refresh(false) ;
}

//-----------------------------My Canvas End-----------------------------//

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame{
   public:
       MyFrame();
       ~MyFrame();
       MyCanvas *m_canvas;
    protected:
       bool m_imageLoaded ;
       void OnOpenImage(wxCommandEvent& WXUNUSED (event));
       DECLARE_EVENT_TABLE()
};

enum
{
	ID_LOAD = 1	
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(ID_LOAD,  MyFrame::OnOpenImage)
END_EVENT_TABLE()


MyFrame::MyFrame() : wxFrame(nullptr,wxID_ANY,"Practice",wxPoint(30,30),wxSize(800,600))
{
    m_canvas = new MyCanvas( this, -1, wxDefaultPosition,wxSize(50, 150));
    wxMenu *file_menu = new wxMenu();
    file_menu->Append(ID_LOAD, _T("Load Image"));

    wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(file_menu, _T("&File"));
	SetMenuBar( menuBar );

    m_imageLoaded = false ;
	Centre() ;
}

MyFrame::~MyFrame()
{

}

void MyFrame::OnOpenImage(wxCommandEvent& WXUNUSED(event) )
{
	wxBitmap bitmap;

	wxString filename = wxFileSelector(_T("Select file"),_T(""),_T(""),_T(""), _T("All files (*.*)|*.*") );
	if ( !filename.empty() )
	{
		m_canvas->LoadImage(filename) ;
		m_imageLoaded = true ;
	}
}


//-----------------------------My Frame End-----------------------------//



//-----------------------------My App Start-----------------------------//
class MyApp:public wxApp
{
    public:
        MyApp();
        ~MyApp();
        virtual bool OnInit();
    private:
        MyFrame* m_frame = NULL;
};

MyApp::MyApp()
{
   
}

MyApp::~MyApp()
{

}

bool MyApp:: OnInit()
{
   m_frame = new MyFrame();
   m_frame->Show();
   return true;
}

wxIMPLEMENT_APP(MyApp);
//-----------------------------My App End-----------------------------//