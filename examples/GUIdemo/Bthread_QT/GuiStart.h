#ifndef GUISTART_H
#define GUISTART_H

#include <iostream>

__declspec(dllexport) enum GWidget{GSLIDER, GLCD};

/*!
 * \brief
 * Class to control Widgets
 * 
  * 
 * \remarks
 * Write remarks for Gui_Control here.
 * 
  */
class __declspec(dllexport) Gui_Control
{

public:
	Gui_Control(GWidget gw);
	~Gui_Control();	

	// initiation
	GWidget getType(void);
	void setControlledWidget(void *ptr_wid);

	// setters
	int setLCDVal(int val);
	int setSliderRange(int min, int max);
	int setWindowTitle(std::string name);
	int hideWidget(void);

	// handlers
	virtual void handleSliderValChange(int val);
	virtual void handleButtonPress(void);
	
private:
	void *_ptr_wid;
	GWidget _type;

};

void __declspec(dllexport) *startGuiThreaded(void);
void __declspec(dllexport) stopGuiThreaded(void *app);
void __declspec(dllexport) showWidget(void *app, Gui_Control *gc);


#endif //GUISTART_H