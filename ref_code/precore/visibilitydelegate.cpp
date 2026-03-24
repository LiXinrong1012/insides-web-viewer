#include "visibilitydelegate.h"

#include <QApplication>
#include <QCheckBox>
#include <QtGui/QApplication>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include "appearance.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CheckBoxDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	//»ñÈ¡Öµ
	bool checked = index.model()->data(index, Qt::DisplayRole).toBool();

	Qt::CheckState state;


	QSize size = check(option, option.rect, Qt::Checked).size();
	QRect checkboxRect = QStyle::alignedRect(option.direction, Qt::AlignCenter, size, option.rect);
	drawCheck(painter, option, checkboxRect, checked?Qt::Checked:Qt::Unchecked);
}



QWidget * CheckBoxDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	QCheckBox *editor = new QCheckBox(parent);
	return editor;
}

void CheckBoxDelegate::setEditorData( QWidget *editor, const QModelIndex &index ) const
{
	bool value = index.model()->data(index, Qt::EditRole).toBool();

	QCheckBox *spinBox = static_cast<QCheckBox*>(editor);
	spinBox->setChecked(value);
}

void CheckBoxDelegate::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
	QCheckBox *spinBox = static_cast<QCheckBox*>(editor);
	bool value = spinBox->isChecked();

	model->setData(index, value, Qt::EditRole);
}

void CheckBoxDelegate::updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	editor->setGeometry(option.rect);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CheckBoxDelegate2::CheckBoxDelegate2(bool eventEnabled, QObject *parent) :
QItemDelegate(parent)
{
	isEventEnabled = eventEnabled;
}

QWidget* CheckBoxDelegate2::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	Q_UNUSED (parent)
		Q_UNUSED (option)
		Q_UNUSED (index)
		return NULL;
}

// FIXME: wrong background on KDE
void CheckBoxDelegate2::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	drawBackground(painter, option, index);
	drawFocus(painter, option, option.rect);
	QStyleOptionViewItemV4 opt(option);
	opt.rect = checkRect(option, option.rect);
	opt.state = opt.state & ~QStyle::State_HasFocus;
	opt.state |= (index.data().toInt() > 0 ? QStyle::State_On : QStyle::State_Off);
	qApp->style()->drawPrimitive(QStyle::PE_IndicatorViewItemCheck, &opt, painter);

}

QRect CheckBoxDelegate2::checkRect(const QStyleOptionViewItem &option, const QRect &bounding) const
{
	QStyleOptionButton opt;
	opt.QStyleOption::operator=(option);
	opt.rect = bounding;
	QRect cr = qApp->style()->subElementRect(QStyle::SE_ViewItemCheckIndicator, &opt);
	int deltaX = (bounding.width()-cr.width())/2;
	int deltaY = (bounding.height()-cr.height())/2;
	return QRect(bounding.left() + deltaX, bounding.top() + deltaY, cr.width(), cr.height());
}

bool CheckBoxDelegate2::editorEvent(QEvent *event, QAbstractItemModel *model,
	const QStyleOptionViewItem &option, const QModelIndex &index)
{
	if (!isEventEnabled)
		return false;

	if(!event || !model)
		return false;

	Qt::ItemFlags flags = model->flags(index);
	if (!(option.state & QStyle::State_Enabled) || !(flags & Qt::ItemIsEnabled))
		return false;


	switch(event->type()) {
	case QEvent::MouseButtonRelease :
	case QEvent::MouseButtonDblClick : {
		QRect cr(checkRect(option, option.rect));
		QMouseEvent *me = static_cast<QMouseEvent*>(event);
		if (me->button() != Qt::LeftButton || !cr.contains(me->pos()))
			return false;

		// eat the double click events inside the check rect
		if(event->type() == QEvent::MouseButtonDblClick)
			return true;
		break;
									   }
	case QEvent::KeyPress : {
		QKeyEvent *kev = static_cast<QKeyEvent*>(event);
		if(kev->key() != Qt::Key_Space && kev->key() != Qt::Key_Select)
			return false;
		break;
							}
	default: return false;
	}


	int value = (index.data().toInt() == 0 ? 2 : 0);
	return model->setData(index, value, Qt::EditRole);
}
