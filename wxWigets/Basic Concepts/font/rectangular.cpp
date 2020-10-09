#include "wx/wx.h"
#include <wx/event.h>
#include <iostream>
using namespace std;


class MyFrame : public wxFrame{
   public:
       MyFrame();
       ~MyFrame();
       void OnPaint(wxPaintEvent& event);
       void OnLeftClick(wxMouseEvent& event);
       void OnDragging(wxMouseEvent& event);
    private:
       bool axis1;
       bool axis2;
       int mouseX1;
       int mouseX2;
       int mouseY1;
       int mouseY2;
       DECLARE_EVENT_TABLE() 
};


class MyApp : public wxApp
{
    public:
       MyApp();
       ~MyApp();
       virtual bool OnInit();
    private:
       MyFrame* m_frame = NULL;
};

MyFrame::MyFrame() : wxFrame(nullptr,wxID_ANY,"Rectangle",wxPoint(30,30),wxSize(800,600))
{
   axis1 = false;
   axis2 = false;
}

bool MyApp :: OnInit()
{
   m_frame = new MyFrame();
   m_frame->Show();
   return true;
}

wxIMPLEMENT_APP(MyApp);

wxBEGIN_EVENT_TABLE(MyFrame,wxFrame)
   EVT_PAINT(MyFrame::OnPaint)
   EVT_LEFT_DOWN(MyFrame::OnLeftClick)
   EVT_MOUSE_EVENTS(MyFrame::OnDragging)
wxEND_EVENT_TABLE()

MyFrame::~MyFrame()
{

}

MyApp::MyApp()
{

}

MyApp::~MyApp()
{

}

void MyFrame :: OnPaint(wxPaintEvent& event)
{
   cout<<axis2<<endl;
   if(axis1==true & axis2==true)
   {
   wxPaintDC dc(this);
    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxRED_BRUSH);
   
    wxCoord w = mouseX2 - mouseX1, h = mouseY1 - mouseY2;
    int x = 0;
    int y = 0;
    
    wxRect recToDraw(mouseX1,mouseX2,w,h);
    dc.DrawRectangle(recToDraw);
      cout<<"Working"<<endl;
   }
}

void MyFrame ::OnLeftClick(wxMouseEvent& event)
{
   
   if(event.LeftDown())
   {
      const wxPoint pt = wxGetMousePosition();
      mouseX1= pt.x;
      mouseY1 = pt.y;
      cout<<"x1: "<<mouseX1<<endl;
      cout<<"y1: "<<mouseY1<<endl;
      axis1 = true;

      OnDragging(event);
   }
  
}

void MyFrame::OnDragging(wxMouseEvent& event)
{
   wxPoint pt2;
   if(event.Dragging())
   {
      pt2 = wxGetMousePosition();
      mouseX2= pt2.x;
      mouseY2 = pt2.y;
      cout<<"x2: "<<mouseX2<<endl;
      cout<<"y2: "<<mouseY2<<endl;
      axis2 = true;
      
     } 
}



