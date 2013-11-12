#ifndef GUISLIDER_H
#define GUISLIDER_H

#include "QtGui\qslider.h"

#include "GuiWidget.h"
#include "GuiStart.h"

class GuiSlider : public GuiWidget
{
	Q_OBJECT

public:
	GuiSlider(QWidget *parent = 0, Gui_Control *gc = 0);

	void changeSliderRange(int min, int max);

public slots:
	void valueChanged(int val);
	
private:
	QSlider *slider;

};

#endif //GUISLIDER_H