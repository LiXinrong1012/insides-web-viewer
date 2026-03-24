#include "expressionparser.h"
#include "Parameter.h"
#include <string>

#define NOTVARNAME "_var_not_found_"

#define RCS10 "$Id: parser.cxx,v 1.11 2006/07/30 05:36:43 liberti Exp liberti $"

ExpressionParser::ExpressionParser() 
{ 
	isinitialized = false; 
// 	markerPt = NULL;
// 	existFunPt = NULL;
	currentvid = 1;
}

// ExpressionParser::ExpressionParser(map<string , Marker*> *mmap, map<string, Function *> *fmap) 
// { 
// 	InitialMap() ;
// 	isinitialized = true; 
// 	markerPt = mmap;
// 	existFunPt = fmap;
// 	currentvid = 1;
// }

ExpressionParser::~ExpressionParser() { }

// set variable ID

// driver evaluating routine (public method)
// Expression ExpressionParser::Parse( const char* buf, list<RigidNode*> & nl, int& nerrors ) 
// {
// 
// 	curr_tok = PEV3PRINT;
// 	Expression ret;
// //	relNode.clear();
// 
// 	input = new stringstream(buf);
// 
// 	no_of_functions = 0;
// 	no_of_errors = 0;
// 
// 	while (*input) 
// 	{
// 		get_token();
// 		switch(curr_tok) 
// 		{
// 		case PEV3END:
// 			break;
// 		case PEV3PRINT:
// 			continue;
// 		case PEV3RP:
// 			if (no_of_functions == 0)
// 			{
// 				error("primary expected, found", curr_tok);
// 			} 
// 			else 
// 			{
// 				no_of_functions--;
// 			}
// 			continue;
// 		default:
// 			ret = expr(false);
// 		}
// 	}
// 
// 	delete input;
// 	nerrors = no_of_errors;
// // 	if(relNode.size() > 0)
// // 	{
// // 		nl = relNode;
// // 	}
// 	return ret;
// }

int ExpressionParser::Parse( Expression& ret, const char* buf)
{

	curr_tok = PEV3PRINT;

	input = new stringstream(buf);

	no_of_functions = 0;
	no_of_errors = 0;

	while (*input) 
	{
		get_token();
		switch(curr_tok) 
		{
		case PEV3END:
			break;
		case PEV3PRINT:
			continue;
		case PEV3RP:
			if (no_of_functions == 0)
				error("primary expected, found", curr_tok);
			else 
				no_of_functions--;
			continue;
		default:
			ret = expr(false);
		}
	}

	delete input;
	return no_of_errors;
}
// parser: report error (private method)

double ExpressionParser::error(const string& s) 
{
	no_of_errors++;
	cerr << "error: " << s << endl ;
	strParseError = s ;
	return 0;
}

double ExpressionParser::error(const string& s, Token_value tk) 
{
	no_of_errors++;
	char tks = tk;
	cerr << "error: " << s << " " << tk << ":" << tks << endl;
	strParseError = s ;
	return 0;
}

// parser: primary expressions (private method)
Expression ExpressionParser::prim(bool get)
{
	Expression ret ;

	if (get)	get_token();

	switch (curr_tok)
	{
	case PEV3NUMBER:
		ret = number_value;
		get_token();
		break;
	case PEV3NAME:	//分辨预定义的参数，模型文件中不区分大小写
		{
			string s(string_value)	;

			if ( dealWithName ( ret, s) != 0 )
				error(getErrorMessage());
		}
		break;
	case PEV3MINUS:
		ret = MinusLink(prim(true));
		break;
	case PEV3LP:
		ret = expr(true);
		if (curr_tok != PEV3RP)
			error("bracket ) expected");
		else 
			get_token();	
		break;
	default:
		error("primary expected, found", curr_tok);
	}
	return ret;
}     

// parser: power
Expression ExpressionParser::power(bool get) 
{    
	Expression ret = prim(get);
	for (;;) 
	{
		switch (curr_tok)
		{
		case PEV3POWER:
			ret = PowerLink(ret, prim(true));
			break;
		default:
			return ret;
		}
	}
}

// parser: products and fractions (private method)
Expression ExpressionParser::term(bool get)
{

	Expression ret = power(get);

	for (;;) 
	{
		switch (curr_tok) 
		{
		case PEV3MUL:
			ret = ProductLink(ret, power(true));
			break;
		case PEV3DIV:
			ret = FractionLink(ret, power(true));
			break;
		default:
			return ret;
		}
	}
}

// parser: sums and subtractions (private method)
Expression ExpressionParser::expr(bool get) 
{

	Expression ret = term(get);

	for (;;) 
	{
		switch (curr_tok) 
		{
		case PEV3PLUS: 
		case PEV3NLPLUS:
			ret = SumLink(ret, term(true));
			break;
		case PEV3MINUS:
			ret = DifferenceLink(ret, term(true));
			break;
		default:
			return ret;
		}
	}
}

// lexical analyser (private method)
Token_value ExpressionParser::get_token()
{
	char ch;

	do
	{ // skip whitespace except '\n' 
		if (!input->get(ch))
			return curr_tok = PEV3END;
	} while (ch != '\n' && isspace(ch));

	switch(ch)
	{
	case ';': case '\n':
		return curr_tok = PEV3PRINT;
	case 0:
		return curr_tok = PEV3END;
	case '*': case '/': case '+': case '-': case '|': 
	case '(': case ')': case '=':
	case '^': case ',':
		return curr_tok = Token_value(ch);
	case '0': case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9': case '.':
		input->putback(ch);
		*input >> number_value;
		return curr_tok = PEV3NUMBER;
	default:  // PEV3NAME, PEV3NAME=, or error
		if (isalpha(ch)||ch=='$') { // '$' 是变量前缀
			char* sv = string_value;
			*sv = ch;
			while (input->get(ch) && (isalnum(ch) || ch == '_' || ch=='.')) {
				*(++sv) = ch;
			}
			*(++sv) = '\0';
			input->putback(ch);
			return curr_tok = PEV3NAME;
		}
		else
		{
			error("bad token");
			return curr_tok = PEV3PRINT;
		}		
	}
}

int ExpressionParser::dealWithName( Expression& ret, const std::string& name )
{
	return 1;
}

std::string ExpressionParser::getErrorMessage() const
{
	return "no error";
}

