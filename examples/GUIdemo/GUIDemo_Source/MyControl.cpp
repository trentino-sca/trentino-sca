#include "MyControl.h"

MyControl::MyControl(GWidget gw, std::list<GUIDemoLCD*> div) : Gui_Control(gw)
{
	_gptr = div;
}

void MyControl::handleSliderValChange(int val)
{
	for( std::list<GUIDemoLCD*>::iterator lcd_iter =  _gptr.begin(); lcd_iter != _gptr.end(); lcd_iter++)
	{
		GUIDemoLCD* lcd = *lcd_iter;
		lcd->showLCDNum(val);
	}
}

void MyControl::handleButtonPress(void)
{
	this->hideWidget();
}