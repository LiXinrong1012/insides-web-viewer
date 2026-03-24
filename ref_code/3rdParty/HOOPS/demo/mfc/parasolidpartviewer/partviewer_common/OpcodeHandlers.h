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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/OpcodeHandlers.h,v 1.13 2010-10-27 21:34:45 heppe Exp $
//

#ifndef OPCODEHANDLERS_H
#define OPCODEHANDLERS_H


#include "HStream.h"
#include "HOpcodeHandler.h"
#include "HOpcodeShell.h"
#include "HMaterialLibrary.h"


class CSolidHoopsView;
class TK_My_Initial_View;
class TK_My_Markup;
class TK_My_Views;


class PartviewerHSFExtras : public BBaseOpcodeHandler
{
private:
	TK_My_Initial_View * m_miv;
	TK_My_Markup * m_mm;
	TK_My_Views * m_mvs;
	CSolidHoopsView * m_pView;
	bool m_saveMarkup;

public:
	PartviewerHSFExtras(CSolidHoopsView * pView, bool save_markup = true);
	~PartviewerHSFExtras();

	TK_Status   Interpret(BStreamFileToolkit &tk, ID_Key key, int variant);
	TK_Status   Execute (BStreamFileToolkit & tk);
	TK_Status	Write (BStreamFileToolkit & tk);
	TK_Status	Read (BStreamFileToolkit & tk);
	void	Reset ();
};


class HTK_PartviewerMaterialHandler : public HTK_Material_Composite
{
private:
	CSolidHoopsView * m_pView;

public:
	HTK_PartviewerMaterialHandler(CSolidHoopsView *view, HMaterialLibrary *hmat)
		:HTK_Material_Composite(hmat) {
		m_pView = view;
	};
	~HTK_PartviewerMaterialHandler() {};

	TK_Status	Read (BStreamFileToolkit & tk);
};


class W3D_Image : public BBaseOpcodeHandler
{
private:
	W3D_Image(const W3D_Image&);
	W3D_Image& operator=(const W3D_Image&);

protected:

	char *                  m_name;         /*!< internal use; name applied to image (if any) */
	int                     m_name_length;  /*!< internal use; Length of name */
	int                     m_size[2];
	char                    m_bpp;

	//! internal use
	void    set_name (char const * string);
	//! internal use
	void    set_name (int length);

public:
	/*! constructor */
	W3D_Image () : BBaseOpcodeHandler ((unsigned char)0xE0), m_name (0), m_name_length (0), m_bpp(0)
	{ m_size[0] = m_size[1] = 0; }
	~W3D_Image();

	TK_Status   Read (BStreamFileToolkit & tk);
	TK_Status   Write (BStreamFileToolkit & tk);
	TK_Status   W3D_Image::Execute (BStreamFileToolkit & tk);
	void        Reset (void);

	/*! Sets the name of the image.  Allocates the buffer and copies the string */
	void            SetName (char const * string)                 { set_name (string);}
	/*! Sets the name buffer.  Allocates a buffer large enough to hold a string of 'length' characters */
	void            SetName (int length)                          { set_name (length);}
	/*! Returns the image name string */
	char const *    GetName (void) const                           { return m_name;}
	/*! Returns the image name string buffer, which may be modified directly */
	char *			 GetName (void)                                { return m_name;}

	void            SetSize (int x, int y )                        { m_size[0] = x; m_size[1] = y;}
	int const*      GetSize (void) const                           { return m_size;}
	int *			GetSize (void)                                 { return m_size;}

	void            SetBitDepth( char bpp )                        { m_bpp = bpp;}
	char const      GetBitDepth (void) const                       { return m_bpp;}
	char			GetBitDepth (void)                             { return m_bpp;}

};

#endif
