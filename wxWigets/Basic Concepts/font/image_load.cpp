#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>
#include <iostream>

using namespace std;

enum
{
	ID_LOAD = 1	
};

class MyCanvas: public wxPanel
{
public:
    MyCanvas( wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size ) ;
    ~MyCanvas() ;
	void LoadImage(wxString fileName) ;
	void OnLeftClick(wxMouseEvent& event);
	void OnDragging(wxMouseEvent& event);
	void OnPaint(wxPaintEvent &event) ;
private:
	int mouseX1;
	int mouseY1;
	int mouseX2;
	int mouseY2;
	bool axis1;
	bool axis2;
	int m_imageWidth ;
	int m_imageHeight ;
    wxBitmap m_imageBitmap ;	
	wxImage *m_imageRGB ;		
    unsigned char* m_myImage ;	
	wxPoint pt;
    

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
	this->SetBackgroundColour((11,11,11));
}

MyCanvas::~MyCanvas()
{
	if (m_myImage)
		free(m_myImage) ;
	if (m_imageRGB)
		delete m_imageRGB ;
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

void MyCanvas::OnLeftClick(wxMouseEvent& event)
{
   if(event.LeftDown())
   {
		wxClientDC dc(this);
    	pt = event.GetLogicalPosition(dc);
		mouseX1= pt.x;
		mouseY1 = pt.y;
		cout<<"x1: "<<mouseX1<<endl;
		cout<<"y1: "<<mouseY1<<endl;
		axis1 = true; 
	  //wxPaintEvent& event1 = NULL;
	  //wxPaintEvent &WXUNUSED(event1); 
	  //OnPaint(event1);
	  wxWindow::Refresh();
	  
   }
}

void MyCanvas::OnDragging(wxMouseEvent& event)
{
	wxPoint pt2;
	//wxPaintDC dc(this);
	wxClientDC dc(this);
	//dc.SetPen(*wxBLACK_PEN);
	//dc.SetBrush(*wxRED_BRUSH);
	//dc.SetBrush(*wxGREEN_BRUSH);
	//wxPaintDC dc(this);
    dc.SetPen(*wxGREEN_PEN);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
    //dc.SetBrush(*wxRED_BRUSH);

   	if(event.Dragging())
   	{
		  
		if(axis1 == true){
			//pt2 = wxGetMousePosition();
			wxClientDC dc(this);//= wx.ClientDC(self)
    		pt2 = event.GetLogicalPosition(dc);
			mouseX2= pt2.x;	
			mouseY2 = pt2.y;
			
			cout<<"x2: "<<mouseX2<<endl;
			cout<<"y2: "<<mouseY2<<endl;
			//wxCoord w = mouseX2 - mouseX1, h = mouseY2 - mouseY1;
			//wxRect recToDraw(mouseX1,mouseY1,w,h);
			//dc.Clear();		
			//dc.DrawRectangle(recToDraw);
			
			//dc.Clear();
			
			//MyCanvas::Refresh();
			axis2 = true;

			}
		else
		{
			cout<<"Please click Left mouse first"<<endl;
		}
     } 
}
void MyCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    wxImage* tempImage;  // the bridge between my image buffer and the bitmap to display
	wxPaintDC dc(this);
	cout<<"In paint"<<endl;
	if (m_myImage)
	{
		tempImage = new wxImage(m_imageWidth, m_imageHeight, m_myImage, true); // lend my image buffer...
		m_imageBitmap = wxBitmap(*tempImage, -1); // ...to get the corresponding bitmap
		delete(tempImage) ;		// buffer not needed any more
		dc.DrawBitmap(m_imageBitmap, 0, 0);
	}
	if(axis1==true & axis2 == true)
	{
		cout<<"IN piant inside"<<endl;
    	wxPaintDC dc(this);
		dc.SetPen(*wxBLACK_PEN);
		wxCoord w =mouseX2-mouseX1, h = mouseY2-mouseY1;
		 dc.DrawRectangle(mouseX1,mouseY1,w,h);
		//dc.SetBrush(wxTRANSPARENT);
        //dc.DrawRectangle(mouseX1,mouseY1,mouseX2-mouseX1,mouseY2-mouseY1);
       /// dc.DrawRectangle(a,b,w,h);
        //dc.DrawRectangle(0,0,50,50);
    }
	
}

//-------------------------------My Frame--------------------------------------//
class MyFrame : public wxFrame{
   public:
       MyFrame();
       ~MyFrame();
    protected:
        void OnOpenImage(wxCommandEvent& WXUNUSED(event) ) ;
        MyCanvas *m_canvas; // the canvas inside the main frame
	    MyCanvas *m_canvas2;
		bool m_imageLoaded ;
        DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(ID_LOAD,  MyFrame::OnOpenImage)
END_EVENT_TABLE()

class MyApp : public wxApp
{
    public:
       MyApp();
       ~MyApp();
       virtual bool OnInit();
    private:
       MyFrame* m_frame = NULL;   
};

MyFrame::MyFrame() : wxFrame(nullptr,wxID_ANY,"Image Load",wxPoint(30,30),wxSize(800,600))
{
    wxMenu *file_menu = new wxMenu();
    file_menu->Append(ID_LOAD, _T("&Open image..."));
    wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(file_menu, _T("&File"));
	SetMenuBar( menuBar );

    m_canvas = new MyCanvas( this, -1, wxDefaultPosition,wxSize(50, 150));
	m_canvas2 = new MyCanvas( this, -1, wxDefaultPosition,wxSize(50, 150));
	m_imageLoaded = false ;
	Centre() ;
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

bool MyApp ::OnInit()
{   
   wxInitAllImageHandlers() ;
   void handlerFuncName(wxMouseEvent& event);
   void handlerFuncName(wxEraseEvent& event);
   m_frame = new MyFrame();
   m_frame->Show();
   SetTopWindow(m_frame);
   return true;
}

MyFrame::~MyFrame()
{

}

MyApp::MyApp()
{

}

MyApp::~MyApp()
{

}

wxIMPLEMENT_APP(MyApp);