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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CModelBrowserDlg.cpp,v 1.18 2010-10-08 23:29:45 chad Exp $
//

// ModelBrowserDlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "CModelBrowserDlg.h"

// HOOPS/3DGS includes

// HOOPS/MVO includes
#include "HBaseView.h"
#include "HSelectionSet.h"
#include "HSelectionItem.h"
#include "HUtilityLocaleString.h"
#include "HSolidModel.h"
// utility includes
#include "vhash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelTreeCtrl

BEGIN_MESSAGE_MAP(CModelTreeCtrl,CTreeCtrl)
	//{{AFX_MSG_MAP(CModelTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
 	ON_WM_DESTROY()
END_MESSAGE_MAP()



// GetNextItem	- Get next item as if outline was completely expanded
// Returns		- The item immediately below the reference item
// hItem		- The reference item
static HTREEITEM GetNextItem( HTREEITEM hItem, CTreeCtrl* pTreeCtrl )
{
	HTREEITEM	hti;
	if( pTreeCtrl->ItemHasChildren( hItem ) && (pTreeCtrl->GetItemState(hItem, TVIS_EXPANDED) & TVIS_EXPANDED))
		return pTreeCtrl->GetChildItem( hItem );		// return first child
	else
	{
		// return next sibling item
		// Go up the tree to find a parent's sibling if needed.
		while( (hti = pTreeCtrl->GetNextSiblingItem( hItem )) == NULL )
		{
			if( (hItem = pTreeCtrl->GetParentItem( hItem ) ) == NULL )
				return NULL;
		}
	}
	return hti;
}

static int const _NAME = ('n') | ('a' << 8) | ('m' << 16) | ('e' << 24);

static
H_WCS get_name()
{
	HUserOptions h_opt_name;
	h_opt_name.Show_One_User_Option("_name");
	HUnicodeOptions h_uni_name;
	h_uni_name.Show_One_Unicode_Option(L"_name");

	H_WCS wcs;
	if(h_opt_name.IsValid()){
		wcs = H_WCS(h_opt_name.m_data);
	}
	if(h_uni_name.IsValid()){
		wcs = H_WCS(h_uni_name.m_data);
	}

	int const len = -HC_Show_One_User_Data(_NAME, 0, 0);
	if(len > 0){
		H_UTF8 utf8;
		HC_Show_One_User_Data(_NAME, utf8.length<void*>(len), len);
		wcs = H_WCS(utf8);
	}
	return wcs;
}

/////////////////////////////////////////////////////////////////////////////
// CModelBrowserDlg dialog
CModelBrowserDlg::CModelBrowserDlg(CWnd* pParent /*=NULL*/, HBaseView * View, wchar_t * ext)
								 : CDialog(CModelBrowserDlg::IDD, pParent)
								 , m_properties(_T(""))
{
	m_pHView = View;
	m_parent = pParent;
	m_dialogactive = false;
	m_is_first_selection = true;
	m_last_selection = 0;
	m_tree_data.empty();
	m_bSuppressShowSelectedItems = false;
	if(ext)
	{
		m_pFileExtension = new wchar_t[wcslen(ext) +1];
		wcscpy(m_pFileExtension, L"");
		wcscpy(m_pFileExtension, ext);
	}
	else
	{
		m_pFileExtension = NULL;
	}
	m_pCurrentFile = new wchar_t[2048];
	m_pCurrentFile[0] = L'\0';
 	//{{AFX_DATA_INIT(CModelBrowserDlg)
	//}}AFX_DATA_INIT
}

CModelBrowserDlg::~CModelBrowserDlg()
{
	delete [] (m_pCurrentFile);
	delete [] (m_pFileExtension);
	std::multimap<std::wstring, FILE_NODE*>::iterator itr;
	for(itr = m_tree_data.begin(); itr != m_tree_data.end(); itr++)
	{
		FILE_NODE* temp = itr->second;
		unsigned int i;

		for(i = 0; i < temp->lay_list.size(); i++) //Layers in File
		{
			LAYER_NODE* tlay = temp->lay_list[i];
			unsigned int ii;
			for(ii = 0; ii < tlay->grp_list.size(); ii++)//Groups in Layer
			{
				GROUP_NODE* ttgrp =  tlay->grp_list[ii];
				delete ttgrp;
			}

			for(unsigned int ii = 0; ii < tlay->blk_list.size(); ii++)//Block Ref in Layer
			{
				BLOCK_REF_NODE* tblkgrp =  tlay->blk_list[ii];
				delete tblkgrp;
			}

			delete tlay;
		}

		for(unsigned int i = 0; i < temp->grp_list.size(); i++) //Groups in File
		{
			GROUP_NODE* tgrp = temp->grp_list[i];
			delete tgrp;
		}

		delete temp;
	}

	m_tree_data.clear();
}

BOOL CModelBrowserDlg::OnInitDialog() 
{
	m_model_tree.SubclassDlgItem(IDC_MODELTREE,this);

    CDialog::OnInitDialog();

	m_image_list.Create( IDB_MODELBROWSER_TREE_ICONS, 16, 1, RGB(255,255,255) );
	m_model_tree.SetImageList( &(m_image_list), TVSIL_NORMAL );	

	m_model_tree.SelectItem(0);
	build_model_tree();

	m_dialogactive = true;	
    return true;
}

long CModelBrowserDlg::insert_item(HC_KEY segment_key, HTREEITEM parent)
{
	long n_inserted = 0;
	if(_tcsicmp(m_pFileExtension, _T("dwg"))==0)
	{
  		LAYER_NODE *current_layer_node=0;
		GROUP_NODE *current_group_node=0;
		BLOCK_REF_NODE* current_block_ref_node = 0;
		FILE_NODE* current_file_node = NULL;

		HC_Open_Segment_By_Key(segment_key);
		if(HC_Show_Existence("user options") || HC_Show_Existence_Unicode((unsigned short const*)L"user options"))
		{
			HUserOptions h_user_opts;
			h_user_opts.Show_User_Options();
			HUnicodeOptions h_unicode_opts;
			h_unicode_opts.Show_Unicode_Options();

			H_WCS wcs;
			wcs.format("%ls, %s", h_unicode_opts.m_data, h_user_opts.m_data);
			wchar_t const * const options = wcs.encodedText();

			if (wcsstr(options, L"filename") != 0)//////////// FILE NAME //////
			{
				HUserOptions h_opt_name;
				h_opt_name.Show_One_User_Option("filename");
				HUnicodeOptions h_uni_opts;
				h_uni_opts.Show_One_Unicode_Option(L"filename");

				H_WCS wcs;
				if(h_user_opts.IsValid()){
					wcs = H_WCS(h_user_opts.m_data);
				}
				if(h_uni_opts.IsValid()){
					wcs = H_WCS(h_uni_opts.m_data);
				}
				wchar_t const * const options = wcs.encodedText();

				m_model_tree.SetItemImage(parent, 0, 0);

				TVINSERTSTRUCT is;
				is.hParent = parent;
				H_TEXT label_text(options);
				is.hInsertAfter=TVI_LAST;
				is.item.mask= TVIF_TEXT;
				is.item.pszText= (LPTSTR)(const TCHAR*)label_text;
				HTREEITEM prt = m_model_tree.InsertItem(&is);
				m_model_tree.SetItemImage(prt, 0, 0);
				HQualifiedKey *qualifiedkey = new HQualifiedKey(segment_key,m_IncludeTemp, m_IncludeCount);
				m_model_tree.SetItemData(prt,(DWORD)qualifiedkey);
				_tcscpy(m_pCurrentFile, _T(""));
				_tcscpy(m_pCurrentFile, H_TEXT(options)); //Set this as CurrentFile
				FILE_NODE* tfile = new FILE_NODE;
				tfile->name = std::wstring(options);
				tfile->me = prt;
				tfile->my_segment = segment_key;
				
				m_tree_data.insert(std::make_pair(tfile->name,tfile));

				n_inserted++;

				//Reset the parent
				parent = prt;

			}//End of FileName
			else //Other User Options Exists
			{
				if(wcsstr(options, L"1") != 0) //////////LAYER NAMES ///////
				{
					char seg_name[1024];

					HC_Show_Segment(segment_key, seg_name);
					///Check whether this segment name contains the following names
					if((strstr(seg_name,"group_names") == NULL )&&(strstr(seg_name,"layer_names") == NULL )&&(strstr(seg_name,"entity_types") == NULL )&&(strstr(seg_name,"block_table") == NULL ))//Valid Entity Segment
					{
						HUserOptions h_opt_name;
						h_opt_name.Show_One_User_Option("1");
						HUnicodeOptions h_uni_name;
						h_uni_name.Show_One_Unicode_Option(L"1");

						H_WCS wcs;
						if(h_opt_name.IsValid()){
							wcs = H_WCS(h_opt_name.m_data);
						}
						if(h_uni_name.IsValid()){
							wcs = H_WCS(h_uni_name.m_data);
						}
						wchar_t const * const options = wcs.encodedText();

						if(wcs.length() > 0)
						{
							wchar_t* tname = new wchar_t[wcslen(options) +1];
							wcscpy(tname, options);

							std::multimap<std::wstring, FILE_NODE*>::iterator tree_data_itr;
							if(m_tree_data.size())
							{
								for(tree_data_itr = m_tree_data.begin(); tree_data_itr != m_tree_data.end(); ++tree_data_itr)
								{
									//if( stricmp(tree_data_itr->first, m_pCurrentFile) == 0)
									FILE_NODE* tfile = tree_data_itr->second;
									if( tfile->me == parent )
									{
										current_file_node = tfile; //For further use in Block/Group loop
										bool lay_present = false;
										if(!tfile->lay_list.empty())//Some Layers are present in this File
										{
											for(unsigned int i = 0; i < tfile->lay_list.size(); i++)
											{
												if(wcsieq(tfile->lay_list[i]->name.c_str(),tname))
												{
													lay_present = true;
													current_layer_node = tfile->lay_list[i];
													break;
													//Layer already exist
												}
											}
										}

										if(lay_present == false)//New layer Entry
										{
											H_WCS layer_name("garbage");
											HC_Open_Segment_By_Key(tfile->my_segment);
											HC_Open_Segment("LAYER_NAMES");
											if (HC_Show_Existence("user options") || HC_Show_Existence_Unicode((unsigned short const*)L"user options"))
											{
												HUserOptions h_user_opts;
												h_user_opts.Show_User_Options();
												HUnicodeOptions h_uni_opts;
												h_uni_opts.Show_Unicode_Options();

												H_WCS wcs;
												if(h_user_opts.IsValid()){
													wcs = H_WCS(h_user_opts.m_data);
												}
												if(h_uni_opts.IsValid()){
													wcs = H_WCS(h_uni_opts.m_data);
												}
												wchar_t const * const options = wcs.encodedText();

												if (wcsstr(options, tname) != 0)
												{
													HUserOptions h_opt_name;
													h_opt_name.Show_One_User_Option(H_ASCII_TEXT(tname));
													if(h_opt_name.IsValid()){
														layer_name = H_WCS(h_opt_name.m_data);
													}
													HUnicodeOptions h_uni_name;
													h_uni_name.Show_One_Unicode_Option(tname);
													if(h_uni_name.IsValid()){
														layer_name = H_WCS(h_uni_name.m_data);
													}
												}
											}
											HC_Close_Segment();
											HC_Close_Segment();

											H_TEXT label_text(layer_name.encodedText());
											TVINSERTSTRUCT is;
											is.hParent = parent;//tfile->me;
											is.hInsertAfter=TVI_LAST;
											is.item.mask= TVIF_TEXT;
											is.item.pszText= (LPTSTR)(const TCHAR*)label_text;
											HTREEITEM temp_prt = m_model_tree.InsertItem(&is);
											m_model_tree.SetItemImage(temp_prt, 0, 0);
											HQualifiedKey *qualifiedkey = new HQualifiedKey(segment_key,m_IncludeTemp, m_IncludeCount);
											m_model_tree.SetItemData(temp_prt,(DWORD)qualifiedkey);
											LAYER_NODE* tlay = new LAYER_NODE;
											tlay->name = std::wstring(tname);
											tlay->me = temp_prt;
											tfile->lay_list.push_back(tlay);
											current_layer_node = tlay;
											n_inserted++;
										}
										break;
									}
									
								}
							}
							delete [] tname;
						}
					}
				} //End of LAYER_NAMES

				if(wcsstr(options, L"4") != 0)//Check For Block Reference
				{
					char seg_name[1024];

					HC_Show_Segment(segment_key, seg_name);
					if((strstr(seg_name,"group_names") == NULL )&&(strstr(seg_name,"layer_names") == NULL )&&(strstr(seg_name,"entity_types") == NULL )&&(strstr(seg_name,"block_table") == NULL ))//Valid Entity Segment
					{
						if(wcsstr(options, L"4") != 0)//////////BLOCK TABLE NAMES ///////
						{
							HUserOptions h_opt_name;
							h_opt_name.Show_One_User_Option("4");
							HUnicodeOptions h_uni_name;
							h_uni_name.Show_One_Unicode_Option(L"4");

							H_WCS wcs;
							if(h_opt_name.IsValid()){
								wcs = H_WCS(h_opt_name.m_data);
							}
							if(h_uni_name.IsValid()){
								wcs = H_WCS(h_uni_name.m_data);
							}
							wchar_t const * const options = wcs.encodedText();

							if(wcs.length() > 0)
							{
								wchar_t * tBlkName = new wchar_t[wcslen(options) +1];
								wcscpy(tBlkName, options);
								if(current_layer_node != 0)//This BLOCK_REF is child of LAYER //No entity esist without layer
								{
									if(m_tree_data.size())
									{
										bool blk_exist = false;
										for(unsigned int i = 0; i < current_layer_node->blk_list.size(); i++)
										{
											if(wcsicmp(current_layer_node->blk_list[i]->name.c_str(), tBlkName) == 0) //Block Ref Exist
											{
												blk_exist = true;
												current_block_ref_node = current_layer_node->blk_list[i];
												break;
											}

										}
										if(blk_exist == false)
										{
											H_WCS blk_name("garbage");
											HC_Open_Segment_By_Key(current_file_node->my_segment);
											HC_Open_Segment("DWG_ENTITY_NAMES");
											HC_Open_Segment("BLOCK_TABLE");
											if (HC_Show_Existence("user options") || HC_Show_Existence_Unicode((unsigned short const*)L"user options"))
											{
												HUserOptions h_user_opts;
												h_user_opts.Show_User_Options();
												HUnicodeOptions h_uni_opts;
												h_uni_opts.Show_Unicode_Options();

												H_WCS wcs;
												if(h_user_opts.IsValid()){
													wcs = H_WCS(h_user_opts.m_data);
												}
												if(h_uni_opts.IsValid()){
													wcs = H_WCS(h_uni_opts.m_data);
												}
												wchar_t const * const options = wcs.encodedText();

												if (wcsstr(options, tBlkName) != 0)
												{
													HUserOptions h_opt_name;
													h_opt_name.Show_One_User_Option(H_ASCII_TEXT(tBlkName));
													if(h_opt_name.IsValid()){
														blk_name = H_WCS(h_opt_name.m_data);
													}
													HUnicodeOptions h_uni_name;
													h_uni_name.Show_One_Unicode_Option(tBlkName);
													if(h_uni_name.IsValid()){
														blk_name = H_WCS(h_uni_name.m_data);
													}
												}
											}
											HC_Close_Segment();
											HC_Close_Segment();
											HC_Close_Segment();
											H_TEXT label_text(blk_name.encodedText());
											TVINSERTSTRUCT is;
											is.hParent = current_layer_node->me;
											is.hInsertAfter=TVI_LAST;
											is.item.mask= TVIF_TEXT;
											is.item.pszText= (LPTSTR)(const TCHAR*)label_text;
											HTREEITEM local_prt = m_model_tree.InsertItem(&is);
											m_model_tree.SetItemImage(local_prt, 0, 0);
											HQualifiedKey *qualifiedkey = new HQualifiedKey(segment_key,m_IncludeTemp, m_IncludeCount);
											m_model_tree.SetItemData(local_prt,(DWORD)qualifiedkey); 
											BLOCK_REF_NODE* tblk = new BLOCK_REF_NODE;
											tblk->name = std::wstring(tBlkName);
											tblk->me = local_prt;
											current_layer_node->blk_list.push_back(tblk);
											current_block_ref_node = tblk;
											n_inserted++;
										}
									}
								}
								delete [] tBlkName;
							}
						}//End of BLOCK_TABLE NAMES 
					}
				}//End of Block Reference

				if(wcsstr(options, L"2") != 0) //Check for Group Name
				{
					char seg_name[1024];

					HC_Show_Segment(segment_key, seg_name);
					if((strstr(seg_name,"group_names") == NULL )&&(strstr(seg_name,"layer_names") == NULL )&&(strstr(seg_name,"entity_types") == NULL )&&(strstr(seg_name,"block_table") == NULL ))//Valid Entity Segment
					{
						if(wcsstr(options, L"2") != 0)//////////GROUPS NAMES ///////
						{
							HUserOptions h_opt_name;
							h_opt_name.Show_One_User_Option("2");
							HUnicodeOptions h_uni_name;
							h_uni_name.Show_One_Unicode_Option(L"2");

							H_WCS wcs;
							if(h_opt_name.IsValid()){
								wcs = H_WCS(h_opt_name.m_data);
							}
							if(h_uni_name.IsValid()){
								wcs = H_WCS(h_uni_name.m_data);
							}
							wchar_t const * const options = wcs.encodedText();

							if(wcs.length() > 0)
							{
								wchar_t* tGrpName = new wchar_t[wcslen(options)+1];
								wcscpy(tGrpName, options);
								if(current_layer_node != 0)//This group is child of LAYER //Every entity belongs to some layer
								{
									if(m_tree_data.size())
									{
										bool grp_exist = false;
										for(unsigned int i = 0; i < current_layer_node->grp_list.size(); i++)
										{
											if(wcsicmp(current_layer_node->grp_list[i]->name.c_str(), (tGrpName)) == 0) //Group Exist
											{
												grp_exist = true;
												current_group_node = current_layer_node->grp_list[i];
												break;
											}

										}
										if(grp_exist == false)
										{
											H_WCS grp_name("garbage");
											HC_Open_Segment_By_Key(current_file_node->my_segment);
											HC_Open_Segment("GROUP_NAMES");
											if (HC_Show_Existence("user options") || HC_Show_Existence_Unicode((unsigned short const*)L"user options"))
											{
												HUserOptions h_user_opts;
												h_user_opts.Show_User_Options();
												HUnicodeOptions h_unicode_opts;
												h_unicode_opts.Show_Unicode_Options();

												H_WCS wcs;
												if(h_user_opts.IsValid()){
													wcs = H_WCS(h_user_opts.m_data);
												}
												if(h_unicode_opts.IsValid()){
													wcs = H_WCS(h_unicode_opts.m_data);
												}
												wchar_t const * const options = wcs.encodedText();

												if (wcsstr(options, tGrpName) != 0)
												{
													HUserOptions h_opt_name;
													h_opt_name.Show_One_User_Option(H_ASCII_TEXT(tGrpName));
													if(h_opt_name.IsValid()){
														grp_name = H_WCS(h_opt_name.m_data);
													}
													HUnicodeOptions h_uni_name;
													h_uni_name.Show_One_Unicode_Option(tGrpName);
													if(h_uni_name.IsValid()){
														grp_name = H_WCS(h_uni_name.m_data);
													}
													if(grp_name.length() == 0)
													{
														HC_Close_Segment();
														return n_inserted;
													}
												}
											}
											HC_Close_Segment();
											HC_Close_Segment();
											H_TEXT label_text(grp_name.encodedText());
											TVINSERTSTRUCT is;
											is.hParent = current_layer_node->me;
											is.hInsertAfter=TVI_LAST;
											is.item.mask= TVIF_TEXT;
											is.item.pszText= (LPTSTR)(const TCHAR*)label_text;
											HTREEITEM local_prt = m_model_tree.InsertItem(&is);
											m_model_tree.SetItemImage(local_prt, 0, 0);
 											HQualifiedKey *qualifiedkey = new HQualifiedKey(segment_key,m_IncludeTemp, m_IncludeCount);
											m_model_tree.SetItemData(local_prt,(DWORD)qualifiedkey); 

											GROUP_NODE* tgrp = new GROUP_NODE;
											tgrp->name = std::wstring(tGrpName);
											tgrp->me = local_prt;
											current_layer_node->grp_list.push_back(tgrp);
											current_group_node = tgrp;
											n_inserted++;
										}
									}
								}
								delete [] tGrpName;
							}
						}//End of GROUPS NAMES 
					}//End of group_names, layer_names, entity_names
				}//End of Group Name

				if(wcsstr(options, L"3") != 0) //Check for Actual Entity
				{
					char seg_name[1024];

					HC_Show_Segment(segment_key, seg_name);
					if((strstr(seg_name,"group_names") == NULL )&&(strstr(seg_name,"layer_names") == NULL )&&(strstr(seg_name,"entity_types") == NULL )&&(strstr(seg_name,"block_table") == NULL ))//Valid Entity Segment
					{
						if (wcsstr(options, L"3") != 0)//////////ENTITY NAMES ///////
						{
							HUserOptions h_opt_name;
							h_opt_name.Show_One_User_Option("3");
							HUnicodeOptions h_uni_name;
							h_uni_name.Show_One_Unicode_Option(L"3");

							H_WCS wcs;
							if(h_opt_name.IsValid()){
								wcs = H_WCS(h_opt_name.m_data);
							}
							if(h_uni_name.IsValid()){
								wcs = H_WCS(h_uni_name.m_data);
							}
							wchar_t const * const options = wcs.encodedText();

							if(wcs.length() > 0)
							{
								wchar_t * tEntName = new wchar_t[wcslen(options)+1];
								wcscpy(tEntName, options);
								H_WCS entity_name("garbage");

								HC_Open_Segment_By_Key(current_file_node->my_segment);
								HC_Open_Segment("DWG_ENTITY_NAMES");
								HC_Open_Segment("ENTITY_TYPES");
								if (HC_Show_Existence("user options") || HC_Show_Existence_Unicode((unsigned short const*)L"user options"))
								{
									HUserOptions h_user_opts;
									h_user_opts.Show_User_Options();
									HUnicodeOptions h_unicode_opts;
									h_unicode_opts.Show_Unicode_Options();

									H_WCS wcs;
									if(h_user_opts.IsValid()){
										wcs = H_WCS(h_user_opts.m_data);
									}
									if(h_unicode_opts.IsValid()){
										wcs = H_WCS(h_unicode_opts.m_data);
									}
									wchar_t const * const options = wcs.encodedText();

									if (wcsstr(options, tEntName) != 0)
									{
										HUserOptions h_opt_name;
										h_opt_name.Show_One_User_Option(H_ASCII_TEXT(tEntName));
										if(h_opt_name.IsValid()){
											entity_name = H_WCS(h_opt_name.m_data);
										}
										HUnicodeOptions h_uni_name;
										h_uni_name.Show_One_Unicode_Option(tEntName);
										if(h_uni_name.IsValid()){
											entity_name = H_WCS(h_uni_name.m_data);
										}
									}
								}
								HC_Close_Segment();
								HC_Close_Segment();
								HC_Close_Segment();

								H_TEXT label_text(entity_name.encodedText());
								TVINSERTSTRUCT is;
								if(current_group_node !=0 && current_layer_node!=0 && current_block_ref_node!=0)
									is.hParent = current_group_node->me;
								else if(current_group_node !=0 && current_layer_node!=0)
									is.hParent = current_group_node->me;
								else if(current_block_ref_node!=0 && current_layer_node!=0)
									is.hParent = current_block_ref_node->me;
								else if(current_layer_node!=0)
									is.hParent = current_layer_node->me;
								
								is.hInsertAfter=TVI_LAST;
								is.item.mask= TVIF_TEXT;
								is.item.pszText= (LPTSTR)(const TCHAR*)label_text;
								HTREEITEM local_prt = m_model_tree.InsertItem(&is);
								m_model_tree.SetItemImage(local_prt, 1, 1);
								HQualifiedKey *qualifiedkey = new HQualifiedKey(segment_key,m_IncludeTemp, m_IncludeCount);
								m_model_tree.SetItemData(local_prt,(DWORD)qualifiedkey); 

 								n_inserted++;

								current_group_node = NULL;
								current_layer_node = NULL;
								current_block_ref_node = NULL;
								current_file_node = NULL;
								delete [] tEntName;
							}
						}///End of ENTITY NAMES ///////

					}//End of group_names, layer_names, entity_names
				}//End of Entity Check
			}//End of else{}
		}//End of HC_Show_Existence("user options") || HC_Show_Existence_Unicode((unsigned short const*)L"user options"))

		//Search for its SubSegments till it get to leaf segment
		char	*type = NULL;
		HC_KEY	new_key;
		
		type = new char [MVO_BUFFER_SIZE];
		assert(type);

		HC_Begin_Contents_Search(".", "includes, segment"); 
			while(HC_Find_Contents (type, &new_key)) 
			{
				if(strstr (type, "segment")) 
				{
					char * segment_name = new char[MVO_BUFFER_SIZE];
					HC_Show_Segment(new_key, segment_name);
					char const * seg = strrchr(segment_name, '/');
					if(!streq(seg, "/model_include")){
						delete [] segment_name;
						n_inserted += insert_item(new_key, parent );
					}
					else {
						delete [] segment_name;
					}
				}
				else if(strstr("include", type))
				{
					m_IncludeTemp[m_IncludeCount++] = new_key;
					HC_KEY includee = HC_KShow_Include_Segment(new_key);
					n_inserted += insert_item(includee, parent );
					m_IncludeCount--;
				}
			}
		HC_End_Contents_Search ();
		H_SAFE_DELETE_ARRAY(type);

		HC_Close_Segment();//Close the input segment
	}
	else
	{
		bool suppress_tree = false;
		bool suppress_node = false;

		HC_Open_Segment_By_Key(segment_key);

			if (HC_Show_Existence("user options") || HC_Show_Existence_Unicode((unsigned short const*)L"user options"))
			{
				HUserOptions h_user_opts;
				HUserOptions h_user_value;

				h_user_opts.Show_User_Options();

				if (strstr(h_user_opts.m_data, "_h_modelbrowser_suppress") != 0)
				{
					h_user_value.Show_One_User_Option("_h_modelbrowser_suppress");
					if(strieq(h_user_value.m_data, "TREE"))
					{
						suppress_node = true;
						suppress_tree = true;
					}
					else if strieq(h_user_value.m_data, "NODE")
						suppress_node = true;
				}

				H_WCS wcs = get_name();
				wchar_t const * const options = wcs.encodedText();

				if(options)
				{
					if (wcslen(options) > 0)
					{
						if( suppress_node == false )
						{
							// this parent is definitely going to have children
							m_model_tree.SetItemImage(parent, 0, 0);

							H_TEXT label_text(options);
							TVINSERTSTRUCT is;
							is.hParent = parent;
							is.hInsertAfter=TVI_LAST;
							is.item.mask= TVIF_TEXT;
							is.item.pszText= (LPTSTR)(const TCHAR*)label_text;
							parent = m_model_tree.InsertItem(&is);

							HQualifiedKey *qualifiedkey = new HQualifiedKey(segment_key,m_IncludeTemp, m_IncludeCount);
							m_model_tree.SetItemData(parent,(DWORD)qualifiedkey);
							if (strcmp(H_ASCII_TEXT(is.item.pszText),"face") == 0)							
								m_model_tree.SetItemImage(parent, 2, 2);
							else
								m_model_tree.SetItemImage(parent, 1, 1);


 
							n_inserted++;
						}
					}
				}
			}

			if(suppress_tree == false)
			{
				char	*type = NULL;
				HC_KEY	new_key;
				
				type = new char [MVO_BUFFER_SIZE];
				assert(type);

				HC_Begin_Contents_Search (".", "includes, segment"); 
					while (HC_Find_Contents (type, &new_key)) 
					{
						if (strstr (type, "segment")) 
						{
							char * segment_name = new char[MVO_BUFFER_SIZE];
							HC_Show_Segment(new_key, segment_name);
							char const * seg = strrchr((char const*)segment_name, '/');
							if(!streq(seg, "/model_include")){
								delete [] segment_name;
								n_inserted += insert_item(new_key, parent );
							}
							else {
								delete [] segment_name;
							}
						}
						else if (strstr("include", type))
						{
							// we are going to take a include route, accumulate the owner seg
							// into the path
							
							m_IncludeTemp[m_IncludeCount++] = new_key;
 							HC_KEY includee = HC_KShow_Include_Segment(new_key);
							n_inserted += insert_item(includee, parent );
							m_IncludeCount--;
						}
					}
				HC_End_Contents_Search ();

				HSolidModel *smodel = (HSolidModel *)m_pHView->GetModel();
				BREP_Face * brepface = smodel->m_TopologyManager->GetFace(segment_key);
				if (brepface)
				{
					START_LIST_ITERATION(BREP_CoEdge, brepface->m_CoEdgeList);
							H_TEXT label_text("coedge");
							TVINSERTSTRUCT is;
							is.hParent = parent;
							is.hInsertAfter=TVI_LAST;
							is.item.mask= TVIF_TEXT;
							is.item.pszText= (LPTSTR)(const TCHAR*)label_text;
							HTREEITEM coedgeitem = m_model_tree.InsertItem(&is);

							HQualifiedKey *qualifiedkey = new HQualifiedKey(temp->m_edge->m_edgekey,m_IncludeTemp, m_IncludeCount);
 
							m_model_tree.SetItemData(coedgeitem,(DWORD)qualifiedkey);
							m_model_tree.SetItemImage(coedgeitem, 3, 3);

							H_TEXT label_text2("edge");							
							is.hParent = coedgeitem;
							is.hInsertAfter=TVI_LAST;
							is.item.mask= TVIF_TEXT;
							is.item.pszText= (LPTSTR)(const TCHAR*)label_text2;
							HTREEITEM edgeitem = m_model_tree.InsertItem(&is);
							qualifiedkey = new HQualifiedKey(temp->m_edge->m_edgekey,m_IncludeTemp, m_IncludeCount);
							m_model_tree.SetItemData(edgeitem,(DWORD)qualifiedkey);
							m_model_tree.SetItemImage(edgeitem, 3, 3);

							if (temp->m_edge->m_vertex1 != INVALID_KEY)
							{
								H_TEXT label_text3("vertex");							
								is.hParent = edgeitem;
								is.hInsertAfter=TVI_LAST;
								is.item.mask= TVIF_TEXT;
								is.item.pszText= (LPTSTR)(const TCHAR*)label_text3;
								HTREEITEM vertexitem1 = m_model_tree.InsertItem(&is);
								HQualifiedKey *qualifiedkey = new HQualifiedKey(temp->m_edge->m_vertex1,m_IncludeTemp, m_IncludeCount);

								m_model_tree.SetItemData(vertexitem1,(DWORD)qualifiedkey);
								m_model_tree.SetItemImage(vertexitem1, 4, 4);
							}
							if (temp->m_edge->m_vertex2 != INVALID_KEY)
							{
								H_TEXT label_text3("vertex");							
								is.hParent = edgeitem;
								is.hInsertAfter=TVI_LAST;
								is.item.mask= TVIF_TEXT;
								is.item.pszText= (LPTSTR)(const TCHAR*)label_text3;
								HTREEITEM vertexitem2 = m_model_tree.InsertItem(&is);
								HQualifiedKey *qualifiedkey = new HQualifiedKey(temp->m_edge->m_vertex2,m_IncludeTemp, m_IncludeCount);
								m_model_tree.SetItemData(vertexitem2,(DWORD)qualifiedkey);
 								m_model_tree.SetItemImage(vertexitem2, 4, 4);
							}


					END_LIST_ITERATION(brepface->m_CoEdgeList);
				}				
				H_SAFE_DELETE_ARRAY(type);
			}

		HC_Close_Segment();
	}

	return n_inserted;
}


