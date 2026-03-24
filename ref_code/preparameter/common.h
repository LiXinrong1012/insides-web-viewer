#pragma once
#include <cassert>
//#include "BasicDataType.h"

#define RCS12 "$Id: common.h,v 1.2 2006/07/30 05:36:44 liberti Exp liberti $"
#define NOVARIABLE -1
#define OPERANDSTRBUF 64
#define EXPRESSIONSTRBUF 2048
#define LARGE 1E10

typedef int Int;

enum OperatorType
{
	SUM, OPT_DIFFERENCE,PRODUCT,FRACTION,POWER,PLUS,MINUS,
	OPT_CONST, VAR, POINTER, OPT_PARAS, 
	OPT_FUNCTION,
	OPT_ERROR
};

// utility functions
extern double Ev3NearZero(void);
extern double Ev3Infinity(void);
