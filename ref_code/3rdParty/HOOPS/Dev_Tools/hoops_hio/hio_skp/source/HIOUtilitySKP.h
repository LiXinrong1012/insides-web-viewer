//
// Copyright (c) 2005 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//


#ifndef _HIO_UTILITY_SKP_2__02052008_1230_
#define _HIO_UTILITY_SKP_2__02052008_1230_

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

//#import "SketchUp.tlb" rename_namespace("SketchUp"), no_auto_exclude, rename("LoadImage", "Load_Image")

#include "HSKPHelper.h"

#include "HTools.h"
#include "HIOManager.h"

#ifdef HIO_SKP
#define HIO_API __declspec (dllexport)
#else
#define HIO_API
#endif

/*! The HIOUtilitySKP is the integration class for the SketchUp toolkit.  Using 
  	this integration class allows you to import Google SketchUp's skp file.
	*/
class HIO_API HIOUtilitySKP : public HInputHandler
{

private:

	 HMODULE m_rHModule;
	 HSKPImporter* m_bImporter;

public:

	CComPtr<ISkpApplication> m_pApp;
	/*!Constructs an HIOUtilitySKP object.*/
	HIOUtilitySKP() 
	{ 
		SetInputOps(HInputOpFileInputByKey);
	};

	~HIOUtilitySKP() 
	{
		
	};

	/*! \return A character pointer denoting the name of the handler. 
	*/
	const char * GetOutputName() { return "HIOUtilitySKP"; }
	const char * GetInputName() { return "HIOUtilitySKP"; }

	/*!This method registers the "skp" extension to this handler as an input handler.*/
	void RegisterInputHandlerTypes() {
		HIORegisterInputType("SKP",this);  // SKP (Google SketchUp's Format)
		HIORegisterInputType("skp",this);  // skp (Google SketchUp's Format)
	};

	/*! \return The type of input style which is #HInputHandlerStyleModel.*/
	HInputHandlerStyle GetInputStyle() {return HInputHandlerStyleModel;};

	/*!	\returns The input extension type that is handled by HIOUtilitySKP which is "skp".*/
	const char * GetInputTypesString() {return "skp";};

	/*! This method reads the SKP file into the segment tree underneath given key.
		\param filename The name of the file to load.
		\param key The HOOPS segment key to load model data into.
		\param options An options class containing any needed extra information for operation.
		\return The #HFileInputResult result of the input operation.
	*/
	HFileInputResult FileInputByKey(const char * FileName, HC_KEY key, HInputHandlerOptions * options);

	HFileInputResult FileInputByKey(const wchar_t * FileName, HC_KEY key, HInputHandlerOptions * options);

	/*! This method reads the SKP file into the segment tree underneath given key.
		\param filename The UNICODE name of the file to load.
		\param key The HOOPS segment key to load model data into.
		\param options An options class containing any needed extra information for operation.
		\return The #HFileInputResult result of the input operation.
	*/
	HFileInputResult FileInputByKey(const unsigned short * FileName, HC_KEY key, HInputHandlerOptions * options);

	/*! This method Initializes Runtime Extension environment and loads sketchup reader libray*/
	void InitSKP();

	/*!This method frees the sketchup reader library.*/
	void  ShutdownSKP();

};

#ifdef HIO_SKP
extern "C" {
	HIO_API void * CreateInput(HIOManager *manager);
	HIO_API void * CreateOutput(HIOManager *manager);
	HIO_API void * CreateConnector(void *unused);
	HIO_API void Free(HIOUtilitySKP *);
	HIO_API void FreeConnector(HIOConnector *connector);
}
#endif



#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif	//_HIO_UTILITY_SKP_2__02052008_1230_






