#pragma once

#include "pp_xml/xerces_headers.h"
#include <iostream>

/*!
*	This class is used to handle errors during parsing xml.
*	@author Jerry He
*	@date 2013.9.9
*/
class XMLErrorHandler : public xercesc::ErrorHandler
{
public:
	// -----------------------------------------------------------------------
	//  Constructors and Destructor
	// -----------------------------------------------------------------------
	XMLErrorHandler() :m_bSawErrors(false){}

	~XMLErrorHandler(){}

	// -----------------------------------------------------------------------
	//  Implementation of the error handler interface
	// -----------------------------------------------------------------------
	void warning(const xercesc::SAXParseException& toCatch);
	void error(const xercesc::SAXParseException& toCatch);
	void fatalError(const xercesc::SAXParseException& toCatch);
	void resetErrors();

	void outputError(const xercesc::SAXParseException& toCatch);
	// -----------------------------------------------------------------------
	//  Getter methods
	// -----------------------------------------------------------------------
	bool getSawErrors() const;

	// -----------------------------------------------------------------------
	//  Private data members
	//
	//  fSawErrors
	//      This is set if we get any errors, and is queryable via a getter
	//      method. Its used by the main code to suppress output if there are
	//      errors.
	// -----------------------------------------------------------------------
	bool    m_bSawErrors;
	bool	m_iOutput;
};

class XmlDOMErrorHandler : public xercesc::HandlerBase
{
public:
	void fatalError(const xercesc::SAXParseException &exc) {
		std::cout<<("Fatal parsing error at line %d\n")<<
			(int)exc.getLineNumber();
	}
};