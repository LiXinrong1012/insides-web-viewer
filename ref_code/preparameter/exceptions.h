#pragma  once
#include <string>
#include <iostream>

using namespace std ;


#define RCS8 "$Id: exceptions.h,v 1.5 2003/10/08 11:13:58 liberti Exp liberti $"
#define HELPURL "http://liberti.dhs.org/"
#define NONE "[none]"
#define STDACTION cerr << strinterface << "::" << scope << ": in [" << operation << "]: " << description << ", code = " << code << ", see " << moreinfo << endl

class ErrBase
{
public:
	string strinterface;
	string scope;
	string operation;
	string description;
	string moreinfo;
	unsigned long code;
	ErrBase() :	code(0), strinterface(NONE), scope(NONE), operation(NONE), 
		description(NONE),  moreinfo(HELPURL) { STDACTION; }
	ErrBase(unsigned long mycode,
		string myif,
		string myscope,
		string myop,
		string mydesc,
		string myinfo) :
	code(mycode), strinterface(myif), scope(myscope), operation(myop), 
		description(mydesc), moreinfo(myinfo) { STDACTION; }
};

class ErrUnknown : public ErrBase
{ 
public:
	ErrUnknown(unsigned long mycode,
		string myif,
		string myscope,
		string myop,
		string mydesc,
		string myinfo) : 
	ErrBase(mycode, myif, myscope, myop, mydesc, myinfo) { STDACTION; }
};

class ErrNotPermitted : public ErrBase 
{ 
public:
	ErrNotPermitted(unsigned long mycode,
		string myif,
		string myscope,
		string myop,
		string mydesc,
		string myinfo) :
	ErrBase(mycode, myif, myscope, myop, mydesc, myinfo) { STDACTION; }
};

class ErrDivideByZero : public ErrBase { 
public:
	string dividend;
	ErrDivideByZero(unsigned long mycode,
		string myif,
		string myscope,
		string myop,
		string mydesc,
		string myinfo, 
		string mydiv) : 
	ErrBase(mycode, myif, myscope, myop, mydesc, myinfo),
		dividend(mydiv) { STDACTION; }
};