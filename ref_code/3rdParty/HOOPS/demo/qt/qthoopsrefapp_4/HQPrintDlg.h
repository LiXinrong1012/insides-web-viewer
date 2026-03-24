

#ifndef HQPRINTDLG_H

#define HQPRINTDLG_H





#include <QFrame>
#include <QButtonGroup>
#include <QDialog>

#include <QLineEdit>



class MyHQWidget;

class QVButtonGroup;

class QRadioButton;

class QCheckBox;



class HQFloatLineEdit: public QLineEdit {

    Q_OBJECT

	public:

	HQFloatLineEdit(QWidget*p, bool only_positive=false);
	virtual ~HQFloatLineEdit();
	float float_value();

	public slots:
	void text_changed(const QString &);

	signals:
	void value_changed(); 

	private:

	QString current_text;
	bool positive;

};



class HQIntLineEdit: public QLineEdit {

    Q_OBJECT

	public:
	HQIntLineEdit(QWidget*p, int min=0, int max=65535);
	virtual ~HQIntLineEdit();
	float int_value();

	public slots:
	void text_changed(const QString &);

	signals:

	void value_changed(); 

	private:
	QString current_text;
	int min, max;

};





class HQPageWidget: public QFrame {

    Q_OBJECT

	public:
	HQPageWidget(QWidget*p);
	virtual ~HQPageWidget();

	void SetMaxDimension(int size); 
	void SetPaperSize(float width, float height);
	void SetMargin(float left, float right, float top, float bottom);

	int max_dimension;
	float paper_width;
	float paper_height;
	float left_margin;
	float right_margin;
	float top_margin;
	float bottom_margin;

	protected:
	void showEvent(QShowEvent * e);
	void paintEvent(QPaintEvent * e);

};



class HQPageSetupDialog : public QWidget {

    Q_OBJECT

	public:
	HQPageSetupDialog(QWidget*p);
	virtual ~HQPageSetupDialog();

	public slots:
	void orientation_changed(int);
	void margins_changed();
	void size_changed();
	void ok_clicked();
	void cancel_clicked();
	void printer_clicked();

	protected:
	void showEvent(QShowEvent * e);

	private:
	HQPageWidget * page_widget;
	QButtonGroup * orientation;
	QRadioButton * orientation_portrait;
	QRadioButton * orientation_landscape;

	HQFloatLineEdit * paper_width;
	HQFloatLineEdit * paper_height;

	HQFloatLineEdit * margin_left;
	HQFloatLineEdit * margin_right;
	HQFloatLineEdit * margin_top;
	HQFloatLineEdit * margin_bottom;

};



class HQPrintDlg : public QDialog {

    Q_OBJECT

	public:
	HQPrintDlg(QWidget*p);
	virtual ~HQPrintDlg();

	void PrintFor(MyHQWidget*mw);

	public slots:
	void select_file();
	void type_file();
	void type_queue();
	void ok_clicked();
	void cancel_clicked();

	protected:
	void showEvent(QShowEvent * e);

	private:
	MyHQWidget * main_widget;

	QRadioButton * printer_type_queue;
	QRadioButton * printer_type_file;
	QLineEdit * printer_queue;
	QLineEdit * printer_file;
	QPushButton * file_button;

	QCheckBox * setup_print_color;
	QCheckBox * setup_print_draft;

	HQPageSetupDialog * page_setup_dialog;

};



#endif













