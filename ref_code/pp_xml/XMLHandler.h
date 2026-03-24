#pragma once

#include "pp_xml/pp_xml_global.h"


#include <QString>

BEGIN_PP_NAMESPACE
typedef void* JXMLItem;
typedef void* XMLParser;

class PP_XML_EXPORT XMLHandler
{
public:
	XMLHandler(void);
	virtual ~XMLHandler(void);

	void ResetXMLParser();	/// remove xml parser.
	bool Create();			/// create default document.
	bool Save(QString strFilePath);

	bool Open(QString strFilePath);
	void Parse(QString strXML);
	QString GetXMLString();

	// Get Functions
	QString GetName (JXMLItem hItem);
	QString	GetData (JXMLItem hItem);
	QString GetText(JXMLItem hItem);
	QString	GetAttribString (JXMLItem hItem, QString strName, QString strDefault = QString(""));
	long	GetAttribLong (JXMLItem hItem, QString strName, long lDefault = 0);
	float	GetAttribFloat (JXMLItem hItem, QString strName, float fDefault = 0.0f);
	double	GetAttribDouble (JXMLItem hItem, QString strName, double dDefault = 0.0);

	JXMLItem FindSingleItem(JXMLItem hItem, QString strName = QString(""));
	JXMLItem GetFirstChild (JXMLItem hItem, QString strName = QString(""));
	JXMLItem GetNextSibling (JXMLItem hItem, QString strName = QString(""));
	JXMLItem GetPrevSibling (JXMLItem hItem, QString strName = QString(""));
	JXMLItem GetParent (JXMLItem hItem);
	JXMLItem GetRoot ();
	/// 获得条目下子条目的数据，需要遍历条目，较慢。Jerry, 2014.6.4
	int		 GetChildCount(JXMLItem hItem);

	// Set Functions
	void SetAttribString (JXMLItem hItem, QString strName, QString strValue);
	void SetAttribLong (JXMLItem hItem, QString strName, long lValue);
	void SetAttribFloat (JXMLItem hItem, QString strName, float fValue);
	void SetAttribDouble (JXMLItem hItem, QString strName, double dValue);
	void SetData(JXMLItem hItem, QString &strData);
	void SetText(JXMLItem hItem, QString& strText);

	// Operations ( Need to set Modified Flag )
	void RemoveAttrib (JXMLItem hItem, QString strName);
	void RemoveData (JXMLItem hItem);

	JXMLItem Append (JXMLItem hItem, QString strName);
	JXMLItem Insert (JXMLItem hItem, QString strName);
	JXMLItem AddChild (JXMLItem hItem, QString strName);
	void Remove (JXMLItem hItem);
	void RemoveChild (JXMLItem hItem, QString strName = QString(""));
	void RemoveAllChild (JXMLItem hItem);
	void RemoveAll ();

	// Modification
	void SetModifiedFlag (bool bModified = TRUE) { m_bModified = bModified; }
	bool GetModifiedFlag () { return m_bModified; }

protected:
	XMLParser	m_pXMLParser;
	bool		m_bInitialized;
	bool		m_bModified;

	void RecreateNew();
};


END_PP_NAMESPACE
