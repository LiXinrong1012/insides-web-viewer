#include "applicationpropertydialog.h"

#include "document.h"
#include "applicationproperty.h"

#include "dirconfigwidget.h"
#include "solveconfigwidget.h"
#include "formatconfigwidget.h"
#include "customconfigwidget.h"
#include "systemconfigwidget.h"
#include "filemanager.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QGroupBox>

using INSEditor::Document;

ApplicationPropertyDialog::ApplicationPropertyDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QHBoxLayout* layout = new QHBoxLayout;
	
	_dirConfigWidget = new DirConfigWidget();
	layout->addWidget(_dirConfigWidget);
	_widgetList<<_dirConfigWidget;

	_solveConfigWidget = new SolveConfigWidget();
	layout->addWidget(_solveConfigWidget);
	_widgetList<<_solveConfigWidget;

	_formatConfigWidget = new FormatConfigWidget();
	layout->addWidget(_formatConfigWidget);
	_widgetList<<_formatConfigWidget;

	_customConfigWidget = new CustomConfigWidget();
	layout->addWidget(_customConfigWidget);
	_widgetList<<_customConfigWidget;

	_systemConfigWidget = new SystemConfigWidget();
	layout->addWidget(_systemConfigWidget);
	_widgetList<<_systemConfigWidget;

	ui.showGroupBox->setLayout(layout);
	
	if (INSEditor::Document::instance()->getProperties())
	{
		_dirConfigWidget->setViewPathEditText(INSEditor::Document::instance()->getProperties()->viewerExecutablePath);
		_dirConfigWidget->setSolverPathEditText(INSEditor::Document::instance()->getProperties()->solverExecutablePath);
		_dirConfigWidget->setFileDiffEditText(INSEditor::Document::instance()->getProperties()->fileDiffExecutablePath);
		_dirConfigWidget->setMaterialLibraryEditText(INSEditor::Document::instance()->getProperties()->materialLibraryPath);

		_solveConfigWidget->setLogsSpinBoxValue(Document::instance()->getProperties()->logsUpdateFrequency);
		_solveConfigWidget->setTreeSpinBoxValue(Document::instance()->getProperties()->treeProcessUpdateFrequency);
		_solveConfigWidget->setMaxSolveNumber(Document::instance()->getProperties()->maxSolveNumber);
		_solveConfigWidget->setIsShowSolver(Document::instance()->getProperties()->isShowSolverUI);

		_formatConfigWidget->setIndentationValue(Document::instance()->getProperties()->formatIndentationValue);
		_formatConfigWidget->setLineMaxNumValue(Document::instance()->getProperties()->formatLineMaxNumValue);

		_customConfigWidget->setIsShowLastFiles(Document::instance()->getProperties()->isShowLastOpenedFiles);
		_customConfigWidget->setIsCreateModelTree(Document::instance()->getProperties()->isCreateModelTree);
		_customConfigWidget->setIsAutoShowHelp(Document::instance()->getProperties()->isAutoShowHelp);

		_systemConfigWidget->setAutoUpdate(Document::instance()->getProperties()->isAutoCheckUpdate);
	}

	connect(ui.savePushButton,SIGNAL(clicked()),this,SLOT(onSavePushButtonClicked()));
	connect(ui.selectListWidget,SIGNAL(	currentRowChanged  ( int  )),this,SLOT(onTreeItemClicked ( int  )));

	hideAllWidget();
	_dirConfigWidget->show();
}

ApplicationPropertyDialog::~ApplicationPropertyDialog()
{
}

void ApplicationPropertyDialog::onSavePushButtonClicked()
{
	INSEditor::ApplicationProperty* ap = INSEditor::Document::instance()->getProperties();

	ap->viewerExecutablePath = _dirConfigWidget->getViewPathEditText();
	ap->solverExecutablePath = _dirConfigWidget->getSolverPathEditText();
	ap->fileDiffExecutablePath = _dirConfigWidget->getFileDiffEditText();
	ap->materialLibraryPath = _dirConfigWidget->getMaterialLibraryEditText();

	ap->logsUpdateFrequency = _solveConfigWidget->getLogsSpinBoxValue();
	ap->treeProcessUpdateFrequency = _solveConfigWidget->getTreeSpinBoxValue();
	ap->maxSolveNumber = _solveConfigWidget->getMaxSolveNumber();
	ap->isShowSolverUI = _solveConfigWidget->isShowSolver();

	ap->formatIndentationValue = _formatConfigWidget->getIndentationValue();
	ap->formatLineMaxNumValue = _formatConfigWidget->getLineMaxNumValue();

	ap->isShowLastOpenedFiles = _customConfigWidget->isShowLastFiles();
	ap->isCreateModelTree = _customConfigWidget->isCreateModelTree();
	ap->isAutoShowHelp = _customConfigWidget->isAutoShowHelp();

	ap->isAutoCheckUpdate = _systemConfigWidget->isAutoUpdate();

	ap->save();
	this->close();
}

void ApplicationPropertyDialog::onTreeItemClicked( int row )
{
	hideAllWidget();

	QString text = ui.selectListWidget->item(row)->text();

	if(!text.compare("Dir",Qt::CaseInsensitive))
		_dirConfigWidget->show();
	else if(!text.compare("Solver",Qt::CaseInsensitive))
		_solveConfigWidget->show();
	else if(!text.compare("Format",Qt::CaseInsensitive))
		_formatConfigWidget->show();
	else if(!text.compare("Custom",Qt::CaseInsensitive))
		_customConfigWidget->show();
	else if(!text.compare("System",Qt::CaseInsensitive))
		_systemConfigWidget->show();
	else
		_dirConfigWidget->show();
}

void ApplicationPropertyDialog::hideAllWidget()
{
	foreach(QWidget* widget,_widgetList)
		widget->hide();
}
