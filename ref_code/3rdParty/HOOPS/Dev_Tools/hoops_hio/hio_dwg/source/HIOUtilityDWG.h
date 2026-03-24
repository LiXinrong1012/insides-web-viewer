//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hio_dwg/source/HIOUtilityDWG.h,v 1.17 2009-04-15 18:50:11 vijay_chavan Exp $
//
#ifndef _HIO_UTILITY_DWG_H
#define _HIO_UTILITY_DWG_H

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include "HTools.h"
#include "HIOManager.h"

#ifdef HIO_DWG
#define HIO_API __declspec (dllexport)
#else
#define HIO_API
#endif


class DWGException
{
public:
	DWGException(const char* msg);
	~DWGException();
	char* what()
	{
		return m_message;
	}
private:
	char* m_message;
};


/*! The HIOUtilityDWG is used for reading DWG files. This utility only supports 
	basic geometry nodes from DWG specification. This is not meant to be a 
	DWG import tool, but the main objective is to provide the developers with a sample code.
*/
class HIO_API HIOUtilityDWG: public HInputHandler
{

public:

	/*!Constructs an HIOUtilityHMF object.*/
	HIOUtilityDWG() {
		SetInputOps(HInputOpFileInputByKey);
	};
	virtual ~HIOUtilityDWG() {;};

	/*!This method registers the "dwg" and "dxf" extensions to this handler as an input handler.*/
	void RegisterInputHandlerTypes() {
		HIORegisterInputType("dwg",this);
		HIORegisterInputType("dxf",this);
	};
	/*! \return A character pointer denoting the name of the handler. 
	*/
	const char * GetOutputName() { return "HIOUtilityDWG"; }
	const char * GetInputName() { return "HIOUtilityDWG"; }

	/*!	\returns The input extension type that is handled by HIOUtilityDWG which are "dwg" and "dxf".*/
	const char * GetInputTypesString() {return "dwg;dxf";};

	/*! \return The type of input style which is #HInputHandlerStyleModel.*/
	HInputHandlerStyle GetInputStyle() {return HInputHandlerStyleModel;};

	/*!
	  This method reads the DWG/DXF file 'filename' into the segment tree underneath key.
		\param filename The name of the file to load.
		\param key The HOOPS segment key to load model data into.
		\param options An options class containing any needed extra information for operation.
		\return The #HFileInputResult result of the input operation.
	*/
	HFileInputResult FileInputByKey(const char * FileName, HC_KEY key, HInputHandlerOptions * options);

	HFileInputResult FileInputByKey(const wchar_t * FileName, HC_KEY key, HInputHandlerOptions * options);

    /*!
	  This method reads the DWG/DXF file 'filename' into the segment tree underneath key.
		\param filename The UNICODE name of the file to load.
		\param key The HOOPS segment key to load model data into.
		\param options An options class containing any needed extra information for operation.
		\return The #HFileInputResult result of the input operation.
	*/
	HFileInputResult FileInputByKey(const unsigned short * FileName, HC_KEY key, HInputHandlerOptions * options);

	/*!
	This method reads the AcDbDatabase objects into the segment tree underneath the key.
	\param pAcDbDatabase A pointer to the AcDbDatabase which is required to be imported to HOOPS.
	\param key The HOOPS key to the segment for data to load in.
	\param options An options class containing any needed extra information for operation.
	\return The #HFileInputResult result of the input operation.
	*/
	HFileInputResult DatabaseInputByKey(AcDbDatabase* pAcDbDatabase, 
										 HC_KEY key, HInputHandlerOptions * options);

	/*!
	This method initializes the RealDWG SDK. Call this once per application lifetime.
	*/
	static bool InitRealDWG();

	/*!
	This method shuts down the RealDWG SDK and releases the memory. Call this once per application lifetime.
	*/
	static bool ShutDownRealDWG();

};


class AcDbDatabase;

/*! This class establishes a connection between the DWG entity and the Hoops entity.
*/
class HIO_API HIOConnectorDWG : public HIOConnector
{

public:
	/*!Constructs an HIOConnectorDWG object.*/
	HIOConnectorDWG() : m_pAcDbDatabase(0) {;};
	~HIOConnectorDWG();

	/*! This method associates this connector with a given AcDbDatabase.
	\param pAcDbDatabase A pointer to the AcDbDatabase object you want this connector to be associated with.
	*/
	void SetDatabase(AcDbDatabase * pAcDbDatabase)
	{   
		// database needs to me alive for DWG pointers to be valid
		m_pAcDbDatabase = pAcDbDatabase;                  
	}

protected:

	//! Autocad Database pointer associated with the DWG file.
	AcDbDatabase * m_pAcDbDatabase;
};


#ifdef HIO_DWG
extern "C" {
	HIO_API void * CreateInput(HIOManager *manager);
	HIO_API void * CreateOutput(HIOManager *manager);
	HIO_API void * CreateConnector(void * unused);
	HIO_API void Free(HIOUtilityDWG *);
	HIO_API void FreeConnector(HIOConnectorDWG *connector);
}
#endif



#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif






