#ifndef INTERACTIVETABLEVIEW_H
#define INTERACTIVETABLEVIEW_H

#include <QTableView>
#include "precore/ResultDocument.h"

/*!
*	代表即帧刷新数据的表格视图。
*	@author Jerry He
*	@date	2014.4.23
*/
using namespace INSIDES;
namespace INSIDES{
	class IResultListener;
}
class InteractiveTableView : public QTableView, public IResultListener
{
	Q_OBJECT

public:
	InteractiveTableView(QWidget *parent);
	~InteractiveTableView();

protected slots:
	void onNewDataAdded();
	void onSelectionChanged();

protected:
	/// invoked after result data has changed.
	virtual void onResultCurrentFrameChanged();


private:
	
};

#endif // INTERACTIVETABLEVIEW_H
