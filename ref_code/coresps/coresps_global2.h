#ifndef CORESPS_GLOBAL2_H
#define CORESPS_GLOBAL2_H


#ifdef CORESPS_LIB
# define CORESPS_EXPORT __declspec(dllexport) 
#else
# define CORESPS_EXPORT __declspec(dllimport) 
#endif


#endif