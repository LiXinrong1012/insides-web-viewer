#ifdef _MSC_VER		
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	include <windows.h>
#endif


#include "hc.h"

#ifdef WINDOWS_SYSTEM
#define USleep Sleep
#include <process.h>
#else
#define USE_PTHREADS_MUTEX 1
#include <unistd.h>
#define USleep usleep
#endif

#define HMUTEX_IMPLEMENT_MUTEX_FUNCTIONS
#include "hmutex.h"


#include <stdlib.h>
#include <stdio.h>



HMutex hoops_lock;

struct {
	HMutex mutex;
	int count;
} quit;

#ifdef WINDOWS_SYSTEM
void do_rotation(void * arg)
#else
void * do_rotation(void * arg)
#endif
{
	int i;
	char path[1024];

	sprintf(path,"?picture/%s",(char*)arg);

	for(i=0;i<360;i++){

		USleep(10);

		LOCK_MUTEX(hoops_lock);
			HC_Open_Segment(path);	
			HC_Orbit_Camera (1.0, 0.0);
			HC_Close_Segment();
		UNLOCK_MUTEX(hoops_lock);	
	}

	LOCK_MUTEX(quit.mutex);
	quit.count--;
	UNLOCK_MUTEX(quit.mutex);

#ifndef WINDOWS_SYSTEM
	return 0;
#endif
}

void * do_updates(void * arg)
{

	for(;;){
		
		USleep(10);

		LOCK_MUTEX(hoops_lock);
		HC_Update_Display ();
		UNLOCK_MUTEX(hoops_lock);

		LOCK_MUTEX(quit.mutex);
		if(quit.count==0){
			UNLOCK_MUTEX(quit.mutex);
			return 0;
		}
		UNLOCK_MUTEX(quit.mutex);
	}
	return 0;
}



int main()
{

	int i;


	char * hoops_paths[4] = {
		"left top window", 
		"left bottom window", 
		"right top window", 
		"right bottom window"
	};

	CREATE_MUTEX(hoops_lock);

 	CREATE_MUTEX(quit.mutex);


	HC_Define_Alias ("?vw", "?include library/volkswagen");
	HC_Open_Segment ("?vw");
		HC_Read_Metafile ("vw", ".", "");
		HC_Set_Visibility ("faces = off");
	HC_Close_Segment ();


	HC_Open_Segment ("?picture");

		HC_Open_Segment (hoops_paths[0]);
		HC_Set_Window (-0.95, 0.0, 0.0, 0.95);
		HC_Include_Segment ("?vw");
		HC_Close_Segment ();

		HC_Open_Segment (hoops_paths[1]);
		HC_Set_Window (-0.95, 0.0, -0.95, 0.0);
		HC_Include_Segment ("?vw");
		HC_Close_Segment ();

		HC_Open_Segment (hoops_paths[2]);
		HC_Set_Window ( 0.0, 0.95, 0.0, 0.95);
		HC_Include_Segment ("?vw");
		HC_Close_Segment ();

		HC_Open_Segment (hoops_paths[3]);
		HC_Set_Window (0.0, 0.95, -0.95, 0.0);
		HC_Include_Segment ("?vw");
		HC_Close_Segment ();

	HC_Close_Segment ();   

	HC_Update_Display ();

	quit.count=4;

#if WINDOWS_SYSTEM
	{
	    unsigned long thread[5];
	    for(i=0;i<4;i++) {
		    thread[i]=_beginthread(do_rotation, 0, (void*)hoops_paths[i]);
	    }
	    do_updates(0);
	}
#else
	{
	    pthread_t thread[5];
	    for(i=0;i<4;i++) {
		    pthread_create(&thread[i], 0, do_rotation, hoops_paths[i]);
	    }
	    pthread_create(&thread[4], 0, do_updates, 0);

	    for(i=0;i<5;i++) {
		    pthread_join(thread[i], 0);
	    }
	}
#endif

	DESTROY_MUTEX(hoops_lock);
 	DESTROY_MUTEX(quit.mutex);

	HC_Exit_Program ();

	return 1;
}


