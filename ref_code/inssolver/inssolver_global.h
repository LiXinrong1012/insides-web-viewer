#ifndef INSSOLVER_GLOBAL_H
#define INSSOLVER_GLOBAL_H


#ifdef INSSOLVER_LIB
# define INSSOLVER_EXPORT _declspec(dllexport)
#else
# define INSSOLVER_EXPORT _declspec(dllimport)
#endif


extern "C" INSSOLVER_EXPORT void* createINSSolver();

#endif // INSSOLVER_GLOBAL_H


