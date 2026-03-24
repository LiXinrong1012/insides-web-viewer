#ifndef HOOPSVISIBILITYSETTINGDIALOG_H
#define HOOPSVISIBILITYSETTINGDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QStyledItemDelegate>

namespace INSIDES{
	class AppearanceItem;
}

using namespace INSIDES;

class QRadioButton;

namespace Ui {class HoopsVisibilitySettingDialog;};

class HoopsVisibilitySettingDialog : public QDialog
{
	Q_OBJECT

public:
	HoopsVisibilitySettingDialog(QWidget *parent = 0);
	~HoopsVisibilitySettingDialog();

	void setAppearance(AppearanceItem* item);
	void setModel(const QModelIndex& modelIndex){_modelIndex=modelIndex;}

protected slots:
	void value2Control();
	void control2Value();

	void checkAllClicked();

private:
	Ui::HoopsVisibilitySettingDialog *ui;
	AppearanceItem*			_appItem;
	QList<QList<QRadioButton*> >	_btnList;
	QModelIndex		_modelIndex;
	bool			_enabled;
};

class VisibilityDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	VisibilityDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;

	void updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const;

};


#endif // HOOPSVISIBILITYSETTINGDIALOG_H
