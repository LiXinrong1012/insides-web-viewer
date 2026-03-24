#ifndef PRE_TDY_BASE_VIEWWIDGET_H
#define PRE_TDY_BASE_VIEWWIDGET_H

#include "base/base_global.h"
#include <QWidget>

class ITreeItemPropertyFunc;

namespace Qtitan{class RibbonPage;}

namespace Base{

/*!
*	Basic virtual class for views that can be added into MultiViewWidget.
*	@author Jerry He
*	@date	2014.3.26
*/
class BASE_EXPORT View : public QObject
{
public:
	View(QObject* parent=0);
	~View();

	/// Get related ribbon page for this type of view.
	virtual Qtitan::RibbonPage* getRibbonPage();
	/// Update the ribbon page control after this view activated.
	virtual void updateRibbonPage();
	
	virtual QString getViewType()const=0;
	virtual QWidget* getWidget()=0;

	/*!	If implemented class has store the actual widget 
	*	in the parent widget, this function should return
	*	the actual widget.
	*/
	virtual QWidget* getActualWidget(){return getWidget();}

	virtual QList<QAction*>	getActionList();

	virtual ITreeItemPropertyFunc* getTreeItemProperties(){return NULL;}

	/// 事件:当前的View会被调用此函数；
	virtual bool onEventFilter(QObject* sender,QEvent* event){return false;}

	virtual bool saveState(QDataStream& out){return true;}
	virtual bool loadState(QDataStream& in,qint64 dataSize){return true;};

private:
	QString _viewType;
	
};

}	//end namespace Base

#endif // PRE_TDY_BASE_VIEWWIDGET_H
