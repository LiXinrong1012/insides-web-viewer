#ifndef PARAMETERSCOLLECTIONWIDGET_H
#define PARAMETERSCOLLECTIONWIDGET_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>


namespace Ui {class ParametersCollectionWidget;};

namespace Base{
class ParametersGroup;
class ParameterItem;

class ParametersCollectionWidget : public QWidget
{
	Q_OBJECT

public:
	ParametersCollectionWidget(QWidget *parent = 0);
	~ParametersCollectionWidget();


	QTreeView* getParas() const;
	QStandardItemModel* getModel() const {return m_model;}
	void load(ParametersGroup* paras, const QString& filter, bool isDebug);
	void filterChanged(const QString& str);

public slots:
	void onFlip();
	void onItemChanged(QStandardItem* item);

private:
	void clear();
	void addItem(const ParameterItem* item, int row);
private:
	ParametersGroup* m_data;
	QTreeView* m_paras;
	QStandardItemModel* m_model;
	std::vector<ParameterItem*> m_items;
	std::vector<int> m_types;
	std::vector<bool> m_dbgSt;

private:
	Ui::ParametersCollectionWidget *ui;
};

}

#endif // PARAMETERSCOLLECTIONWIDGET_H
