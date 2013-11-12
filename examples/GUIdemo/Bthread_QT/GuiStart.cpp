#include "GuiStart.h"

#include "GuiLCD.h"
#include "GuiSlider.h"

#include "bthread_qt.h"

#include <iostream>

static ThreadedApplication *_app;

// Functions
void *startGuiThreaded(void)
{
	if (_app == NULL)
	{
		_app = new ThreadedApplication();
		boost::thread appThread(boost::ref(*_app));
		_app->waitForApplicationRun();
	}

	return (void *) _app;
}

void showWidget(void *app, Gui_Control *gc)
{
	((ThreadedApplication*)app)->showMyWidget(gc->getType(), gc);
}

void stopGuiThreaded(void *app)
{
	((ThreadedApplication*)app)->stop();
}


// Gui_Control
/*!
 * \brief
 * Constructs Gui_Control
 * 
 * \param gw
 * Type of widget
 * 
  */
Gui_Control::Gui_Control(GWidget gw)
{
	_type = gw;
}

Gui_Control::~Gui_Control()
{
	// control killed
}

/*!
 * \brief
 * Return type of controled widget
 * 
 * \returns
 * Return type of controled widget
 * 
 */
GWidget Gui_Control::getType(void)
{
	return _type;
}

/*!
 * \brief
 * Sets pointer to controlled widget
 * 
 * \param ptr_wid
 * pointer to the controlled widget
 *
 */
void Gui_Control::setControlledWidget(void *ptr_wid)
{
	_ptr_wid = ptr_wid;
}

/*!
 * \brief
 * Sets LCD value if controlled widget supports it
 * 
 * \param val
 * Value to be set
 * 
 * \returns
 * 0 - no error; 1 - not supported
 * 
 */
int Gui_Control::setLCDVal(int val)
{
	if (_type == GWidget::GLCD)
		((GuiLCD*) _ptr_wid)->changeLCDval(val);
	else
		return 1;

	return 0;
}

/*!
 * \brief
 * Sets range for slider if widget supports it
 * 
 * \param min
 * min value of slider to be set
 * 
 * \param max
 * max value of slider to be set
 * 
 * \returns
 * 0 - no error; 1 - not supported
 * 
 */
int Gui_Control::setSliderRange(int min, int max)
{
	if (_type == GWidget::GSLIDER)
		((GuiSlider*) _ptr_wid)->changeSliderRange(min, max);
	else
		return 1;

	return 0;
}

/*!
 * \brief
 * Sets window title of controlled widget
 * 
 * \param name
 * Window title to be set
 * 
 */
int Gui_Control::setWindowTitle(std::string name)
{
	((GuiWidget *) _ptr_wid)->changeWindowTitle(name);

	return 0;
}

int Gui_Control::hideWidget(void)
{
	((GuiWidget *) _ptr_wid)->hideWidget();

	return 0;
}

/*!
 * \brief
 * Handles change of slider value
 * 
 * \param val
 * Slider value
 * 
 */
void Gui_Control::handleSliderValChange(int val)
{
	std::cout << "val of slider is: " << val << std::endl;
}

/*!
 * \brief
 * Handles button press
 * 
 */
void Gui_Control::handleButtonPress(void)
{
	std::cout << "button pressed" << std::endl;
	this->hideWidget();
}
