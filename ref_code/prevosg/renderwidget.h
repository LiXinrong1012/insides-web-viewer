#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>
#include <QTimer>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgQt/GraphicsWindowQt>

#include <osg/MatrixTransform>
#include <osg/NodeVisitor>
#include <osg/Texture2D>

#include <osgGA/GUIEventAdapter>

#include <osg/Light>
#include <osg/LightModel>
#include <osg/LightSource>

namespace Ui {class RenderWidget;};

class RenderWidget : public QWidget,public osgViewer::Viewer
{
	Q_OBJECT

public:
	RenderWidget(QWidget *parent = 0,osg::Node *scene = NULL);
	~RenderWidget();

protected:
	virtual void paintEvent( QPaintEvent* event );

private:
	QWidget* getRenderWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene );
	osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false );
private:
	Ui::RenderWidget *ui;
	QTimer _timer;
};

#endif // RENDERWIDGET_H
