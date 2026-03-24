

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


#if IS_X11
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef check
#undef check
#endif

#include <QtCore>
#include <QtGui>


#include "MyHQWidget.h"
#include "HQPrintDlg.h"




HQFloatLineEdit::HQFloatLineEdit(QWidget*p, bool only_positive):QLineEdit(p)

{
	current_text = QString("1");	
	positive = only_positive;
	connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(text_changed(const QString &))); 
}



HQFloatLineEdit::~HQFloatLineEdit()

{



}



float HQFloatLineEdit::float_value()

{
	return current_text.toFloat();
}



void HQFloatLineEdit::text_changed(const QString & new_string)

{
	bool can_convert;
	float value = new_string.toFloat(&can_convert); 

	if(can_convert || !new_string.compare(QString(""))) {

		if(positive && (value<0.0f)){
			setText(current_text);
			return;
		}

		current_text = new_string;
		emit value_changed();
	}else
		setText(current_text);
}





HQIntLineEdit::HQIntLineEdit(QWidget*p, int in_min, int in_max):QLineEdit(p)

{
	current_text = QString("1");	
	min=in_min;
	max=in_max;
	connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(text_changed(const QString &))); 
}



HQIntLineEdit::~HQIntLineEdit()

{



}



float HQIntLineEdit::int_value()

{
	return current_text.toInt();
}



void HQIntLineEdit::text_changed(const QString & new_string)

{
	bool can_convert;
	float value = new_string.toInt(&can_convert); 

	if(can_convert || !new_string.compare(QString(""))) {

		if(can_convert && (value<min||value>max)){
			setText(current_text);
			return;
		}

		current_text = new_string;
		emit value_changed();
	}else
		setText(current_text);
}





HQPageWidget::HQPageWidget(QWidget*p):QFrame(p)

{
	max_dimension=128;
	paper_width=8.5f;
	paper_height=11.0f;
	left_margin=1.0f;
	right_margin=1.0f;
	top_margin=1.0f;
	bottom_margin=1.0f;
}





HQPageWidget::~HQPageWidget()

{



}



void HQPageWidget::paintEvent(QPaintEvent * e)

{
	int x, y, w, h, offset;

	rect().getRect(&x,&y,&w,&h); 

	offset = (int)((float)w*0.1f);

	QPainter p(this);
	p.fillRect(x+offset, y+offset, w-offset, h-offset, QColor(96,96,96));

	int x1, y1, w1, h1;
	x1 = x;
	y1 = y;
	w1 = w-offset;
	h1 = h-offset;

	p.fillRect(x1,y1,w1,h1, QColor(255,255,255));
	p.setPen(Qt::black);
	p.drawRect(x1,y1,w1,h1);
	p.setPen(Qt::DotLine);
	p.setBrush(Qt::Dense6Pattern); 

	float l,r,t,b;
	l = left_margin/paper_width;
	t = top_margin/paper_height;
	r = (paper_width-right_margin)/paper_width;
	b = (paper_height-bottom_margin)/paper_height;
	if(l<0.0) l=0.0f;
	if(t<0.0) t=0.0f;
	if(r<0.0) r=0.0f;
	if(b<0.0) b=0.0f;
	if(l>paper_width) l=paper_width;
	if(t>paper_height) t=paper_height;
	if(r>paper_width) r=paper_width;
	if(b>paper_height) b=paper_height;
	if(l>r) l=r; 
	if(t>b) t=b; 
	int x2,y2,w2,h2;
	x2 = x1 + (int)(w1*l);
	y2 = y1 + (int)(h1*t);
	w2 = -x2 + (int)(w1*r);
	h2 = -y2 + (int)(h1*b);
	p.setClipRect(x1+1,y1+1,w1-2,h1-2);
	p.fillRect(x2,y2,w2,h2, QColor(255,255,255));
	p.drawRect(x2,y2,w2,h2);

}





void HQPageWidget::showEvent(QShowEvent * e)

{
	if(paper_width>paper_height){
		setMinimumWidth((int)max_dimension);
		setMinimumHeight((int)((paper_height/paper_width) * max_dimension));
	}else{
		setMinimumWidth((int)((paper_width/paper_height) * max_dimension));
		setMinimumHeight((int)max_dimension);
	}

}



void HQPageWidget::SetMaxDimension(int size)

{
	max_dimension=size;
	showEvent(0);
	update();
}



void HQPageWidget::SetPaperSize(float width, float height)

{
	paper_width=width;
	paper_height=height;
	showEvent(0);
	update();
}



void HQPageWidget::SetMargin(float left, float right, float top, float bottom)

{
	left_margin=left;
	right_margin=right;
	top_margin=top;
	bottom_margin=bottom;
	showEvent(0);
	update();
}





HQPageSetupDialog::HQPageSetupDialog(QWidget*p):QWidget(p)

{
	QGridLayout* top_layout = new QGridLayout;
		
		page_widget = new HQPageWidget(this);

		QGroupBox * paper_box = new QGroupBox("Paper Size");
			QGridLayout* paper_box_layout = new QGridLayout;

			QLabel * width_label = new QLabel;
			width_label->setText("Paper Width");
			paper_width = new HQFloatLineEdit(paper_box,true);
			paper_width->insert(QString::number(page_widget->paper_width));
			connect(paper_width, SIGNAL(value_changed()), this, SLOT(size_changed())); 

			QLabel * height_label = new QLabel;
			height_label->setText("Paper Height");
			paper_height = new HQFloatLineEdit(paper_box,true);
			paper_height->insert(QString::number(page_widget->paper_height));
			connect(paper_height, SIGNAL(value_changed()), this, SLOT(size_changed())); 
			
			paper_box_layout->addWidget(width_label, 0, 0);
			paper_box_layout->addWidget(paper_width, 0, 1);
			paper_box_layout->addWidget(height_label, 1, 0);
			paper_box_layout->addWidget(paper_height, 1, 1);
		paper_box->setLayout(paper_box_layout);

		QGroupBox* orientation_box = new QGroupBox(tr("Page Orientation"));
			QVBoxLayout* orientation_layout = new QVBoxLayout;

			orientation = new QButtonGroup(orientation_layout);
			orientation->setExclusive(true);
			orientation_portrait = new QRadioButton("Portrait");
			orientation_landscape = new QRadioButton("Landscape");
			orientation_portrait->setChecked(true);
			connect(orientation, SIGNAL(pressed(int)), this, SLOT(orientation_changed(int))); 
			orientation->addButton(orientation_portrait);
			orientation->addButton(orientation_landscape);

			orientation_layout->addWidget(orientation_portrait);
			orientation_layout->addWidget(orientation_landscape);
		orientation_box->setLayout(orientation_layout);

		// "Page Margin" group box
		QGroupBox * margin_box = new QGroupBox("Page Margin");
			QGridLayout * margin_grid = new QGridLayout; 


			QLabel * left_label = new QLabel;
			left_label->setText("Left");
			margin_left = new HQFloatLineEdit(this);
			margin_left->insert(QString::number(page_widget->left_margin));
			margin_left->setEnabled(true);
			connect(margin_left, SIGNAL(value_changed()), this, SLOT(margins_changed())); 

			QLabel * right_label = new QLabel;
			right_label->setText("Right");
			margin_right = new HQFloatLineEdit(this);
			margin_right->insert(QString::number(page_widget->right_margin));
			margin_right->setEnabled(true);
			connect(margin_right, SIGNAL(value_changed()), this, SLOT(margins_changed())); 

			QLabel * top_label = new QLabel;
			top_label->setText("Top");
			margin_top = new HQFloatLineEdit(this);
			margin_top->insert(QString::number(page_widget->top_margin));
			margin_top->setEnabled(true);
			connect(margin_top, SIGNAL(value_changed()), this, SLOT(margins_changed())); 

			QLabel * bottom_label = new QLabel;
			bottom_label->setText("Bottom");
			margin_bottom = new HQFloatLineEdit(this);
			margin_bottom->insert(QString::number(page_widget->bottom_margin));
			margin_bottom->setEnabled(true);
			connect(margin_bottom, SIGNAL(value_changed()), this, SLOT(margins_changed())); 

			margin_grid->addWidget(left_label, 0, 0);
			margin_grid->addWidget(margin_left, 0, 1);
			margin_grid->addWidget(right_label, 0, 2);
			margin_grid->addWidget(margin_right, 0, 3);
			margin_grid->addWidget(top_label, 1, 0);
			margin_grid->addWidget(margin_top, 1, 1);
			margin_grid->addWidget(bottom_label, 1, 2);
			margin_grid->addWidget(margin_bottom, 1, 3);

		margin_box->setLayout(margin_grid);


		top_layout->addWidget(page_widget, 0, 1);
		top_layout->addWidget(paper_box, 1, 0, 1, 3);
		top_layout->addWidget(orientation_box, 2, 0, 1, 1);
		top_layout->addWidget(margin_box, 2, 1, 1, 2);
	setLayout(top_layout);



}



HQPageSetupDialog::~HQPageSetupDialog()

{



}



void HQPageSetupDialog::orientation_changed(int id)

{

	size_changed();
}



void HQPageSetupDialog::margins_changed()

{
	page_widget->SetMargin(
		margin_left->float_value(),
		margin_right->float_value(),
		margin_top->float_value(),
		margin_bottom->float_value());
}



void HQPageSetupDialog::size_changed()

{

	if(orientation_landscape->isChecked()) 
		page_widget->SetPaperSize(paper_height->float_value(), paper_width->float_value());
	else
		page_widget->SetPaperSize(paper_width->float_value(), paper_height->float_value());
}





void HQPageSetupDialog::showEvent(QShowEvent * e)

{

	paper_width->setText(paper_width->text().toLatin1());
	paper_height->setText(paper_height->text().toLatin1());


	margin_left->setText(margin_left->text().toLatin1());
	margin_right->setText(margin_right->text().toLatin1());
	margin_top->setText(margin_top->text().toLatin1());
	margin_bottom->setText(margin_bottom->text().toLatin1());


}



void HQPageSetupDialog::ok_clicked()

{
	hide();
}



void HQPageSetupDialog::cancel_clicked()

{
	hide();
}



void HQPageSetupDialog::printer_clicked()

{
	QMessageBox::information( this,"Unavailable", "This feature is unavailable at this time.");
}









HQPrintDlg::HQPrintDlg(QWidget*p):QDialog(p)

{
	//just to make sure it's at it's minimum size
	setMaximumWidth(100);

	// "Printer" group box
	QGroupBox* printer_box = new QGroupBox(tr("Printer"));
	QGridLayout* printer_type_box_layout = new QGridLayout;
		QLabel * type_label = new QLabel;
		type_label->setText("Type");

		printer_type_queue = new QRadioButton("Queue");
		printer_type_file = new QRadioButton("File");
		connect(printer_type_queue, SIGNAL(released()), this, SLOT(type_queue())); 
		connect(printer_type_file, SIGNAL(released()), this, SLOT(type_file())); 
		#ifdef WINDOWS_SYSTEM
			printer_type_queue->setEnabled (false);
		#endif

		QLabel * queue_label = new QLabel;
		queue_label->setText("Queue");
		printer_queue = new QLineEdit;
		printer_queue->setMinimumWidth(200);

		QLabel * file_label = new QLabel;
		file_label->setText("File");
		printer_file = new QLineEdit;
		printer_file->setMinimumWidth(200);
		file_button = new QPushButton("File Chooser");
		connect(file_button, SIGNAL(pressed()), this, SLOT(select_file())); 


		printer_type_box_layout->addWidget(type_label, 0, 0);
		printer_type_box_layout->addWidget(printer_type_queue, 0, 1);
		printer_type_box_layout->addWidget(printer_type_file, 0, 2);
		printer_type_box_layout->addWidget(queue_label, 1, 0);
		printer_type_box_layout->addWidget(printer_queue, 1, 1);
		printer_type_box_layout->addWidget(file_label, 2, 0);
		printer_type_box_layout->addWidget(printer_file, 2, 1);
		printer_type_box_layout->addWidget(file_button, 2, 2);
	printer_box->setLayout(printer_type_box_layout);

	// "Page" group box
	QGroupBox * g_box = new QGroupBox("Page");
	QVBoxLayout * g_box_layout = new QVBoxLayout;
		page_setup_dialog = new HQPageSetupDialog(g_box);
		g_box_layout->addWidget(page_setup_dialog);
	g_box->setLayout(g_box_layout);


	QGroupBox * print_setup_box = new QGroupBox(tr("Options"));
		QVBoxLayout* print_setup_box_layout = new QVBoxLayout;
		setup_print_color = new QCheckBox("Color", print_setup_box);
		setup_print_draft = new QCheckBox("Draft", print_setup_box);
		print_setup_box_layout->addWidget(setup_print_color);
		print_setup_box_layout->addWidget(setup_print_draft);
	print_setup_box->setLayout(print_setup_box_layout);


	QWidget * bottom_box = new QWidget(this);
		QHBoxLayout* bottom_box_layout = new QHBoxLayout;

		
		bottom_box_layout->setSpacing(5);
		QPushButton * ok_button = new QPushButton("Ok", bottom_box);
		connect(ok_button, SIGNAL(clicked()), this, SLOT(ok_clicked())); 
		QPushButton * cancel_button = new QPushButton("Cancel", bottom_box);
		connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancel_clicked())); 
		ok_button->setFixedWidth(64);
		cancel_button->setFixedWidth(64);

		bottom_box_layout->addWidget(ok_button);
		bottom_box_layout->addWidget(cancel_button);
	bottom_box->setLayout(bottom_box_layout);


	QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addWidget(printer_box);
	main_layout->addWidget(g_box);
	main_layout->addWidget(print_setup_box);
	main_layout->addWidget(bottom_box);

	setLayout(main_layout);

}



