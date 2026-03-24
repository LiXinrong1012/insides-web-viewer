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
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HIOUtilityPDF.h,v 1.28 2010-09-03 12:07:56 guido Exp $
//

#ifndef _HIOUTILITYPDF_H
#define _HIOUTILITYPDF_H

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#include "HTools.h"
#include "HIOManager.h"
#include "HDB.h"
#include <string>
#include <map>



/*!The HU3DOptions class provides information to the HIOUtilityU3D class to output U3D files.
*/
class MVO_API HU3DOptions
{
public:
	/*! Constructs an HU3DOptions object. */
	HU3DOptions() {Reset();};
	/*! This method sets this class to a default state. */
	void Reset(){
		m_bExportLines = m_bExportAnnotations = false;
	};

	/*! If in 3D mode, export lines optionally. */
	bool m_bExportLines;
	/*! If in 3D mode, export annotations optionally. */
	bool m_bExportAnnotations;

	/*! returns true if we are exporting lines. */
	bool const ExportLines(void) const {return m_bExportLines;};
	/*! pass in true to export lines. */
	void ExportLines(bool onoff) {m_bExportLines = onoff;};
	/*! returns true if we are exporting annotations. */
	bool const ExportAnnotations(void) const {return m_bExportAnnotations;};
	/*! pass in true to export annotations. */
	void ExportAnnotations(bool onoff) {m_bExportAnnotations = onoff;};
};

/*!The HPDFOptions class provides information to the HIOUtilityPDF class to output PDF files.
*/
class MVO_API HPDFOptions : public HOutputHandlerOptions
{
public:
	/*! Constructs an HPDFOptions object. */
	HPDFOptions();
	/*! Clean up... */
	~HPDFOptions();

	/*!  This fills in some of the default values. */
	bool PopulateOptions();

	char const * GetType() const;

	/*! This method sets this class to a default state. */
	void Reset();
	/*! Set this member to true if you want the 3d annotation to be automatically enabled when opening the pdf file.*/
	bool m_bActivateOnPageOpen;
	/*! This member defines in inches in the left direction from the left of the page's
		left boarder where the annotation's left boarder will be. */
	float m_fAnnotLeft;
	/*! This member defines in inches in the left direction from the
		right of the page's right border where the annotation's right boarder will be. */
	float m_fAnnotRight;
	/*! This member defines in inches in the up direction from the
		bottom of the page's bottom border where the annotation's bottom boarder will be. */
	float m_fAnnotBottom;
	/*! This member defines in inches in the up direction (yes, up direction) from the
		top of the page's top border where the annotation's top boarder will be. */
	float m_fAnnotTop;

	/*! This member defines in inches in the left to right direction where to put the text.*/
	float m_fTextX;
	/*! This member defines in inches in the bottom to top direction where to put the text.*/
	float m_fTextY;
	/*! This member temporarily holds the name of the file.  This is duplicated and will likely be removed. */
	wchar_t const * m_filename;

	void *m_pPRCAsmModelFile;
	char *m_AnimationData;
	HU3DOptions m_U3dOptions;

	bool const ActivateOnPageOpen(void) const {return m_bActivateOnPageOpen;};
	void ActivateOnPageOpen(bool onoff) {m_bActivateOnPageOpen = onoff;};
	float const AnnotLeft(void) const {return m_fAnnotLeft;};
	void AnnotLeft(float f) {m_fAnnotLeft = f;};
	float const AnnotRight(void) const {return m_fAnnotRight;};
	void AnnotRight(float f) {m_fAnnotRight = f;};
	float const AnnotBottom(void) const {return m_fAnnotBottom;};
	void AnnotBottom(float f) {m_fAnnotBottom = f;};
	float const AnnotTop(void) const {return m_fAnnotTop;};
	void AnnotTop(float f) {m_fAnnotTop = f;};

	/*! returns a reference  to the U3DOptions.  Call HPDFOptions::U3dOptions().whatever() to modify U3D. */
	HU3DOptions & U3dOptions() {return m_U3dOptions;};

	float const TextX(void) const {return m_fTextX;};
	void TextX(float f) {m_fTextX = f;};
	float const TextY(void) const {return m_fTextY;};
	void TextY(float f) {m_fTextY = f;};
	__wchar_t const * filename(void) const {return (__wchar_t const*) m_filename;};
	void filename(__wchar_t const * c) {m_filename = (wchar_t const*)c;};
#ifdef _MSC_VER
	void filename(unsigned short const * c) {filename((__wchar_t const*)c);};
#endif

	//! Some file formats, such as pdf and dwf,  support 2d and/or 3d output.  Set this to true for 3d output.
	bool const Output2d() const {return m_b2dOutput;};
	//! Some file formats, such as pdf and dwf,  support 2d and/or 3d output.  Set this to true for 3d output.
	void Output2d(bool const tf) {m_b2dOutput = tf;};

	bool const OutputNative() const {return m_bNativeOutput;};
	void OutputNative(bool const tf) {m_bNativeOutput = tf;};

	std::basic_string<__wchar_t> const & NativeFileName() const {return *m_pNativeFileName;};
	void NativeFileName(std::basic_string<__wchar_t> const & tf) {
		delete m_pNativeFileName;
		m_pNativeFileName = new std::basic_string<__wchar_t>(tf);
	};
#ifdef _MSC_VER
	void NativeFileName(std::basic_string<unsigned short> const & tf) {
		NativeFileName(std::basic_string<__wchar_t>(tf.begin(), tf.end()));
	}
#endif

	bool const OutputAVI() const {return m_bAVIOutput;};
	void OutputAVI(bool const tf) {m_bAVIOutput = tf;};

