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
 * $Id: OOCTCommon.h,v 1.1 2010-05-14 23:18:45 guido Exp $
 */

#ifndef OOCTCommon_H
#define OOCTCommon_H

#ifdef _MSC_VER
#define OOC_API __declspec (dllexport)
#else
#define OOC_API
#endif

#ifndef alter
#define alter
#endif // alter

#include <stdlib.h>

#include "vlist.h"
#include "vhash.h"

#ifndef INVALID_KEY
#define INVALID_KEY (-1L)
#endif

#include "HOpcodeShell.h"

#define COMMON_BUFFER_SIZE 4096

class  HPoint 
{ 
public:
	float		x;	//!< The x-coordinate of a 3-dimensional point.
	float		y;	//!< The y-coordinate of a 3-dimensional point.
	float		z;	//!< The z-coordinate of a 3-dimensional point.
	
	/*! The default constructor. */
	HPoint() : x(0), y(0), z(0) {};

	/*! This constructor accepts floats for the x, y and z coordinates.*/
	HPoint(float X, float Y, float Z=0.0f) : x(X), y(Y), z(Z) {};
	
	/*! This constructor accepts a pointer to an HPoint object. */
	HPoint(HPoint const * p) : x(p->x), y(p->y), z(p->z) {};
	
	/*! This constructor accepts an HPoint reference. */
	HPoint(HPoint const & p) : x(p.x), y(p.y), z(p.z) {};
	
	/*!  This method packs an HPoint object with coordinate values.  */
	void Set(float X, float Y, float Z=0.0f) { x=X; y=Y; z=Z; };
	
	/*!  This method packs an HPoint object with coordinate values from a given HPoint.  */
	void Set(HPoint *p) { x=p->x; y=p->y; z=p->z; };
	
	/*!  This method packs an HPoint object with coordinate values from a given HPoint.  */
	void Set(HPoint const *p) { x=p->x; y=p->y; z=p->z; };
	
	/*!  This method packs an HPoint object with coordinate values from a given HPoint that is passed by reference.  */
	void Set(HPoint &p) { x=p.x; y=p.y; z=p.z; };
	
	/*!  This method packs an HPoint object with coordinate values from a given HPoint that is passed by reference.  */
	void Set(const HPoint &p) { x=p.x; y=p.y; z=p.z; };

	/*!  This method increases/decreases the coordinate values of an existing HPoint object.  
	\param X The amount in which you want to increment or decrement the x coordinate.
	\param Y The amount in which you want to increment or decrement the y coordinate.
	\param Z The amount in which you want to increment or decrement the z coordinate.
	*/
	void Add(float X, float Y, float Z=0.0){ x+=X; y+=Y; z+=Z; };

	HPoint const operator -(const HPoint &p2) const
	{
 		return HPoint(x-p2.x, y-p2.y, z-p2.z);
	}

	HPoint const operator +(const HPoint &p2) const
	{
 		return HPoint(x+p2.x, y+p2.y, z+p2.z);
	}

	HPoint const operator *(float const rhs) const
	{
 		return HPoint(x*rhs, y*rhs, z*rhs);
	}

	HPoint const operator /(float const rhs) const
	{
 		return HPoint(x/rhs, y/rhs, z/rhs);
	}

