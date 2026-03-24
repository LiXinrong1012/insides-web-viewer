//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/HQFrameRateDlg.cpp,v 1.8 2008-12-09 00:04:42 david Exp $
//

#if 0

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

	//qt includes
#include <QtGui>
#include <QtCore>

	//local includes
#include "HQFrameRateDlg.h"
#include "MyHQWidget.h"
#include "HConstantFrameRate.h"


HQFrameRateDlg::HQFrameRateDlg( QWidget* parent,const char * name, HBaseView *view)
	:QDialog()
{

	FRState = false;
	minimum_FR = 10;
	OpStarted = false;
	_parent = parent;

	

	QTabWidget * tabs = new QTabWidget;
	QVBoxLayout * dialog_layout = new QVBoxLayout;
	setLayout(dialog_layout);
	
	dialog_layout->addWidget(tabs);

	// The three buttons at the bottom of the dialog
	QWidget* buttons = new QWidget;
		QHBoxLayout* button_layout = new QHBoxLayout;

		QPushButton* ok_button = new QPushButton("OK");
		connect(ok_button, SIGNAL(clicked()), this, SLOT(OnOKClicked()));
		ok_button->setEnabled(true);

		QPushButton* cancel_button = new QPushButton("Cancel");
		connect(cancel_button, SIGNAL(clicked()), this, SLOT(reject()));
		cancel_button->setEnabled(true);

		QPushButton* apply_button = new QPushButton("Apply");
		connect(apply_button, SIGNAL(clicked()), this, SLOT(Apply()));
		apply_button->setEnabled(true);


		button_layout->addWidget(ok_button);
		button_layout->addWidget(cancel_button);
		button_layout->addWidget(apply_button);
	buttons->setLayout(button_layout);

	dialog_layout->addWidget(buttons);

	QWidget* frame_rate_settings = new QWidget;
	QWidget* lod_settings = new QWidget;
	tabs->addTab(frame_rate_settings, "Frame Rate Settings");
	tabs->addTab(lod_settings, "Lod Settings");

	// set up dialog box layout
	QVBoxLayout * framerate_layout= new QVBoxLayout; 
	frame_rate_settings->setLayout(framerate_layout);
	//tabs->setFixedSize(344,364);
	
	maintain_fr = new QCheckBox("Maintain Constant Frame Rate");
	connect(maintain_fr, SIGNAL(clicked()), this, SLOT(OnFROnOff()));
	
	
	//framerate_label
	framerate_layout->addWidget(maintain_fr);

	QLabel* desired_label = new QLabel("Desired Minimum Frame Rate:");
	framerate_layout->addWidget(desired_label);

	minFR_field = new QLineEdit;
	minFR_field->setText("10");
	//connect(minFR_field, SIGNAL(textChanged(const QString &)), this, SLOT(OnChangeFR(const QString &))); 
	minFR_field->setEnabled(true);

	QWidget* fps_box = new QWidget;
	QBoxLayout * hbox1_layout = new QHBoxLayout;
	fps = new QLabel("fps");
	hbox1_layout->addWidget(minFR_field);
	hbox1_layout->addSpacing(10);
	hbox1_layout->addWidget(fps);
	fps_box->setLayout(hbox1_layout);

	framerate_layout->addWidget(fps_box);


	// Radio buttons
	QButtonGroup* radio_buttons = new QButtonGroup;
	reduction_allowed = new QRadioButton("Only Detail Reduction allowed");
	reduction_allowed->setChecked(true);
	//connect(maintainFR_button, SIGNAL(clicked()), parent, SLOT(OnViewFROptsChange())); 
	framerate_layout->addWidget(reduction_allowed);
	radio_buttons->addButton(reduction_allowed);

	QRadioButton* increase_allowed_once = new QRadioButton("Detail Increase allowed once");
	framerate_layout->addWidget(increase_allowed_once);
	radio_buttons->addButton(increase_allowed_once);

	QRadioButton* increase_allowed = new QRadioButton("Detail Increase Allowed"); 
	framerate_layout->addWidget(increase_allowed);
	radio_buttons->addButton(increase_allowed);

	radio_buttons->setExclusive(true);

	QGridLayout* lod_layout = new QGridLayout;
	lod_layout->setRowMinimumHeight(0, 20);
	lod_layout->setRowMinimumHeight(5, 20);
	lod_layout->setColumnMinimumWidth(0, 20);
	lod_layout->setColumnMinimumWidth(3, 20);
	lod_layout->addWidget(new QLabel("Detail Levels:"), 1, 1, Qt::AlignRight|Qt::AlignBottom);
	lod_layout->addWidget(new QLabel("Falloff Level:"), 1, 2, Qt::AlignLeft|Qt::AlignBottom);
	detail_level = new QComboBox;
	connect(detail_level, SIGNAL(activated(int)), this, SLOT(OnDetailLevel(int)));
	QStringList detail_levels;
	detail_levels << "1" << "2" << "3" << "4" << "5" << "6" << "7";
	detail_level->insertItems(0, detail_levels);
	falloff_level = new QComboBox;
	QStringList falloff_levels;
	falloff_levels << ".00" << ".10" << ".20" << ".30" << ".40" << ".50" << ".60" << ".70" << ".80" << ".90";
	falloff_level->insertItems(0, falloff_levels);
	lod_layout->addWidget(detail_level, 2, 1, Qt::AlignRight|Qt::AlignTop);
	lod_layout->addWidget(falloff_level, 2, 2, Qt::AlignLeft|Qt::AlignTop);
	use_lod_generation = new QCheckBox("Use High Quality LOD Generation");
	use_lod_generation->setChecked(true);
	lod_layout->addWidget(use_lod_generation, 4, 0, 1, 4, Qt::AlignCenter);
	slider = new QSlider(Qt::Horizontal);
	slider->setSingleStep(1);
	slider->setTickInterval(1);
	slider->setMaximum(1);
	slider->setTickPosition(QSlider::TicksAbove);
	lod_layout->addWidget(slider, 5,0,1,5, Qt::AlignCenter);

	lod_settings->setLayout(lod_layout);

	framerate_layout->activate();
	frame_rate_settings->show();
	tabs->show();

	dialog_layout->activate();

	/**********************************************************/
	//m_buselod = true;
	
	//m_init = false;
	m_pHView = view;
	m_pCFR = m_pHView->GetConstantFrameRateObject();
	HConstFRSimpType **sd;
	float fr;
	int length;

	mlist = 0;
	mlistLength = 0;

	m_pCFR->GetMode(&sd,&fr,&length);
	
 
	//m_bconstantframerate = sd ? 1 : 0;
	maintain_fr->setChecked(sd ? true : false);

	for (int i=0;i<length;i++)
	{
		if (sd[i]->GetType() == ConstFRSolidBBoxType)
			m_bboundingboxes = true;
		if (sd[i]->GetType() == ConstFRLodClampType || sd[i]->GetType()==
			ConstFRLodThresholdType)
			{
				//m_buselod = 1;
				use_lod_generation->setChecked(true);
				if (sd[i]->GetType() == ConstFRLodThresholdType){
					//m_bthreshold = true;
				}

		}
	}
	//m_min_framerate = (int)fr;
	m_increase=m_pCFR->GetDetailIncMode();

	/**********************************************************/

	show();
}

