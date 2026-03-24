#include "AnimationToolbar.h"

#include "PixmapManager.h"
#include "activeviewobject.h"
#include "AnimationControler.h"
#include <QtGui>

#include "Console.h"

namespace Base{


AnimationToolbar::AnimationToolbar(QWidget*parent)
	:QToolBar(parent)
	,m_lastPos(0)
{	
	this->setWindowTitle(tr("Animation"));
	init();
	qApp->installEventFilter(this);
}


inline void setActionIcon(QAction* ac,const char* name)
{
	QPixmap* a=PixmapManager()->get(name);
	if(a)
		ac->setIcon(*a);
}

void AnimationToolbar::init()
{
	m_acStart=addAction("Start",this,SLOT(start()));
	m_acPause=addAction("Pause",this,SLOT(pause()));
	m_acStop=addAction("Stop",this,SLOT(stop()));
	m_acPrevious=addAction("Previous",this,SLOT(previous()));
	m_acNext=addAction("Next",this,SLOT(next()));

	setActionIcon(m_acStart,":/resources/menu/ani/play.png");
	setActionIcon(m_acPause,":/resources/menu/ani/pause.png");
	setActionIcon(m_acStop,":/resources/menu/ani/stop.png");
	setActionIcon(m_acPrevious,":/resources/menu/ani/left.png");
	setActionIcon(m_acNext,":/resources/menu/ani/right.png");

	m_sliderSpeed=new QSlider(Qt::Horizontal);

	QSizePolicy sizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
	m_sliderSpeed->setSizePolicy(sizePolicy);
	m_sliderSpeed->setRange(1,10);
	addWidget(m_sliderSpeed);
	connect(m_sliderSpeed,SIGNAL(valueChanged(int)),this,SLOT(setSpeed(int)));

	m_iSpeed=1;

	m_sliderCurrentFrame=new QSlider(Qt::Horizontal);
	m_sliderCurrentFrame->setMinimumWidth(150);
	m_sliderCurrentFrame->setMaximumWidth(250);

	QSizePolicy sizePolicy2(QSizePolicy::Fixed,QSizePolicy::Preferred);
	m_sliderCurrentFrame->setSizePolicy(sizePolicy2);
	addWidget(m_sliderCurrentFrame);
	connect(m_sliderCurrentFrame,SIGNAL(valueChanged(int)),this,SLOT(onFrameValueChanged(int)));
	m_sliderCurrentFrame->setValue(0);

	m_enableGlobalKey=new QCheckBox(this);
	m_enableGlobalKey->setText("");
	m_enableGlobalKey->setEnabled(false);
	m_enableGlobalKey->setFocusPolicy(Qt::NoFocus);
	addWidget(m_enableGlobalKey);

	m_timer=new QTimer(this);
	m_interval=50;
	m_timer->setInterval(m_interval);

	connect(m_timer,SIGNAL(timeout()),this,SLOT(next()));
	updateUi();
}

AnimationToolbar::~AnimationToolbar(void)
{
}

void AnimationToolbar::start()
{
	AnimationControler* controler=ActiveViewObject::instance()->animationControler();
	if(!controler->hasAnimation())
		return;
	int currentFrame=controler->getCurrentFrame();
	int frameSize=controler->getFrameCount();
	if(currentFrame>=frameSize-1){
		m_sliderCurrentFrame->setValue(0);
	}

	m_timer->start();
	updateUi();
}
void AnimationToolbar::pause()
{
	m_timer->stop();
	updateUi();
}
void AnimationToolbar::stop()
{
	m_timer->stop();
	m_sliderCurrentFrame->setValue(0);
	updateUi();
}
void AnimationToolbar::next()
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

void AnimationToolbar::previous()
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

void AnimationToolbar::updateUi()
{
	AnimationControler* controler=ActiveViewObject::instance()->animationControler();
	m_enableGlobalKey->setEnabled(true);

	if(!controler || !controler->hasAnimation()){
		this->setEnabled(false);
		return;
	}
	else{
		m_sliderCurrentFrame->setRange(0,controler->getFrameCount()-1);
		this->setEnabled(true);
	}

	if(m_timer->isActive()){
		m_acStart->setEnabled(false);
		m_acPause->setEnabled(true);
		m_acStop->setEnabled(true);
	}
	else{
		m_acStart->setEnabled(true);
		m_acPause->setEnabled(false);
		m_acStop->setEnabled(false);
	}

}

void AnimationToolbar::onFrameValueChanged( int v )
{
	ActiveViewObject::instance()->animationControler()->setCurrentFrame(v);
}

void AnimationToolbar::setCurrentValue( int v )
{
	m_sliderCurrentFrame->setValue(v);
}

void AnimationToolbar::onKeyPressed( QKeyEvent * event )
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
			m_lastPos=m_sliderCurrentFrame->value();
		}
	}

}

bool AnimationToolbar::eventFilter( QObject* caller, QEvent* evt )
{
	if (evt->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent=(QKeyEvent*)(evt);
		if(keyEvent && m_enableGlobalKey->isChecked()){
			onKeyPressed(keyEvent);
		}
	}
	return false;
}



}