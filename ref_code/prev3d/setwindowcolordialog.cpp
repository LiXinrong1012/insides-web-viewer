#include "setwindowcolordialog.h"
#include "ui_setwindowcolordialog.h"
#include "HBaseView.h"

#include <QColorDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>

SetWindowColorDialog::SetWindowColorDialog(QWidget*p,  HBaseView * pBaseView)
	:QDialog(p,0)

{
	ui = new Ui::SetWindowColorDialog();
	ui->setupUi(this);

	_baseView = pBaseView;	

	// "Window Background Color" group box
	QGroupBox * top_box = new QGroupBox("Window Background Color");
	QGridLayout * margin_grid = new QGridLayout; 



	_color1Frame = new QFrame(top_box);
	_color1Frame->setAutoFillBackground(true);
	_color1Frame->setFixedSize(64,32);
	_color1Frame->setFrameStyle(QFrame::Box|QFrame::Plain);
	QPushButton * top_color_button = new QPushButton("Top Color");
	top_color_button->setMinimumWidth(96);
	connect(top_color_button, SIGNAL(clicked()), this, SLOT(chooseWindowTopColor())); 


	_color2Frame = new QFrame(top_box);
	_color2Frame->setAutoFillBackground(true);
	_color2Frame->setFixedSize(64,32);
	_color2Frame->setFrameStyle(QFrame::Box|QFrame::Plain);
	QPushButton * bottom_color_button = new QPushButton("Bottom Color");
	connect(bottom_color_button, SIGNAL(clicked()), this, SLOT(chooseWindowBottomColor())); 
	bottom_color_button->setMinimumWidth(96);

	margin_grid->addWidget(_color1Frame, 0, 0);
	margin_grid->addWidget(top_color_button, 0, 1);
	margin_grid->addWidget(_color2Frame, 1, 0);
	margin_grid->addWidget(bottom_color_button, 1, 1);

	top_box->setLayout(margin_grid);

	// The two buttons at the bottom of the dialog
	QWidget* buttons = new QWidget;
	QHBoxLayout* button_layout = new QHBoxLayout;

	QPushButton* ok_button = new QPushButton("OK");
	connect(ok_button, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
	ok_button->setEnabled(true);

	QPushButton* cancel_button = new QPushButton("Cancel");
	connect(cancel_button, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
	cancel_button->setEnabled(true);

	button_layout->addWidget(ok_button);
	button_layout->addWidget(cancel_button);
	buttons->setLayout(button_layout);

	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->addWidget(top_box);
	main_layout->addWidget(buttons);
	setLayout(main_layout);
	this->setFixedSize(0,0);
}

SetWindowColorDialog::~SetWindowColorDialog()
{
	delete ui;
}

void SetWindowColorDialog::showEvent(QShowEvent * e)
{
	HPoint window_top_color;
	HPoint window_bottom_color;
	_baseView->GetWindowColor( window_top_color, window_bottom_color );
	_topColor.setRgb( (int)(window_top_color.x * 255), (int)(window_top_color.y * 255), (int)(window_top_color.z * 255) );
	_bottomColor.setRgb( (int)(window_bottom_color.x * 255),(int)(window_bottom_color.y * 255), (int)(window_bottom_color.z * 255) );

	QPalette pal1 = _color1Frame->palette();
	pal1.setColor(QPalette::Background, _topColor);
	_color1Frame->setPalette(pal1);

	QPalette pal2 = _color2Frame->palette();
	pal2.setColor(QPalette::Background, _bottomColor);
	_color2Frame->setPalette(pal2);


}

void SetWindowColorDialog::onOkBtnClicked()
{
	HPoint window_top_color;
	HPoint window_bottom_color;

	window_top_color.x = _topColor.red()/255.0;
	window_top_color.y = _topColor.green()/255.0;
	window_top_color.z = _topColor.blue()/255.0;

	window_bottom_color.x = _bottomColor.red()/255.0;
	window_bottom_color.y = _bottomColor.green()/255.0;
	window_bottom_color.z = _bottomColor.blue()/255.0;

	_baseView->SetWindowColor( window_top_color, window_bottom_color );
	_baseView->Update();

	hide();
}

void SetWindowColorDialog::onCancelBtnClicked()
{
	hide();
}


void SetWindowColorDialog::chooseWindowTopColor()
{
	QColor c = QColorDialog::getColor(_topColor,this);
	if(c.isValid()) _topColor = c;
	QPalette p = _color1Frame->palette();
	p.setColor(QPalette::Background, _topColor);
	_color1Frame->setPalette(p);
}

void SetWindowColorDialog::chooseWindowBottomColor()
{
	QColor c = QColorDialog::getColor(_bottomColor,this);
	if(c.isValid()) _bottomColor = c;
	QPalette p = _color2Frame->palette();
	p.setColor(QPalette::Background, _bottomColor);
	_color2Frame->setPalette(p);
}
