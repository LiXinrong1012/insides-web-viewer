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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSUtility.h,v 1.15 2008-11-26 21:21:41 guido Exp $
//

#ifndef hsutility
#define hsutility

#include "HTools.h"

#ifdef PARASOLID
#include "parasolid_kernel.h"
#include "kernel_interface.h"
#endif // PARASOLID

#ifdef ACIS
#define HA_OPERATION_SUBTRACT 1
#define HA_OPERATION_UNITE 2
#define HA_OPERATION_INTERSECT 3
class BODY;
extern void acis_boolean(unsigned long operation, BODY* target, unsigned long number_of_tools, BODY** tools);
#endif // ACIS

class MultiSelectManager;

class  QualifiedKey
{
public:
	QualifiedKey(HC_KEY key, int length, HC_KEY *m_IncludeList)
	{
		m_Key = key;
		m_IncludeList = 0;
		m_IncludeListLength = 0;
	}
	QualifiedKey()
	{
		m_IncludeList = 0;
		m_Key = INVALID_KEY;
		m_IncludeListLength = 0;
	}

	~QualifiedKey()
	{
		if (m_IncludeListLength)
			delete [] m_IncludeList;
	}

	void Select(HBaseView *view);
	HC_KEY GetKey() { return m_Key; }
	HC_KEY GetKeyHash() { return m_Key; }

	void SetKey(HC_KEY key) { m_Key= key; }
	HC_KEY *m_IncludeList;
	int  m_IncludeListLength;
	HC_KEY m_Key;
};



class  MultiSelectItem
{
public:
	MultiSelectItem(HC_KEY key);
	~MultiSelectItem();
	void AddAssociatedKey(HC_KEY key, int length = 0, HC_KEY *include_list = 0);
	void AddAssociatedSelectItem(HC_KEY key, int length = 0, HC_KEY *include_list = 0);
	void MultiSelect(MultiSelectManager *msm, HBaseView *view);
	QualifiedKey m_Key;
	struct vlist_s *	m_AssociatedKeyList;
	struct vlist_s*		m_AssociatedSelectItemList;

};

class  MultiSelectManager
{
public:
	MultiSelectManager();
	~MultiSelectManager();

	MultiSelectItem *CreateMultiSelectItem(HC_KEY key);
	MultiSelectItem *GetMultiSelectItem(HC_KEY key);
	HC_KEY MultiSelect(HC_KEY key, HBaseView *view);

	struct vhash_s *		m_SelectItemHash;
	struct vlist_s *		m_SelectItemList;
	bool m_bHasItems;
};





#ifdef PARASOLID
extern int report_ifail(int ifail,int expect);
extern void parasolid_boolean(PK_boolean_function_t operation, PK_BODY_t target, int number_of_tools, PK_BODY_t *tools);
extern void TransposePoint(HPoint *point, PK_TRANSF_t trans, bool inverse);
void TransposePoint(PK_VECTOR_t *dpoint, PK_TRANSF_t trans, bool inverse);
void TransposeInstancedPoint(PK_VECTOR_t *dpoint, bool inverse);
void TransposeInstancedPoint(HPoint *point, bool inverse);

PK_ERROR_code_t PK_BSURF_sf_free(PK_BSURF_sf_t bsurf_sf);

HC_KEY Parasolid2HoopsNurbsSurface( PK_BSURF_t bsurf );
HC_KEY ParasolidBCurve2HoopsNurbsCurve( PK_BCURVE_t bcurve, bool trim);
HC_KEY ParasolidSPCurve2HoopsNurbsCurve( PK_SPCURVE_t spcurve, 
								  double u_start_param, double u_end_param, 
								  double v_start_param, double v_end_param, bool trim );
void ParasolidSPCurve2HoopsTrimPoly(PK_SPCURVE_t sp_curve, PK_INTERVAL_t pk_intl, 
								  double u_start_param, double u_end_param, 
								  double v_start_param, double v_end_param );

void InsertTrimData( HC_KEY bsurf_key, PK_SURF_t pk_surf, PK_SURF_trim_data_t trim_data, bool use_polyline);
#endif // PARASOLID

#ifdef GRANITE
extern void granite_boolean(KIntersectionType operation, KBody_ptr target, KBodyList_ptr tools);
#endif // GRANITE


#endif	// hsutility