	void EmbeddedFile(int index, std::basic_string<__wchar_t> const & s){
		m_embeddedFiles->insert(make_pair(index, s));
	};

	std::map<int, std::basic_string<__wchar_t> > const * EmbeddedFiles() const
	{
		return m_embeddedFiles;
	};

	bool const came_from_adobe() const {return m_bAdobe;};
	void came_from_adobe(bool const tf) {m_bAdobe = tf;};

private:	
	//! Some file formats, such as pdf and dwf,  support 2d and/or 3d output.  Set this to true for 3d output.
	bool m_b2dOutput;
	bool m_bAdobe;
	bool m_bNativeOutput;
	bool m_bAVIOutput;
	std::basic_string<__wchar_t> * m_pNativeFileName;
	std::map<int, std::basic_string<__wchar_t> > * m_embeddedFiles;
};


/*! The HIOUtilityPDF class outputs 2d and 3d pdf files.
*/
class MVO_API HIOUtilityPDF: public HOutputHandler
{
public:
	/*! Constructs an HIOUtilityPDF object. */
	HIOUtilityPDF() { 
		SetOutputOps(HOutputOpFileOutputByKey);
	};

	~HIOUtilityPDF() {;};

	/*! \return A character pointer denoting the name of the handler. 
	*/
	const char * GetOutputName() { return "HIOUtilityPDF"; }

	/*!This method registers the "pdf" extension to this handler as an output handler.*/
	void RegisterOutputHandlerTypes() {
		HC_Begin_Segment_Search("/driver/pdf");{
			char seg[100];
			while(HC_Find_Segment(seg)){
				if(strieq(seg, "/driver/pdf")){
					HIORegisterOutputType("pdf",this);
					break;
				}
			}
		}HC_End_Segment_Search();
	};

	/*! \return The string of the type of output this handler creates which is "pdf".*/
	const char * GetOutputTypesString() {return "pdf";};
	/*! \return The type of output style which is HOutputHandlerStyleHardcopy.*/
	HOutputHandlerStyle GetOutputStyle() {return HOutputHandlerStyleHardcopy;};

	/*! \return The default HSRA for the HIOUtilityPDF instance.*/
	const char * GetOutputDefaultHSRA() {return "painters";};

	/*! This method checks if there's a u3d handler registered.  If there is, then we can output a 3d pdf file.
	\return True if this handler can output 3d pdf file or false if it cannot.
	*/
	bool Has3dSupport(){
		return (HDB::GetHIOManager()->GetOutputHandler("u3d") != (HOutputHandler*)0);
	}

	/*! This method exports the HOOPS segment tree under the given key to a pdf file.
		\param filename The name of the file to output.
		\param key The HOOPS segment key to output model data from.
		\param options Pass a pointer to HPDFOptions with information to specify the dimensions of the output as well as if you want a 3D or 2D output.
		\return The #HFileOutputResult result of the output operation.
	*/
	HFileOutputResult FileOutputByKey(const __wchar_t * filename, HC_KEY key, HOutputHandlerOptions * options);

#ifdef _MSC_VER
	HFileOutputResult FileOutputByKey(const unsigned short * filename, HC_KEY key, HOutputHandlerOptions * options){
		H_UTF16 utf16;
		utf16.encodedText((utf16_char const*) filename);
		return FileOutputByKey(H_WCS(utf16).encodedText(), key, options);
	}
#endif

	HFileOutputResult FileOutputByKey(const char * filename, HC_KEY key, HOutputHandlerOptions * options){
		return FileOutputByKey(H_WCS(filename).encodedText(), key, options);
	}

protected:
	/*! This method exports the HOOPS segment tree under the given key to a 2D pdf file.
		\param filename The name of the file to output.
		\param key The HOOPS segment key to output model data from.
		\param options Pass a pointer to HPDFOptions with information to specify the dimensions of the output as well as if you want a 3D or 2D output.
		\return The #HFileOutputResult result of the output operation.
	*/
	HFileOutputResult FileOutputByKey2D(const __wchar_t * filename, HC_KEY key, HOutputHandlerOptions * options);
	HFileOutputResult FileOutputByKey2D(const char * filename, HC_KEY key, HOutputHandlerOptions * options){
		return FileOutputByKey2D((__wchar_t*)H_WCS(filename).encodedText(), key, options);
	}

	/*! This method exports the HOOPS segment tree under the given key to a 3D pdf file.
		\param filename The name of the file to output.
		\param key The HOOPS segment key to output model data from.
		\param options Pass a pointer to HPDFOptions with information to specify the dimensions of the output as well as if you want a 3D or 2D output.
		\return The #HFileOutputResult result of the output operation.
	*/
	HFileOutputResult FileOutputByKey3D(const __wchar_t * filename, const char *, HC_KEY key, HOutputHandlerOptions * options);
	HFileOutputResult FileOutputByKey3D(const char * filename, const char * type, HC_KEY key, HOutputHandlerOptions * options){
		return FileOutputByKey3D((__wchar_t*)H_WCS(filename).encodedText(), type, key, options);
	}

	/*! This method exports the HOOPS segment tree under the given key to a pdf portfolio.
	\param filename The name of the file to output.
	\param key The HOOPS segment key to output model data from.
	\param options Pass a pointer to HPDFOptions with information to specify the dimensions of the output as well as if you want a 3D or 2D output.
	\return The #HFileOutputResult result of the output operation.
	*/
	HFileOutputResult FileOutputByKeyPortfolio(const __wchar_t * filename, HC_KEY key, HPDFOptions * options);

};


#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif
