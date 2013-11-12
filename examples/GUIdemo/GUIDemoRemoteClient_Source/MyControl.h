#ifndef MYCONTROLH
#define MYCONTROLH

#include <list>

#include "services/TrentinoExampleGUIDemoLCD.h"	
#include "..\GUIDemoRemoteClient_Source\GuiStart.h"

using namespace Trentino::Example::GUIDemo;

class MyControl  : public Gui_Control
{
public:
	MyControl(GWidget gw, std::list<GUIDemoLCD*> div);
	void handleSliderValChange(int val);
	void handleButtonPress(void);

private:
	std::list<GUIDemoLCD*> _gptr;
};

#endif //MYCONTROLH