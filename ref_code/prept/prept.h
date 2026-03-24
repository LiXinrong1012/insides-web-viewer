#ifndef PREPT_H
#define PREPT_H

#include "prept/prept_global.h"
#include "prept/insuiplugin.h"

class ModelTreeWidget;


class PREPT_EXPORT PREPUIPlugin : public QObject, public INSUIPlugin
{
	Q_OBJECT
	Q_INTERFACES(INSUIPlugin)

public:
	PREPUIPlugin();
	~PREPUIPlugin();

	virtual QString getKeyname();
	virtual void initUI(QMainWindow* mainWindow);

	private slots:
		void onDisableUIUpdating(bool b);

private:
	ModelTreeWidget* _modelTreeWidget;

};

#endif // PREPT_H
