// HQDeleter.cpp - implementation of the HOOPS/Qt class HQDeleter 
// More about this class 
  
  
// HOOPS/Qt includes 
#include "HQDeleter.h" 

// HOOPS/MVO includes 
#include "HTools.h"

#include <QEvent>
#include <QHash>
  

HQDeleter::HQDeleter( QObject * parent, const char * name ) 
 : QObject( parent ) 
{ 
	
	objects = new QHash<int, QObject*>;
} 

HQDeleter::~HQDeleter() 
{ 
	processDeletes();
	delete objects; 
} 
  

void HQDeleter::processDeletes() 
{ 
	
	QHash<int, QObject*>::iterator i = objects->begin();
	while( objects->erase(i) != objects->end() )
	{ 
		++i;
	} 
} 

void HQDeleter::detectOtherDelete() 
{ 
	objects->remove( objects->key(sender()) ); 
} 
  

bool HQDeleter::event( QEvent * e )
{
#if (QT_VERSION >= 200)
	if ( e && e->type() == QEvent::User ) {
#else
	if ( e && e->type() == 12345 ) {
#endif
		processDeletes();
		return true;
	}else{
		return false;
	}
}
  
void HQDeleter::deleteLater( QObject * o )
{
	if ( objects->count() == 0 ) {
#if (QT_VERSION >= 200)
		QEvent * e = new QEvent( QEvent::User );
#else
		QEvent * e = new QEvent( 12345 );
#endif

		QApplication::postEvent( this, e );
	}


	if ( !objects->contains( objects->key(o) ) ) {
		objects->insert( objects->key(o), (QObject*) o);
		connect( o, SIGNAL(destroyed()), this, SLOT(detectOtherDelete()) );
	}
	
}

 