// 1. Scan the model segment tree for the user options
// 2. Create a tree based on the user options
bool CModelBrowserDlg::build_model_tree()
{
	int n_inserted = 0;
	m_IncludeCount = 0;
	if(m_pHView)
		n_inserted = insert_item(m_pHView->GetModelKey(), TVI_ROOT);

	if(n_inserted < 1)
	{
		H_TEXT label_text(_T("No Model Structure Data Found"));
		TVINSERTSTRUCT is;
		is.hParent = TVI_ROOT;
		is.hInsertAfter = TVI_LAST;
		is.item.mask= TVIF_TEXT;
		is.item.pszText= (LPTSTR)(const TCHAR*)label_text;
		HTREEITEM item = m_model_tree.InsertItem(&is);
		m_model_tree.SetItemData(item,(DWORD)INVALID_KEY);

		m_properties = _T("Please ensure your segment tree has \'_name\' user option set");
		UpdateData(FALSE);
	}

	return true;
}

void CModelBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModelBrowserDlg)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_PROPERTIES, m_properties);
}

BEGIN_MESSAGE_MAP(CModelBrowserDlg, CDialog)
	//{{AFX_MSG_MAP(CModelBrowserDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MODELTREE, OnSelchangedTree)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_MODELTREE, OnItemexpandingTree1)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_MODELTREE, OnItemexpandedTree1)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define I2V(x) ((void *)(POINTER_SIZED_INT)(x))

