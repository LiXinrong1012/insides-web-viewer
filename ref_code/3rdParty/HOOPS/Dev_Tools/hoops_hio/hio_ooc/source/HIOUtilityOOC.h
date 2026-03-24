/*
 * Copyright (c) 2009 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: HIOUtilityOOC.h,v 1.7 2009-10-19 19:25:22 ann Exp $
 */

#ifndef _HIOUTILITYOOC_H
#define _HIOUTILITYOOC_H

#include "HIOManager.h"
#include "utf_utils.h"

#ifdef _MSC_VER
#define HIO_API __declspec (dllexport)
#else
#define HIO_API
#endif

class HIO_API HOOCOptions {
public:
	HOOCOptions () {};
	~HOOCOptions () {};
};

/*! The HIOUtilityOOC is the HIO plug-in class for the HOOPS/OOC module.  Using 
  	this input handler, you can load OOC files that have been preprocess by ooc.exe 
	into the HOOPS database.
	*/
class HIO_API HIOUtilityOOC : public HInputHandler {
public:
	/*!Constructs an HIOUtilitySKP object.*/
	HIOUtilityOOC ();
	~HIOUtilityOOC ();
	

	/*! This method reads the OOC file into the segment tree underneath given key.
		\param filename The UNICODE name of the file to load.
		\param key The HOOPS segment key to load model data into.
		\param options An options class containing any needed extra information for operation.
		\return The #HFileInputResult result of the input operation.
	*/
	HFileInputResult FileInputByKey ( wchar_t const * filename, HC_KEY key, HInputHandlerOptions * options );
	
	/*! This method reads the OOC file into the segment tree underneath given key.
		\param filename The name of the file to load.
		\param key The HOOPS segment key to load model data into.
		\param options An options class containing any needed extra information for operation.
		\return The #HFileInputResult result of the input operation.
	*/	HFileInputResult FileInputByKey ( char const * filename, HC_KEY key, HInputHandlerOptions * options ) {
		return FileInputByKey(H_WCS(filename).encodedText(), key, options);
	};
	
	char const * GetInputName () { return "HIOUtilityOOC"; };
	char const * GetInputTypesString () { return "ooc"; };
	HInputHandlerStyle GetInputStyle () { return HInputHandlerStyleModel; };
	void RegisterInputHandlerTypes ();

	static bool FreePointCloudData ( int signal, void * signal_data, void * user_data );
	static bool UpdateCheck ( float request_time, float actual_time, void * user_data );
};

#ifdef HIO_OOC_IMPORT
extern "C" {
	HIO_API void * CreateInput ( HIOManager * manager );
	HIO_API void * CreateOutput ( HIOManager * manager );
	HIO_API void * CreateConnector ( void * unused );
	HIO_API void Free ( HIOUtilityOOC * handler );
	HIO_API void FreeConnector ( HIOConnector * connector );
}
#endif

#endif // _HIOUTILITYOOC_H
