#ifndef RENDERVIEW2_H
#define RENDERVIEW2_H

#include "Base/view.h"

class TmpWidget2;

class RenderView2 : public Base::View
{
	Q_OBJECT

public:
	RenderView2(QObject *parent=0);
	~RenderView2();

	virtual QWidget* getWidget();
private:
	TmpWidget2* _widget;
	
};

#endif // RENDERVIEW2_H