HQFrameRateDlg::~HQFrameRateDlg()
{
}

void HQFrameRateDlg::OnDetailLevel(int level){
	slider->setMaximum(level+1);
}


void HQFrameRateDlg::OnOKClicked(){
	Apply();
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());
    if (HC_Show_Existence("rendering options"))
	HC_UnSet_Rendering_Options();
    HC_Close_Segment();
	close();
}

void HQFrameRateDlg::OnCancelClicked(){
	HC_Open_Segment_By_Key(m_pHView->GetModelKey());
    if (HC_Show_Existence("rendering options"))
	HC_UnSet_Rendering_Options();
    HC_Close_Segment();
	close();
}

void HQFrameRateDlg::OnFROnOff()
{
	FRState = maintain_fr->isChecked();
	if(FRState){
		minFR_field->setEnabled(true);
	}
	else{
		minFR_field->setEnabled(false);
	}

}

void HQFrameRateDlg::Apply(){

	minimum_FR = minFR_field->text().toFloat();
	((MyHQWidget*)_parent)->OnViewFROptsChange();

	if (maintain_fr->isChecked())
	{

			// if we have an opengl card then don't do the wireframe case since OpenGL cards
			// do not typically provide good wireframe acceleration

			if (use_lod_generation->isChecked())
			{							 			
				if (streq(m_pHView->GetDriverType(), "opengl") || streq(m_pHView->GetDriverType(), "direct3d"))				
				{
					//HConstFRSimpType **mlist=new HConstFRSimpType *[3];						
					cleanupSimpList();
					mlistLength = 2;
					mlist=new HConstFRSimpType *[3];
					mlist[0] = new HFrNoSimp;
					mlist[1] = new HFrLodThreshold(0,6);
					if (m_bboundingboxes)
					{
						mlist[2] = new HFrSolidBBox;						
						m_pCFR->Init(minFR_field->text().toFloat(), mlist, 3);   
						mlistLength = 3;
					}
					else 
						m_pCFR->Init(minFR_field->text().toFloat(), mlist, 2);   

				}
				else
				{							
					//HConstFRSimpType **mlist=new HConstFRSimpType *[4];						
					cleanupSimpList();
					mlist=new HConstFRSimpType *[4];						
					mlistLength = 3;
					mlist[0] = new HFrNoSimp;
					mlist[1] = new HFrLodThreshold(0,6);
					mlist[2] = new HFrWireframe(1,1);						
 					if (m_bboundingboxes)
					{ 
						mlist[3] = new HFrSolidBBox;						
						m_pCFR->Init(minFR_field->text().toFloat(), mlist, 4);   
						mlistLength = 4;
					}
					else
						m_pCFR->Init(minFR_field->text().toFloat(), mlist, 3);   
				}
				//this is optional to precalculate the LOD settings..
				
 
			}
			else
			{

				if (streq(m_pHView->GetDriverType(), "opengl") || streq(m_pHView->GetDriverType(), "direct3d"))				
				{
 					//HConstFRSimpType **mlist=new HConstFRSimpType *[2];						
					cleanupSimpList();
					mlist=new HConstFRSimpType *[2];						
					mlistLength = 2;
					mlist[0] = new HFrNoSimp;
  					mlist[1] = new HFrSolidBBox(0,1);						

 					m_pCFR->Init(minFR_field->text().toFloat(),mlist,2);


				}
				else
				{
 					//HConstFRSimpType **mlist=new HConstFRSimpType *[3];						
					cleanupSimpList();
					mlist=new HConstFRSimpType *[3];						
					mlistLength = 3;
					mlist[0] = new HFrNoSimp;
 					mlist[1] = new HFrWireframe;						
					mlist[2] = new HFrSolidBBox(0,1);						
 					m_pCFR->Init(minFR_field->text().toFloat(),mlist,3);


				}
			}
			m_pCFR->SetDetailIncMode( reduction_allowed->isChecked() ? (DetailChangeMode)1 : (DetailChangeMode)0);
			m_pCFR->AdjustDefaultDetailLevelToModel();
			m_pCFR->Start();	
 		
		}	
		else
		{
			m_pCFR->Stop();	
			m_pCFR->Shutdown();   
			cleanupSimpList();
		}
}

void HQFrameRateDlg::OnChangeFR(const QString  & newFR)
{
	minimum_FR = newFR.toFloat();
	((MyHQWidget*)_parent)->OnViewFROptsChange();

}

 
void HQFrameRateDlg::cleanupSimpList(){

	for (int i=0;i<mlistLength;i++)
			delete mlist[i];

	delete [] mlist;
	mlist = 0;
	mlistLength = 0;

}


#endif