void CModelBrowserDlg::show_if_selected(HTREEITEM item, struct vhash_s* selected_keys)
{
	CString temp = m_model_tree.GetItemText(item);
	HQualifiedKey * item_key = (HQualifiedKey *)m_model_tree.GetItemData(item);
	if(item_key)
	{
		if(vhash_lookup_item(selected_keys, I2V(item_key->MakeHashKey()), 0) == VHASH_STATUS_SUCCESS)
		{
			//m_model_tree.EnsureVisible(item);
			m_model_tree.SetItemState(item,TVIS_BOLD,TVIS_BOLD);
			m_last_selection = item;
		}
		else
		{
			m_model_tree.SetItemState(item,!TVIS_BOLD,TVIS_BOLD);
		}
	}

}




//this function updates the selected item display (bold) in the tree control for the visible
//elements
//needs to be called whenever the selection has changed
//this is the main cause for speed problems with a large number of selections
//fix: have to think of a way to speed up the selection process...
void CModelBrowserDlg::ShowSelectedItems()
{
	if (!m_bSuppressShowSelectedItems)
	{
	HTREEITEM root = m_model_tree.GetRootItem();
	if(root == NULL)
		return;
	
	vhash_t* selected_keys = new_vhash(10, malloc, free);
	HSelectionSet *selection_set = m_pHView->GetSelection();
	for (unsigned int i=0; i < selection_set->GetSize(); i++)
	{
		HSmartSelItem * item = (HSmartSelItem *)selection_set->GetSelectionItemAt(i);
		HC_KEY firstinclude = INVALID_KEY;
		if (item->GetIncludeCount())
			firstinclude =  ((HC_KEY *)(item->GetIncludeKeys()))[0];

		long HashKey;
		if (firstinclude == m_pHView->GetViewKey())		
			HashKey = HQualifiedKey::MakeHashKey(item->GetKey(),item->GetIncludeCount()-2, (HC_KEY *)(item->GetIncludeKeys()+2)); 
		else
			HashKey = HQualifiedKey::MakeHashKey(item->GetKey(),item->GetIncludeCount()-1, (HC_KEY *)(item->GetIncludeKeys()+1)); 

//		while(1)
		{
			vhash_insert_item(selected_keys, I2V(HashKey), 0);
//			selection_key = HC_KShow_Owner_By_Key(selection_key);
//			if(selection_key == INVALID_KEY || selection_key == model_key)
//				break;
		}
	}

	HTREEITEM hti = m_model_tree.GetRootItem();
 	while( hti )
	{
		show_if_selected(hti, selected_keys);
		hti = GetNextItem( hti, &m_model_tree );
 	}
	if(m_last_selection != 0)
	{
		HQualifiedKey *qkey = (HQualifiedKey *)m_model_tree.GetItemData(m_last_selection);
		update_properties_display(qkey);
		m_last_selection = 0;
	}
	else
	{
		m_properties = _T("no active selection");
		UpdateData(FALSE);
	}

	delete_vhash(selected_keys);
	}
}



