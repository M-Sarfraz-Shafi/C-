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
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame{
   public:
       MyFrame();
       ~MyFrame();
};

MyFrame::MyFrame() : wxFrame(nullptr,wxID_ANY,"Load Image",wxPoint(30,30),wxSize(800,600))
{
    this->SetBackgroundColour(*wxBLUE);
    std::string image_path = samples::findFile("starry_night.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);


    //image subimage load
//     cv::Range rows(1, 64);
// cv::Range cols(1, 67);
// Mat rez = src(rows, cols);
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
     
};

MyApp::MyApp()
{
 
}

MyApp::~MyApp()
{

}

bool MyApp:: OnInit()
{
   wxInitAllImageHandlers();
   m_frame = new MyFrame();
   m_frame->Show();
   return true;
}

wxIMPLEMENT_APP(MyApp);