	HPoint const & operator += (HPoint const & rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	
	HPoint const & operator -= (HPoint const & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	HPoint const & operator *= (float const rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	HPoint const & operator /= (float const rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	bool operator ==(HPoint const & rhs) const
	{
		return Equal(&rhs);
	}
	
	bool operator !=(HPoint const & rhs) const
	{
		return !Equal(&rhs);
	}


/*!\def HPOINT_EPSILON */
#define HPOINT_EPSILON (1e-5f)  //!<  HPOINT_EPSILON


	/*! This method checks if the xyz components of the point are equal.  */
	bool Equal(HPoint const *p, float epsi = HPOINT_EPSILON) const { 
		return (bool)(
			(x - p->x < epsi) && (x - p->x > -epsi) &&
			(y - p->y < epsi) && (y - p->y > -epsi) &&
			(z - p->z < epsi) && (z - p->z > -epsi));
	};

	/*!  This method checks if the xyz components of the point are equal.  */
	bool Equal(HPoint const &p, float epsi = HPOINT_EPSILON) const { 
		return Equal(&p, epsi);
	};
};



#define OBSPX 0x1
#define OBSPY 0x2
#define OBSPZ 0x4
#define OBSP_GARBAGE 0x8 /* unused but reserved */

class OOCT_KDTreeItem
{
public:
	OOCT_KDTreeItem(int partitiontype);
	OOCT_KDTreeItem *kids[4];
 	void AppendItem(void *item);
	int m_PartitionType;
	vlist_s *m_ItemList;
	bool m_bMinMaxSet;
	HPoint m_min;
	HPoint m_max;
};


class OOCT_KDTree {
public:
	OOCT_KDTree(int max_depth, HPoint min, HPoint max);
	void InsertItem(void *item, HPoint *itemmin, HPoint *itemmax, bool testrun);
	void CleanTree();
	void CleanTreeRecursive(OOCT_KDTreeItem *subtree);
	void CleanTreeRecursive2(OOCT_KDTreeItem *subtree, OOCT_KDTreeItem *parent, int num);
	void InsertItemRecursive(OOCT_KDTreeItem *subtree, void *item, HPoint min,HPoint max, HPoint *item_min, HPoint *item_max,int max_depth, int remaining_dimensions, int sparseid, bool testrun);

	HPoint				m_min;			
	HPoint				m_max;
	int					m_max_depth;		
	OOCT_KDTreeItem *		m_root;			
};
 



class OOCT_Instance
{
public:
	OOCT_Instance()
	{
		m_key = INVALID_KEY;
		m_id = -1;		
		m_FileLocation = -1;
		m_bIsLoaded = false;	
		m_timestamp = 0;

		
	}
	long m_FileLocation;
	long m_LengthOnFile;
	HC_KEY m_key;
	long m_id;
	long m_last_id;
 	HPoint m_min;
	HPoint m_max;
	bool m_bIsLoaded;
	long m_timestamp;	
};



class OOCT_Entity
{
public:
	OOCT_Entity()
	{
		m_key = INVALID_KEY;	
		m_Instance = 0;
 	}
	OOCT_Instance *m_Instance;
 	HC_KEY m_key;
	float m_diameter;
	HPoint m_center;
	long m_InstanceLocation;
	
	
};


class IdKeyPair
{
public:
	IdKeyPair()
	{
		m_key = INVALID_KEY;
		m_id = -1;
		m_last_id = -1;
		m_bIsInstance = false;
 	}
	HC_KEY m_key;
	long m_id;
	long m_last_id;
 	bool m_bIsInstance;
};


class OOCT_World {
 
public:
	OOCT_World ();
	~OOCT_World ();
	
	// sets up various variables for pre-processing and/or loading the point cloud
	void Initialize ( wchar_t const * ooct_file_in );
	void PreProcess ();
	void AssociateKey(HC_KEY key);
	IdKeyPair *GetIdKeyPair(HC_KEY key);
	void IdentifySegmentsRecursive(HC_KEY key, int level, bool firstinstance);
	void UpdateLastCountRecursive(HC_KEY key);
 	long  GetFilePosFromKDNodeID(int nodeid);

	void CreateAtomicInstance(IdKeyPair *IdKey, HPoint *min, HPoint *max);
	void CreateAtomicEntity(IdKeyPair *idKey, float matrix[16], char *color);
	void CreateAtomicEntitiesRecursive(HC_KEY key, int level);
	IdKeyPair * GetIdKeyPairFromId(long id);
	void SerializeInstances();
	OOCT_Entity * GetAtomicEntity(HC_KEY key);
 	OOCT_Instance * GetInstanceFromKey(HC_KEY  key);

	OOCT_Instance * GetInstance(long counter);

	void QuickFindLastRecursive(HC_KEY key, long &last);
	void GenerateHoopsKDTree(OOCT_KDTree *tree);
	void GenerateHoopsKDTreeRecursive(OOCT_KDTreeItem *item);
 	 void SerializeKDTree();

	void Serialize();
	void Restore();

	long m_id;
 	struct vlist_s *				m_LoadSegmentList;
	struct vlist_s *				m_LoadKDTreeNodeList;
	
	long							m_TimeStamp;
	struct vlist_s *				m_SparseList;
	int								m_ItemIDCount;
	void SerializeKDTreeRecursive(OOCT_KDTreeItem *subtree, int ItemID);
//	void ReadNodes(int startnode, int depth);


private:
 
	wchar_t *						m_ooct_file_name;
 	wchar_t * 						m_ooct_file_dir;
	size_t							m_ooct_file_dir_len;
	wchar_t *						m_node_dir_prefix;
	size_t							m_node_dir_prefix_len;

	HStreamFileToolkit *			m_stream_toolkit;
	HStreamFileToolkit *			m_stream_toolkit_readwrite;
	struct vhash_s *				m_KeyToIdKeyPairHash;
	struct vhash_s *				m_IdToIdKeyPairHash;
	struct vhash_s *				m_IdToInstanceHash;
	struct vhash_s *				m_KeyToInstanceHash;
	struct vhash_s *				m_KeyToAtomicEntityHash;
	struct vlist_s *				m_AtomicInstancesList;
	struct vlist_s *				m_AtomicEntityList;
 	long m_InstanceCount;
 	OOCT_Instance **					m_InstanceArray;
 	int								m_CurrentSerializationPosition;
	FILE *							m_InstanceFileHandle;
	FILE *							m_KDTreeFileHandle;
	FILE *							m_KDTreeFileMapHandle;
	long							m_CurrentFileLocation;
	double							m_MaxDiameter;
 	OOCT_KDTree						*m_kdtree;
	HC_KEY							m_startkey;
	int								m_NumberOfKDNodes;
	struct vhash_s *				m_KDNodeIDToFilePosHash;
	HC_KEY							m_path[256];

};






class TK_OOCT_Shell : public HTK_Shell 
{
public:
        TK_OOCT_Shell (OOCT_World *ooct_world) : HTK_Shell()
	   {
		   m_ooct_world = ooct_world;
	   }

 	TK_Status   Execute (BStreamFileToolkit & tk);
 
	OOCT_World *m_ooct_world;

};


class TK_OOCT_Shell2 : public HTK_Shell 
{
public:
        TK_OOCT_Shell2 (OOCT_World *ooct_world) : HTK_Shell()
	   {
		   m_ooct_world = ooct_world;
	   }

 	TK_Status   Execute (BStreamFileToolkit & tk);
 
	OOCT_World *m_ooct_world;

};


class TK_OOCT_Line : public HTK_Line 
{

public:

	TK_Status   Execute (BStreamFileToolkit & tk) {
		return TK_Normal;
	}
};
class TK_OOCT_Polypoint : public HTK_Polypoint
{

public:
       TK_OOCT_Polypoint (unsigned char opcode) : HTK_Polypoint (opcode) {}


	TK_Status   Execute (BStreamFileToolkit & tk) {
		return TK_Normal;
	}
};
class TK_OOCT_Ellipse : public HTK_Ellipse
{
public:
       TK_OOCT_Ellipse (unsigned char opcode) : HTK_Ellipse (opcode) {}


	TK_Status   Execute (BStreamFileToolkit & tk) {
		return TK_Normal;
	}
};


class TK_OOCT_Text : public HTK_Text
{
public:
       TK_OOCT_Text (unsigned char opcode) : HTK_Text (opcode) {}


	TK_Status   Execute (BStreamFileToolkit & tk) {
		return TK_Normal;
	}
};

class TK_OOCT_Point : public HTK_Point
{
public:
       TK_OOCT_Point (unsigned char opcode) : HTK_Point (opcode) {}


	TK_Status   Execute (BStreamFileToolkit & tk) {
		return TK_Normal;
	}
};

class TK_OOCT_Open_Segment : public HTK_Open_Segment
{
public:
        TK_OOCT_Open_Segment (OOCT_World *ooct_world) : HTK_Open_Segment()
	   {
		   m_ooct_world = ooct_world;
	   }


	TK_Status   Execute (BStreamFileToolkit & tk) {
		HTK_Open_Segment::Execute(tk);
		m_ooct_world->AssociateKey(last_key(tk));
		return TK_Normal;
	}

	OOCT_World *m_ooct_world;

};

class TK_OOCT_Close_Segment : public HTK_Close_Segment
{
public:
        TK_OOCT_Close_Segment (OOCT_World *ooct_world) : HTK_Close_Segment()
	   {
		   m_ooct_world = ooct_world;
	   }


	TK_Status   Execute (BStreamFileToolkit & tk) {
		HTK_Close_Segment::Execute(tk);
		m_ooct_world->AssociateKey(last_key(tk));
  		return TK_Normal;
	}

	OOCT_World *m_ooct_world;

};


class TK_OOCT_Open_Segment2 : public HTK_Open_Segment
{
public:
        TK_OOCT_Open_Segment2 (OOCT_World *ooct_world) : HTK_Open_Segment()
	   {
		   m_ooct_world = ooct_world;
	   }


	TK_Status   Execute (BStreamFileToolkit & tk) {
		HTK_Open_Segment::Execute(tk);
		char text[4096];
		HC_Show_Segment(last_key(tk), text);
		m_ooct_world->AssociateKey(last_key(tk));
		m_ooct_world->SerializeInstances();
		return TK_Normal;
	}

	OOCT_World *m_ooct_world;

};

class TK_OOCT_Close_Segment2 : public HTK_Close_Segment
{
public:
        TK_OOCT_Close_Segment2 (OOCT_World *ooct_world) : HTK_Close_Segment()
	   {
		   m_ooct_world = ooct_world;
	   }


	TK_Status   Execute (BStreamFileToolkit & tk) {
		HTK_Close_Segment::Execute(tk);
		char text[4096];
		HC_Show_Segment(last_key(tk), text);
 		m_ooct_world->AssociateKey(last_key(tk));
		m_ooct_world->SerializeInstances();
  		return TK_Normal;
	}

	OOCT_World *m_ooct_world;

};


#endif // OOCTCommon_H

