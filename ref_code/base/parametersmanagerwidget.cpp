#include "parametersmanagerwidget.h"
#include "ui_parametersmanagerwidget.h"
#include "parameterscollectionwidget.h"

#include "ParametersManager.h"
#include <QtGui>
#include <QtCore>

namespace Base{

PathEdit::PathEdit(QWidget* parent):
QWidget(parent)
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	m_le = new QLineEdit;
	layout->addWidget(m_le);
	m_tb = new QToolButton;
	m_tb->setText(tr("Browser"));
	layout->addWidget(m_tb);
	m_dialog = new QFileDialog(this);
	connect(m_tb, SIGNAL(clicked(bool)), this, SLOT(onBrowser()));
	setFocusProxy(m_le);
}


void PathEdit::onBrowser()
{
	if (m_dialog->exec() == QDialog::Accepted) {
		QStringList files = m_dialog->selectedFiles();
		if (files.size() > 0) {
			m_le->setText(files[0]);
		} else {
			m_le->setText("");
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

ParaValueDelegate::ParaValueDelegate(const std::vector<int>* types, const std::vector<bool>* dbgSt, QObject* parent)
	:QItemDelegate(parent),
	m_types(types),
	m_dbgSt(dbgSt)
{
}

QWidget* ParaValueDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	//QVariant var = index.data();
	switch (m_types->at(index.row())) {
	case QVariant::Color:
		{
			QColorDialog cd(index.data(Qt::DecorationRole).value<QColor>(), parent);
			if (cd.exec() == QDialog::Accepted) {
				if (const QStandardItemModel* md = qobject_cast<const QStandardItemModel*>(index.model())) {
					if (QStandardItem* item = md->itemFromIndex(index)) {
						item->setData(QVariant(cd.currentColor()), Qt::DecorationRole);
					}
				}
			}
			return NULL;
		}
	case ParameterItem::PathString:
		{
			PathEdit* pe = new PathEdit(parent);
			return pe;
		}
	case ParameterItem::DirString:
		{
			PathEdit* pe = new PathEdit(parent);
			pe->getDialog()->setFileMode(QFileDialog::Directory);
			pe->getDialog()->setOption(QFileDialog::ShowDirsOnly, true);
			pe->getDialog()->setLabelText(QFileDialog::Accept, tr("Choice"));
			return pe;
		}
	case ParameterItem::VoidStarPointer://same as default
	default:
		break;
	}
	QWidget* w = QItemDelegate::createEditor(parent, option, index);
	if (QDoubleSpinBox* db = qobject_cast<QDoubleSpinBox*>(w)) {
		db->setDecimals(6);
	}
	return w;
}

void ParaValueDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	QVariant var = index.data();
	switch (m_types->at(index.row())) {
	case QVariant::Color://don't process
		break;
	case ParameterItem::PathString:
	case ParameterItem::DirString:
		if (PathEdit* pe = qobject_cast<PathEdit*>(editor)) {
			pe->setPath(var.toString());
		}
		break;
	case ParameterItem::VoidStarPointer://same as default
	default:
		QItemDelegate::setEditorData(editor, index);
		break;
	}
}

void ParaValueDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (PathEdit* pe = qobject_cast<PathEdit*>(editor)) {
		model->setData(index, pe->getPath());
	} else {
		QItemDelegate::setModelData(editor, model, index);
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
ParametersManagerWidget::ParametersManagerWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::ParametersManagerWidget();
	ui->setupUi(this);


	connect(ui->filterLE, SIGNAL(textChanged(const QString&)), this, SLOT(onFilterChanged(const QString&)));
	connect(ui->filterTB, SIGNAL(clicked(bool)), this, SLOT(onClearFilter()));

	//load(ParametersManager());
}

ParametersManagerWidget::~ParametersManagerWidget()
{
	delete ui;
}

void ParametersManagerWidget::clearChildren()
{
	QLayout* l=ui->mainWidget;
	QLayoutItem *item;
	QLayoutIterator it = l->iterator();

	while((item = it.takeCurrent()) != 0) {
		l->remove(item->widget());
	}

	for(QList<ParametersCollectionWidget*>::Iterator b=m_collectionList.begin();
		b!=m_collectionList.end();++b)
	{
		delete *b;
	}
	m_collectionList.clear();
}
void ParametersManagerWidget::load(ParametersManager* pcs)
{
	clearChildren();

	QString filter = ui->filterLE->text();
	int collectionCount=pcs->getCollectionCount();
	for(int i=0;i<collectionCount;++i){
		ParametersGroup* c=pcs->getCollection(i);
		ParametersCollectionWidget* widget=new ParametersCollectionWidget(this);
		widget->load(c,filter,pcs->isDebug());
		ui->mainWidget->add(widget);
		m_collectionList.push_back(widget);
	}
	ui->mainWidget->addStretch(0);
}

void ParametersManagerWidget::onFilterChanged(const QString& str)
{
	for(int i=0;i<m_collectionList.size();++i)
		m_collectionList[i]->filterChanged(str);
}

void ParametersManagerWidget::onClearFilter()
{
	ui->filterLE->setText("");
}



static int _getItemType(const ParameterItem* item)
{
	return item->getType() == ParameterItem::ValidType ? item->getVariant().type() : item->getType();
}




}