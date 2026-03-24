//
// Copyright (c) 2002 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/Hoops3dStreamProperty.h,v 1.8 2008-02-20 19:52:15 chad Exp $
//

#ifndef __Hoops3dStreamPROPERTY_H_
#define __Hoops3dStreamPROPERTY_H_

#include "resource.h"       // main symbols
#include "guidlist.h"

#include "HTools.h"		// required for MVO_BUFFER_SIZE

EXTERN_C const CLSID CLSID_Hoops3dStreamProperty;

/////////////////////////////////////////////////////////////////////////////
// CHoops3dStreamProperty
class ATL_NO_VTABLE CHoops3dStreamProperty :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHoops3dStreamProperty, &CLSID_Hoops3dStreamProperty>,
	public IPropertyPageImpl<CHoops3dStreamProperty>,
	public CDialogImpl<CHoops3dStreamProperty>
{
public:
	CHoops3dStreamProperty();

	enum {IDD = IDD_Hoops3dStreamPROPERTY};

//DECLARE_REGISTRY_RESOURCEID(IDR_Hoops3dStreamPROPERTY)
static void FixGuid(char *in1, char *in2, wchar_t *out1, wchar_t *out2)
{
	char res[256];
	strcpy(res, "{");
	strcat(res, in2);
	strcat(res, "}");
	mbstowcs(out2, res, strlen(res)+1);
	mbstowcs(out1, in1, strlen(in1)+1);
}


static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
{
	_ATL_REGMAP_ENTRY entries[2];

	wchar_t key1[256];
	wchar_t data1[256];


	FixGuid("PROPID", CLSID_HOOPS3DSTREAMPROPERTY_CLASS, key1, data1);

	entries[0].szKey = key1;
	entries[0].szData = data1;
	entries[1].szKey = 0;
	entries[1].szData = 0;

	return(_Module.UpdateRegistryFromResource(IDR_Hoops3dStreamPROPERTY, bRegister,entries));
}

 

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHoops3dStreamProperty) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CHoops3dStreamProperty)
	CHAIN_MSG_MAP(IPropertyPageImpl<CHoops3dStreamProperty>)
	COMMAND_HANDLER(IDC_BROWSE, BN_CLICKED, OnClickedBrowse)
	COMMAND_HANDLER(IDC_EMBED, BN_CLICKED, OnClickedEmbed)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void);
 

	LRESULT OnClickedBrowse(WORD hNotifyCode, WORD wID, HWND hWNdCtl, BOOL &bHandled);	
 
 	
	TCHAR m_filename[MVO_BUFFER_SIZE];
	bool m_embed;
 
	LRESULT OnClickedEmbed(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
 
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
 
};



#endif //__Hoops3dStreamPROPERTY_H_
