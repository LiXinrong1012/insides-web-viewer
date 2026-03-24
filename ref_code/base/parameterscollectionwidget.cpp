#include "parameterscollectionwidget.h"
#include "ui_parameterscollectionwidget.h"
#include "ParametersManagerWidget.h"
#include "ParametersManager.h"

namespace Base
{

ParametersCollectionWidget::ParametersCollectionWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::ParametersCollectionWidget();
	ui->setupUi(this);

	m_data=NULL;
	m_paras=ui->paraView;
	m_model = new QStandardItemModel(0, 2);
	QStringList headers;
	headers << tr("Keyword") << tr("Value");
	m_model->setHorizontalHeaderLabels(headers);
	m_paras->setModel(m_model);
	m_paras->setItemDelegateForColumn(1, new ParaValueDelegate(&m_types, &m_dbgSt));

	connect(m_model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onItemChanged(QStandardItem*)));
	connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(onFlip()));
}

ParametersCollectionWidget::~ParametersCollectionWidget()
{
	delete ui;
}


void ParametersCollectionWidget::load(ParametersGroup *paras, const QString& filter, bool isDebug)
{
	ui->pushButton->setText(paras->getName());
	m_model->blockSignals(true);
	clear();
	m_data = paras;
	paras->reset();
	int row = 0;
	while (const ParameterItem* item = paras->next()) {
		if (!item->getDebugOnly() || isDebug) {
			addItem(item, row++);
		}
	}
	filterChanged(filter);
	m_model->blockSignals(false);
}

static int _getItemType(const ParameterItem* item)
{
	return item->getType() == ParameterItem::ValidType ? item->getVariant().type() : item->getType();
}

void ParametersCollectionWidget::addItem(const ParameterItem* item, int row)
{
	m_model->insertRow(row);
	QStandardItem* key = new QStandardItem(item->getKeyword());
	key->setFlags(key->flags() & ~Qt::ItemIsEditable);
	m_model->setItem(row, 0, key);
	int type = _getItemType(item);
	m_types.push_back(type);
	m_dbgSt.push_back(item->getDebugOnly());
	QStandardItem* value = new ParaSetItem(item);
	if (!item->getChangeable()) {
		value->setFlags(value->flags() & ~Qt::ItemIsEditable);
	}
	if (type == QVariant::Color) {
		value->setData(item->getVariant(), Qt::DecorationRole);
	} else {
		value->setData(item->getVariant(), Qt::DisplayRole);
	}
	m_model->setItem(row, 1, value);
}

void ParametersCollectionWidget::clear()
{
	m_model->setRowCount(0);
	m_types.clear();
	m_dbgSt.clear();
	m_data = NULL;
}

void ParametersCollectionWidget::filterChanged(const QString& str)
{
	for (int i = 0; i < m_model->rowCount(); ++i) {
		bool hd = !m_model->data(m_model->index(i, 0)).toString().contains(str, Qt::CaseInsensitive);
		m_paras->setRowHidden(i, QModelIndex(), hd);
	}
}

void ParametersCollectionWidget::onFlip()
{
	ui->paraView->setVisible(!ui->paraView->isVisible());
}

void ParametersCollectionWidget::onItemChanged(QStandardItem* item)
{
	if (ParaSetItem* pit = dynamic_cast<ParaSetItem*>(item)) {
		if (const ParameterItem* it = pit->getItem()) {
			ParameterItem newItem=*it;
			if (_getItemType(it) == QVariant::Color) {
				newItem.setVariant(item->data(Qt::DecorationRole));
			} else {
				newItem.setVariant(item->data(Qt::EditRole));
			}
			m_data->set(newItem,true);
		}
	}
}

}	//end namespace Base;