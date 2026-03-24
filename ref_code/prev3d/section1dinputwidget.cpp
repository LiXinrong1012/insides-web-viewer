#include "section1dinputwidget.h"
#include "ui_section1dinputwidget.h"


static bool _String2FloatVec( const QString& str, QList<double>& vec )
{
	QStringList strVec=str.split(",");
	int n=strVec.size();
	for(int i=0;i<n;++i)
	{
		double x=strVec[i].toDouble();
		vec.push_back(x);
	}
	return true;
}

Section1DInputWidget::Section1DInputWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::Section1DInputWidget();
	ui->setupUi(this);

	onTypeChanged();
}

Section1DInputWidget::~Section1DInputWidget()
{
	delete ui;
}

void Section1DInputWidget::onTypeChanged()
{
	int currType=ui->_type->currentIndex();

	switch(currType){
	case 0:	//Ô²
		setVisual_Circle(true);
		setVisual_Ellipse(false);
		setVisual_Rectangle(false);
		setVisual_Userdefined(false);
		break;
	case 1:	// ·½
		setVisual_Circle(false);
		setVisual_Ellipse(false);
		setVisual_Rectangle(true);
		setVisual_Userdefined(false);
		break;
	case 2:	//ÍÖÔ²
		setVisual_Circle(false);
		setVisual_Ellipse(true);
		setVisual_Rectangle(false);
		setVisual_Userdefined(false);
		break;
	case 3:
		setVisual_Circle(false);
		setVisual_Ellipse(false);
		setVisual_Rectangle(false);
		setVisual_Userdefined(true);
		break;
	}

}

void Section1DInputWidget::setVisual_Circle( bool flag )
{
	ui->_radius->setVisible(flag);
	ui->_txtRadius->setVisible(flag);

}

void Section1DInputWidget::setVisual_Ellipse( bool flag )
{
	ui->_xradius->setVisible(flag);
	ui->_yradius->setVisible(flag);
	ui->_txtXRadius->setVisible(flag);
	ui->_txtYRadius->setVisible(flag);
}

void Section1DInputWidget::setVisual_Rectangle( bool flag )
{
	ui->_xlength->setVisible(flag);
	ui->_ylength->setVisible(flag);
	ui->_txtXLength->setVisible(flag);
	ui->_txtYLength->setVisible(flag);
}

void Section1DInputWidget::setVisual_Userdefined( bool flag )
{
	ui->_points->setVisible(flag);
	ui->_txtPoints->setVisible(flag);
}


bool Section1DInputWidget::onOKClicked()
{
	_section1DPoints.clear();
	switch(ui->_type->currentIndex())
	{
	case 0:
		{
			int slices=ui->_slice->value();
			double radius=ui->_radius->value();
			for(int i=0;i<slices;++i)
				_section1DPoints<<radius*cos(3.1415926*2*i/slices)<<radius*sin(3.1415926*2*i/slices);
		}
		break;
	case 1:
		{
			double xlength=ui->_xlength->value()/2;
			double ylength=ui->_ylength->value()/2;

			_section1DPoints<<-xlength<<-ylength
				<<xlength<<-ylength
				<<xlength<<ylength
				<<-xlength<<ylength;
		}
		break;
	case 2:
		{
			int slices=ui->_slice->value();
			double xradius=ui->_xradius->value();
			double yradius=ui->_yradius->value();
			for(int i=0;i<slices;++i)
				_section1DPoints<<xradius*cos(3.1415926*2*i/slices)<<yradius*sin(3.1415926*2*i/slices);
		}
	case 3:
		{
			QString pointsStr=ui->_points->text();
			_String2FloatVec(pointsStr,_section1DPoints);
		}
		break;
	}
	QString paraStr=ui->_parameters->text();
	_String2FloatVec(paraStr,_section1DParameters);
	return true;
}


QList<double> Section1DInputWidget::get1DSectionPoints()
{
	return _section1DPoints;
}

QList<double> Section1DInputWidget::get1DParameters()
{
	return _section1DParameters;
}

