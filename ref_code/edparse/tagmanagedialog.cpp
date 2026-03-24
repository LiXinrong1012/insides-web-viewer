#include "tagmanagedialog.h"
#include "ui_tagmanagedialog.h"

#include "edcore/document.h"
#include "edcore/solution.h"
#include "edcore/project.h"

#include <QInputDialog>

using namespace INSEditor;

TagManageDialog::TagManageDialog(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::TagManageDialog();
	ui->setupUi(this);

	QStringList tags = Document::instance()->getSolution()->getTagList();
	ui->tagsListWidget->addItems(tags);

	connect(ui->delBtn,SIGNAL(clicked()),this,SLOT(onDelBtnClicked()));
	connect(ui->newTagsBtn,SIGNAL(clicked()),this,SLOT(onNewTagsBtnClicked()));
}

TagManageDialog::~TagManageDialog()
{
	delete ui;
}

void TagManageDialog::onNewTagsBtnClicked()
{
	QString tags = QInputDialog::getText(this,tr("New Tag"),tr("New Tag Name(Support multiple, use';' separate)"));
	if(tags.isEmpty())
		return;

	QStringList allTags=tags.split(";",QString::SkipEmptyParts);
	QStringList originalTags=INSEditor::Document::instance()->getSolution()->getTagList();

	foreach(QString str,allTags)
	{
		if(!originalTags.contains(str,Qt::CaseInsensitive))
			originalTags.push_back(str);
	}
	originalTags.sort();
	INSEditor::Document::instance()->getSolution()->setTagList(originalTags);

	ui->tagsListWidget->clear();
	ui->tagsListWidget->addItems(originalTags);
}

void TagManageDialog::onDelBtnClicked()
{
	QString tag = ui->tagsListWidget->currentItem()->text();
	QStringList originalTags=INSEditor::Document::instance()->getSolution()->getTagList();
	originalTags.removeOne(tag);

	Document::instance()->getSolution()->setTagList(originalTags);

	QList<Project*> proList = Document::instance()->getSolution()->getAllProjects();
	foreach(Project* pro, proList)
	{
		QStringList tags = pro->getTags();
		tags.removeOne(tag);
		pro->setTags(tags);
	}

	ui->tagsListWidget->clear();
	ui->tagsListWidget->addItems(originalTags);
}

