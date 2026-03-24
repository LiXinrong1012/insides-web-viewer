#pragma once

#include "base/base_global.h"
#include <QToolBar>

class QSlider;
class QCheckBox;

namespace Base{

class BASE_EXPORT AnimationToolbar :
	public QToolBar
{
	Q_OBJECT;

public:
	AnimationToolbar(QWidget*parent=0);
	~AnimationToolbar(void);

	QAction* getActionStart(){return m_acStart;}
	QAction* getActionStop(){return m_acStop;}

protected:
	void init();
	void setCurrentValue(int v);

	void onKeyPressed ( QKeyEvent * event );
	virtual bool eventFilter(QObject* caller, QEvent* evt);


	public slots:	
		void next();
		void start();
		void pause();
		void stop();
		void previous();
		void setSpeed(int speed){m_iSpeed=speed;}
		void updateUi();


		protected slots:
			void onFrameValueChanged(int v);

private:
	QAction*	m_acStart;
	QAction*	m_acPause;
	QAction*	m_acStop;
	QAction*	m_acNext;
	QAction*	m_acPrevious;

	QSlider*	m_sliderSpeed;
	QSlider*	m_sliderCurrentFrame;
	QCheckBox*	m_enableGlobalKey;

	int			m_iSpeed;

	QTimer*		m_timer;
	int			m_interval;
	int			m_lastPos;
};


}