HQualifiedKey * CModelBrowserDlg::Select(HTREEITEM item)
{
	HSelectionSet* selection = m_pHView->GetSelection();
	HQualifiedKey *	item_key = (HQualifiedKey *)m_model_tree.GetItemData(item);
	if (item_key && item_key->m_Key != INVALID_KEY)
		selection->Select(item_key->m_Key,item_key->m_IncludeListLength, item_key->m_pIncludeList);
	return item_key;
}


//this function is called whenever a selection is changed in the tree control
//this could be the result of a selection/deselection in the tree control or in the view 
void CModelBrowserDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// The first SelChange message isn't real selection. It is triggered automatically
	// because of the initial root selection - so ignore it - Rajesh B (28-Sep-06)
	
	m_bSuppressShowSelectedItems = true;
	if(m_is_first_selection)
	{
		m_is_first_selection = false;
		return;
	}
	NM_TREEVIEW* pNMTreeView	= (NM_TREEVIEW*)pNMHDR;
	TVITEM itemnew				= pNMTreeView->itemNew;
	HQualifiedKey * item_key;

	HSelectionSet* selection = m_pHView->GetSelection();
	selection->DeSelectAll();

	HTREEITEM hItem = itemnew.hItem;
	HTREEITEM hti;
	bool entityselect = selection->GetAllowEntitySelection();

	if( m_model_tree.ItemHasChildren( hItem ))
	{
		selection->SetAllowEntitySelection(true);
		HTREEITEM second_item = m_model_tree.GetChildItem( hItem );
		item_key = Select(second_item);
		
		while( (hti = m_model_tree.GetNextSiblingItem( second_item )))
		{
			selection->SetAllowEntitySelection(true);
	 		item_key = Select(hti);
			second_item=hti;
		}  
	}
	{
 		 selection->SetAllowEntitySelection(true);
		 item_key = Select(itemnew.hItem);		
	}
	
    selection->SetAllowEntitySelection(entityselect);
	m_pHView->Update();

	m_bSuppressShowSelectedItems = false;
	ShowSelectedItems();

	update_properties_display(item_key);

	*pResult = 0;
}


