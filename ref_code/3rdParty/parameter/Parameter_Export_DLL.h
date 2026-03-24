#pragma  once

#ifdef TDY_PARAMTER_LIB
# define PARAMETER_EXPORT __declspec(dllexport)
#else
# define PARAMETER_EXPORT __declspec(dllimport)
#endif