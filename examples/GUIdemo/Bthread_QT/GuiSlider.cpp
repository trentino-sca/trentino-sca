#include "GuiSlider.h"

GuiSlider::GuiSlider(QWidget *parent, Gui_Control *gc) : GuiWidget(parent, gc)
{
	QFont butFont("Times", 18, QFont::Bold);

    QPushButton *quit = new QPushButton(tr("Quit"), this);
    quit->setFont(butFont);

	QGridLayout *grid = new QGridLayout;
    
	slider = new QSlider;

	grid->addWidget(slider);

    QWidget *lcdRanges = new QWidget;
    lcdRanges->setLayout(grid);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(quit);
    layout->addWidget(lcdRanges);

    this->setLayout(layout);

	this->resize(200, 200);

	connect(quit, SIGNAL(clicked()), this, SLOT(mega_super_Exit()));
	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
}

void GuiSlider::changeSliderRange(int min, int max)
{
	slider->setRange(min, max);
}

void GuiSlider::valueChanged(int val)
{
	getGC()->handleSliderValChange(val);
}