#include <QHBoxLayout>

#include "vieweroptionsdialog.h"
#include "ui_vieweroptionsdialog.h"

#include "lightingwidget.h"
#include "appsettings.h"

ViewerOptionsDialog::ViewerOptionsDialog(HBaseView* view)
	:_hBaseView(view)
{
	ui = new Ui::ViewerOptionsDialog();
	ui->setupUi(this);

	_lightingWidget = new LightingWidget(this);
	_lightingWidget->setHBaseView(view);
	_lightingWidget->updateLightingWidget();
	QHBoxLayout* layout = new QHBoxLayout(ui->showGroupBox);
	layout->addWidget(_lightingWidget);
	_widgetList << _lightingWidget;

	ui->showGroupBox->setLayout(layout);
}

ViewerOptionsDialog::~ViewerOptionsDialog()
{
	delete ui;
}

