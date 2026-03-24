#ifndef TESTMATERIALDIALOG_H
#define TESTMATERIALDIALOG_H

#include <QDialog>
namespace Ui {class TestMaterialDialog;};

class TestMaterialDialog : public QDialog
{
	Q_OBJECT

public:
	TestMaterialDialog(QWidget *parent = 0);
	~TestMaterialDialog();

	void initList(const QString& list1,const QString& list2);
	const QString& getCurrentMaterial(){return _currentMaterial;}
	const QString& getCurrentEnvironment(){return _currentEnvironment;}
	const QString& getAmbientColor();
	const QString& getSpecularColor();
	const QString& getEmissionColor();
	const QString& getDiffuseColor();
	int getGloss();
	bool isAddClicked(){return _addClicked;}

private slots:
	void onAddPushButtonClicked();

private:
	Ui::TestMaterialDialog *ui;
	QString _currentMaterial;
	QString _currentEnvironment;
	QString _ambient;
	QString _specular;
	QString _emission;
	QString _diffuse;
	int _gloss;
	bool _addClicked;
};

#endif // TESTMATERIALDIALOG_H
