/*
    Documents and view FrameWork
    Example Doodle from book    
*/

#include <wx/wx.h>
#include <wx/utils.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <wx/docview.h>

using namespace std;

//-----------------------------Doodle Start-----------------------------//
// Define a new frame
class DoodleFrame: public wxDocParentFrame
{
DECLARE_CLASS(DoodleFrame)
DECLARE_EVENT_TABLE()
public:
DoodleFrame(wxDocManager *manager, wxFrame *frame, wxWindowID id,
const wxString& title, const wxPoint& pos,
const wxSize& size, long type);
/// Show About box
void OnAbout(wxCommandEvent& event);
/// Get edit menu
wxMenu* GetEditMenu() const { return m_editMenu; }
/// Get canvas
DoodleCanvas* GetCanvas() const { return m_canvas; }
private:
wxMenu *
DoodleCanvas*
};


IMPLEMENT_CLASS(DoodleFrame, wxDocParentFrame)
BEGIN_EVENT_TABLE(DoodleFrame, wxDocParentFrame)
EVT_MENU(DOCVIEW_ABOUT, DoodleFrame::OnAbout)
END_EVENT_TABLE()

DoodleFrame::DoodleFrame(wxDocManager *manager, wxFrame *parent,
wxWindowID id, const wxString& title,
const wxPoint& pos, const wxSize& size, long type):
wxDocParentFrame(manager, parent, id, title, pos, size, type)
{
m_editMenu = NULL;
m_canvas = new DoodleCanvas(this,
wxDefaultPosition, wxDefaultSize, 0);
m_canvas->SetCursor(wxCursor(wxCURSOR_PENCIL));
// Give it scrollbars
m_canvas->SetScrollbars(20, 20, 50, 50);
m_canvas->SetBackgroundColour(*wxWHITE);
m_canvas->ClearBackground();
// Give it an icon
SetIcon(wxIcon(doodle_xpm));
// Make a menu bar
wxMenu *fileMenu = new wxMenu;
wxMenu *editMenu = (wxMenu *) NULL;
fileMenu->Append(wxID_NEW, wxT(“&New...”));
fileMenu->Append(wxID_OPEN, wxT(“&Open...”));
fileMenu->Append(wxID_CLOSE, wxT(“&Close”));
fileMenu->Append(wxID_SAVE, wxT(“&Save”));
fileMenu->Append(wxID_SAVEAS, wxT(“Save &As...”));
fileMenu->AppendSeparator();
fileMenu->Append(wxID_PRINT, wxT(“&Print...”));
fileMenu->Append(wxID_PRINT_SETUP, wxT(“Print &Setup...”));
fileMenu->Append(wxID_PREVIEW, wxT(“Print Pre&view”));
editMenu = new wxMenu;
editMenu->Append(wxID_UNDO, wxT(“&Undo”));
editMenu->Append(wxID_REDO, wxT(“&Redo”));
editMenu->AppendSeparator();
editMenu->Append(DOCVIEW_CUT, wxT(“&Cut last segment”));
m_editMenu = editMenu;
fileMenu->AppendSeparator();
fileMenu->Append(wxID_EXIT, wxT(“E&xit”));
wxMenu *helpMenu = new wxMenu;
helpMenu->Append(DOCVIEW_ABOUT, wxT(“&About”));
wxMenuBar *menuBar = new wxMenuBar;
menuBar->Append(fileMenu, wxT(“&File”));
menuBar->Append(editMenu, wxT(“&Edit”));
menuBar->Append(helpMenu, wxT(“&Help”));
// Associate the menu bar with the frame
SetMenuBar(menuBar);
// A nice touch: a history of files visited. Use this menu.
manager->FileHistoryUseMenu(fileMenu);
}
void DoodleFrame::OnAbout(wxCommandEvent& WXUNUSED(event) )
{
(void)wxMessageBox(wxT(“Doodle Sample\n(c) 2004, Julian Smart”),
wxT(“About Doodle”));
}

/*
* Represents a doodle document
*/
class DoodleDocument: public wxDocument
{
DECLARE_DYNAMIC_CLASS(DoodleDocument)
public:
DoodleDocument() {};
~DoodleDocument();
/// Saves the document
wxOutputStream& SaveObject(wxOutputStream& stream);
/// Loads the document
wxInputStream& LoadObject(wxInputStream& stream);
inline wxList& GetDoodleSegments() { return m_doodleSegments; };
private:
wxList m_doodleSegments;
};


