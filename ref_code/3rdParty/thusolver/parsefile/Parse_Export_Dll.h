#ifdef	PARSE_EXPORT_DLL
#define PARSE_EXPORT  __declspec(dllexport)
#else
#define PARSE_EXPORT  __declspec(dllimport)
#endif