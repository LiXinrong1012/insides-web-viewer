#ifndef ACTIVEVIEWOBJECT_H
#define ACTIVEVIEWOBJECT_H

#include "base/base_global.h"
#include <QObject>


namespace Base{
class View;
class ViewLayoutManager;
class AnimationControler;

/*!
*	This class is a global object that informs the current active
*	views, etc.
*	@author Jerry He
*	@date	2014.3.26
*/
class BASE_EXPORT ActiveViewObject : public QObject
{
	Q_OBJECT

public:
	enum {MODEL_STATUS_MODEL,MODEL_STASTUS_DYNAMIC,MODEL_STATUS_EIGEN};

	static ActiveViewObject* instance();

	/*!	get current ViewLayoutManager. */
	ViewLayoutManager* currentViewLayoutManager()const{return _layoutManager;}

	View* activeView()const{return _activeView;}

	/*! 整个数据当前处于何种状态：
	*	MODEL_STATUS_MODEL: 显示模型的状态
	*	MODEL_STATUS_DYNAMIC: 显示帧动画的状态
	*	MODEL_STATUS_EIGEN:	显示模态动画的状态
	*/
	int getModelStatus()const{return _modelStatus;}
	void setModelStatus(int modelStatus);
	void notifyModelStatusChanged(){emit modelStatusChanged(_modelStatus);}

	AnimationControler* animationControler()const{return _animationControler;}
	void setAnimationControler(AnimationControler* c){_animationControler=c;}


	// only for temporary, Jerry, 2014.5.13
	void setSelect(long key,int count,const int* faces,const int* vertex1,const int* vertex2);

public slots:
	void setActiveView(View* view);
	void setLayoutManager(ViewLayoutManager* layoutManager){_layoutManager=layoutManager;}



signals:
	void activeViewChanged(View* view);

	void modelStatusChanged(int modelStatus);

	// only for temporary, Jerry, 2014.5.13
	void sigSetSelect(long key,int count,const int* faces,const int* vertex1,const int* vertex2);


protected:
	virtual bool eventFilter ( QObject * watched, QEvent * event );

private:
	ActiveViewObject(QObject *parent=0);
	~ActiveViewObject();
	Q_DISABLE_COPY(ActiveViewObject);

	View*			_activeView;
	ViewLayoutManager*	_layoutManager;
	AnimationControler*		_animationControler;
	int				_modelStatus;
	
};

}

#endif // ACTIVEVIEWOBJECT_H
