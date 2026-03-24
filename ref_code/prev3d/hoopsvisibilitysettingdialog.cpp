#include "hoopsvisibilitysettingdialog.h"
#include "ui_hoopsvisibilitysettingdialog.h"

#include <QtCore/QAbstractItemModel>
#include <QtGui/QPainter>

#include "Base/Console.h"
#include "base/PixmapManager.h"

#include "precore/appearance.h"

using namespace Base;


HoopsVisibilitySettingDialog::HoopsVisibilitySettingDialog(QWidget *parent)
	: QDialog(parent)
	,_appItem(NULL)
	,_enabled(false)
{
	ui = new Ui::HoopsVisibilitySettingDialog();
	ui->setupUi(this);

	QList<QRadioButton*> btnList;
	// 0: all
	btnList<<ui->rb0_1<<ui->rb0_2<<ui->rb0_3;
	_btnList<<btnList;

	// 1: Face
	btnList.clear();
	btnList<<ui->rb1_1<<ui->rb1_2<<ui->rb1_3;
	_btnList<<btnList;
	
	// 2: Line
	btnList.clear();
	btnList<<ui->rb2_1<<ui->rb2_2<<ui->rb2_3;
	_btnList<<btnList;

	// 3: Vertex
	btnList.clear();
	btnList<<ui->rb3_1<<ui->rb3_2<<ui->rb3_3;
	_btnList<<btnList;

	// 4: Edge
	btnList.clear();
	btnList<<ui->rb4_1<<ui->rb4_2<<ui->rb4_3;
	_btnList<<btnList;

	// 5: Marker
	btnList.clear();
	btnList<<ui->rb5_1<<ui->rb5_2<<ui->rb5_3;
	_btnList<<btnList;

	// 6: Text
	btnList.clear();
	btnList<<ui->rb6_1<<ui->rb6_2<<ui->rb6_3;
	_btnList<<btnList;

	connect(ui->buttonGroup,SIGNAL(buttonClicked (int)),this,SLOT(control2Value()));

	connect(ui->buttonGroup_2,SIGNAL(buttonClicked (int)),this,SLOT(control2Value()));
	connect(ui->buttonGroup_3,SIGNAL(buttonClicked (int)),this,SLOT(control2Value()));
	connect(ui->buttonGroup_4,SIGNAL(buttonClicked (int)),this,SLOT(control2Value()));
	connect(ui->buttonGroup_5,SIGNAL(buttonClicked (int)),this,SLOT(control2Value()));
	connect(ui->buttonGroup_7,SIGNAL(buttonClicked (int)),this,SLOT(control2Value()));

	connect(ui->buttonGroup_6,SIGNAL(buttonClicked (int)),this,SLOT(checkAllClicked()));
	_enabled=true;
}

HoopsVisibilitySettingDialog::~HoopsVisibilitySettingDialog()
{
	delete ui;
}

void HoopsVisibilitySettingDialog::setAppearance( AppearanceItem* item )
{
	_appItem=item;
	
	value2Control();
}

static void _control2Value(AppearanceItem* item,AppearanceItem::VisibilityItem t,QList<QList<QRadioButton*> >& btns,int index)
{
	if(btns[index][0]->isChecked())
		item->setVisibilityType(t,AppearanceItem::Undefined);
	else if(btns[index][1]->isChecked())
		item->setVisibilityType(t,AppearanceItem::Visual);
	else
		item->setVisibilityType(t,AppearanceItem::Invisual);
}

void HoopsVisibilitySettingDialog::control2Value()
{
	if(!_enabled)
		return;

	_control2Value(_appItem,AppearanceItem::Face,_btnList,1);
	_control2Value(_appItem,AppearanceItem::Line,_btnList,2);
	_control2Value(_appItem,AppearanceItem::Vertex,_btnList,3);
	_control2Value(_appItem,AppearanceItem::Edge,_btnList,4);
	_control2Value(_appItem,AppearanceItem::Marker,_btnList,5);
	_control2Value(_appItem,AppearanceItem::Text,_btnList,6);

	const_cast<QAbstractItemModel*>(_modelIndex.model())->setData(_modelIndex,(qlonglong)(void*)_appItem,Qt::EditRole);
}

