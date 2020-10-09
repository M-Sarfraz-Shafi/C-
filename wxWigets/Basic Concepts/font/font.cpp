#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/sizer.h>
#include <wx/image.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/wxprec.h>
#include <iostream>
using namespace std;
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class wxImagePanel : public wxPanel
{
    public:
        //wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format);
        wxImagePanel();
        int m_imageWidth ;
	    int m_imageHeight ;

        wxBitmap m_imageBitmap ;	
	    wxImage *m_imageRGB ;		
        unsigned char* m_myImage ;
        wxString fileName;
};

wxImagePanel::wxImagePanel(/*wxFrame* parent, wxString file, wxBitmapType format*/) 
{
    m_myImage=NULL;
	m_imageRGB = NULL ;
    fileName = wxFileSelector(_T("Please Select file"),_T(""),_T(""),_T(""), _T("All files (*.*)|*.*") );
	//fileName = wxFileSelector(_T("Select file"),_T(""),_T(""),_T(""), _T("All files (*.*)|*.*") );
	m_imageRGB = new wxImage(fileName, wxBITMAP_TYPE_ANY, -1); // ANY => can load many image formats
	m_imageBitmap = wxBitmap(*m_imageRGB, -1); // ...to get the corresponding bitmap

	m_imageWidth = m_imageRGB->GetWidth() ;
	m_imageHeight = m_imageRGB->GetHeight() ;

    cout<<m_imageWidth<<endl;
    cout<<m_imageHeight<<endl;
	m_myImage = (unsigned char*)malloc(m_imageWidth * m_imageHeight * 3) ;
	memcpy(m_myImage, m_imageRGB->GetData(), m_imageWidth * m_imageHeight * 3) ;


	SetSize(m_imageWidth, m_imageHeight) ;
	//GetParent()->SetClientSize(GetSize()) ;

// update display
	Refresh(false) ;
}



class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
};

class MyFrame : public wxFrame
{
    public:
        MyFrame();
        wxButton *btn_load_image;
        wxPanel* panel;
    private:
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnloadButtonClick(wxCommandEvent& event);
};

enum
{
    button_load_image= 1
};

MyFrame::MyFrame(): wxFrame(NULL, wxID_ANY, "Image Handling")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile,"&File");
    menuBar->Append(menuHelp,"&Help");
    SetMenuBar( menuBar );
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this,wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    panel= new wxPanel(this, wxID_ANY);
    btn_load_image = new wxButton(panel,button_load_image,_T("Log In"),  wxPoint(180, 220));//, wxDefaultSize,0); 
      
    Bind(wxEVT_BUTTON,&MyFrame::OnloadButtonClick,this,button_load_image);
   
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("A project for Image loading and drawing rectangular on it."," ",wxOK | wxICON_INFORMATION); 
}

void MyFrame::OnloadButtonClick(wxCommandEvent& event)
{
   // wxMessageBox("A project for Image loading and drawing rectangular on it."," ",wxOK | wxICON_INFORMATION); 
    wxImagePanel * my_imagePanel = new wxImagePanel( /*frame, wxT("image.jpg"), wxBITMAP_TYPE_JPEG*/);
}
bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MyFrame *frame = new MyFrame();
    
    
   frame->Show(true);
   
    return true;
}

wxIMPLEMENT_APP(MyApp);