/*
* Defines a line from one point to the other
*/
class DoodleLine: public wxObject
{
public:
DoodleLine(wxInt32 x1 = 0, wxInt32 y1 = 0,
wxInt32 x2 = 0, wxInt32 y2 = 0)
{ m_x1 = x1; m_y1 = y1; m_x2 = x2; m_y2 = y2; }
wxInt32
wxInt32
wxInt32
wxInt32
m_x1;
m_y1;
m_x2;
m_y2;
};
/*
* Contains a list of lines: represents a mouse-down doodle
*/
class DoodleSegment: public wxObject
{
public:
DoodleSegment(){};
DoodleSegment(DoodleSegment& seg);
~DoodleSegment();
void Draw(wxDC *dc);
/// Saves the segment
wxOutputStream& SaveObject(wxOutputStream& stream);
/// Loads the segment
wxInputStream& LoadObject(wxInputStream& stream);
/// Gets the lines
wxList& GetLines() { return m_lines; }
private:
wxList m_lines;
};


/*
* DoodleDocument
*/
IMPLEMENT_DYNAMIC_CLASS(DoodleDocument, wxDocument)
DoodleDocument::~DoodleDocument()
{
WX_CLEAR_LIST(wxList, m_doodleSegments);
}
wxOutputStream& DoodleDocument::SaveObject(wxOutputStream& stream)
{
wxDocument::SaveObject(stream);
wxTextOutputStream textStream( stream );
wxInt32 n = m_doodleSegments.GetCount();
textStream << n << wxT(‘\n’);
wxList::compatibility_iterator node = m_doodleSegments.GetFirst();
while (node)
{
DoodleSegment *segment = (DoodleSegment *)node->GetData();
segment->SaveObject(stream);
textStream << wxT(‘\n’);
node = node->GetNext();
}
return stream;
}
wxInputStream& DoodleDocument::LoadObject(wxInputStream& stream)
{
wxDocument::LoadObject(stream);
wxTextInputStream textStream( stream );
wxInt32 n = 0;
textStream >> n;
for (int i = 0; i < n; i++)
{
DoodleSegment *segment = new DoodleSegment;
segment->LoadObject(stream);
m_doodleSegments.Append(segment);
}
return stream;
}
/*
* DoodleSegment
*/
DoodleSegment::DoodleSegment(DoodleSegment& seg)
{
wxList::compatibility_iterator node = seg.GetLines().GetFirst();
while (node)
{
DoodleLine *line = (DoodleLine *)node->GetData();
DoodleLine *newLine = new DoodleLine(line->m_x1, line->m_y1,
line->m_x2, line->m_y2);
GetLines().Append(newLine);
node = node->GetNext();
}
}
DoodleSegment::~DoodleSegment()
{
WX_CLEAR_LIST(wxList, m_lines);
}
wxOutputStream &DoodleSegment::SaveObject(wxOutputStream& stream)
{
wxTextOutputStream textStream( stream );
wxInt32 n = GetLines().GetCount();
textStream << n << wxT(‘\n’);
wxList::compatibility_iterator node = GetLines().GetFirst();
while (node)
{
DoodleLine *line = (DoodleLine *)node->GetData();
textStream
<< line->m_x1 << wxT(“ “)
<< line->m_y1 << wxT(“ “)
<< line->m_x2 << wxT(“ “)
<< line->m_y2 << wxT(“\n”);
node = node->GetNext();
}
return stream;
}
wxInputStream &DoodleSegment::LoadObject(wxInputStream& stream)
{
wxTextInputStream textStream( stream );
wxInt32 n = 0;
textStream >> n;
for (int i = 0; i < n; i++)
{
DoodleLine *line = new DoodleLine;
textStream
>> line->m_x1
>> line->m_y1
>> line->m_x2
>> line->m_y2;
GetLines().Append(line);
}
return stream;
}
void DoodleSegment::Draw(wxDC *dc)
{
wxList::compatibility_iterator node = GetLines().GetFirst();
while (node)
{DoodleLine *line = (DoodleLine *)node->GetData();
dc->DrawLine(line->m_x1, line->m_y1, line->m_x2, line->m_y2);
node = node->GetNext();
}
}

