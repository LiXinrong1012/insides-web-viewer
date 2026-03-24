#include "testmaterialdialog.h"
#include "ui_testmaterialdialog.h"

TestMaterialDialog::TestMaterialDialog(QWidget *parent)
	: QDialog(parent)
	,_addClicked(false)
{
	ui = new Ui::TestMaterialDialog();
	ui->setupUi(this);

	connect(ui->addPushbutton,SIGNAL(clicked()),this,SLOT(onAddPushButtonClicked()));
}

TestMaterialDialog::~TestMaterialDialog()
{
	delete ui;
}

void TestMaterialDialog::initList( const QString& list1,const QString& list2 )
{
	QStringList strList1 = list1.split(";");
	QStringList strList2 = list2.split(";");

	ui->materialListWidget->clear();
	ui->environmentListWidget->clear();

	ui->materialListWidget->addItems(strList1);
	ui->environmentListWidget->addItems(strList2);
}

void TestMaterialDialog::onAddPushButtonClicked()
{
	QListWidgetItem* item1 = ui->materialListWidget->currentItem();
	QListWidgetItem* item2 = ui->environmentListWidget->currentItem();
	if(!item1)
		item1 = ui->materialListWidget->item(0);
	if(!item2)
		item2 = ui->environmentListWidget->item(0);

	this->_currentMaterial = item1->text();
	this->_currentEnvironment = item2->text();

	_ambient = ui->ambientLineEdit->text();
	_specular = ui->specularLineEdit->text();
	_emission = ui->emissionLineEdit->text();
	_diffuse = ui->diffuseLineEdit->text();
	_gloss = ui->glossSpinBox->value();
	_addClicked = true;
	this->close();
}

const QString& TestMaterialDialog::getAmbientColor()
{
	return _ambient;
}

const QString& TestMaterialDialog::getSpecularColor()
{
	return _specular;
}

const QString& TestMaterialDialog::getEmissionColor()
{
	return _emission;
}

int TestMaterialDialog::getGloss()
{
	return _gloss;
}

const QString& TestMaterialDialog::getDiffuseColor()
{
	return _diffuse;
}

