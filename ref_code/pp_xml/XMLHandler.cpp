#include "XMLHandler.h"
#include "pp_xml/xerces_headers.h"
#include "XMLErrorHandler.h"
#include "XMLDataExchange.h"
#include <QFileInfo>
#include <QSharedPointer>

using namespace xercesc;
using namespace std;
using namespace XERCES_CPP_NAMESPACE;

XERCES_CPP_NAMESPACE_USE

USING_PP_NAMESPACE

static const char*  gXMLInMemBuf =
("\
<?xml version='1.0' encoding='UTF-8'?>\n\
<JERRYHE>\n\
	<EASYPLOT>\n\
	</EASYPLOT>\n\
</JERRYHE>\
");

static const char*  gMemBufId = ("PRODUCT");


#define _XPARSER(x) ((XercesDOMParser*)(x))
#define _XELEMENT(x) ((DOMElement*)(x))

inline QString _get_attribute(JXMLItem item,const QString& name)
{
	QString attribValue =XtoQ( _XELEMENT(item)->getAttribute(QtoX(name)) );
	return attribValue;
}

XMLHandler::XMLHandler( void )
	:m_pXMLParser(NULL)
	,m_bInitialized(false)
	,m_bModified(false)
{
	XMLPlatformUtils::Initialize();
}

XMLHandler::~XMLHandler( void )
{
	ResetXMLParser();
	XMLPlatformUtils::Terminate();
}

void XMLHandler::ResetXMLParser()
{
	if( m_pXMLParser != NULL ){
		_XPARSER(m_pXMLParser)->reset();
		delete _XPARSER(m_pXMLParser);
	}
	m_pXMLParser = NULL;
}

bool XMLHandler::Create()
{
	RecreateNew();

	QSharedPointer<MemBufInputSource> memBufIS =QSharedPointer<MemBufInputSource>(new MemBufInputSource
		(
		(const XMLByte*)gXMLInMemBuf
		, strlen(gXMLInMemBuf)
		, gMemBufId
		, false
		));
	

	//
	//  Get the starting time and kick off the parse of the indicated
	//  file. Catch any exceptions that might propagate out of it.
	//
	try
	{
		const unsigned long startMillis = XMLPlatformUtils::getCurrentMillis();
		_XPARSER(m_pXMLParser)->parse(*memBufIS);
		XMLCh xmlChs[1024];
		XercesDOMParser *parser=_XPARSER(m_pXMLParser);
		DOMDocument *doc=parser->getDocument();
		/*
		XMLString::transcode("JERRYHE",xmlChs,1023);
		DOMElement *elem=doc->createElement(xmlChs);
		doc->appendChild(elem);
		
		XMLString::transcode("EASYPLOT",xmlChs,1023);
		DOMElement *easyplot=doc->createElement(xmlChs);
		elem->appendChild(easyplot);
		*/
		
		const unsigned long endMillis = XMLPlatformUtils::getCurrentMillis();
	}
	catch (const OutOfMemoryException&)
	{
		return false;
	}
	catch (const XMLException& e)
	{
		return false;
	}
	return true; 
}

bool XMLHandler::Save( QString strFilePath )
{
	try
	{
		XMLCh tempStr[100];
		XMLString::transcode("LS", tempStr, 99);
		DOMImplementation *impl          = DOMImplementationRegistry::getDOMImplementation(tempStr);
		DOMLSSerializer         *theSerializer = ((DOMImplementationLS*)impl)->createLSSerializer();
		static bool gSplitCdataSections    = true;
		static bool gDiscardDefaultContent = true;
		static bool gUseFilter             = false;
		static bool gFormatPrettyPrint     = true;
		static bool gWriteBOM              = false;

		DOMConfiguration* config=theSerializer->getDomConfig();
		config->setParameter(XMLString::transcode("format-pretty-print"), true);
		theSerializer->setNewLine(XMLString::transcode("\n"));

		/*
		if(config->canSetFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections))
			config->setFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections);

		if(theSerializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent))
			theSerializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent);

		if(theSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint))
			theSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint);

		if(theSerializer->canSetFeature(XMLUni::fgDOMWRTBOM, gWriteBOM))
			theSerializer->setFeature(XMLUni::fgDOMWRTBOM, gWriteBOM);
			*/


		XMLCh strFileName[1024];
		XMLString::transcode(strFilePath.toLatin1().constData(),strFileName,1023);
		const XMLCh *tempFilePath = strFileName;//QtoX(strFilePath);


		// Specify the target for the XML output.
		XMLFormatTarget *formatTarget = new LocalFileFormatTarget(tempFilePath);
		//XMLFormatTarget *myFormTarget = new StdOutFormatTarget();

		// Create a new empty output destination object.
		DOMLSOutput *output = ((DOMImplementationLS*)impl)->createLSOutput();

		// Set the stream to our target.
		output->setByteStream(formatTarget);

		// Write the serialized output to the destination.
		DOMDocument *doc=_XPARSER(m_pXMLParser)->getDocument();
		theSerializer->write(doc, output);

		// Cleanup.
		theSerializer->release();
		delete formatTarget;
		output->release();
	}
	catch (const OutOfMemoryException&)
	{
		return FALSE;
	}
	catch (XMLException& e)
	{
		//Console().Error(XMLString::transcode(e.getMessage()));
		return FALSE;
	}

	return TRUE;
}

