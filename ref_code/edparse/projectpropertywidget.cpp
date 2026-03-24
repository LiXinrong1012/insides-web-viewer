#include "projectpropertywidget.h"
#include "edcore/project.h"

#include <QFileInfo>
#include <QDateTime>

ProjectPropertyWidget::ProjectPropertyWidget(QWidget *parent)
	: QWidget(parent)
	,_project(NULL)
{
	ui.setupUi(this);

	connect(ui.includeDirLineEdit,SIGNAL(textChanged()),this,SLOT(saveState()));
	connect(ui.logTextEdit,SIGNAL(textChanged()),this,SLOT(saveState()));
}


ProjectPropertyWidget::~ProjectPropertyWidget()
{
}

void ProjectPropertyWidget::saveState()
{
	if(!_project)
		return;

	_project->setIncludeDirectory(ui.includeDirLineEdit->text());
	_project->setLog(ui.logTextEdit->toPlainText());
	_project->save();
}

void ProjectPropertyWidget::setProject( INSEditor::Project* project )
{
	_project=project;
	if(!project){
		return;
	}
	ui.includeDirLineEdit->setText(project->getIncludeDirectory());
	ui.logTextEdit->setText(project->getLog());

	QFileInfo info(project->getDirectory());
	ui.createTimeLineEdit->setText(info.created().toString(Qt::ISODate));
	ui.lastEditTimeEdit->setText(info.lastModified().toString(Qt::ISODate));
}
