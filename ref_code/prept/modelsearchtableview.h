#ifndef MODELSEARCHTABLEVIEW_H
#define MODELSEARCHTABLEVIEW_H

#include "precore/ISelectionSupplier.h"
#include "IModelViewColumns.h"
#include <QTableView>


using namespace INSIDES;

class ModelSearchTableView 
	: public QTableView
	,public ISelectionSupplier
	,public IViewColumns
{
	Q_OBJECT

public:
	ModelSearchTableView(QWidget *parent);
	~ModelSearchTableView();

protected slots:
	void onStructChanged();

	void onClicked(const QModelIndex & index);
	void onColumnSizeChanged(int index,int oldSize,int newSize);

	void slot_SelectionChanged(const QItemSelection &, const QItemSelection &);
	void slot_CurrentChanged ( const QModelIndex & current, const QModelIndex & previous );

protected:
	virtual void ss_onSetSelection_protected(const QList<BaseItem*>& selection );
	virtual void ss_onSetClicked_projected(BaseItem* item);

private:
	
};



#endif // MODELSEARCHTABLEVIEW_H