bool XMLHandler::Open( QString strFilePath )
{
	QFileInfo file(strFilePath);
	if(!file.exists()){
		return false;
	}
	RecreateNew();

	try
	{
		QByteArray str=strFilePath.toLatin1();
		_XPARSER(m_pXMLParser)->parse(str.constData());
	}
	catch (const OutOfMemoryException&)
	{
		return false;
	}
	catch (const XMLException& e)
	{
		return false;
	}
	catch (...)
	{
		return false;
	}


	return true;
}

void XMLHandler::RecreateNew()
{
	ResetXMLParser();
	m_pXMLParser = new XercesDOMParser();
	XercesDOMParser* parser=_XPARSER(m_pXMLParser);
	parser->setValidationScheme(XercesDOMParser::Val_Auto);
	parser->setDoNamespaces(true);
	parser->setDoSchema(true);
	parser->setValidationSchemaFullChecking(true);
	parser->setCreateEntityReferenceNodes(true);
	parser->setIncludeIgnorableWhitespace(false);
	XMLErrorHandler *errorReporter=new XMLErrorHandler();	
	parser->setErrorHandler(errorReporter);

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Get Functions
QString XMLHandler::GetName(JXMLItem hItem )
{
	DOMNode* pNode = (DOMNode*)_XELEMENT(hItem);
	return XtoQ(pNode->getNodeName());
}
QString pp::XMLHandler::GetText( JXMLItem hItem )
{
	DOMNode* pNode = (DOMNode*)_XELEMENT(hItem);
	return XtoQ(pNode->getTextContent());
}

void pp::XMLHandler::SetText( JXMLItem hItem, QString& strText )
{
	DOMNode* pNode = (DOMNode*)_XELEMENT(hItem);
	pNode->setTextContent(QtoX(strText));
}

int pp::XMLHandler::GetChildCount( JXMLItem hItem )
{
	if(!hItem)
		return 0;
	JXMLItem curr=this->GetFirstChild(hItem);
	int n=0;
	while(curr){
		n++;
		curr=this->GetNextSibling(curr);
	}
	return n;
}

QString	XMLHandler::GetAttribString(JXMLItem hItem, QString strName, QString strDefault)
{
	QString attribValue = _get_attribute(hItem,strName);

	if(attribValue != (""))
		return attribValue;
	else
		return strDefault;
}

long XMLHandler::GetAttribLong(JXMLItem hItem, QString strName, long lDefault)
{
	QString attribValue = _get_attribute(hItem,strName);

	if(attribValue != (""))
		return (attribValue.toLong());
	else
		return lDefault;

}

float XMLHandler::GetAttribFloat(JXMLItem hItem, QString strName, float fDefault)
{
	QString attribValue = _get_attribute(hItem,strName);

	if(attribValue != (""))
		return (float)(attribValue.toDouble());
	else
		return fDefault;
}

double XMLHandler::GetAttribDouble(JXMLItem hItem, QString strName, double dDefault)
{
	QString attribValue = _get_attribute(hItem,strName);

	if(!attribValue.isEmpty())
		return (attribValue.toDouble());
	else
		return dDefault;
}

QString	XMLHandler::GetData (JXMLItem hItem)
{
	DOMNode* pNode = (DOMNode*)_XELEMENT(hItem)->getFirstChild();
	while(pNode)
	{
		if( pNode->getNodeType() == DOMNode::CDATA_SECTION_NODE )
		{
			return XtoQ(pNode->getNodeValue());
		}
		pNode = pNode->getNextSibling();
	}
	return ("");
}


JXMLItem XMLHandler::GetFirstChild (JXMLItem hItem, QString strName)
{
	DOMNode* pNode = (DOMNode*)_XELEMENT(hItem)->getFirstChild();
	while(pNode)
	{
		if( (pNode->getNodeType() == DOMNode::ELEMENT_NODE ||
			pNode->getNodeType() == DOMNode::CDATA_SECTION_NODE )	&&
			( strName == ("") || strName == XtoQ(pNode->getNodeName() )) )
		{
			return (JXMLItem)pNode;
		}
		pNode = pNode->getNextSibling();
	}
	return NULL;
}

JXMLItem XMLHandler::GetNextSibling (JXMLItem hItem, QString strName)
{
	DOMNode* pNode = (DOMNode*)_XELEMENT(hItem)->getNextSibling();
	while(pNode)
	{
		if( (pNode->getNodeType() == DOMNode::ELEMENT_NODE ||
			pNode->getNodeType() == DOMNode::CDATA_SECTION_NODE )	&&
			( strName == ("") || strName == XtoQ(pNode->getNodeName() ) ))
		{
			return (JXMLItem)pNode;
		}
		pNode = pNode->getNextSibling();
	}
	return NULL;
}

JXMLItem XMLHandler::GetPrevSibling (JXMLItem hItem, QString strName)
{
	DOMNode* pNode = (DOMNode*)_XELEMENT(hItem)->getPreviousSibling();
	while(pNode)
	{
		if(( pNode->getNodeType() == DOMNode::ELEMENT_NODE ||
			pNode->getNodeType() == DOMNode::CDATA_SECTION_NODE )	&&
			( strName == ("") || strName == XtoQ(pNode->getNodeName() ) ))
		{
			return (JXMLItem)pNode;
		}
		pNode = pNode->getPreviousSibling();
	}
	return NULL;
}

JXMLItem XMLHandler::GetParent (JXMLItem hItem)
{
	DOMNode* pNode = (DOMNode*)_XELEMENT(hItem);
	if(pNode->getNodeType() == DOMNode::ELEMENT_NODE)
		return (JXMLItem)(pNode->getParentNode());
	return NULL;
}

JXMLItem XMLHandler::GetRoot()
{
	DOMDocument *document = _XPARSER(m_pXMLParser)->getDocument();
	DOMElement *rootElementNode = document->getDocumentElement();
	return (JXMLItem)rootElementNode;
}

// Set Functions
void XMLHandler::SetAttribString(JXMLItem hItem, QString strName, QString strValue)
{
	DOMElement* pElem = _XELEMENT(hItem);
	if(pElem != NULL)
		pElem->setAttribute(QtoX(strName), QtoX(strValue));
}

void XMLHandler::SetAttribLong(JXMLItem hItem, QString strName, long lValue)
{
	QString strValue=QString::number(lValue);
	DOMElement* pElem = _XELEMENT(hItem);
	if(pElem != NULL)
		pElem->setAttribute(QtoX(strName), QtoX(strValue));
}

void XMLHandler::SetAttribFloat(JXMLItem hItem, QString strName, float fValue)
{
	QString strValue=QString::number(fValue);
	DOMElement* pElem = _XELEMENT(hItem);
	if(pElem != NULL)
		pElem->setAttribute(QtoX(strName), QtoX(strValue));
}

void XMLHandler::SetAttribDouble(JXMLItem hItem, QString strName, double dValue)
{
	QString strValue=QString::number(dValue);
	DOMElement* pElem = _XELEMENT(hItem);
	if(pElem != NULL)
		pElem->setAttribute(QtoX(strName), QtoX(strValue));
}

void XMLHandler::SetData(JXMLItem hItem, QString &strData)
{
	DOMDocument *document = _XPARSER(m_pXMLParser)->getDocument();
	DOMCDATASection *CDataSectionNode = document->createCDATASection(QtoX(strData));
	DOMNode* pNode = (DOMNode*)_XELEMENT(hItem);
	if (pNode != NULL)
		pNode->appendChild(CDataSectionNode);
}

// Operations ( Need to set Modified Flag )
void XMLHandler::RemoveAttrib (JXMLItem hItem, QString strName)
{
	DOMElement* pElem = _XELEMENT(hItem);
	if(pElem != NULL)
		pElem->removeAttribute(QtoX(strName));
}

void XMLHandler::RemoveData (JXMLItem hItem)
{
	DOMNode* pNode = (DOMNode*)_XELEMENT(hItem);
	DOMNode* pChildNode = pNode->getFirstChild();
	if(pNode != NULL)
	{
		while(pChildNode)
		{
			DOMNode *prevNode = pChildNode;
			pChildNode = pChildNode->getNextSibling();
			if((prevNode->getNodeType() == DOMNode::CDATA_SECTION_NODE)) 
				pNode->removeChild(prevNode);
		}
	}
}

JXMLItem XMLHandler::Append (JXMLItem hItem, QString strName)
{
	DOMNode *nextNode = _XELEMENT(hItem)->getNextSibling();
	DOMNode *parentNode = _XELEMENT(hItem)->getParentNode();
	DOMDocument *document = _XPARSER(m_pXMLParser)->getDocument();
	DOMElement *newElement = document->createElement(QtoX(strName));
	if(parentNode != NULL)
	{
		if(nextNode == NULL)
		{
			return (JXMLItem)(parentNode->appendChild(newElement));
		}
		else
		{
			return (JXMLItem)(parentNode->insertBefore(newElement, nextNode));
		}
	}
	return NULL;
}

JXMLItem XMLHandler::Insert (JXMLItem hItem, QString strName)
{
	DOMNode *pNode = (DOMNode*)_XELEMENT(hItem);
	DOMNode *parentNode = pNode->getParentNode();
	if(parentNode != NULL && pNode != (DOMNode *)GetRoot())
	{
		DOMDocument *document = _XPARSER(m_pXMLParser)->getDocument();
		DOMElement *newElement = document->createElement(QtoX(strName));

		if( newElement->getNodeType() == DOMNode::ELEMENT_NODE && 
			pNode->getNodeType() == DOMNode::ELEMENT_NODE)
			return (JXMLItem)(parentNode->insertBefore(newElement, pNode));
	}
	return NULL;
}

JXMLItem XMLHandler::AddChild (JXMLItem hItem, QString strName)
{
	DOMDocument *document = _XPARSER(m_pXMLParser)->getDocument();
	DOMElement *newElement = document->createElement(QtoX(strName));
	DOMNode *pNode = (DOMNode*)_XELEMENT(hItem);
	if(pNode != NULL)
		return (JXMLItem)(pNode->appendChild(newElement));
	return NULL;
}

void XMLHandler::Remove (JXMLItem hItem)
{
	DOMNode *pNode = (DOMNode*)_XELEMENT(hItem);
	DOMNode *pParentNode = pNode->getParentNode();
	if(pParentNode != NULL && pNode->getNodeType() == DOMNode::ELEMENT_NODE)
		pParentNode->removeChild(pNode);
}

void XMLHandler::RemoveChild (JXMLItem hItem, QString strName)
{
	DOMNode *pNode = (DOMNode*)_XELEMENT(hItem);
	DOMNode *pChildNode = pNode->getFirstChild();
	if(pNode != NULL)
	{
		while(pChildNode)
		{
			DOMNode *prevNode = pChildNode;
			pChildNode = pChildNode->getNextSibling();
			if( (prevNode->getNodeType() == DOMNode::ELEMENT_NODE) && 
				( strName == ("") || strName == XtoQ(prevNode->getNodeName() )))
				pNode->removeChild(prevNode);
		}
	}
}

void XMLHandler::RemoveAllChild (JXMLItem hItem)
{
	DOMNode *pNode = (DOMNode*)_XELEMENT(hItem);
	DOMNode* pChildNode = pNode->getFirstChild();
	if (pNode != NULL)
	{
		while(pChildNode)
		{
			DOMNode* pPrevNode = pChildNode;
			pChildNode = pChildNode->getNextSibling();
			if( pPrevNode->getNodeType() == DOMNode::ELEMENT_NODE)
			{
				pNode->removeChild(pPrevNode);
			}
		}
	}
}

void XMLHandler::RemoveAll ()
{
	DOMElement *rootElementNode = _XELEMENT(GetRoot());	
	RemoveAllChild((JXMLItem)rootElementNode);
}

JXMLItem XMLHandler::FindSingleItem(JXMLItem hItem, QString strName)
{
	DOMNodeList* pNodeList = _XELEMENT(hItem)->getElementsByTagName(QtoX(strName));
	if(pNodeList->getLength() != 0)
	{
		for(unsigned int i = 0; i < pNodeList->getLength(); i++)
		{
			DOMNode *pNode = (DOMNode *)pNodeList->item(i);		
			if( pNode->getNodeType() == DOMNode::ELEMENT_NODE &&
				( strName == ("") || strName == XtoQ(pNode->getNodeName() ) ))
			{
				return (JXMLItem)pNode;
			}
		}
	}
	return NULL;
}



