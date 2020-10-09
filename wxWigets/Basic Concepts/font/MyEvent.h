//-----------------My Event Start-----------------------//
class MyEvent: public wxEvent
{
   public:
      MyEvent(wxWindow* win = (wxWindow*) NULL);
      wxEvent* Clone() const {return new MyEvent(*this);}

	DECLARE_DYNAMIC_CLASS( MyEvent )
};

typedef void (wxEvtHandler::*myEventFunction)(MyEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( myEVT_MYEVENT, 1 )
END_DECLARE_EVENT_TYPES()


#define EVT_MYEVENT(func)                              \
	DECLARE_EVENT_TABLE_ENTRY( myEVT_MYEVENT,      \\
		-1,                                    \\
		-1,                                    \\
		(wxObjectEventFunction)                \\
		(myEventFunction) & func,              \\
		(wxObject *) NULL ),
// End of MyEvent.h

//---------------------My Event End-------------------------//