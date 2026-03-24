#include "HoopsMaterialDelegate.h"

#include "base/Console.h"
#include "precore/appearance.h"

#include "prev3dcore/colorset/colorSetForm.h"

using namespace Base;

void HoopsMaterialDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	if (option.state & QStyle::State_Selected)
		painter->fillRect(option.rect, option.palette.highlight());

	AppearanceItem* item=static_cast<AppearanceItem*>((void*)index.data().toLongLong());
	if(!item)
		return;

	float tmp=option.rect.width()/4.0;
	int w=ceilf(tmp);
	if(item->getUseColor(AppearanceItem::Color_Point)){
		const QColor& tmpColor=item->getColor(AppearanceItem::Color_Face);
		painter->fillRect(option.rect.x(),option.rect.y(),w,option.rect.height(),tmpColor);
	}
	if(item->getUseColor(AppearanceItem::Color_Line)){
		const QColor& tmpColor=item->getColor(AppearanceItem::Color_Line);
		painter->fillRect(option.rect.x()+tmp,option.rect.y(),w,option.rect.height(),tmpColor);
	}
	if(item->getUseColor(AppearanceItem::Color_Edge)){
		const QColor& tmpColor=item->getColor(AppearanceItem::Color_Edge);
		painter->fillRect(option.rect.x()+2*tmp,option.rect.y(),w,option.rect.height(),tmpColor);
	}
	if(item->getUseColor(AppearanceItem::Color_Face)){
		const QColor& tmpColor=item->getColor(AppearanceItem::Color_Face);
		painter->fillRect(option.rect.x()+3*tmp,option.rect.y(),w,option.rect.height(),tmpColor);
	}
}


QWidget *HoopsMaterialDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	ColorSetForm* editor = new ColorSetForm(parent);
	editor->setModel(index);

	return editor;
}

void HoopsMaterialDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	AppearanceItem* item=static_cast<AppearanceItem*>((void*)index.data().toLongLong());
	if(!item){
		QStyledItemDelegate::setEditorData(editor, index);
		return;
	}

	ColorSetForm *starEditor = qobject_cast<ColorSetForm *>(editor);
	starEditor->setAppearance(item);
	starEditor->setModel(index);
}

void HoopsMaterialDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	QStyledItemDelegate::setModelData(editor, model, index);
}


void HoopsMaterialDelegate::updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	//editor->setGeometry(option.rect);
	//QStyledItemDelegate::updateEditorGeometry(editor,option,index);
	//editor->setGeometry(option.rect.x(), option.rect.y(), 200, 90);
}

