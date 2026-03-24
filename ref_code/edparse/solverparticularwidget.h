#ifndef SOLVERPARTICULARWIDGET_H
#define SOLVERPARTICULARWIDGET_H

#include <QWidget>
namespace Ui {class SolverParticularWidget;};

class SolverParticularWidget : public QWidget
{
	Q_OBJECT

public:
	SolverParticularWidget(QWidget *parent = 0);
	~SolverParticularWidget();

private:
	Ui::SolverParticularWidget *ui;
};

#endif // SOLVERPARTICULARWIDGET_H