/*
* A doodle command
*/
class DoodleCommand: public wxCommand
{
public:
DoodleCommand(const wxString& name, int cmd, DoodleDocument *doc,
DoodleSegment *seg);
~DoodleCommand();
/// Overrides
virtual bool Do();
virtual bool Undo();
/// Combine do/undo code since the commands are symmetric
bool DoOrUndo(int cmd);
protected:
DoodleSegment* m_segment;
DoodleDocument* m_doc;
int
m_cmd;
};
/*
* Doodle command identifiers
*/
#define DOODLE_CUT 1
#define DOODLE_ADD 2
/*
* DoodleCommand
*/
DoodleCommand::DoodleCommand(const wxString& name, int command,
DoodleDocument *doc, DoodleSegment *seg):
wxCommand(true, name)
{
m_doc = doc;
m_segment = seg;
m_cmd = command;
}
DoodleCommand::~DoodleCommand()
{
if (m_segment)
delete m_segment;
}
bool DoodleCommand::Do()
{
return DoOrUndo(m_cmd);
}
bool DoodleCommand::Undo()
{
switch (m_cmd)
{
case DOODLE_ADD:
{
return DoOrUndo(DOODLE_CUT);
}
case DOODLE_CUT:
{
return DoOrUndo(DOODLE_ADD);
}
}
return true;
}
bool DoodleCommand::DoOrUndo(int cmd)
{
switch (cmd)
{
case DOODLE_ADD:
{
wxASSERT( m_segment != NULL );
if (m_segment)
m_doc->GetDoodleSegments().Append(m_segment);
m_segment = NULL;
m_doc->Modify(true);
m_doc->UpdateAllViews();
break;
}
case DOODLE_CUT:
{
wxASSERT( m_segment == NULL );
// Cut the last segment
if (m_doc->GetDoodleSegments().GetCount() > 0)
{
wxList::compatibility_iterator node = m_doc-
>GetDoodleSegments().GetLast();
m_segment = (DoodleSegment *)node->GetData();
m_doc->GetDoodleSegments().Erase(node);
m_doc->Modify(true);
m_doc->UpdateAllViews();
}
break;
}
}
return true;
}
/*
* DoodleView mediates between documents and windows
*/
class DoodleView: public wxView
{
DECLARE_DYNAMIC_CLASS(DoodleView)
DECLARE_EVENT_TABLE()
public:
DoodleView() { m_frame = NULL; }
~DoodleView() {};
/// Called when the document is created
virtual bool OnCreate(wxDocument *doc, long flags);
/// Called to draw the document
virtual void OnDraw(wxDC *dc);
/// Called when the view needs to be updated
virtual void OnUpdate(wxView *sender, wxObject *hint = NULL);
/// Called when the view is closed
virtual bool OnClose(bool deleteWindow = true);
/// Processes the cut command
void OnCut(wxCommandEvent& event);
private:
DoodleFrame*
};
IMPLEMENT_DYNAMIC_CLASS(DoodleView, wxView)
BEGIN_EVENT_TABLE(DoodleView, wxView)
EVT_MENU(DOODLE_CUT, DoodleView::OnCut)
END_EVENT_TABLE()
// What to do when a view is created.
bool DoodleView::OnCreate(wxDocument *doc, long WXUNUSED(flags))
{
// Associate the appropriate frame with this view.
m_frame = GetMainFrame();
SetFrame(m_frame);
m_frame->GetCanvas()->SetView(this);
// Make sure the document manager knows that this is the
// current view.
Activate(true);
// Initialize the edit menu Undo and Redo items
doc->GetCommandProcessor()->SetEditMenu(m_frame->GetEditMenu());
doc->GetCommandProcessor()->Initialize();
return true;
}
// This function is used for default print/preview
// as well as drawing on the screen.
void DoodleView::OnDraw(wxDC *dc)
{
dc->SetFont(*wxNORMAL_FONT);
dc->SetPen(*wxBLACK_PEN);
wxList::compatibility_iterator node = ((DoodleDocument
*)GetDocument())->GetDoodleSegments().GetFirst();
while (node)
{
DoodleSegment *seg = (DoodleSegment *)node->GetData();
seg->Draw(dc);
node = node->GetNext();
}
}
void DoodleView::OnUpdate(wxView *WXUNUSED(sender), wxObject
*WXUNUSED(hint))
{
if (m_frame && m_frame->GetCanvas())
m_frame->GetCanvas()->Refresh();
}
// Clean up windows used for displaying the view.
bool DoodleView::OnClose(bool WXUNUSED(deleteWindow))
{
if (!GetDocument()->Close())
return false;
// Clear the canvas
m_frame->GetCanvas()->ClearBackground();
m_frame->GetCanvas()->SetView(NULL);
if (m_frame)
m_frame->SetTitle(wxTheApp->GetAppName());
SetFrame(NULL);
// Tell the document manager to stop routing events to the view
Activate(false);
return true;
}
void DoodleView::OnCut(wxCommandEvent& WXUNUSED(event))
{
DoodleDocument *doc = (DoodleDocument *)GetDocument();
doc->GetCommandProcessor()->Submit(
new DoodleCommand(wxT(“Cut Last Segment”), DOODLE_CUT, doc,
NULL));
}
/*
* DoodleCanvas is the window that displays the doodle document
*/
class DoodleView;
class DoodleCanvas: public wxScrolledWindow
{
DECLARE_EVENT_TABLE()
public:
DoodleCanvas(wxWindow *parent, const wxPoint& pos,
const wxSize& size, const long style);
/// Draws the document contents
virtual void OnDraw(wxDC& dc);
/// Processes mouse events
void OnMouseEvent(wxMouseEvent& event);
/// Set/get view
void SetView(DoodleView* view) { m_view = view; }
DoodleView* GetView() const { return m_view; }
protected:
DoodleView *m_view;
};
/*
* Doodle canvas implementation
*/
BEGIN_EVENT_TABLE(DoodleCanvas, wxScrolledWindow)
EVT_MOUSE_EVENTS(DoodleCanvas::OnMouseEvent)
END_EVENT_TABLE()
// Define a constructor
DoodleCanvas::DoodleCanvas(wxWindow *parent, const wxPoint& pos,
const wxSize& size, const long style):
wxScrolledWindow(parent, wxID_ANY, pos, size, style)
{
m_view = NULL;
}
// Define the repainting behavior
void DoodleCanvas::OnDraw(wxDC& dc)
{
if (m_view)
m_view->OnDraw(& dc);
}
// This implements doodling behavior. Drag the mouse using
// the left button.
void DoodleCanvas::OnMouseEvent(wxMouseEvent& event)
{
// The last position
static int xpos = -1;
static int ypos = -1;
static DoodleSegment *currentSegment = NULL;
if (!m_view)
return;
wxClientDC dc(this);
DoPrepareDC(dc);
dc.SetPen(*wxBLACK_PEN);
// Take into account scrolling
wxPoint pt(event.GetLogicalPosition(dc));
if (currentSegment && event.LeftUp())
{
if (currentSegment->GetLines().GetCount() == 0)
{
delete currentSegment;
currentSegment = NULL;
}
else
{

    // We’ve got a valid segment on mouse left up, so store it.
DoodleDocument *doc = (DoodleDocument *) GetView()-
>GetDocument();
doc->GetCommandProcessor()->Submit(
new DoodleCommand(wxT(“Add Segment”), DOODLE_ADD, doc,
currentSegment));
GetView()->GetDocument()->Modify(true);
currentSegment = NULL;
}
}
if (xpos > -1 && ypos > -1 && event.Dragging())
{
if (!currentSegment)
currentSegment = new DoodleSegment;
DoodleLine *newLine = new DoodleLine;
newLine->m_x1 = xpos;
newLine->m_y1 = ypos;
newLine->m_x2 = pt.x;
newLine->m_y2 = pt.y;
currentSegment->GetLines().Append(newLine);
dc.DrawLine(xpos, ypos, pt.x, pt.y);
}
xpos = pt.x;
ypos = pt.y;
}

