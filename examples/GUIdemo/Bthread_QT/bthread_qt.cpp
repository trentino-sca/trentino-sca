#include <boost/thread/locks.hpp>

#include "GuiSlider.h"
#include "GuiLCD.h"
#include "bthread_qt.h"
 
int Application::staticArgc = 1;
char Application::staticDummy[] = "QtLibApplication";
char *Application::staticArgv[2] = { staticDummy, nullptr };
 
void DialogProvider::customEvent(QEvent *event)
{
  if (!_qtApp)
    return;
 
  if (event->type() == _qtApp->showMyWidgetEventType())
  {
    ShowWaitDialogEvent *ev = static_cast< ShowWaitDialogEvent * >(event);

	QWidget *myWidget = NULL;

	if (ev->gw() == GWidget::GSLIDER)
		myWidget = new GuiSlider(0, ev->gc());
	else
		myWidget = new GuiLCD(0, ev->gc());
    myWidget->setAttribute(Qt::WA_DeleteOnClose);
    myWidget->show();
  }
 
  QObject::customEvent(event);
  signalEventProcessed();
}
 
Application::Application() :
  QApplication(staticArgc,staticArgv),
  _dpInstance(nullptr),
  _showMyWidgetEventType(static_cast< QEvent::Type >(QEvent::registerEventType()))
{
  setQuitOnLastWindowClosed(false);
}
 
DialogProvider *Application::dpInstance()
{
  if (!_dpInstance)
    _dpInstance = createDialogProvider(this);
 
  return _dpInstance;
}