bool CModelBrowserDlg::update_properties_display(HQualifiedKey * qualified_key)
{
	HC_KEY new_key = INVALID_KEY;
	
	if (qualified_key)
		new_key = qualified_key->m_Key;

 
	m_properties.Empty();

	char type[MVO_BUFFER_SIZE];
	if (new_key != INVALID_KEY)
	{
	HC_Show_Key_Type(new_key, type);
	if (strcmp(type, "segment") == 0)
	{
		HC_Open_Segment_By_Key(new_key);
			if (HC_Show_Existence("user options") || HC_Show_Existence_Unicode((unsigned short const*)L"user options"))
			{
				HUserOptions h_user_opts;
				h_user_opts.Show_User_Options();

				if(h_user_opts.IsValid()){
					m_properties += h_user_opts.m_data;
		
				}

				HUnicodeOptions h_unicode_opts;
				h_unicode_opts.Show_Unicode_Options();
				if(h_unicode_opts.IsValid()){
					m_properties += h_unicode_opts.m_data;
				}

			}
		HC_Close_Segment();
	}
	}
	UpdateData(FALSE);
	return true;
}

//called whenever the expands a subtree for the first time
void CModelBrowserDlg::OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ShowSelectedItems();
}
 
void CModelBrowserDlg::OnClose() 
{
	m_dialogactive = false;
	CDialog::OnClose();
}

