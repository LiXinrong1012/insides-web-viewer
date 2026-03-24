// HQtMain.cpp 
//  
// HOOPS/MVO and HOOPS/QT global variables are declared and initialized 
// One Qt QApplication object is instanced and configured 
// One initial HQApplication object is instanced 
// The Qt event processing loop is launched 
// Qt Headers 
#include <QApplication>
#include <QMessageBox>
#include <QObject>

// HOOPS/MVO Headers 
#include "HDB.h" 

// HOOPS/Qt Headers 
#include "HQApplication.h" 
#include "HQDeleter.h" 

#include "HTManager.h"

// HOOPS Headers 
#include "hc.h" 

// Create Global pointer to HOOPS/MVO class HDB 
HDB * m_pHDB=0; 

// Create a global pointer to HOOPS/Qt class HQDeleter 
HQDeleter * deleter=0; 
  

class timer : public QObject {
public:
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
private:
	int id;
};

int main( int argc, char **argv ) 
{  

	// Initialize the global HOOPS Database Object 
	m_pHDB = new HDB(); 
	m_pHDB->Init();


	// Create an HQDeleter object and initialize the global pointer 
	deleter = new HQDeleter();

	QApplication::setColorSpec( QApplication::ManyColor );

	// Create the one QApplication object 
	QApplication * a = new QApplication(argc,argv); 
	a->setQuitOnLastWindowClosed(false);


#if IS_OSX
	m_pHDB->SetDriverType("cocoa_opengl");
#else
	switch( QMessageBox::information( 0, "Visualize", 
		"Do you want use:", "&Opengl", 
#if IS_X11
		"&X11", 
#else 
		"&GDI", 
#endif
		0, 1)) { 

	    case 0:
	    	m_pHDB->SetDriverType("opengl");
		break;
	    case 1:
#if IS_X11
	    	m_pHDB->SetDriverType("x11");
#else
	    	m_pHDB->SetDriverType("msw");
#endif
		break;
	}
#endif

	a->setQuitOnLastWindowClosed(true);

	if(argc == 2){
		
		HQApplication * ha = new HQApplication(a, argv[1]);
		//NOP
		ha=ha;
	}else{

		HQApplication * ha = new HQApplication(a);
		//NOP
		ha=ha;
	}

	// Launch the Qt event processing loop 
	a->exec(); 

	// Clean up 
	delete m_pHDB;

	return EXIT_SUCCESS;

} 



