#ifndef RENDERVIEW_H
#define RENDERVIEW_H

#include "base/view.h"

class RenderView : public Base::View
{
	Q_OBJECT

public:
	RenderView(QObject *parent=0);
	~RenderView();

	virtual QWidget* getWidget();
private:
	QWidget* m_widget;
	
};

#endif // RENDERVIEW_H
