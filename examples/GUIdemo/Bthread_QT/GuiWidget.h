#ifndef GUIWIDGET_H
#define GUIWIDGET_H

#include <QtGui/QApplication>
#include <QFont>
#include <QtGui/QGridLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

#include "GuiStart.h"

class GuiWidget : public QWidget
{
	Q_OBJECT

public:
    GuiWidget(QWidget *parent = 0, Gui_Control *gc = 0);

	Gui_Control *getGC(void);

	void changeWindowTitle(std::string title);
	void hideWidget(void);

public slots:
	void mega_super_Exit();
	
signals:
	void signChangeTitle(QString);
	void signHideWidget(void);

private:
	Gui_Control *_gc;

};

#endif //GUIWIDGET_H