static void _value2Control(AppearanceItem* item,AppearanceItem::VisibilityItem t,QList<QList<QRadioButton*> >& btns,int index)
{
	switch(item->getVisibilityType(t)){
	case AppearanceItem::Visual:
		btns[index][1]->setChecked(true);
		break;
	case AppearanceItem::Invisual:
		btns[index][2]->setChecked(true);
		break;;
	case AppearanceItem::Undefined:
		btns[index][0]->setChecked(true);
		break;
	default:
		Base::Console().Error("Potential error in the visibility dialog.");
	}
}

void HoopsVisibilitySettingDialog::value2Control()
{
	if(!_appItem)
		return;

	_enabled=false;

	_value2Control(_appItem,AppearanceItem::Face,_btnList,1);
	_value2Control(_appItem,AppearanceItem::Line,_btnList,2);
	_value2Control(_appItem,AppearanceItem::Vertex,_btnList,3);
	_value2Control(_appItem,AppearanceItem::Edge,_btnList,4);
	_value2Control(_appItem,AppearanceItem::Marker,_btnList,5);
	_value2Control(_appItem,AppearanceItem::Text,_btnList,6);
	_enabled=true;
}

void HoopsVisibilitySettingDialog::checkAllClicked()
{
	_enabled=false;
	int v=2;
	if(_btnList[0][0]->isChecked())
		v=0;
	else if(_btnList[0][1]->isChecked())
		v=1;

	for(int i=0;i<6;++i)
		_btnList[i+1][v]->setChecked(true);

	_enabled=true;
	control2Value();
}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void VisibilityDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	if (option.state & QStyle::State_Selected)
		painter->fillRect(option.rect, option.palette.highlight());

	AppearanceItem* item=static_cast<AppearanceItem*>((void*)index.data().toLongLong());
	if(!item)
		return;

	QPixmap* pic=NULL;
	if(item->isVisibilityAll())
		pic=PixmapManager()->get(":/resources/items/a012x16x16.png");
	else if(item->isVisibilityUndefined())
		pic=PixmapManager()->get(":/resources/items/a014x16x16.png");
	else
		pic=PixmapManager()->get(":/resources/items/a013x16x16.png");


	int h=option.rect.height();
	painter->drawPixmap(option.rect.x()+(option.rect.width()-h)/2,
		option.rect.y(),h,h,*pic);
	//QStyledItemDelegate::paint(painter, option, index);
}


QWidget *VisibilityDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	AppearanceItem* item=static_cast<AppearanceItem*>((void*)index.data().toLongLong());
	index.model();
	//if(!item)
	//return QStyledItemDelegate::createEditor(parent, option, index);

	HoopsVisibilitySettingDialog* editor = new HoopsVisibilitySettingDialog(parent);
	editor->setModel(index);

	return editor;
}

void VisibilityDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	AppearanceItem* item=static_cast<AppearanceItem*>((void*)index.data().toLongLong());
	if(!item){
		QStyledItemDelegate::setEditorData(editor, index);
		return;
	}

	HoopsVisibilitySettingDialog *starEditor = qobject_cast<HoopsVisibilitySettingDialog *>(editor);
	starEditor->setAppearance(item);
	starEditor->setModel(index);
}

void VisibilityDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	//if (index.data().canConvert<StarRating>()) {
	//	StarEditor *starEditor = qobject_cast<StarEditor *>(editor);
	//	model->setData(index, QVariant::fromValue(starEditor->starRating()));
	//} else {
	//	
	//}
	QStyledItemDelegate::setModelData(editor, model, index);
}


void VisibilityDelegate::updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	//editor->setGeometry(option.rect);
	//QStyledItemDelegate::updateEditorGeometry(editor,option,index);
	//editor->setGeometry(option.rect.x(), option.rect.y(), 200, 90);
}

