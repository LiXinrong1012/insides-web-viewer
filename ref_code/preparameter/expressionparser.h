#pragma once
// includes

#include <iostream>  // I/O
#include <sstream>
#include <strstream>
#include <string>    // strings
#include <map>       // map
#include <cctype>    // isalpha(), etc.
#include <cmath> 
#include "expression.h"
#include "link.h"

#define RCS9 "$Id: parser.h,v 1.7 2006/07/30 05:36:42 liberti Exp liberti $"

// global declarations
//using namespace std;

enum Token_value {
	PEV3NAME, PEV3NUMBER, PEV3END, PEV3PLUS = '+', PEV3NLPLUS = '|', 
	PEV3MINUS = '-', PEV3MUL = '*', PEV3DIV = '/', PEV3POWER = '^', 
	PEV3PRINT = ';', PEV3ASSIGN = '=', PEV3LP = '(', PEV3RP = ')',
	PEV3COMMA = ','
};

// constants
const double PEV3infinity = 1.0e300;
// #define PEV3PI 3.1415926535897932385
// #define PEV3E 2.7182818284590452354
// #define PEV3SIN45 0.707106781186548
// #define PEV3COS45 0.707106781186548
#define PEV3NOVARIABLE -1
#define PEV3UNKNOWNVAR -2



class ExpressionParser
{
public:
	ExpressionParser();
	~ExpressionParser();

	//Expression Parse( const char* buf, list<RigidNode*> & nl, int& nerrors );

	int	Parse( Expression& ret, const char* buf) ;

protected:
	virtual int dealWithName( Expression& ret,  const std::string& name);
	virtual std::string getErrorMessage()const;


protected:
	// internal parser/lexer data 
	Token_value curr_tok;
	int no_of_errors, no_of_functions;
	string strParseError ;

	// parser: report error (private method)
	double		error(const string& s);
	double		error(const string& s, Token_value tk);

	// parser: sums and subtractions (private method)
	Expression	expr(bool get);

	// lexical analyser (private method)
	Token_value	get_token();

	// progressive vid
	int currentvid;

private:
	// contains the map varnames -> varindices

	double number_value;
	char string_value[1024];

	istream *input;    

	// if parser hasn't been initialized with SetVariableIDs, false
	bool isinitialized;



private:  

	// parser: primary expressions (private method)
	Expression	prim(bool get);

	// parser: power
	Expression	power(bool get);

	// parser: products and fractions (private method)
	Expression	term(bool get);


}; // end class ExpressionParser