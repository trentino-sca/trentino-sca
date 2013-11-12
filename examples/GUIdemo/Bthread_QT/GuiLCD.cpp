#include "GuiLCD.h"

GuiLCD::GuiLCD(QWidget *parent, Gui_Control *gc) : GuiWidget(parent, gc)
{
	QFont butFont("Times", 18, QFont::Bold);
	QPushButton *quit = new QPushButton(tr("Quit"), this);
    quit->setFont(butFont);

	QLCDNumber *lcd = new QLCDNumber;

	QGridLayout *grid = new QGridLayout;
    grid->addWidget(lcd);

    QWidget *lcdRanges = new QWidget;
    lcdRanges->setLayout(grid);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(quit);
    layout->addWidget(lcdRanges);

    this->setLayout(layout);

	this->resize(400, 200);

	connect(this, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
	connect(quit, SIGNAL(clicked()), this, SLOT(mega_super_Exit()));
}

void GuiLCD::changeLCDval(int val)
{
	emit valueChanged(val);
}