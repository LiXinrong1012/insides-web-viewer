#ifndef INSLIC_H
#define INSLIC_H


#ifdef INSLIC_LIB
# define INSLIC_EXPORT __declspec(dllexport)
#else
# define INSLIC_EXPORT __declspec(dllimport)
#endif

/*!
*	This header is used to support FlexNET license support.
*	@author Jerry He
*	@date	2014.6.18
*/

extern "C" 
{
	INSLIC_EXPORT bool init();
	INSLIC_EXPORT bool co(const char* feature,const char* ver);
	INSLIC_EXPORT bool ci(const char*feature);
	INSLIC_EXPORT void tc();
}


#endif // INSLIC_H
