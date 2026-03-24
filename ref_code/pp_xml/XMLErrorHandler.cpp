#include "XMLErrorHandler.h"
#include "XMLDataExchange.h"
#include "xercesc/sax/SAXParseException.hpp"
#include <iostream>

using namespace xercesc;
using namespace std;


inline bool XMLErrorHandler::getSawErrors() const
{
	return m_bSawErrors;
}

void XMLErrorHandler::warning(const SAXParseException& toCatch)
{
	outputError(toCatch);
}


void XMLErrorHandler::error(const SAXParseException& toCatch)
{
	m_bSawErrors = true;
	outputError(toCatch);
}

void XMLErrorHandler::fatalError(const SAXParseException& toCatch)
{
	m_bSawErrors = true;
	outputError(toCatch);
}

void XMLErrorHandler::resetErrors()
{
	m_bSawErrors = false;
}

void XMLErrorHandler::outputError( const xercesc::SAXParseException& toCatch )
{
	if(m_iOutput){
	QString str=XtoQ(toCatch.getMessage());
	wcout<<str.toStdWString()<<endl;
	}
}

