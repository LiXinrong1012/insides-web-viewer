#include "animationcontrolwidget.h"
#include "ui_animationcontrolwidget.h"

#include "activeviewobject.h"
#include "AnimationControler.h"
#include "Console.h"

#include <QTimer>
#include <QKeyEvent>

namespace Base{

AnimationControlWidget* AnimationControlWidget::_instance=NULL;

AnimationControlWidget::AnimationControlWidget(QWidget *parent)
	: QWidget(parent)
	,m_lastPos(0)
{
	ui = new Ui::AnimationControlWidget();
	ui->setupUi(this);

	init();
	qApp->installEventFilter(this);

	_instance=this;
}

AnimationControlWidget::~AnimationControlWidget()
{
	delete ui;
}

void AnimationControlWidget::init()
{
	ui->btnStart->setDefaultAction(ui->actionStart);
	ui->btnPause->setDefaultAction(ui->actionPause);
	ui->btnStop->setDefaultAction(ui->actionStop);
	ui->btnPrevious->setDefaultAction(ui->actionPrevious);
	ui->btnNext->setDefaultAction(ui->actionNext);

	ui->sliderSpeed->setRange(1,15);
	connect(ui->sliderSpeed,SIGNAL(valueChanged(int)),this,SLOT(setSpeed(int)));

	m_iSpeed=1;


	connect(ui->sliderCurrentFrame,SIGNAL(valueChanged(int)),this,SLOT(onFrameValueChanged(int)));
	ui->sliderCurrentFrame->setValue(0);

	ui->cbGlobalControl->setFocusPolicy(Qt::NoFocus);

	m_timer=new QTimer(this);
	m_interval=ui->valueInterval->value();
	m_timer->setInterval(m_interval);

	connect(m_timer,SIGNAL(timeout()),this,SLOT(next()));

	connect(ui->valueInterval,SIGNAL(valueChanged(int)),this,SLOT(setInterval(int)));
	updateUi();
}

void AnimationControlWidget::setCurrentValue( int v )
{
	ui->sliderCurrentFrame->setValue(v);
}

void AnimationControlWidget::onKeyPressed( QKeyEvent * event )
{
	if(event->key()==Qt::Key_Space){
		setCurrentValue(m_lastPos);
		if(!m_timer->isActive())
			start();
	}
	else if(event->key()==Qt::Key_Return
		|| event->key()==Qt::Key_Enter){
			if(m_timer->isActive()){
				pause();
				m_lastPos=ui->sliderCurrentFrame->value();
			}
	}
}

bool AnimationControlWidget::eventFilter( QObject* caller, QEvent* evt )
{
	if (evt->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent=(QKeyEvent*)(evt);
		if(keyEvent && ui->cbGlobalControl->isChecked()){
			onKeyPressed(keyEvent);
		}
	}
	return false;
}

void AnimationControlWidget::next()
{
	AnimationControler*controler=ActiveViewObject::instance()->animationControler();
	int currentFrame=controler->getCurrentFrame();
	int frameSize=controler->getFrameCount();

	if(m_iSpeed+currentFrame>=frameSize){
		setCurrentValue(frameSize-1);
		m_timer->stop();
		updateUi();
		return;
	}

	setCurrentValue(m_iSpeed+currentFrame);
	updateUi();
}

void AnimationControlWidget::start()
{
	AnimationControler* controler=ActiveViewObject::instance()->animationControler();
	if(!controler->hasAnimation())
		return;
	int currentFrame=controler->getCurrentFrame();
	int frameSize=controler->getFrameCount();
	if(currentFrame>=frameSize-1){
		ui->sliderCurrentFrame->setValue(0);
	}

	m_timer->start();
	updateUi();
}

void AnimationControlWidget::pause()
{
	m_timer->stop();
	updateUi();
}

void AnimationControlWidget::stop()
{
	m_timer->stop();
	ui->sliderCurrentFrame->setValue(0);
	updateUi();
}

void AnimationControlWidget::previous()
{
	AnimationControler* controler=ActiveViewObject::instance()->animationControler();
	int currentFrame=controler->getCurrentFrame();
	if(currentFrame==0)
		return;

	if(currentFrame-m_iSpeed<0){
		setCurrentValue(0);
		m_timer->stop();
		updateUi();
		return;
	}

	setCurrentValue(currentFrame-m_iSpeed);
	updateUi();
}

void AnimationControlWidget::updateUi()
{
	AnimationControler* controler=ActiveViewObject::instance()->animationControler();
	ui->cbGlobalControl->setEnabled(true);

	if(!controler || !controler->hasAnimation()){
		this->setEnabled(false);
		ui->actionStart->setEnabled(false);
		ui->actionStop->setEnabled(false);
		ui->actionPause->setEnabled(false);
		ui->actionNext->setEnabled(false);
		ui->actionPrevious->setEnabled(false);
		return;
	}
	else{
		ui->sliderCurrentFrame->setRange(0,controler->getFrameCount()-1);
		ui->valueCurrentFrame->setMinimum(0);
		ui->valueCurrentFrame->setMaximum(controler->getFrameCount()-1);
		this->setEnabled(true);
		ui->actionStart->setEnabled(true);
		ui->actionStop->setEnabled(true);
		ui->actionPause->setEnabled(true);
		ui->actionNext->setEnabled(true);
		ui->actionPrevious->setEnabled(true);
	}

	if(m_timer->isActive()){
		ui->actionStart->setEnabled(false);
		ui->actionPause->setEnabled(true);
		ui->actionStop->setEnabled(true);
	}
	else{
		ui->actionStart->setEnabled(true);
		ui->actionPause->setEnabled(false);
		ui->actionStop->setEnabled(false);
	}
}

void AnimationControlWidget::onFrameValueChanged( int value )
{
	ActiveViewObject::instance()->animationControler()->setCurrentFrame(value);
}

void AnimationControlWidget::setInterval( int value )
{
	m_interval=value;
	m_timer->setInterval(value);
}

AnimationControlWidget* AnimationControlWidget::instance()
{
	return _instance;
}

QAction* AnimationControlWidget::getActionStart()
{
	return ui->btnStart->defaultAction();
}

QAction* AnimationControlWidget::getActionStop()
{
	return ui->btnStop->defaultAction();
}

QAction* AnimationControlWidget::getActionPause()
{
	return ui->actionPause;
}

QAction* AnimationControlWidget::getActionNext()
{
	return ui->actionNext;
}

QAction* AnimationControlWidget::getActionPrevious()
{
	return ui->actionPrevious;
}


}	// end namespace Base