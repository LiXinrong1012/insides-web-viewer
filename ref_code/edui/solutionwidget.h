#ifndef SOLUTIONWIDGET_H
#define SOLUTIONWIDGET_H

#include <QTreeWidget>

class QTreeWidgetItem;
class INSEntity;

class SolutionWidget : public QTreeWidget
{
	Q_OBJECT

public:
	SolutionWidget(QWidget *parent);
	~SolutionWidget();


signals:
	void entityDoubleClicked(INSEntity* entity);

public slots:
	void updateTree();

private slots:
	void onContextMenu(const QPoint&);
	void onItemDoubleClicked( QTreeWidgetItem * item, int column);

	void onNewFile();
	void onAddFiles();
	void onAddFolder();
	void onRemove();
	void onSetAsStartup();
	

private:
	QTreeWidgetItem* _visibleRootItem;

	QAction*	_newFile;
	QAction*	_addFiles;
	QAction*	_addFolder;
	QAction*	_remove;
	QAction*	_setAsStartup;


private:
	void createActions();

	QTreeWidgetItem* createTreeWidgetItem(QTreeWidgetItem* treeRoot,const INSEntity* enity);
	void updateTreeItem(QTreeWidgetItem* treeRoot,const INSEntity* entityRoot);
	INSEntity* getSelectedEntity();
	QList<INSEntity*> getSelectedEntities();
	void addNewEntity(INSEntity* entity);
};

#endif // SOLUTIONWIDGET_H
