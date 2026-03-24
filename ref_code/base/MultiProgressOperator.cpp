#include "MultiProgressOperator.h"
#include <QMutex>
#include <stack>
#include <QMainWindow>

#include "ui_mulprogressdialog.h"
#include "ui_progressbarwidget.h"

#include "Console.h"

using namespace std;

static QMainWindow*	_mainWindow=NULL;

namespace Base
{


void MultiProgressOperator::startProgress(const char* progressDescription)
{
	//MulProgressDialog*box=new MulProgressDialog();
	MulProgressDialogMapper::instance()->startProgress(progressDescription);
	//box->setLabelText(progressDescription);
	//box->exec();
}
bool MultiProgressOperator::setProgress(int i)
{
	return MulProgressDialogMapper::instance()->setProgress(i);
}
void MultiProgressOperator::stopProgress()
{
	MulProgressDialogMapper::instance()->stopProgress();
}

bool MultiProgressOperator::isProgressCanceled()
{
	return false;
}
void MultiProgressOperator::terminateProgress()
{


}

void MultiProgressOperator::setMainWindow( QMainWindow* mainWindow )
{
	_mainWindow=mainWindow;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class MulProgressDialogMapperPrivate
{
public:
	MulProgressDialog* _dlg;
	//QMainWindow*	_mainWindow;
	QMutex _mutex;

	MulProgressDialogMapperPrivate();
};

MulProgressDialogMapperPrivate::MulProgressDialogMapperPrivate():_dlg(NULL)
{
	//QMainWindow* p=ParameterManager()->get<QMainWindow>("HQApplication");
	//_mainWindow=p;
	//if(!p){
		//Base::Console().Error("Mulitple Progress Dialog initilize failed.");
	//}
}

MulProgressDialogMapper* MulProgressDialogMapper::_instance=NULL;

MulProgressDialogMapper* MulProgressDialogMapper::instance()
{
	if(!_instance)
		_instance=new MulProgressDialogMapper();
	return _instance;
}

MulProgressDialogMapper::MulProgressDialogMapper()
:_ptr(new MulProgressDialogMapperPrivate())
{

}
MulProgressDialogMapper::MulProgressDialogMapper(QObject *parent)
	: QObject(parent)
	,_ptr(new MulProgressDialogMapperPrivate())
{
}

MulProgressDialogMapper::~MulProgressDialogMapper()
{

}

void MulProgressDialogMapper::startProgress(const QString& description)
{
	QMetaObject::invokeMethod(this,"sStartProgress",Q_ARG(QString,description));
}
bool MulProgressDialogMapper::setProgress(int percent)
{
	QMetaObject::invokeMethod(this,"sSetProgress",/*Qt::AutoConnection,
		Q_RETURN_ARG(bool,ret),*/
		Q_ARG(int,percent));

	return true;
}
void MulProgressDialogMapper::stopProgress()
{
	QMetaObject::invokeMethod(this,"sStopProgress");
}

void MulProgressDialogMapper::sStartProgress(const QString& description)
{
	if(!_mainWindow){
		Base::Console().Error("Main window should set before using multi-progress dialog.");
		return;
	}

	if(!_ptr->_dlg){
		MulProgressDialog* dlg=new MulProgressDialog(description,_mainWindow);
		_ptr->_dlg=dlg;
		dlg->exec();
		return;
	}
	_ptr->_dlg->startProgress(description);
}
bool MulProgressDialogMapper::sSetProgress(int percent)
{
	if(!_ptr->_dlg)
		return false;
		
	_ptr->_dlg->setProgress(percent);
	return true;
}
void MulProgressDialogMapper::sStopProgress()
{
	_ptr->_mutex.lock();
	if(!_ptr->_dlg){
		_ptr->_mutex.unlock();
		return;
	}
	_ptr->_dlg->stopProgress();
	if(_ptr->_dlg->isTerminated()
		||_ptr->_dlg->isFinished()){
		if(_ptr->_dlg->isTerminated())
			emit progressTerminated();
		else
			emit progressFinished();
		delete _ptr->_dlg;
		_ptr->_dlg=NULL;

		_ptr->_mutex.unlock();
		return;
	}
	_ptr->_mutex.unlock();
	return;
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class MulProgressDialogPrivate
{
public:
	typedef stack<ProgressBarWidget*> KeyMap;
	KeyMap _progressBarWidgets;
	ProgressBarWidget*	_currentProgressBarWidget;
	bool _isTerminated;
	bool _isFinshed;

	MulProgressDialogPrivate():_currentProgressBarWidget(NULL),_isTerminated(false),_isFinshed(false){}

	void insertProgressBarWidget(Ui::MulProgressDialogClass* ui,
		MulProgressDialog* parent,const QString& discription);
	void setProgress(int v);
	void stopProgress(Ui::MulProgressDialogClass* ui,MulProgressDialog* parent);
};

const int WIDTH=500;
const int HEIGHT=80;

void MulProgressDialogPrivate::insertProgressBarWidget(Ui::MulProgressDialogClass* ui,
	MulProgressDialog* parent,const QString& discription)
{
	ProgressBarWidget* w=new ProgressBarWidget(NULL);
	w->setDescription(discription);
	ui->_verticalLayout->addWidget(w);
	_progressBarWidgets.push(w);
	parent->resize(WIDTH,HEIGHT*_progressBarWidgets.size());
	_currentProgressBarWidget=w;
}

void MulProgressDialogPrivate::setProgress(int v)
{
	if(_currentProgressBarWidget)
		_currentProgressBarWidget->setProgress(v);
}

void MulProgressDialogPrivate::stopProgress(Ui::MulProgressDialogClass*ui,MulProgressDialog* parent)
{
	_progressBarWidgets.pop();
	ui->_verticalLayout->removeWidget(_currentProgressBarWidget);
	delete _currentProgressBarWidget;

	if(_progressBarWidgets.size()==0){
		_isFinshed=true;
		parent->accept();
		return;
	}
	_currentProgressBarWidget=_progressBarWidgets.top();
}


MulProgressDialog::MulProgressDialog(const QString& discription,QWidget *parent)
	: QDialog(parent)
	,_ptr(new MulProgressDialogPrivate())
{
	ui=new Ui::MulProgressDialogClass();
	ui->setupUi(this);
	_ptr->insertProgressBarWidget(ui,this,discription);
}

MulProgressDialog::~MulProgressDialog()
{
	delete ui;
}

void MulProgressDialog::startProgress(const QString& discription)
{
	_ptr->insertProgressBarWidget(ui,this,discription);
}
void MulProgressDialog::setProgress(int percent)
{
	_ptr->setProgress(percent);
}
void MulProgressDialog::stopProgress()
{
	_ptr->stopProgress(ui,this);
}

bool MulProgressDialog::isTerminated()
{
	return _ptr->_isTerminated;
}

bool MulProgressDialog::isFinished()
{
	return _ptr->_isFinshed;
}

void MulProgressDialog::onRejected()
{
	_ptr->_isTerminated=true;
}



ProgressBarWidget::ProgressBarWidget(QWidget *parent)
	: QWidget(parent)
{
	ui=new Ui::ProgressBarWidgetClass();
	ui->setupUi(this);
}

ProgressBarWidget::~ProgressBarWidget()
{
	delete ui;
}

void ProgressBarWidget::setProgress(int percent)
{
	ui->_PBWProgressBar->setValue(percent);
}

void ProgressBarWidget::setDescription(const QString& discription)
{
	ui->_PBWDisplayText->setText(discription);
}

}