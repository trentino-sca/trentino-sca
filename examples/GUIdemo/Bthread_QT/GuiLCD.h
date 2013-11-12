#ifndef GUILCD_H
#define GUILCD_H

#include "QtGui\qlcdnumber.h"

#include "GuiWidget.h"
#include "GuiStart.h"

class GuiLCD : public GuiWidget
{
	Q_OBJECT

public:
	GuiLCD(QWidget *parent = 0, Gui_Control *gc = 0);

	void changeLCDval(int val);

signals:
	void valueChanged(int val);
};

#endif //GUILCD_H