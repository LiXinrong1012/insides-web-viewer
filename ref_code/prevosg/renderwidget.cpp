#include "renderwidget.h"
#include "ui_renderwidget.h"
#include <QVBoxLayout>

RenderWidget::RenderWidget(QWidget *parent,osg::Node *scene)
	: QWidget(parent)
{
	ui = new Ui::RenderWidget();
	ui->setupUi(this);

	QWidget* renderWidget = getRenderWidget( createGraphicsWindow(0,0,100,100), scene);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(renderWidget);
	layout->setContentsMargins(0, 0, 0, 1);
	setLayout( layout );

	connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
	_timer.start( 10 );
}

RenderWidget::~RenderWidget()
{
	delete ui;
}

QWidget* RenderWidget::getRenderWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene )
{
	osg::Camera* camera = this->getCamera();
	camera->setGraphicsContext( gw );

	const osg::GraphicsContext::Traits* traits = gw->getTraits();

	camera->setClearColor( osg::Vec4(0.0, 0.0, 0.0, 1.0) );
	camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
	camera->setProjectionMatrixAsPerspective(45.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 0.1f, 100.0f );
	camera->setViewMatrixAsLookAt(osg::Vec3d(0, 0, 1), osg::Vec3d(0, 0, 0), osg::Vec3d(0, 1, 0));

	osg::StateSet* globalStateset = camera->getStateSet();
	if (globalStateset)
	{
		osg::LightModel* lightModel = new osg::LightModel;
		lightModel->setAmbientIntensity(osg::Vec4(0,0,0,0));
		globalStateset->setAttributeAndModes(lightModel, osg::StateAttribute::ON);
	}

	this->setSceneData( scene );
//	this->addEventHandler(new ManipulatorSceneHandler());

	return gw->getGLWidget();
}

osgQt::GraphicsWindowQt* RenderWidget::createGraphicsWindow( int x, int y, int w, int h, const std::string& name/*=""*/, bool windowDecoration/*=false */ )
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowName = name;
	traits->windowDecoration = windowDecoration;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = ds->getNumMultiSamples();

	return new osgQt::GraphicsWindowQt(traits.get());
}

void RenderWidget::paintEvent( QPaintEvent* event )
{
	frame(); 
}