/*
* Declare an application class
*/
class DoodleApp: public wxApp
{
public:
DoodleApp();
/// Called on app initialization
virtual bool OnInit();
/// Called on app exit
virtual int OnExit();
private:
wxDocManager* m_docManager;
};
DECLARE_APP(DoodleApp)
IMPLEMENT_APP(DoodleApp)
DoodleApp::DoodleApp()
{
m_docManager = NULL;
}
bool DoodleApp::OnInit()
{
// Create a document manager
m_docManager = new wxDocManager;
// Create a template relating drawing documents to their views
(void) new wxDocTemplate(m_docManager, wxT(“Doodle”), wxT(“*.drw”),
wxT(“”), wxT(“drw”), wxT(“Doodle Doc”), wxT(“Doodle View”),
CLASSINFO(DoodleDocument), CLASSINFO(DoodleView));
// Register the drawing document type on Mac
#ifdef __WXMAC__
wxFileName::MacRegisterDefaultTypeAndCreator( wxT(“drw”) , ‘WXMB’ ,
‘WXMA’ ) ;
#endif
// If we have only got one window, we only get to edit
// one document at a time.
m_docManager->SetMaxDocsOpen(1);
// Create the main frame window
DoodleFrame* frame = new DoodleFrame(m_docManager, NULL, wxID_ANY,
wxT(“Doodle Sample”), wxPoint(0, 0), wxSize(500, 400),
wxDEFAULT_FRAME_STYLE);
frame->Centre(wxBOTH);
frame->Show(true);
SetTopWindow(frame);
return true;
}
int DoodleApp::OnExit()
{
delete m_docManager;
return 0;
}


//-----------------------------Doodle End-----------------------------//
/*
//-----------------------------My Frame Start-----------------------------//
class MyFrame : public wxFrame
{
public:
    MyFrame();
    ~MyFrame();
};

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Doc/View FrameWork", wxPoint(30, 30), wxSize(800, 600))
{
}

MyFrame::~MyFrame()
{
}

//-----------------------------My Frame End-----------------------------//

class MyApp : public wxApp
{
public:
    MyApp();
    ~MyApp();
    virtual bool OnInit();

private:
    MyFrame *m_frame = NULL;
};

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

bool MyApp::OnInit()
{
    m_frame = new MyFrame();
    m_frame->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);*/