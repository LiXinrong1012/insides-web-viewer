#ifndef PARAMETERSMANAGERWIDGET_H
#define PARAMETERSMANAGERWIDGET_H

#include "base/base_global.h"
#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QFileDialog>
#include <QItemDelegate>
#include <QStandardItem>
#include <vector>


namespace Ui {class ParametersManagerWidget;};


namespace Base{
class ParameterItem;
class ParametersManager;
class ParametersCollectionWidget;

class PathEdit : public QWidget
{
	Q_OBJECT
public:
	PathEdit(QWidget* parent);

	QFileDialog* getDialog() const {return m_dialog;}
	QString getPath() const {return m_le->text();}
	void setPath(const QString& path){m_le->setText(path);}

	public slots:
		void onBrowser();
private:
	QLineEdit* m_le;
	QToolButton* m_tb;
	QFileDialog* m_dialog;
};


class ParaValueDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	ParaValueDelegate(const std::vector<int>* types, const std::vector<bool>* dbgSt, QObject* parent = NULL);

public:
	virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
	virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
private:
	const std::vector<int>* m_types;
	const std::vector<bool>* m_dbgSt;
};

class ParaSetItem : public QStandardItem
{
public:
	ParaSetItem(const ParameterItem* item)
		:m_item(item)
	{
	}

	const ParameterItem* getItem() const {return m_item;}
private:
	const ParameterItem* m_item;
};


class BASE_EXPORT ParametersManagerWidget : public QWidget
{
	Q_OBJECT

public:
	ParametersManagerWidget(QWidget *parent = 0);
	~ParametersManagerWidget();

	void load(ParametersManager* pcs);

public slots:
	void onClearFilter();
	void onFilterChanged(const QString& str);

private:
	Ui::ParametersManagerWidget *ui;
	QList<ParametersCollectionWidget*> m_collectionList;

	void clearChildren();
};


}	//end namespace Base


#endif // PARAMETERSMANAGERWIDGET_H
