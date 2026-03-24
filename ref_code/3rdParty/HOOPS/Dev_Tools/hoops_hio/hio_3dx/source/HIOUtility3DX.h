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
// $Header: /files/homes/master/cvs/hoops_master/hio_3dx/source/HIOUtility3DX.h,v 1.1 2010-09-09 00:37:05 chad Exp $
//

#ifndef _HIOUTILITY3DX_H
#define _HIOUTILITY3DX_H

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include "HTools.h"
#include "HIOManager.h"

#ifdef HIO_3DX
#define HIO_API __declspec (dllexport)
#else
#define HIO_API
#endif


/*! The HIOUtility3DX class is used for loading a variety of CAD formats (mostly Brep) into HOOPS. It requires an installation of HOOPS 3D Exchange.
	The CAD file is converted to an internal format (PRC) which is then parsed for hierachy information and to create the tesselated data.

*/
class HIO_API HIOUtility3DX: public HInputHandler, public HOutputHandler
{

public:

	/*!Constructs an HIOUtility object.*/
	HIOUtility3DX();
	virtual ~HIOUtility3DX() {};

	/*!This method registers the appropriate extensions to this handler as an input handler.*/
	void RegisterInputHandlerTypes();
	/*! \return A character pointer denoting the name of the handler. 
	*/
	const char * GetOutputName() { return "HIOUtility3DX"; }
	const char * GetInputName() { return "HIOUtility3DX"; }

	/*!	\returns The input extension type that is handled by HIOUtility3DX.*/
	const char * GetInputTypesString() {return "prc;prd;x_t;x_b;step;stp;igs;iges;CATPart;CATProduct;"
		"cgr;session;model;3dxml;CADDS;PD;XV3;XV0;prt;asm;xpr;xas;neu;asm.1;prt.1;jt;SLDPRT;SLDASM;mf1;"	
	"arc;unv;pkg;sdp;sdpc;sdw;sdwc;sda;sdac;sds;sdsc;ses;bdl;psm;pwd;par;asm;sat;sab;ipt;iam;ifc;dae"; }
 
		

	/*! \return The type of input style which is #HInputHandlerStyleModel.*/
	HInputHandlerStyle GetInputStyle() {return HInputHandlerStyleModel;};

	/*!
	  This method reads the modeller file 'filename' into the segment tree underneath key.
		\param filename The name of the file to load.
		\param key The HOOPS segment key to load model data into.
		\param options An options class containing any needed extra information for operation.
		\return The #HFileInputResult result of the input operation.
	*/
	HFileInputResult FileInputByKey(const wchar_t * FileName, HC_KEY key, HInputHandlerOptions * options);

	HFileInputResult FileInputByKey(const char * FileName, HC_KEY key, HInputHandlerOptions * options){
		return FileInputByKey(H_WCS(FileName).encodedText(), key, options);
	};

	HFileInputResult FileInputByKey(const unsigned short * FileName, HC_KEY key, HInputHandlerOptions * options){
		H_UTF16 utf16;
		utf16.encodedText((utf16_char const*) FileName);
		return FileInputByKey(H_WCS(utf16).encodedText(), key, options);
	};

	HFileOutputResult FileOutputByKey(const wchar_t * filename, HC_KEY key, HOutputHandlerOptions * options);

	HFileOutputResult FileOutputByKey(const unsigned short * filename, HC_KEY key, HOutputHandlerOptions * options){
		H_UTF16 utf16;
		utf16.encodedText((utf16_char const*) filename);
		return FileOutputByKey(H_WCS(utf16).encodedText(), key, options);
	}

	HFileOutputResult FileOutputByKey(const char * filename, HC_KEY key, HOutputHandlerOptions * options){
		return FileOutputByKey(H_WCS(filename).encodedText(), key, options);
	}

	void RegisterOutputHandlerTypes();

	const char *  GetOutputTypesString() {
		return "prc;iges;step;x_t;stl";
	}

	HOutputHandlerStyle GetOutputStyle() {
		return HOutputHandlerStyleModel;
	}
};





/*!The H3DXOptions creates a PRC file from an existing HOOPS segment tree. It requires an installation of HOOPS 3D Exchange.
*/

class HIO_API H3DXOptions
{
public:
	/*! Constructs an H3DXOptions object. */
	H3DXOptions() {Reset();};
	/*! This method sets this class to a default state. */
	void Reset(){
		m_bSaveToPDF = false;
		m_pAsmModelFile = 0;
	};

 	bool	m_bSaveToPDF;
	void *	m_pAsmModelFile;
};




#ifdef HIO_3DX
extern "C" {
	HIO_API void * CreateInput(HIOManager *manager);
	HIO_API void * CreateOutput(HIOManager *manager);
	HIO_API void * CreateConnector(void * unused);
	HIO_API void Free(HIOUtility3DX *);
 }


#endif

#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif
