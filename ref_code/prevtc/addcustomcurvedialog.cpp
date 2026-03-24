#include "addcustomcurvedialog.h"
#include "ui_addcustomcurvedialog.h"


AddCustomCurveDialog::AddCustomCurveDialog(QWidget *parent)
	: QDialog(parent)
	,_isAddMode(true)
{
	ui = new Ui::AddCustomCurveDialog();
	ui->setupUi(this);

	connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(onAddBtnClicked()));
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

			CurveItemTitle item;
			item.type=CurveItemTitle::Custom;
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

		CurveItemTitle title = _aboutUpdateCurveTitle;
		title.itemContent = curveStr;
		emit updateItem(title);
	}
}

void AddCustomCurveDialog::updateConText()
{
	ui->txtInput->setText(_aboutUpdateCurveTitle.itemContent);
}

