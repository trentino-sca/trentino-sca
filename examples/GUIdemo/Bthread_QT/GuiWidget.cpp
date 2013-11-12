#include "GuiWidget.h"

GuiWidget::GuiWidget(QWidget *parent, Gui_Control *gc)
    :QWidget(parent)
{
	_gc = gc;
	_gc->setControlledWidget(this);

	connect(this, SIGNAL(signChangeTitle(QString)), this, SLOT(setWindowTitle(QString)));
	connect(this, SIGNAL(signHideWidget(void)), this, SLOT(hide()));
}

Gui_Control *GuiWidget::getGC(void)
{
	return _gc;
}

void GuiWidget::mega_super_Exit()
{
	_gc->handleButtonPress();
}

void GuiWidget::changeWindowTitle(std::string name)
{
	emit signChangeTitle(QString::fromStdString(name));
}

void GuiWidget::hideWidget(void)
{
	emit signHideWidget();
}