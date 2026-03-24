#ifndef ANIMATIONCONTROLWIDGET_H
#define ANIMATIONCONTROLWIDGET_H

#include "base/base_global.h"
#include <QWidget>
namespace Ui {class AnimationControlWidget;};


namespace Base{

/*!
*	This widget is used to add into Ribbon UI.
*	It controls the animation display.
*	@see AnimationToolbar
*	@author Jerry He
*	@date	2014.7.21
*/
class BASE_EXPORT AnimationControlWidget : public QWidget
{
	Q_OBJECT

public:
	AnimationControlWidget(QWidget *parent = 0);
	~AnimationControlWidget();
			
	/// ·µ»ØÎ¨Ò»µ¥Àý
	static AnimationControlWidget* instance();

	void updateUi();

	QAction* getActionStart();
	QAction* getActionStop();
	QAction* getActionPause();
	QAction* getActionNext();
	QAction* getActionPrevious();

protected:
	void init();
	void setCurrentValue(int v);

	void onKeyPressed ( QKeyEvent * event );
	virtual bool eventFilter(QObject* caller, QEvent* evt);


	protected slots:	
		void next();
		void start();
		void pause();
		void stop();
		void previous();
		void setSpeed(int speed){m_iSpeed=speed;}


		void onFrameValueChanged(int value);

		void setInterval(int value);

private:
	Ui::AnimationControlWidget *ui;


	int			m_iSpeed;

	QTimer*		m_timer;
	int			m_interval;
	int			m_lastPos;


	static AnimationControlWidget* _instance;
};

} // end namespace Base


#endif // ANIMATIONCONTROLWIDGET_H
