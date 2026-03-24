#ifndef TREEHEADERMODIFICATIONDIALOG_H
#define TREEHEADERMODIFICATIONDIALOG_H

#include <QDialog>
namespace Ui {class TreeHeaderModificationDialog;};

class ComTreeModel;

class TreeHeaderModificationDialog : public QDialog
{
	Q_OBJECT

public:
	TreeHeaderModificationDialog(QWidget *parent,ComTreeModel* treeModel);
	~TreeHeaderModificationDialog();

protected slots:
	void updateViews();
	void updateItems();
	void updateDisplayedItems();
	void onAdd();
	void onRemove();

	void onMoveUp();
	void onMoveDown();

	void onOK();

private:
	Ui::TreeHeaderModificationDialog *ui;
	QList<QString>	_displayItemList;
	ComTreeModel*	_treeModel;
};

#endif // TREEHEADERMODIFICATIONDIALOG_H
