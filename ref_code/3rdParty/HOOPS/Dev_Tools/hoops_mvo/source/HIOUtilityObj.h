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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HIOUtilityObj.h,v 1.18 2008-12-16 18:46:49 guido Exp $
//


#ifndef _HIOUTILITYOBJ_H
#define _HIOUTILITYOBJ_H

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include "HTools.h"
#include "HIOManager.h"

/*! The HIOUtilityObj class reads and writes Alias|Wavefront files.
*/
class MVO_API HIOUtilityObj: public HInputHandler, public HOutputHandler
{

public:

	/*!Constructs an HIOUtilityObj object.*/
	HIOUtilityObj() {
		SetInputOps(HInputOpFileInputByKey);
	};
	virtual ~HIOUtilityObj() {;};

	/*! \return A character pointer denoting the name of the handler. 
	*/
	const char * GetOutputName() { return "HIOUtilityObj"; }
	const char * GetInputName() { return "HIOUtilityObj"; }


	/*!This method registers the "obj" extension to this handler as an input handler.*/
	void RegisterInputHandlerTypes() {
		HIORegisterInputType("obj",this);
	}

	/*!	\returns The input extension type that is handled by HIOUtilityObj which is "obj".*/
	const char * GetInputTypesString() {return "obj";};

	/*! \return The type of input style which is #HInputHandlerStyleModel.*/
	HInputHandlerStyle GetInputStyle() {return HInputHandlerStyleModel;};

	/*!
	  This method reads an Alias|Wavefront file.  The file contents are mapped
	  to a HOOPS shell primitive that is inserted into the HOOPS segment specified by the key.
		\param filename The name of the file to load.
		\param key The HOOPS segment key to load model data into.
		\param options An options class containing any needed extra information for operation.
		\return The #HFileInputResult result of the input operation.
	*/
	HFileInputResult FileInputByKey(const __wchar_t * FileName, HC_KEY key, HInputHandlerOptions * options);

	HFileInputResult FileInputByKey(const char * FileName, HC_KEY key, HInputHandlerOptions * options){
		return FileInputByKey(H_WCS(FileName).encodedText(), key, options);
	};

	HFileInputResult FileInputByKey(const unsigned short * FileName, HC_KEY key, HInputHandlerOptions * options){
		H_UTF16 utf16;
		utf16.encodedText((utf16_char const*) FileName);
		return FileInputByKey(H_WCS(utf16).encodedText(), key, options);
	};

	/*!This method registers the "obj" and "OBJ" extensions to this handler as an output handler.*/
	void RegisterOutputHandlerTypes() {
		HIORegisterOutputType("OBJ",this); 
		HIORegisterOutputType("obj",this); 
	};

	/*! \return The type of output style which is HOutputHandlerStyleModel.*/
	HOutputHandlerStyle GetOutputStyle() {return HOutputHandlerStyleModel;};

		/*! \return The string of the type of output this handler creates which is "obj".*/
	const char * GetOutputTypesString() 
	{return "obj";};

	/*!
	  This method writes a Alias|Wavefront file out of the segment tree underneath the given key.
		\param filename The name of the file to output.
		\param key The HOOPS segment key to output model data from.
		\param options The options class containing any needed extra information for the operation.
		\return The #HFileOutputResult result of the output operation.
	*/
	HFileOutputResult FileOutputByKey(const __wchar_t * filename, HC_KEY key, HOutputHandlerOptions * options);

	HFileOutputResult FileOutputByKey(const unsigned short * filename, HC_KEY key, HOutputHandlerOptions * options){
		H_UTF16 utf16;
		utf16.encodedText((utf16_char const*) filename);
		return FileOutputByKey(H_WCS(utf16).encodedText(), key, options);
	}

	HFileOutputResult FileOutputByKey(const char * filename, HC_KEY key, HOutputHandlerOptions * options){
		return FileOutputByKey(H_WCS(filename).encodedText(), key, options);
	}
};


#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif
