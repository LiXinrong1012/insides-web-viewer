#include "dirconfigwidget.h"
#include "ui_dirconfigwidget.h"

#include <QFileDialog>

DirConfigWidget::DirConfigWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::DirConfigWidget();
	ui->setupUi(this);

	connect(ui->viewerSelectPathToolButton,SIGNAL(clicked()),this,SLOT(onViewerSelectPathToolButtonClicked()));
	connect(ui->solverSelectPathToolButton,SIGNAL(clicked()),this,SLOT(onSolverSelectPathToolButtonClicked()));
	connect(ui->diffExeSelectPathToolButton,SIGNAL(clicked()),this,SLOT(onDiffExeSelectPathToolButtonClicked()));
}

DirConfigWidget::~DirConfigWidget()
{
	delete ui;
}

void DirConfigWidget::onViewerSelectPathToolButtonClicked()
{
	QString filePath = QFileDialog::getOpenFileName(this,tr("Select file position"),".","exe file(*.exe)");
	if(filePath.isEmpty())
		return;
	ui->viewerPathLineEdit->setText(filePath);
	ui->viewerPathLineEdit->setToolTip(filePath);
}

void DirConfigWidget::onSolverSelectPathToolButtonClicked()
{
	QString filePath = QFileDialog::getOpenFileName(this,tr("Select file position"),".","exe file(*.exe)");
	if(filePath.isEmpty())
		return;
	ui->solverPathLineEdit->setText(filePath);
	ui->solverPathLineEdit->setToolTip(filePath);
}

void DirConfigWidget::onSelectPathToolButton_3Clicked()
{
	QString filePath = QFileDialog::getOpenFileName(this,tr("Select file position"),".","exe file(*.exe)");
	if(filePath.isEmpty())
		return;
	ui->fileDiffLineEdit->setText(filePath);
	ui->fileDiffLineEdit->setToolTip(filePath);
}

void DirConfigWidget::setViewPathEditText( const QString& text )
{
	ui->viewerPathLineEdit->setText(text);
	ui->viewerPathLineEdit->setToolTip(text);
}

void DirConfigWidget::setSolverPathEditText( const QString& text )
{
	ui->solverPathLineEdit->setText(text);
	ui->solverPathLineEdit->setToolTip(text);
}

void DirConfigWidget::setFileDiffEditText( const QString& text )
{
	ui->fileDiffLineEdit->setText(text);
	ui->fileDiffLineEdit->setToolTip(text);
}

QString DirConfigWidget::getViewPathEditText()
{
	return ui->viewerPathLineEdit->text();
}

QString DirConfigWidget::getSolverPathEditText()
{
	return ui->solverPathLineEdit->text();
}

QString DirConfigWidget::getFileDiffEditText()
{
	return ui->fileDiffLineEdit->text();
}

void DirConfigWidget::setMaterialLibraryEditText( const QString& text )
{
	ui->materialLibraryLineEdit->setText(text);
	ui->materialLibraryLineEdit->setToolTip(text);
}

QString DirConfigWidget::getMaterialLibraryEditText()
{
	return ui->materialLibraryLineEdit->text();
}
