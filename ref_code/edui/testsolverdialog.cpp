#include "testsolverdialog.h"
#include "ui_testsolverdialog.h"

#include "edcore/document.h"
#include "edcore/solution.h"
#include "edcore/project.h"
#include "edcore/solveprocess.h"

using namespace INSEditor;

TestSolverDialog::TestSolverDialog(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::TestSolverDialog();
	ui->setupUi(this);
}

TestSolverDialog::~TestSolverDialog()
{
	delete ui;
}

void TestSolverDialog::onConnect()
{
	Project* p=Document::instance()->getSolution()->getMainProject();
	if(p)
		p->openWithSolver2();
}

void TestSolverDialog::onStart()
{
	Project* p=Document::instance()->getSolution()->getMainProject();
	if(p){
		SendToServerMessage mes;
		mes.command=SendToServerMessage::START;
		mes.message="Try to start from Editor";
		p->getSolveProcess()->sendMessage(mes);
	}
}

void TestSolverDialog::onPause()
{
}

void TestSolverDialog::onRestart()
{
}

