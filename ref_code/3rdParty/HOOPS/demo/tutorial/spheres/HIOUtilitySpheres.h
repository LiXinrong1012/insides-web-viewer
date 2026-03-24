
#ifndef _HIO_UTILITY_SPHERES_H
#define _HIO_UTILITY_SPHERES_H

#include "HTools.h"
#include "HIOManager.h"

/*! The HIOUtilitySpheres class is used for reading and writing Sphere Files (.sph) */
class HIOUtilitySpheres: public HInputHandler, public HOutputHandler
{

public:

	HIOUtilitySpheres() {
		SetInputOps(HInputOpFileInputByKey);
		SetOutputOps(HOutputOpFileOutputByKey);
	};

	virtual ~HIOUtilitySpheres() {;};

	/* ! Register this object to serve as the input handler for files with the .sph extension */
	void RegisterInputHandlerTypes() {
		HIORegisterInputType("sph",this);
	};


	/*! \return A character pointer denoting the name of the handler. 
	*/
	const char * GetOutputName() { return "HIOUtilitySpheres"; }
	const char * GetInputName() { return "HIOUtilitySpheres"; }

	const char * GetInputTypesString() {return "sph";};
	HInputHandlerStyle GetInputStyle() {return HInputHandlerStyleModel;};

	/*!
	  This method reads an .sph file into the segment referenced by 'key'.   
	*/
	HFileInputResult FileInputByKey(const char * FileName, HC_KEY key, HInputHandlerOptions * options) {
		return FileInputByKey(H_WCS(FileName).encodedText(), key, options);
	}

	HFileInputResult FileInputByKey(const __wchar_t * FileName, HC_KEY key, HInputHandlerOptions * options);

	/* ! Register this object to serve as the output handler for files with the .sph extension */
	void RegisterOutputHandlerTypes() {
		HIORegisterOutputType("sph",this);
	};

	const char * GetOutputTypesString() {return "sph";};
	HOutputHandlerStyle GetOutputStyle() {return HOutputHandlerStyleModel;};

	/*!
	  This method creates an .sph file of the segment tree defined under the segment referened by 'key'.
	*/
	HFileOutputResult FileOutputByKey(const char * FileName, HC_KEY key, HOutputHandlerOptions * options) {
		H_UTF16 utf16;
		utf16.encodedText((utf16_char const*) FileName);
		return FileOutputByKey(H_WCS(utf16).encodedText(), key, options);
	}

	HFileOutputResult FileOutputByKey(const __wchar_t * FileName, HC_KEY key, HOutputHandlerOptions * options);
};

#endif