HQPrintDlg::~HQPrintDlg()

{



}



void HQPrintDlg::PrintFor(MyHQWidget * mw) 

{
	main_widget = mw;	
	show();
}



void HQPrintDlg::showEvent(QShowEvent * e)

{
}



void HQPrintDlg::select_file()

{

	QString s = QFileDialog::getSaveFileName( this, "caption", ".", "Postscript File(*.ps)" ); 

	if(!s.isNull() && !s.toLatin1().isNull()) {
		printer_file->setText(s.toLatin1());
	}
}



void HQPrintDlg::type_file()

{
	printer_type_queue->setChecked(false);
	printer_type_file->setChecked(true);
	printer_queue->setEnabled(false);
	printer_file->setEnabled(true);
	file_button->setEnabled(true);
}



void HQPrintDlg::type_queue()

{
	printer_type_queue->setChecked(true);
	printer_type_file->setChecked(false);
	printer_queue->setEnabled(true);
	printer_file->setEnabled(false);
	file_button->setEnabled(false);
}



void HQPrintDlg::ok_clicked()

{




    char tmp_file_base[32];
    
    char tmp_filename[8192];
    char whole_tmp_filename[8192];



    sprintf(tmp_file_base,"%lu", (unsigned long)time(0));

#if defined(IS_X11) || defined(IS_OSX)
    char cwd[8192]; 
    getcwd(cwd,9192);
    sprintf(tmp_filename,"%s.ps",tmp_file_base);
    sprintf(whole_tmp_filename,"%s/%s",cwd,tmp_filename);
#else   
    sprintf(tmp_filename,"%s.ps",tmp_file_base);
    sprintf(whole_tmp_filename,"%s",tmp_filename);
#endif


    bool file_printing = printer_type_file->isChecked();

    main_widget->OnPrintPage(tmp_filename);

    if(file_printing){

	    char rename_cmd[4096];
#if defined(IS_X11) || defined(IS_OSX)
		sprintf(rename_cmd, "mv %s %s", QDir::convertSeparators(whole_tmp_filename).toLatin1().data(), 
			QDir::convertSeparators(printer_file->text()).toLatin1().data());
#else
		sprintf(rename_cmd, "copy /y %s %s", QDir::convertSeparators(whole_tmp_filename).toLatin1().data(), 
			QDir::convertSeparators(printer_file->text()).toLatin1().data());
#endif
	    bool failed = system(rename_cmd);

	    if(failed)
		    QMessageBox::information( this, "Print Failed" , "Printing has failed");

    }else{

	    const char * arg1 = printer_queue->text().toLatin1();
	    const char * arg2 = whole_tmp_filename;

	    if(!arg1 || !arg2 || !strcmp("",arg1)){
		    QMessageBox::information( this, "Print Failed" , "Printing has failed");
	    }else{

			char print_cmd[4096];


#if defined(IS_X11) || defined(IS_OSX)
			sprintf(print_cmd, "%s %s", arg1, arg2);
#else
			sprintf(print_cmd, "copy %s %s", arg2, arg1);
#endif

			bool failed = system(print_cmd);

			if(failed)
				QMessageBox::information( this, "Print Failed" , "Printing has failed");
		    		
	    }
    }

    char delete_cmd[4096];

#if defined(IS_X11) || defined(IS_OSX)
    sprintf(delete_cmd, "rm %s", whole_tmp_filename);
#else
    sprintf(delete_cmd, "del %s", whole_tmp_filename);
#endif
    system(delete_cmd);

    hide();
}



void HQPrintDlg::cancel_clicked()

{
	hide();
}







