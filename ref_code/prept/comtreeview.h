#ifndef COMTREEVIEW_H
#define COMTREEVIEW_H

#include <QTreeView>
#include <QItemDelegate>
#include <vector>

#include "precore/ISelectionSupplier.h"
#include "precore/modeldocumentlistener.h"

namespace INSIDES{
	class BaseItem;
}

using namespace INSIDES;


typedef INSIDES::BaseItem TreeItemClass;

class TreeItemDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	TreeItemDelegate(QObject* parent = NULL);

public:
	virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
	virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
};


class ComTreeView : public QTreeView, public ISelectionSupplier
	,public ModelDocumentListener
{
	Q_OBJECT

public:
	ComTreeView(QWidget *parent);
	~ComTreeView();


	TreeItemClass* getSelectedCoreItem();
	QList<TreeItemClass*> getSelectedCoreItems();

	void setModel(QAbstractItemModel* model);

protected:
	void doc_BeginRootItemChanging(BaseItem* currentRoot,BaseItem* old);
	void doc_BeginSavingDocument();
	//connect(model,SIGNAL(viewManagerBeginChanging()),
	//view,SLOT(saveCollapseStatus()));
	//connect(model,SIGNAL(viewManagerChanged()),
	//view,SLOT(restoreCollapseStatus()));

	public slots:


		void onStructChanged();

	virtual void reset();

	void restoreCollapseStatus(QModelIndex index=QModelIndex());
	void saveCollapseStatus(QModelIndex index=QModelIndex());

private slots:
	void onContextMenu(const QPoint& pos);

	// 右键菜单，暂时放在这里，未来需要统一设计。
	void onRemoveItem();
	void onEditAppearance();
	void onModify();
	void onShowProperties();
	void onDoubleClicked ( const QModelIndex & index );
	void onClicked(const QModelIndex & index);

	void onColumnSizeChanged(int index,int oldSize,int newSize);

	void slot_SelectionChanged(const QItemSelection &, const QItemSelection &);
	void slot_CurrentChanged ( const QModelIndex & current, const QModelIndex & previous );

signals:
	void selectionChanged(const std::vector<BaseItem*>& selection);


protected:

	//virtual void selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );

	virtual void ss_onSetSelection_protected(const QList<BaseItem*>& selection );
	virtual void ss_onSetClicked_projected(BaseItem* item){/*to do, Jerry,2014,3,8*/}



private:
	QAction*		_editAppearanceAction;
	QAction*		_showPropertiesAction;
	QAction*		_setVisual;
	QAction*		_setInvisual;
	QAction*		_setUndefined;

	void index2Items(QModelIndexList l, QList<TreeItemClass*>& entities);
	TreeItemClass* getCurrentItem()const;
};


#endif // COMTREEVIEW_H
