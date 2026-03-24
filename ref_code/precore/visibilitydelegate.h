#ifndef VISIBILITYDELEGATE_H
#define VISIBILITYDELEGATE_H

#include <QStyledItemDelegate>
#include <QItemDelegate>





class CheckBoxDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	CheckBoxDelegate(QWidget *parent = 0) : QItemDelegate(parent) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;

	void updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const;

};


class CheckBoxDelegate2 : public QItemDelegate
{
	Q_OBJECT

public:
	explicit CheckBoxDelegate2(bool eventEnabled, QObject* parent = 0);
	QRect checkRect(const QStyleOptionViewItem &option, const QRect &bounding) const;

private:
	bool isEventEnabled;
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
		const QModelIndex& index ) const;
	void paint(QPainter* painter, const QStyleOptionViewItem& option,
		const QModelIndex& index) const;
	bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option,
		const QModelIndex& index);
};

#endif // VISIBILITYDELEGATE_H
