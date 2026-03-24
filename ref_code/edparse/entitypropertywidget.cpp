#include "entitypropertywidget.h"
#include "edcore/entity.h"
#include "edcore/project.h"

#include <QFileInfo>
#include <QDateTime>

EntityPropertyWidget::EntityPropertyWidget(QWidget *parent)
	: QWidget(parent)
	,_entity(NULL)
{
	ui.setupUi(this);
	
	connect(ui.entityCopyCheckBox,SIGNAL(clicked()),this,SLOT(saveState()));
	connect(ui.logTextEdit,SIGNAL(textChanged()),this,SLOT(saveState()));
}

EntityPropertyWidget::~EntityPropertyWidget()
{
}

void EntityPropertyWidget::saveState()
{
	if(!_entity)
		return;

	if (ui.entityCopyCheckBox->isChecked())
		_entity->setCreateNewOneWhenCopy(true);
	else
		_entity->setCreateNewOneWhenCopy(false);

	_entity->setLog(ui.logTextEdit->toPlainText());
	_entity->getProject()->save();
}

void EntityPropertyWidget::setEntity( INSEditor::Entity* entity )
{
	_entity=entity;
	if(!entity){
		ui.entityCopyCheckBox->setChecked(false);
		ui.logTextEdit->setText(QString());
		return;
	}

	if(entity->isCreateNewOneWhenCopy())
		ui.entityCopyCheckBox->setChecked(true);
	else
		ui.entityCopyCheckBox->setChecked(false);

	ui.logTextEdit->setText(entity->getLog());

	QFileInfo info(entity->getFullFileName());

	if(!info.exists())
		return;

	ui.createTimeLineEdit->setText(info.created().toString(Qt::ISODate));
	ui.lastEditTimeEdit->setText(info.lastModified().toString(Qt::ISODate));
}