void CModelBrowserDlg::OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
}

void CModelBrowserDlg::ValidateModelTree()
{
	m_model_tree.DeleteAllItems();
}

void CModelBrowserDlg::OnSize(UINT nType, int cx, int cy) 
{	
	CDialog::OnSize(nType, cx, cy); 

	if( cx < 241 )
		cx = 241;
	if( cy < 250 )
		cy = 250;

	if (m_dialogactive)
	{
		CWnd *wnd = GetDlgItem(IDC_MODELBROWSERWRAP);
		wnd->SetWindowPos( 0, 0, 0, cx-15, cy-10, SWP_NOMOVE | SWP_NOREPOSITION);
		
		wnd = GetDlgItem(IDC_STRUCTURE_WRAP);
		wnd->SetWindowPos( 0, 0, 0, cx-30, cy-140, SWP_NOMOVE | SWP_NOREPOSITION);

		m_model_tree.SetWindowPos( 0, 0, 0, cx-45, cy-162, SWP_NOMOVE | SWP_NOREPOSITION );

		wnd = GetDlgItem(IDC_PROPERTIES_WRAP);
		wnd->SetWindowPos( 0, 15, cy-120, cx-30, 105, SWP_NOREPOSITION);

		wnd = GetDlgItem(IDC_PROPERTIES);
		wnd->SetWindowPos( 0, 22, cy-105, cx-45, 80, SWP_NOREPOSITION);
	}
}


void CModelTreeCtrl::Clean(HTREEITEM hti)
{
	HTREEITEM sibling = hti;
	while (1)
	{
		HQualifiedKey * item_key = (HQualifiedKey *)GetItemData(sibling);
		if (item_key)
			delete item_key;	
		 HTREEITEM child = GetChildItem( sibling );
		 if (child)
			Clean(child);
		sibling = GetNextSiblingItem( sibling  );
		if (!sibling)
			break;

 	}
}
		

void CModelTreeCtrl::OnDestroy()
{
	HTREEITEM hti = GetRootItem();
 	Clean(hti);

}
