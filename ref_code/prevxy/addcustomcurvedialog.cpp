#include "addcustomcurvedialog.h"
#include "ui_addcustomcurvedialog.h"

#include <QMessageBox>



AddCustomCurveDialog::AddCustomCurveDialog(QWidget *parent)
	: QDialog(parent)
	,_isAddMode(true)
	,_isUse(false)
{
	ui = new Ui::AddCustomCurveDialog();
	ui->setupUi(this);

//	connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(onAdd()));
	connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(onBtnAddClicked()));
}
 
AddCustomCurveDialog::~AddCustomCurveDialog()
{
	delete ui;
}

void AddCustomCurveDialog::onAddBtnClicked()
{
	//QString test="1+result_comp(Instances.WITHOUT_ROTATE10,0,0)";
	static int id=1;
	QString text=ui->txtInput->text();
	if(_isAddMode)
	{
		QStringList allCurves=text.split(";",QString::SkipEmptyParts);
		foreach(QString str,allCurves)
		{
			QString curveStr=str.remove("\n");
			curveStr=curveStr.trimmed();
			if(curveStr.isEmpty())
				continue;

			XYItemTitle item;
			item.type=XYItemTitle::Custom;
			item.itemContent=curveStr;
			item.name=QString("Custom curve %1").arg(id++);

			emit addItem(item);
		}
	}
	else
	{
		QString curveStr=text.remove("\n");
		curveStr=curveStr.trimmed();
		if(curveStr.isEmpty())
			return;

		XYItemTitle title = _aboutUpdateCurveTitle;
		title.itemContent = curveStr;
		emit updateItem(title);
	}
}

void AddCustomCurveDialog::updateConText()
{
	ui->txtInput->setText(_aboutUpdateCurveTitle.itemContent);
}

QString AddCustomCurveDialog::getCustomText()
{
	QString text=ui->txtInput->text();
	QString curveStr=text.remove("\n");
	curveStr=curveStr.trimmed();
	return curveStr;
}

void AddCustomCurveDialog::onBtnAddClicked()
{
	if(ui->txtInput->text().isEmpty())
	{
		QMessageBox::warning(this,"Warning","The custom data is empty !");
		return;
	}

	_isUse = true;
	emit useCustomData();
	this->hide();
}

