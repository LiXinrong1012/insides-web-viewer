#pragma once

#include <QObject>
#include <QApplication>
// HOOPS/MVO Headers 
#include "HDB.h" 

// HOOPS/Qt Headers 
//#include "HQDeleter.h" 

#include "HTManager.h"

// HOOPS Headers 
#include "hc.h" 
#include "vlist.h"

// Create Global pointer to HOOPS/MVO class HDB 
HDB * m_pHDB=0; 

// Create a global pointer to HOOPS/Qt class HQDeleter 
//HQDeleter * deleter=0; 


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

int init_HOOPS()
{  

	// Initialize the global HOOPS Database Object 
	m_pHDB = new HDB(); 
	m_pHDB->Init();


	// Create an HQDeleter object and initialize the global pointer 
	//deleter = new HQDeleter();

	return 0;
} 

void destroy_HOOPS()
{
	// Clean up 
	delete m_pHDB;
}

struct DriverNamePair
{
	QString UiName;
	const char *DriverName;
};

#define countof(x) sizeof(x)/sizeof(x[0])

const char * choose_Driver()
{
#ifdef SOLARIS_SYSTEM
	const char * driver = 0;

	switch( QMessageBox::information( 0, "Qt HOOPS Viewer", 
		"Do you want use:", "&OpenGL",
		"&X11", 
		0)) 
	{ 
	case 0:
		driver = "opengl";
		break;
	case 1:
		driver = "x11";
		break;
	}

	return driver;

#else
	const DriverNamePair DRIVERS[] = {
#ifndef IS_OSX
		{"&OpenGL","opengl"},
#endif
		{"OpenGL &2","opengl2"},
		{"&DirectX 9","dx9"},
		{"&X11","x11"},
		{"&GDI","msw"},
		{"Cocoa OpenGL", "cocoa_opengl"}
	};	

	VList<const DriverNamePair*> available;

	// Check available drivers
	for (int i = 0 ; i < countof(DRIVERS) ; i++)
	{	
		if (HC_QShow_Existence(H_FORMAT_TEXT("/driver/%s",DRIVERS[i].DriverName),"self"))	
			available.AddLast(&DRIVERS[i]);
	}	

	const char *driver = 0;

	// If there's only one driver available, use it.
	if (available.Count() == 1)	
		driver = available.PeekFirst()->DriverName;	

	// Otherwise show a pop-up with the available drivers to let the user choose one.
	else if (available.Count() > 1)
	{
		QMessageBox msgBox(QMessageBox::Question,"Qt HOOPS Viewer","Do you want to use:");

		available.ResetCursor();
		while(available.PeekCursor())
		{
			msgBox.addButton(available.PeekCursor()->UiName,QMessageBox::AcceptRole);	
			available.AdvanceCursor();
		}

		msgBox.exec();
		QString which = msgBox.clickedButton()->text();			

		for (int i = 0 ; i < countof(DRIVERS) ; i++)
		{
			if (which == DRIVERS[i].UiName)
			{
				driver = DRIVERS[i].DriverName;
				break;
			}
		}
	}

	return driver;
#endif
}


const char * choose_DefaultDriver()
{
#ifdef SOLARIS_SYSTEM
	const char * driver = 0;

	switch( QMessageBox::information( 0, "Qt HOOPS Viewer", 
		"Do you want use:", "&OpenGL",
		"&X11", 
		0)) 
	{ 
	case 0:
		driver = "opengl";
		break;
	case 1:
		driver = "x11";
		break;
	}

	return driver;

#else
	const DriverNamePair DRIVERS[] = {
		{"&DirectX 9","dx9"},
#ifndef IS_OSX
		{"&OpenGL","opengl"},
#endif
		{"OpenGL &2","opengl2"},
		{"&X11","x11"},
		{"&GDI","msw"},
		{"Cocoa OpenGL", "cocoa_opengl"}
	};	

	VList<const DriverNamePair*> available;

	// Check available drivers
	for (int i = 0 ; i < countof(DRIVERS) ; i++)
	{	
		if (HC_QShow_Existence(H_FORMAT_TEXT("/driver/%s",DRIVERS[i].DriverName),"self"))	
			available.AddLast(&DRIVERS[i]);
	}	

	const char *driver = 0;

	// If there's only one driver available, use it.
	if (available.Count() >= 1)	
		driver = available.PeekFirst()->DriverName;	


	return driver;
#endif
}
