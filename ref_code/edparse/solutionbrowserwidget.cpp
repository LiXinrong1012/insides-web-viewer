#include "solutionbrowserwidget.h"
#include "ui_solutionbrowserwidget.h"

#include "edcore/document.h"
#include "edcore/solution.h"

using namespace INSEditor;

SolutionBrowserWidget::SolutionBrowserWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::SolutionBrowserWidget();
	ui->setupUi(this);

	SolutionBrowserTreeWidget* tree = ui->treeWidget;
	tree->initHeader();

	connect(ui->cbFilterTags,SIGNAL(currentIndexChanged (int)),
		ui->treeWidget,SLOT(onTagsCurrentIndexChanged(int)));

	connect(ui->treeWidget,SIGNAL(tagsChanged()),this,SLOT(updateTags()));

	updateTags();
}

SolutionBrowserWidget::~SolutionBrowserWidget()
{
	delete ui;
}

SolutionBrowserTreeWidget* SolutionBrowserWidget::getSolutionBrowserTreeWidget()
{
	return ui->treeWidget;
}


void SolutionBrowserWidget::updateTags()
{
	Solution* solution=Document::instance()->getSolution();
	if(!solution)
		return;

	QStringList allTags=solution->getTagList();
	if(ui->cbFilterTags)
		ui->cbFilterTags->clear();
	ui->cbFilterTags->addItem("All Tags");
	ui->cbFilterTags->addItems(allTags);

	if(solution->getCurrentTag().isEmpty())
		ui->cbFilterTags->setCurrentIndex(0);
	else
		ui->cbFilterTags->setCurrentIndex(allTags.indexOf(solution->getCurrentTag()));

	ui->cbFilterTags->adjustSize();
}








