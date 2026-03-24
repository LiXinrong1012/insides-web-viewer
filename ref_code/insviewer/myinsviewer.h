#ifndef MYINSVIEWER_H
#define MYINSVIEWER_H

#include "insviewer.h"
#include "insviewer_global.h"

#include <QObject>

class INSViewerManager;


class INSVIEWER_EXPORT MyINSViewer : public INSViewer
{
	
public:
	MyINSViewer();
	virtual ~MyINSViewer();

	virtual void setPara(const INSViewerPara& para);
	virtual void importModel(const QString& fullName);
	virtual void importResult();
	virtual void importEigen();
	virtual void fresh();
	virtual void heightLight();

private:
	INSViewerPara _viewerPara;
};

#endif // MYINSVIEWER_H
