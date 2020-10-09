#include "main.h"
#include "absolute.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {

    Absolute *absolute2 = new Absolute("Absolute");
    absolute2->Show(true);

    return true;
}