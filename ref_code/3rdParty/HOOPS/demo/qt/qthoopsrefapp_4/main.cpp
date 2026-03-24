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
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/main.cpp,v 1.42 2010-10-26 23:40:17 david Exp $
//


#include <qapplication.h>
#include <qmessagebox.h>
#include <qobject.h>

#if 0
//#ifdef OSX_SYSTEM
#include <qplatinumstyle.h>
#endif

#include "HDB.h"
#include "HQApplication.h"
#include "HQWidget.h"

#include "HTManager.h"

#include "hc.h"
#include "hversion.h"

#ifdef PARASOLID
#include "parasolid_kernel.h"
#include "kernel_interface.h"
#include "hp_bridge.h"
#endif


/*global hoops database object*/
HDB * m_pHDB=0;

HQApplication * m_pHQApplication=0;

class timer : public QObject {
public:
	int id;
	timer( int ms ) {
		id = startTimer( ms );
	};
	~timer() {
		killTimer(id);
	};

    void timerEvent( QTimerEvent * ) {
		float time;

		HC_Show_Time( &time );
		HDB::GetHTManager()->Tick( time );
	};
};

#ifdef PARASOLID
void SetupParasolid()
{
	#ifdef IS_WIN

 	unsigned long length;
	auto	HKEY 		app_name;
	auto	DWORD		type;
    auto	char 		return_string[2048];
    auto	char 		InstallationDirectory[2048];
	
	if (RegOpenKeyEx (HKEY_CURRENT_USER, "HOOPS", 0L,
			  KEY_QUERY_VALUE, &app_name) != ERROR_SUCCESS)
	    length = 0; /* Explicit failure */
	else
	{
		length = sizeof (return_string);
		if (RegQueryValueEx (app_name, "INSTALLATION_DIRECTORY", NULL, &type,
				 (LPBYTE)return_string,
				 &length) != ERROR_SUCCESS)
			length = 0;	/* Explicit Failure */
	}
	RegCloseKey (app_name);

	if (length > 0)
		sprintf (InstallationDirectory, return_string);
	else
	{
		sprintf (InstallationDirectory, "..\\..");
//		AfxMessageBox("Could not find Registry entries to determine location of your HOOPS Installation.\nYou may not be able to load in Parasolid X_T file or run the Application's help pages");
	}
	#endif

 	char	SchemaPath[256], PartsDirectory[512];

	sprintf(SchemaPath, "%s\\parasolid\\schema", InstallationDirectory);
	sprintf(PartsDirectory, "%s\\parasolid\\parts", InstallationDirectory);

	SetCurrentDirectory(PartsDirectory);

	HP_Init(SchemaPath, PK_LOGICAL_false);

	PK_TOPOL_facet_mesh_o_t     generation_settings;

	PK_TOPOL_facet_mesh_o_m( generation_settings );

	generation_settings.shape = PK_facet_shape_convex_c ;
	generation_settings.match = PK_facet_match_topol_c;
	generation_settings.density = PK_facet_density_no_view_c;
	generation_settings.cull = PK_facet_cull_none_c;
	generation_settings.n_loops = 0;
	generation_settings.loops = 0;
	generation_settings.max_facet_sides = 3;
	generation_settings.is_min_facet_width = PK_LOGICAL_false;
	generation_settings.min_facet_width = 0;
	generation_settings.is_max_facet_width = PK_LOGICAL_false;
	generation_settings.max_facet_width = 0;
	generation_settings.is_curve_chord_tol = PK_LOGICAL_false;
	generation_settings.curve_chord_tol = 0;
	generation_settings.is_curve_chord_max = PK_LOGICAL_false;
	generation_settings.curve_chord_max = 0;
	generation_settings.is_curve_chord_ang = PK_LOGICAL_true;
	generation_settings.curve_chord_ang = 0.6; //radians
	generation_settings.is_surface_plane_tol = PK_LOGICAL_false;
	generation_settings.surface_plane_tol = 0.0;
	generation_settings.is_surface_plane_ang = PK_LOGICAL_true; // was false, i.e. use Parasolid defaults
	generation_settings.surface_plane_ang = 0.25; // was zero, .4 begins to improve things, smaller is finer.  This controls tessellation at non-edge boundaries.
	generation_settings.is_facet_plane_tol = PK_LOGICAL_false;
	generation_settings.facet_plane_tol = 0.0;
	generation_settings.is_facet_plane_ang = PK_LOGICAL_true;
	generation_settings.facet_plane_ang = 0.01; // radians   // was .02.  This controls tessellation at edge boundaries.
	generation_settings.is_local_density_tol = PK_LOGICAL_false;
	generation_settings.local_density_tol = 0.0;
	generation_settings.is_local_density_ang = PK_LOGICAL_false;
	generation_settings.local_density_ang = 0.0;

	HP_Set_Tessellation_Options(0, 0, &generation_settings);
	HP_Set_Rendering_Options("merge faces = off");


}
#endif

#if 0
/*needed for blowfish password for now*/
#include "hpi_encoding.h" 
#endif

int main( int argc, char **argv )
{	

#if defined(INTERNAL_RELEASE_LICENSE) && !defined(_DEBUG)
	HC_Define_System_Options( INTERNAL_RELEASE_LICENSE );
	HC_Define_System_Options("no warnings, no info, no errors, no fatal errors, no message limit");
#else
	HC_Define_System_Options("no message limit");
#endif

#ifdef OSX_SYSTEM
	HC_Define_System_Options("font directory = (/Library/Fonts, ~/Library/Fonts)");	
#endif

	/*initalize global hoops database object*/
	m_pHDB = new HDB();
	m_pHDB->Init();

	//QApplication::setColorSpec( QApplication::ManyColor );	
	QApplication * a = new QApplication(argc,argv);	

	//This work around is temporary, it should not be needed 
	//with the next version of QT	
	a->setQuitOnLastWindowClosed(false);

	m_pHDB->SetDriverType(HQWidget::ChooseDriver());
	
	a->setQuitOnLastWindowClosed(true);

#ifdef PARASOLID
	SetupParasolid();	
#endif

	if(argc == 2){
		m_pHQApplication = new HQApplication(a, argv[1]);
	}else{
		m_pHQApplication = new HQApplication(a);
	}

	timer *main_timer = new timer(10);
	a->exec();

	#ifdef PARASOLID
		HP_Close();
	#endif

	delete main_timer;
	delete m_pHDB;
 	return 1;
}


