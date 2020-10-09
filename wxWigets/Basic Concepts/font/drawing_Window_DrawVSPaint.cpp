/*
    Bitmap Button with function
    Drawing 
    2 separte panels    
*/

#include <wx/wx.h>
#include <wx/utils.h> 
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

//-----------------------------My Image Load Start-----------------------------//
class MyCanvas : public wxScrolledWindow
{
    private:
        wxImage image;
        wxBitmapButton *myButton_bm;
        int w, h, startX, startY;
        int mouseX1, mouseY1, mouseX2, mouseY2;
        bool axis1, axis2, rightClicked;	
        wxPoint pt;
        wxPoint pt2;
    public:
        int x,y;
        MyCanvas(wxFrame* parent, wxString file, wxBitmapType format,int startX, int startY);
        void OnButtonClick(wxCommandEvent& event);
        void CreateButton();
        void Draw_Rectangular();
        void Draw_Image();
        void OnPaint(wxPaintEvent & evt);
        void OnLeftClick(wxMouseEvent& event);
        void OnDragging(wxMouseEvent& event);
        void OnMotion(wxMouseEvent& event);
        DECLARE_EVENT_TABLE()
};

enum{
    ID_BUTTON_BM = 1
};

BEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
    EVT_PAINT(MyCanvas::OnPaint)
    //EVT_MOTION(MyCanvas::OnMotion)
    EVT_LEFT_DOWN(MyCanvas::OnLeftClick)
    EVT_MOTION(MyCanvas::OnDragging)
    EVT_BUTTON(ID_BUTTON_BM, MyCanvas::OnButtonClick)
   
END_EVENT_TABLE()

MyCanvas::MyCanvas(wxFrame* parent, wxString file, wxBitmapType format,int startX, int startY) : wxScrolledWindow(parent)
{
    this->SetBackgroundColour((11,11,11));
    image.LoadFile(file, format,-1);
    w = image.GetWidth();
    h = image.GetHeight();
    if(w>500)
    {
        w=500;
        image.Rescale(w, h);
        if(h>500)
        {
            h=500;
            image.Rescale(w,h);
        }
    }else if (h>500)
    {
        h=500;
        image.Rescale(w, h);
    }
    
    SetSize(w, h+200) ;
	GetParent()->SetClientSize(GetSize()) ;
    this->SetSize(startX,startY,w,h);
    axis1 = false;
    axis2 = false;
}
    
void MyCanvas::OnLeftClick(wxMouseEvent& event)
{
   if(event.LeftIsDown())
   {
        wxClientDC dc(this);
        pt = event.GetLogicalPosition(dc);
        //pt = event.GetPosition();
        
        mouseX1= pt.x ;
        mouseY1 = pt.y;
        x = mouseX1;
        y = mouseY1;
        axis1 = true;
        wxWindow::Refresh();
   }
   else
   {
       axis1 = false;
   }
}

void MyCanvas::OnDragging(wxMouseEvent& event)
{
	wxPoint pt2;
    cout<<"Inside ondragging func"<<endl;
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
    else
    {
        axis1 = false;
        axis2 = false;
    }
}

void MyCanvas::OnMotion(wxMouseEvent& event)
{
   //if (event.Moving()) {
         wxClientDC dc(this);
        pt2 = event.GetLogicalPosition(dc);
       // pt2 = event.GetPosition();
       
        x = pt2.x;
        y = pt2.y;
    cout<<"X_axis: "<<x<<"Y_axis: "<<y<<endl;
   // }//
 
}

void MyCanvas::Draw_Rectangular()
{
    wxPaintDC dc(this);
    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    if(axis1==true & axis2==true )
    {   
        wxCoord w =mouseX2-mouseX1, h = mouseY2-mouseY1;
        dc.DrawRectangle(mouseX1,mouseY1,w,h);
    }
}

void MyCanvas::Draw_Image()
{
    wxClientDC dc(this);
    wxBitmap image_map(image);
    dc.DrawBitmap( image_map, 0, 0, false ); 
}

void MyCanvas::OnPaint(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    wxBitmap image_map(image);
    dc.DrawBitmap( image_map, 0, 0, false );
    Draw_Rectangular();
}

void MyCanvas::OnButtonClick(wxCommandEvent& event)
{
    wxClientDC dc(this);
    dc.Clear();
    Draw_Image();
}

void MyCanvas::CreateButton()
{
    wxImage image2 = image;
    wxBitmap button_image(image2.Rescale(100, 100));
    myButton_bm = new wxBitmapButton(this,ID_BUTTON_BM,button_image,wxPoint (w/2,h+10),wxSize (100,100),0,wxDefaultValidator,wxButtonNameStr );

}

//-----------------------------My Image Load End-----------------------------//

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame{
   public:
       MyFrame();
       ~MyFrame();
       void Set_StatusBasr(int x, int y);
};

MyFrame::MyFrame() : wxFrame(nullptr,wxID_ANY,"Load Image",wxPoint(30,30),wxSize(800,600))
{
   
    //CreateStatusBar();
    
   // int x_axix =  MyApp.drawPane->x;
    //int y_axis = drawPane2->y;
   // string str = to_string(x_axix);
    //string str2 = to_string(y_axis);

    //SetStatusText( "str");
}

void MyFrame::Set_StatusBasr(int x, int y)
{
    CreateStatusBar();
    SetStatusText( to_string(x));
}
MyFrame::~MyFrame()
{

}

//-----------------------------My Frame End-----------------------------//

class MyApp:public wxApp
{
    public:
        MyApp();
        ~MyApp();
        //int x_axis, y_axis;
        virtual bool OnInit();
    private:
        MyFrame* m_frame = NULL;
        MyCanvas * drawPane;
        MyCanvas * drawButton;
};

MyApp::MyApp()
{
   //x_axis = drawPane->x;
   //y_axis = drawPane->y;
}

MyApp::~MyApp()
{

}

bool MyApp:: OnInit()
{
   wxInitAllImageHandlers();
   m_frame = new MyFrame();
   wxString filename = wxFileSelector(_T("Select file"),_T(""),_T(""),_T(""), _T("All files (*.*)|*.*") );

   drawPane = new MyCanvas( m_frame, filename, wxBITMAP_TYPE_ANY,100,100);
   
   drawButton = new MyCanvas( m_frame, filename, wxBITMAP_TYPE_ANY,300,300);
   drawPane->CreateButton();
   
   //m_frame->Set_StatusBasr(drawPane->x,drawPane->y);
   m_frame->Show();
   return true;
}

wxIMPLEMENT_APP(MyApp);