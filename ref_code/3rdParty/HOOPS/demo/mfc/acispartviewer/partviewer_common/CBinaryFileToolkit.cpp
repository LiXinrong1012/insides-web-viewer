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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/CBinaryFileToolkit.cpp,v 1.70 2011-01-26 23:45:17 chad Exp $
//

#include "stdafx.h"
#include <afxtempl.h>
#include <io.h>
#include <sys/stat.h>
#include "HSInclude.h"

#include "StreamingThread.h"
#include "stdafx.h"
#include "HStream.h"
#include "HOpcodeShell.h"
#include "hsolidmodel.h"
#include "CSolidHoopsView.h"
#include "CBinaryFileToolkit.h"
#include "CSolidHoopsApp.h"
#include "HUtilityLocaleString.h"


#ifdef ACIS
#include "acis_ts3d_id_attrib.h"
#include "testwire.hxx"
#endif

#ifndef nobreak
  #define nobreak   //do nothing
#endif

#define HOOPS_VERSION_VERTEX_SUPPORT 1785

// this provides some metadata about the body types used for saving/restoring map information from ASF/PSF files
enum BodyTypeInfo {
	BTI_UNKNOWN,		// we don't know what type of body/entity this is (it's mapping won't be saved out to ASF/PSF files)
	BTI_SOLID_BODY,		// either a solid or sheet body (i.e., body has faces)
	BTI_WIRE_BODY,		// wire body (i.e., body has edges)
	BTI_VERTEX_BODY		// vertex body (i.e., body is a single vertex)
};

long CModellerInfo::Compute_Geometry_Keys(long index, long max_count, HC_KEY* keys)
{
	int maxcount = m_objects[index]->GetKeyNum();
	for (int i=0;i<maxcount;i++)
		keys[i] = m_objects[index]->m_keys[i];
	return maxcount;
}

#ifdef ACIS
long CModellerInfo::Compute_Entity_Index(HC_KEY key, int eclass)
{
	long entity;
	outcome error = 0;
	int entityClass;
	long body;

	if (HC_Show_Existence_By_Key(key, "self"))
	{
 		int found = m_map.Lookup(key,(long &)entity);
		if (!found)
		{
			if (eclass == BODY_TYPE ) // || eclass == PK_CLASS_instance)
			{
				HC_KEY ancestorSegment;
				// be more forgiving if they are interested in a body pointer; 
				// in case this entity has been rendered in merge_faces mode we need
				// to be a bit tricky about obtaining this info, if and only if 
				// they are looking to get the body associated with a given shell.
				char keytype[MVO_BUFFER_SIZE];
				HC_Show_Key_Type(key, keytype);
				if (keytype[0] == 's' && keytype[1] == 'h') //|| eclass == PK_CLASS_instance)
				{
					ancestorSegment = HC_KShow_Owner_By_Key(key);
					found = m_map.Lookup(ancestorSegment,(long &)entity);
					// look to the parent and grandparent segment of this shell in the hopes of finding
					// a body segment, which will have a mapping to the body entity.
					while (!found && ancestorSegment != -1)
					{
						ancestorSegment = HC_KShow_Owner_By_Key(ancestorSegment);
						found = m_map.Lookup(ancestorSegment,(long &)entity);
					}
					if( found )
						return entity;
					else
						return 0;
				}
				else
					return 0;
			}
			else
				return 0; 
		}
	}
	else
	{
		return 0;
	}
	if ( (ENTITY_ask_class(entity, entityClass)) != true )
 		return 0;
	if( entityClass == EDGE_TYPE )
	{
		if( eclass == BODY_TYPE )
		{
			int numfaces;
			long* faces;
			error = EDGE_ask_faces(entity, &numfaces, &faces);
			if (numfaces)
				FACE_ask_body(faces[0],&body);
			else
				body=0;
			delete faces;			
			return body;	 	 
		}
		else if( eclass == EDGE_TYPE )
			return entity;
//		case PK_CLASS_ellipse:
		else if( eclass == ENTITY_TYPE )
			return entity; 	  
		else
			return 0;
	}
	else if( entityClass == FACE_TYPE )
	{
		if( eclass == BODY_TYPE )
		{
			error = FACE_ask_body(entity, &body);
			return body; 
		}
		else if( eclass == FACE_TYPE )
			return entity; 	 	 
		else
			return 0;
	}
	else if( entityClass == BODY_TYPE )
	{
		if( eclass == BODY_TYPE )
			return entity;
		else
			return 0;
	}
	else
		return 0;
}
#endif  //ACIS



bool CModellerInfo::ask_bodies(int * const nbodies, long** const body_indices)
{
	*nbodies = m_objects[0]->m_numchildren;
	if (body_indices)
	{
		*body_indices = new long[*nbodies];
		for (int i=0;i<(*nbodies);i++)
			(*body_indices)[i] = m_objects[0]->m_children[i];
	}
	return true;
}


bool CModellerInfo::BODY_ask_faces(long body_index, int * const nfaces, long** const face_indices)
{
	*nfaces = m_objects[body_index]->m_numchildren;
	if (face_indices)
	{
		*face_indices = new long[*nfaces];
		for (int i=0;i<(*nfaces);i++)
			(*face_indices)[i] = m_objects[body_index]->m_children[i];
	}
	return true;
}

bool CModellerInfo::WIRE_BODY_ask_edges ( long body_index, int * const nedges, long ** const edge_indices ) {
	*nedges = m_objects[body_index]->m_numchildren;
	if (edge_indices) {
		*edge_indices = new long[*nedges];
		for ( int i = 0 ; i < (*nedges) ; i++ )
			(*edge_indices)[i] = m_objects[body_index]->m_children[i];
	}
	return true;
}


bool CModellerInfo::FACE_ask_body(long face_index, long* const body_index)
{
	*body_index = m_objects[face_index]->m_parents[0];
 	return true;
}



bool CModellerInfo::EDGE_ask_faces(long edge_index, int * const nfaces, long ** const face_indices)
{
	*nfaces = ((CEdgeModellerObject *)m_objects[edge_index])->m_numparents;
	if (face_indices)
	{
		*face_indices = new long[*nfaces];
		for (int i=0;i<(*nfaces);i++)
			(*face_indices)[i] = m_objects[edge_index]->m_parents[i];
	}
	return true;
}

bool CModellerInfo::EDGE_ask_verts(long edge_index, int * const nvertex, long** const vertex_indices)
{
	*nvertex = m_objects[edge_index]->m_numchildren;
	if (vertex_indices)
	{
		*vertex_indices = new long[*nvertex];
		for (int i=0;i<(*nvertex);i++)
			(*vertex_indices)[i] = m_objects[edge_index]->m_children[i];
	}
	return true;
}

bool CModellerInfo::FACE_ask_edges(long face_index, int * const nedges, long** const edge_indices)
{
	*nedges = m_objects[face_index]->m_numchildren;
	if (edge_indices)
	{
		*edge_indices = new long[*nedges];
		for (int i=0;i<(*nedges);i++)
			(*edge_indices)[i] = m_objects[face_index]->m_children[i];
	}
	return true;
}


bool CModellerInfo::ENTITY_ask_class(long entity_index, KERN_CLASS_TYPEDEF& eclass)
{
	eclass = m_objects[entity_index]->AskClass();
	return true;
}


bool CModellerInfo::ENTITY_ask_identifier(long entity_index, int *ident)
{
	*ident = m_objects[entity_index]->m_identifier;
	return true;
}

 
void CModellerInfo::SetModellerObject (int pos, CModellerObject * object)  
{
    if (m_objects[pos] != 0)
        delete m_objects[pos];
    m_objects[pos] = object;
}

CModellerObject * CModellerInfo::GetModellerObject (int pos)  
{
    return( m_objects[pos]);
}


// uses standard apis to generate a temp prt file name in a temp
// direction - aka gsfCE17.prt
static void generate_temp_filename(TCHAR * retFilename)
{
	TCHAR temp_dir[_MAX_DIR];
	DWORD dir_len = GetTempPath( _MAX_DIR,  temp_dir );
	assert( dir_len != 0);	assert( dir_len <= _MAX_DIR);
	UINT res = GetTempFileName( temp_dir, _T("HOOPS"), 0, retFilename);
	assert( res != 0);
//	// change the extension from .tmp to .prt
//	int fname_len = strlen( retFilename );
//	retFilename[fname_len-3] = 'p';
//	retFilename[fname_len-2] = 'r'; 
//	retFilename[fname_len-1] = 't'; 
}

void	TK_PSUser_Data::putdata(void *data, int size)
{
	if (m_size+size>=m_buffer_size)
	{
		Resize(m_buffer_size+size+8192);
	}
	memcpy(&m_data[m_size],data,size);
	m_size+=size;
}


void TK_PSUser_Data::Reset()
{
	m_pos = 0;
    TK_User_Data::Reset();
}

void	TK_PSUser_Data::getdata(long &data)
{
	data = *((int *)(&m_data[m_pos]));	
	m_pos+=sizeof(long);
}

void	TK_PSUser_Data::getdata(char &data)
{
	data = m_data[m_pos];	
	m_pos++;
}

void	TK_PSUser_Data::getdata(void *data,int len)
{
	memcpy(data, &m_data[m_pos],len);	
	m_pos+=len;
}




#ifdef ACIS
TK_PSUser_Data::TK_PSUser_Data (HSolidModel * pHModel, CModellerInfo **mi, ENTITY_LIST& ent_list, bool psf) : TK_User_Data(), m_entityList(ent_list), m_pHModel(pHModel)
#endif //ACIS
{
	m_mi = new CModellerInfo;
	*mi = m_mi;
	m_pos = 0;
	m_mi->m_bPSF = psf;
	m_mystage = 0;
	m_psf_filesize = 0;
	m_psf_filehandle = 0;
	m_psf_file_buff = 0;
	m_psf_buff_count = 0;

}

 
TK_Status TK_PSClose_Segment::Write(BStreamFileToolkit &tk) 
{	TK_Status status = TK_Normal;

	switch( m_mystage ) {
		case 0: {
			if((status = HTK_Close_Segment::Write(tk)) != TK_Normal )
				return status;
			m_mystage++;
		} nobreak;
		case 1: {
			//segment can have lods, so make sure this one is recorded as LOD 0.
			if((status = Tag( tk, 0 )) != TK_Normal )
				return status;
			m_mystage = 0;
		} break;
	}
	return (status);
}

 

TK_Status TK_PSLine::Write(BStreamFileToolkit &tk) 
{
	TK_Status status = TK_Normal;

	switch( m_mystage ) {
		case 0: {
			if((status = HTK_Line::Write(tk)) != TK_Normal )
				return status;
			m_mystage++;
		} nobreak;
		case 1: {
			if((status = Tag( tk, -1 )) != TK_Normal )
				return status;
			m_mystage = 0;
		} break;
	}
	return (status);
}

TK_Status TK_PSPolypoint::Write(BStreamFileToolkit &tk) 
{
	TK_Status status = TK_Normal;

	switch( m_mystage ) {
		case 0: {
			if((status = HTK_Polypoint::Write(tk)) != TK_Normal )
				return status;
			m_mystage++;
		} nobreak;
		case 1: {
			if((status = Tag( tk, -1 )) != TK_Normal )
				return status;
			m_mystage = 0;
		} break;
	}
	return (status);
}

TK_Status TK_PSPoint::Write(BStreamFileToolkit &tk) 
{
	TK_Status status = TK_Normal;

	switch( m_mystage ) {
		case 0: {
			if((status = HTK_Point::Write(tk)) != TK_Normal )
				return status;
			m_mystage++;
		} nobreak;
		case 1: {
			if((status = Tag( tk, -1 )) != TK_Normal )
				return status;
			m_mystage = 0;
		} break;
	}
	return (status);
}

TK_Status TK_PSPolyPolypoint::Write(BStreamFileToolkit &tk) 
{
	TK_Status status = TK_Normal;

	switch( m_mystage ) {
		case 0: {
			if((status = HTK_PolyPolypoint::Write(tk)) != TK_Normal )
				return status;
			m_mystage++;
		} nobreak;
		case 1: {
			if((status = Tag( tk, -1 )) != TK_Normal )
				return status;
			m_mystage = 0;
		} break;
	}
	return (status);
}


TK_Status TK_PSEllipse::Write(BStreamFileToolkit &tk) 
{
	TK_Status status = TK_Normal;

	switch( m_mystage ) {
		case 0: {
			if((status = HTK_Ellipse::Write(tk)) != TK_Normal )
				return status;
			m_mystage++;
		} nobreak;
		case 1: {
			if((status = Tag( tk, -1 )) != TK_Normal )
				return status;
			m_mystage = 0;
		} break;
	}
	return (status);
}

TK_Status TK_PSCircle::Write(BStreamFileToolkit &tk) 
{
	TK_Status status = TK_Normal;

	switch( m_mystage ) {
		case 0: {
			if((status = HTK_Circle::Write(tk)) != TK_Normal )
				return status;
			m_mystage++;
		} nobreak;
		case 1: {
			if((status = Tag( tk, -1 )) != TK_Normal )
				return status;
			m_mystage = 0;
		} break;
	}
	return (status);
}

TK_Status TK_PSNURBS_Curve::Write ( BStreamFileToolkit & tk ) {
	TK_Status status = TK_Normal;

	switch (m_mystage) {
		case 0: {
			if ((status = HTK_NURBS_Curve::Write(tk)) != TK_Normal)
				return status;
			m_mystage++;
		} nobreak;

		case 1: {
			if ((status = Tag(tk, -1)) != TK_Normal)
				return status;
			m_mystage = 0;
		} break;
	}

	return status;
}


TK_Status TK_PSComment::Execute (BStreamFileToolkit & tk) 
{
	// check if this is us, if yes, we should install our 
	// user data opcode handler
    if (!strcmp (m_comment, FILE_COMMENT_ID))
	{
#ifdef ACIS
		tk.SetOpcodeHandler( TKE_Start_User_Data,new TK_PSUser_Data(m_pHModel, &m_pHModel->m_mi, m_pHModel->GetEntityList()));
#endif // ACIS
	}
	return TK_Comment::Execute(tk);
};



// chunk size to read/write modeler files embedded in hsfs. They get really huge which 
// we can't swallow whole - out of memory - Rajesh B (24-Jun-04)
#define PSF_BUFF_CHUNK_SIZE			(64*1024)	// 65K - is that good size?


TK_Status TK_PSUser_Data::Read (BStreamFileToolkit & tk) alter 
{
    TK_Status       status = TK_Normal;

    switch (m_stage) {
        case 0: {
			// get the total opcode size - which we really don't need 
            if ((status = GetData (tk, m_size)) != TK_Normal)
                return status;

            m_stage++;
        }   nobreak;
        case 1: {
			// get the topology block size
            if ((status = GetData (tk, m_size)) != TK_Normal)
                return status;
            set_data (m_size);      // allocate space

            m_stage++;
        }   nobreak;

        case 2: {
			// get the topology data
            if ((status = GetData (tk, m_data, m_size)) != TK_Normal)
                return status;
            m_stage++;
        }   nobreak;

        case 3: {
			// check if we have got the modeler file attached. It is the 5th byte from start
			if( m_data[4] )
			{
				int filesize = 0;
				if ((status = GetData (tk, filesize )) != TK_Normal)
					return status;

				m_psf_filesize = filesize;

				// create a temporary file to write the modeler file
				generate_temp_filename(m_psf_tempfilename.GetBuffer(_MAX_PATH));
				m_psf_tempfilename.ReleaseBuffer();

				// prepare to write
				m_psf_filehandle = _tfopen(m_psf_tempfilename, _T("wb"));
				if (!m_psf_filehandle)
				{
					TCHAR msg[MVO_BUFFER_SIZE];
					_stprintf(msg, _T("Failed to create a temporary modeler file - %s"), m_psf_tempfilename );
					AfxMessageBox(msg);
					return TK_Error;
				}
				m_psf_buff_count = 0;
				m_psf_file_buff = new char[PSF_BUFF_CHUNK_SIZE];

			}
            m_stage++;

		} nobreak;

		case 4: {
			if( m_data[4] )
			{
				// write the file out in chunks. As the file could get too big to read it in a 
				// single buffer
				while (m_psf_buff_count < m_psf_filesize)
				{
					int next_block = m_psf_filesize - m_psf_buff_count;
					if( next_block > PSF_BUFF_CHUNK_SIZE )
						next_block = PSF_BUFF_CHUNK_SIZE;

					if ((status = GetData (tk, m_psf_file_buff, next_block)) != TK_Normal)
						return status;
					fwrite(m_psf_file_buff, sizeof(char), next_block, m_psf_filehandle);
					m_psf_buff_count += next_block;
				}
				fclose(m_psf_filehandle);
				H_SAFE_DELETE_ARRAY(m_psf_file_buff);
			}
            m_stage++;
		} nobreak

        case 5: {
            unsigned char       stop_code;

            if ((status = GetData (tk, stop_code)) != TK_Normal)
                return status;

            if (stop_code != TKE_Stop_User_Data)    // sanity check
                return tk.Error();

            m_stage = -1;
        }   break;

        default:
            return tk.Error();
    }

    return status;
}

 
TK_Status TK_PSUser_Data::Execute ( BStreamFileToolkit & tk ) {
	long num_bodies, num_entities;
	getdata(num_entities);
 	m_mi->Init(num_entities + 1);
	getdata((char &)m_mi->m_bPSF);
	getdata(num_bodies);
 
	long counter = 0;
	long index;
	BodyTypeInfo bti = BTI_UNKNOWN;
	HC_KEY key;
	 
	CBaseModellerObject *baseobj = new CBaseModellerObject;
	m_mi->SetModellerObject(counter++, baseobj);
	int basechildnum = 0;
	baseobj->SetChildNum(num_bodies);
	
	for ( int i = 0 ; i < num_bodies ; i++ ) {
#ifdef ACIS
		if (tk.GetVersion() >= HOOPS_VERSION_VERTEX_SUPPORT) {
			bti = BTI_UNKNOWN;
			getdata(&bti, sizeof(BodyTypeInfo));
		}
#endif // ACIS

		CBodyModellerObject *bodyobj;
		int bodyparent;

#ifdef ACIS
		if (tk.GetVersion() < HOOPS_VERSION_VERTEX_SUPPORT || bti != BTI_VERTEX_BODY)
		{
#endif // ACIS

			bodyobj = new CBodyModellerObject;
			if (m_mi->m_bPSF)
				getdata(&bodyobj->m_identifier, sizeof(int));

			getdata(index);
			tk.IndexToKey(index, key);
			m_mi->m_map.SetAt(key, counter);
			bodyobj->SetKey(key);

#ifdef ACIS
		}
		else {
			bodyobj = new CAcornBodyModellerObject;
			if (m_mi->m_bPSF)
				getdata(&bodyobj->m_identifier, sizeof(int));
		}
#endif // ACIS

		bodyparent = counter;
		baseobj->m_children[basechildnum++] = counter;	
		m_mi->SetModellerObject(counter++, bodyobj);

#ifdef ACIS
		if (tk.GetVersion() >= HOOPS_VERSION_VERTEX_SUPPORT && bti == BTI_UNKNOWN)
			continue;

		if (tk.GetVersion() < HOOPS_VERSION_VERTEX_SUPPORT || bti == BTI_SOLID_BODY) 
		{
#endif // ACIS
			long num_faces;
			getdata(num_faces);
			bodyobj->SetChildNum(num_faces);
			int bodychildnum = 0;
			for ( int j = 0 ; j < num_faces ; j++ ) {
				CFaceModellerObject *faceobj = new CFaceModellerObject;
				bodyobj->m_children[bodychildnum++] = counter;	
				faceobj->SetParent(bodyparent);

				if (m_mi->m_bPSF)
					getdata(&faceobj->m_identifier, sizeof(int));
				getdata(index);

				if (index) {
					m_mi->m_bTesselatedFaces = true;			
					tk.IndexToKey(index, key);
				}
				else
					key = 0;

				m_mi->m_map.SetAt(key, counter);
				int faceparent = counter;

				m_mi->SetModellerObject(counter++, faceobj);
			
				faceobj->SetKey(key);
				long num_edges;
				getdata(num_edges);
				faceobj->SetChildNum(num_edges);
				int facechildnum = 0;
				for ( int k = 0 ; k < num_edges ; k++ ) {
					CEdgeModellerObject *edgeobj = NULL;
					char keynum;
					getdata(keynum);
					if (keynum != -1) {
						edgeobj = new CEdgeModellerObject;
						if (m_mi->m_bPSF)
							getdata(&edgeobj->m_identifier, sizeof(int));

						edgeobj->AddParent(faceparent);		

						faceobj->m_children[facechildnum++] = counter;
						m_mi->SetModellerObject(counter, edgeobj);
						edgeobj->SetKeyNum(keynum);
						for ( int l = 0 ; l < keynum ; l++ ) {
							getdata(index);

							if (index)
								tk.IndexToKey(index, key);
							else
								key = 0;
							m_mi->m_map.SetAt(key, counter);
							edgeobj->SetKey(l, key);
						}
						counter++;
					}
					else {
						long edgepointer;
						getdata(edgepointer);
						edgeobj = (CEdgeModellerObject *)m_mi->GetModellerObject(edgepointer + 1);
						edgeobj->AddParent(faceparent);
						faceobj->m_children[facechildnum++] = edgepointer + 1;
					}

#				ifdef ACIS
					if (tk.GetVersion() >= HOOPS_VERSION_VERTEX_SUPPORT) {
						long num_verts;
						getdata(num_verts);
						edgeobj->SetChildNum(num_verts);
						int edgechildnum = 0;
						for ( int vertInd = 0 ; vertInd < num_verts ; vertInd++ ) {
							index = 0;
							key = INVALID_KEY;
							CVertexModellerObject *vertobj = new CVertexModellerObject;

							if (m_mi->m_bPSF)
								getdata(&vertobj->m_identifier, sizeof(int));

							edgeobj->m_children[edgechildnum++] = counter;
							
							getdata(index);
							if (index)
								tk.IndexToKey(index, key);
							else
								key = 0;

							m_mi->m_map.SetAt(key, counter);
							vertobj->SetKey(key);
							m_mi->SetModellerObject(counter, vertobj);

							counter++;
						} // End of vertex loop
					}
#				endif // ACIS
				} // End of edge loop
			} // End of face loop
#ifdef ACIS
		}
		// at this point, it should be guaranteed tk.GetVersion() >= HOOPS_VERSION_VERTEX_SUPPORT
		else if (bti == BTI_WIRE_BODY) {
			long num_edges;
			getdata(num_edges);
			bodyobj->SetChildNum(num_edges);
			int bodychildnum = 0;
			for ( int k = 0 ; k < num_edges ; k++ ) {
				CEdgeModellerObject *edgeobj = NULL;
				char keynum;
				getdata(keynum);
				if (keynum != -1) {
					edgeobj = new CEdgeModellerObject;
					if (m_mi->m_bPSF)
						getdata(&edgeobj->m_identifier, sizeof(int));

					edgeobj->AddParent(bodyparent);		

					bodyobj->m_children[bodychildnum++] = counter;
					m_mi->SetModellerObject(counter, edgeobj);
					edgeobj->SetKeyNum(keynum);
					for ( int l = 0 ; l < keynum ; l++ ) {
						getdata(index);

						if (index)
							tk.IndexToKey(index, key);
						else
							key = 0;
						m_mi->m_map.SetAt(key, counter);
						edgeobj->SetKey(l, key);
					}
					counter++;
				}
				else {
					long edgepointer;
					getdata(edgepointer);
					edgeobj = (CEdgeModellerObject *)m_mi->GetModellerObject(edgepointer + 1);
					edgeobj->AddParent(bodyparent);
					bodyobj->m_children[bodychildnum++] = edgepointer + 1;
				}

				long num_verts;
				getdata(num_verts);
				edgeobj->SetChildNum(num_verts);
				int edgechildnum = 0;
				for ( int vertInd = 0 ; vertInd < num_verts ; vertInd++ ) {
					index = 0;
					key = INVALID_KEY;
					CVertexModellerObject *vertobj = new CVertexModellerObject;

					if (m_mi->m_bPSF)
						getdata(&vertobj->m_identifier, sizeof(int));

					edgeobj->m_children[edgechildnum++] = counter;

					getdata(index);
					if (index)
						tk.IndexToKey(index, key);
					else
						key = 0;

					m_mi->m_map.SetAt(key, counter);
					vertobj->SetKey(key);
					m_mi->SetModellerObject(counter, vertobj);

					counter++;
				} // End of vertex loop
			} // End of edge loop
		}
		else if (bti == BTI_VERTEX_BODY) {
			CAcornBodyModellerObject *acorn = static_cast<CAcornBodyModellerObject *>(bodyobj);

			int num_keys;
			getdata(&num_keys, sizeof(int));

			acorn->SetKeyNum(num_keys);

			for ( int j = 0 ; j < num_keys ; j++ ) {
				index = 0;
				key = INVALID_KEY;

				getdata(index);
				tk.IndexToKey(index, key);
				acorn->SetKey(j, key);
			}
		}
		else {
			// we should never hit this
			assert(0);
		}
#endif // ACIS
	} // End of body loop

	TK_Status status = TK_Normal;
	
	if (m_mi->m_bPSF)
		status = ExecutePS(tk);

	if (status == TK_Normal)
		m_mi->m_bIsValid = true;

	return status;       // we don't do anything with it by default
}


 

#ifdef ACIS
IdEntityHashStatus TK_PSUser_Data::build_id_entity_map ( ENTITY_LIST & elist ) {
	IdEntityHashStatus retval = ID_ENT_HASH_OK;
	
	elist.init();
	ENTITY *e;

	for ( e = elist.first() ; e != 0 ; e = elist.next() ) {
		ATTRIB_T3D_ID *t3d_id = static_cast<ATTRIB_T3D_ID *>(find_attrib(e, ATTRIB_T3D_TYPE, ATTRIB_T3D_ID_TYPE));
		if (t3d_id) {
			// this entity has a TS3D attribute -- check to see if it's in the hash
			ENTITY *lookup;
			if (m_idEntityHash.LookupItem(t3d_id->get_ID(), &lookup) == VHASH_STATUS_SUCCESS) {
				// ID already exists in the hash, so make sure it's unique
				if (lookup != e) {
					// two different entities have the same ID
					retval = ID_ENT_HASH_CONFLICTING;
					break;
				}
			}
			else {
				// ID is not in the hash, so add it
				m_idEntityHash.InsertItem(t3d_id->get_ID(), e);
			}
		}
		else {
			// this entity doesn't have a TS3D attribute
			retval = ID_ENT_HASH_MISSING;
			break;
		}
	}

	return retval;
}

bool TK_PSUser_Data::has_t3d_attribute ( ENTITY * entity, ATTRIB_T3D_ID *& ts3d_id ) {
	if (entity && (ts3d_id = static_cast<ATTRIB_T3D_ID *>(find_attrib(entity, ATTRIB_T3D_TYPE, ATTRIB_T3D_ID_TYPE))))
		return true;
	else
		return false;
}

void display_error_message ( IdEntityHashStatus id_ent_hash_status, bool read = true ) {
	wchar_t error_message[8192];

	wcscpy(error_message, L"");

	switch (id_ent_hash_status) {
		case ID_ENT_HASH_CONFLICTING: {
			wcscat(error_message, L"Two or more entities in the ACIS data use the same identifier.");
		} break;

		case ID_ENT_HASH_MISSING: {
			wcscat(error_message, L"One or more entities in the ACIS data do not have an identifier.");
		} break;

		default: {
			wcscat(error_message, L"Unknown problem arose mapping identifiers to entities in ACIS data.");
		}
	}

	if (read)
		wcscat(error_message, L"\n\nIncomplete ASF written out -- Contains no ACIS modeller data.");
	else
		wcscat(error_message, L"\n\nInvalid ASF file -- Part Viewer behavior (e.g., selection, render modes, etc.) may be incorrect.");

	MessageBox(0, error_message, L"ERROR", MB_OK | MB_ICONERROR);
}

TK_Status TK_PSUser_Data::ExecutePS ( BStreamFileToolkit & tk ) {
	// we should already have a temporary file written out in the Read function
	// read this file using ACIS api and populate entity list
	FILE *fp;
	ENTITY *entity = 0;
	outcome o;
	fp = _tfopen(m_psf_tempfilename, _T("rb"));
	if (!fp) {
		AfxMessageBox(_T("Failed to read ACIS data. The data may be corrupt"));
		return TK_Error;
	}

	// NOTE: The default behavior of this option in ACIS R18 has changed from 'TRUE' to 'FALSE'. 
	// We need to have it true.
	restore_tags.set(TRUE);
	DELTA_STATE *ds;
	o = api_note_state(ds);
	CHECK_OUTCOME(o);
	bool has_history = false;

	HISTORY_STREAM_LIST hslist;
	DELTA_STATE_LIST dslist;
	o = api_restore_entity_list_with_history(fp, FALSE, m_entityList, hslist, dslist);
	CHECK_OUTCOME(o);
	if (hslist.iteration_count()) {
		has_history = true;
		m_pHModel->SetHistoryStream(hslist[0]);
		o = api_note_state(ds);
		CHECK_OUTCOME(o);
	}

	if (m_entityList.iteration_count() < 1) {
		AfxMessageBox(_T("No ACIS entities found in the ACIS data"));
		return TK_Error;
	}
	fclose(fp);
	// get rid of temp file
	assert(_tunlink(m_psf_tempfilename) != -1);

	// for each body, face and edge, set the bridge associativity
	m_entityList.init();
	ENTITY_LIST body_elist = m_entityList;
	body_elist.init();
	long *bodies;
	int num_bodies;
	m_mi->ask_bodies(&num_bodies, &bodies);
	for ( int i = 0 ; i < num_bodies ; i++ ) {
		int body_id;

		m_mi->ENTITY_ask_identifier(bodies[i], &body_id);

		ENTITY *body;
		if (has_history) {
			outcome o = api_get_entity_from_id(body_id, body, NULL);
			check_outcome(o);
		}
		else {
			if (m_idEntityHash.LookupItem(body_id, &body) == VHASH_STATUS_FAILED) {
				IdEntityHashStatus id_ent_hash_status = build_id_entity_map(body_elist);
				if (id_ent_hash_status == ID_ENT_HASH_OK) {
					// the map was built without problems
					if (m_idEntityHash.LookupItem(body_id, &body) == VHASH_STATUS_FAILED) {
						// we still don't have an entity associated with this ID -- something is wrong
						return TK_Error;
					}
				}
				else {
					// problem building the map
					display_error_message(id_ent_hash_status, false);

					return TK_Error;
				}
			}
		}

		if (is_BODY(body) && (tk.GetVersion() < HOOPS_VERSION_VERTEX_SUPPORT || is_solid_body(body))) {
			HC_KEY body_key;
			int num_keys = m_mi->Compute_Geometry_Keys(bodies[i], 1, &body_key);
			if (num_keys <= 0)
				continue;

			HA_Associate_Key_To_Entity(body, body_key);

			long *faces;
			int num_faces;
			m_mi->BODY_ask_faces(bodies[i], &num_faces, &faces);

			for ( int j = 0 ; j < num_faces ; j++ ) {
				int face_id;
				m_mi->ENTITY_ask_identifier(faces[j], &face_id);
				ENTITY * face;
				if (has_history) {
					outcome o = api_get_entity_from_id(face_id, face, NULL);
					check_outcome(o);
				}
				else {
					if (m_idEntityHash.LookupItem(face_id, &face) == VHASH_STATUS_FAILED) {
						ENTITY_LIST face_list;
						o = api_get_faces(body, face_list);
						check_outcome(o);

						IdEntityHashStatus id_ent_hash_status = build_id_entity_map(face_list);
						if (id_ent_hash_status == ID_ENT_HASH_OK) {
							// the map was built without problems
							if (m_idEntityHash.LookupItem(face_id, &face) == VHASH_STATUS_FAILED) {
								// we still don't have an entity associated with this ID -- something is wrong
								return TK_Error;
							}
						}
						else {
							// problem building the map
							display_error_message(id_ent_hash_status, false);

							return TK_Error;
						}
					}
				}

				HC_KEY keys[1000];
				int num_keys = m_mi->Compute_Geometry_Keys(faces[j], 1000, keys);
				for ( int knum = 0 ; knum < num_keys ; knum++ )
					HA_Associate_Key_To_Entity(face, keys[knum]);
				
				long *edges;
				int num_edges;
				m_mi->FACE_ask_edges(faces[j], &num_edges, &edges);
				for ( int k = 0 ; k < num_edges ; k++ ) {
					int edge_id;
					m_mi->ENTITY_ask_identifier(edges[k], &edge_id);
					ENTITY * edge;
					if (has_history) {
						outcome o = api_get_entity_from_id(edge_id, edge, NULL);
						check_outcome(o);
					}
					else {
						if (m_idEntityHash.LookupItem(edge_id, &edge) == VHASH_STATUS_FAILED) {
							ENTITY_LIST edge_list;
							o = api_get_edges(face, edge_list);
							check_outcome(o);

							IdEntityHashStatus id_ent_hash_status = build_id_entity_map(edge_list);
							if (id_ent_hash_status == ID_ENT_HASH_OK) {
								// the map was built without problems
								if (m_idEntityHash.LookupItem(edge_id, &edge) == VHASH_STATUS_FAILED) {
									// we still don't have an entity associated with this ID -- something is wrong
									return TK_Error;
								}
							}
							else {
								// problem building the map
								display_error_message(id_ent_hash_status, false);

								return TK_Error;
							}
						}
					}

					HC_KEY keys[1000];
					int num_keys = m_mi->Compute_Geometry_Keys(edges[k], 1000, keys);
					for ( int knum = 0 ; knum < num_keys ; knum++ )
						HA_Associate_Key_To_Entity(edge, keys[knum]);

					long *verts;
					int numverts;
					m_mi->EDGE_ask_verts(edges[k], &numverts, &verts);
					for ( int vertInd = 0 ; vertInd < numverts ; vertInd++ ) {
						int vert_id;
						m_mi->ENTITY_ask_identifier(verts[vertInd], &vert_id);
						ENTITY *vertex;
						if (has_history) {
							outcome o = api_get_entity_from_id(vert_id, vertex, NULL);
							check_outcome(o);
						}
						else {
							if (m_idEntityHash.LookupItem(vert_id, &vertex) == VHASH_STATUS_FAILED) {
								ENTITY_LIST vert_list;
								o = api_get_vertices(edge, vert_list);
								check_outcome(o);

								IdEntityHashStatus id_ent_hash_status = build_id_entity_map(vert_list);
								if (id_ent_hash_status == ID_ENT_HASH_OK) {
									// the map was built without problems
									if (m_idEntityHash.LookupItem(vert_id, &vertex) == VHASH_STATUS_FAILED) {
										// we still don't have an entity associated with this ID -- something is wrong
										return TK_Error;
									}
								}
								else {
									// problem building the map
									display_error_message(id_ent_hash_status, false);

									return TK_Error;
								}
							}
						}

						HC_KEY vert_key = INVALID_KEY;
						int numkeys = m_mi->Compute_Geometry_Keys(verts[vertInd], 1, &vert_key);
						if (numkeys <= 0)
							continue;
						HA_Associate_Key_To_Entity(vertex, vert_key);

					}
					delete verts;
				}
				delete edges;
			}
			delete faces;
		}
		else if (is_BODY(body) && tk.GetVersion() >= HOOPS_VERSION_VERTEX_SUPPORT && is_wire_body(body)) {
			HC_KEY body_key;
			int num_keys = m_mi->Compute_Geometry_Keys(bodies[i], 1, &body_key);
			if (num_keys <= 0)
				continue;

			HA_Associate_Key_To_Entity(body, body_key);

			long *edges;
			int num_edges;

			m_mi->WIRE_BODY_ask_edges(bodies[i], &num_edges, &edges);

			for ( int j = 0 ; j < num_edges ; j++ ) {
				int edge_id;
				m_mi->ENTITY_ask_identifier(edges[j], &edge_id);
				ENTITY *edge;

				if (m_idEntityHash.LookupItem(edge_id, &edge) == VHASH_STATUS_FAILED) {
					ENTITY_LIST edge_list;
					o = api_get_edges(body, edge_list);
					check_outcome(o);

					IdEntityHashStatus id_ent_hash_status = build_id_entity_map(edge_list);
					if (id_ent_hash_status == ID_ENT_HASH_OK) {
						// the map was built without problems
						if (m_idEntityHash.LookupItem(edge_id, &edge) == VHASH_STATUS_FAILED) {
							// we still don't have an entity associated with this ID -- something is wrong
							return TK_Error;
						}
					}
					else {
						// problem building the map
						display_error_message(id_ent_hash_status, false);

						return TK_Error;
					}
				}

				HC_KEY keys[1000];
				int num_keys = m_mi->Compute_Geometry_Keys(edges[j], 1000, keys);
				for ( int knum = 0 ; knum < num_keys ; knum++ )
					HA_Associate_Key_To_Entity(edge, keys[knum]);

				long *verts;
				int num_verts;
				m_mi->EDGE_ask_verts(edges[j], &num_verts, &verts);
				for ( int k = 0 ; k < num_verts ; k++ ) {
					int vert_id;
					m_mi->ENTITY_ask_identifier(verts[k], &vert_id);
					ENTITY *vertex;
	
					if (m_idEntityHash.LookupItem(vert_id, &vertex) == VHASH_STATUS_FAILED) {
						ENTITY_LIST vert_list;
						o = api_get_vertices(edge, vert_list);
						check_outcome(o);

						IdEntityHashStatus id_ent_hash_status = build_id_entity_map(vert_list);
						if (id_ent_hash_status == ID_ENT_HASH_OK) {
							// the map was built without problems
							if (m_idEntityHash.LookupItem(vert_id, &vertex) == VHASH_STATUS_FAILED) {
								// we still don't have an entity associated with this ID -- something is wrong
								return TK_Error;
							}
						}
						else {
							// problem building the map
							display_error_message(id_ent_hash_status, false);

							return TK_Error;
						}
					}


					HC_KEY vert_key = INVALID_KEY;
					int num_keys = m_mi->Compute_Geometry_Keys(verts[k], 1, &vert_key);
					if (num_keys <= 0)
						continue;
					HA_Associate_Key_To_Entity(vertex, vert_key);
				}
				delete verts;
			}
			delete edges;
		}
		else if (is_VERTEX(body) && tk.GetVersion() >= HOOPS_VERSION_VERTEX_SUPPORT) {
			// free vertex
			HC_KEY vertex_keys[1000];
			int num_keys = m_mi->Compute_Geometry_Keys(bodies[i], 1000, vertex_keys);
			assert(num_keys < 1000);

			if (num_keys <= 0)
				continue;

			for ( int j = 0 ; j < num_keys ; j++ ) {
				HA_Associate_Key_To_Entity(body, vertex_keys[j]);
			}
		}
		else {
			// mappings for these entities may or may not work correctly (i.e., those items that aren't solid, sheet, wire or vertex bodies).
		}
	}
	delete bodies;

	return TK_Normal;						
}
#endif  //ACIS




 
TK_Status   TK_PSUser_Data::Write (BStreamFileToolkit & tk)
{
    TK_Status       status = TK_Normal;
 
    switch (m_stage) {
        case 0: {
			// user data coming
            if ((status = PutOpcode (tk, 0)) != TK_Normal)
                return status;
            m_stage++;
        }   nobreak;

        case 1: {
			// do we need to write modeler file as well? Yes, then get going
			if (m_mi->m_bPSF)
				InterpretPS(tk);
            m_stage++;
        }   nobreak;


        case 2: {
			// write total opcode size which really two blocks
			// block 1 is topology information plus it's size
			// block 2 is modeler file (if required) it's size
			long size = m_size + sizeof(int);
			if( m_psf_filesize )
				size += m_psf_filesize + sizeof(int);
            if ((status = PutData (tk, size)) != TK_Normal)
                return status;
            m_progress = 0;
            m_stage++;
        }   nobreak;

        case 3: {
			// write out the size of first block which is topology info
            if ((status = PutData (tk, m_size)) != TK_Normal)
                return status;
            m_stage++;
        }   nobreak;

        case 4: {
			// write out the topology info itself
            if ((status = PutData (tk, m_data, m_size)) != TK_Normal)
                return status;
            m_stage++;
        }   nobreak;

		case 5: {
			if( m_psf_filesize ) {
				// write out the size of second block which is modeler file
				if ((status = PutData (tk, m_psf_filesize)) != TK_Normal)
					return status;

				// prepare to read the temporary file
				m_psf_filehandle = _tfopen(m_psf_tempfilename, _T("rb"));
				if( !m_psf_filehandle )
					return tk.Error("Unable to open temporary modeler file");

				m_psf_file_buff = new char[PSF_BUFF_CHUNK_SIZE];
				m_psf_buff_count = 0;
			}
			m_stage++;
		}   nobreak;
		case 6: {
			if( m_psf_filesize ) {
				// read it in chunks - we have seen upto 200MB monster modeler files 
				// we can't swallow it in one bite at all - Rajesh B (22-Jun-04)
				if(m_psf_buff_count)
				{
					// we reached eof but were unable to PutData last time.
					if ((status = PutData (tk, m_psf_file_buff, m_psf_buff_count)) != TK_Normal)
						return status;

					m_psf_buff_count = 0;
				}

				// read file in chunsk and dump it
				while( !feof( m_psf_filehandle ) )
				{
					if(!m_psf_buff_count)
					{
						m_psf_buff_count = fread( m_psf_file_buff, sizeof( char ), PSF_BUFF_CHUNK_SIZE, m_psf_filehandle);
						if(ferror( m_psf_filehandle ) != 0)
							return tk.Error("Failed to read temporary modeler file");
					}

					if ((status = PutData (tk, m_psf_file_buff, m_psf_buff_count)) != TK_Normal)
						return status;

					m_psf_buff_count = 0;
				}
				
				fclose( m_psf_filehandle );
				H_SAFE_DELETE_ARRAY(m_psf_file_buff);

				// get rid of the temporary file
				int iRes = _tunlink( m_psf_tempfilename );				assert( iRes != -1 );
			}
			m_stage++;
		}   nobreak;


        case 7: {
			// huf! done with that....
            if ((status = PutData (tk, (unsigned char)TKE_Stop_User_Data)) != TK_Normal)
                return status;
 
            m_stage = -1;
        }   break;

        default:
            return tk.Error();
    }

    return status;
}





#ifdef ACIS
IdEntityHashStatus TK_PSUser_Data::check_id_validity ( ENTITY * e ) {
	IdEntityHashStatus retval = ID_ENT_HASH_OK;
	int id;
	ATTRIB_T3D_ID *ts3d_id;
	bool need_to_create_attrib = false;

	if (has_t3d_attribute(e, ts3d_id)) {
		// entity already has a TS3D ID attribute - make sure it is unique
		id = ts3d_id->get_ID();
	}
	else {
		// we need to add a TS3D ID attribute (if possible)

		// NOTE: The ACIS function used will not necessarily give us a unique identifier
		//   If it does, we proceed with writing out the stream file,
		//   If not, we abort.
		//
		//   Customers will need to implement a more robust ID generation approach to handle this situation
		outcome o = api_get_entity_id(e, id);
		check_outcome(o);
		need_to_create_attrib = true;
	}

	ENTITY *f;
	if (m_idEntityHash.LookupItem(id, &f) == VHASH_STATUS_FAILED) {
		m_idEntityHash.InsertItem(id, e);

		if (need_to_create_attrib) {
			ACIS_NEW ATTRIB_T3D_ID(e, id);
		}
	}
	else if (e != f) {
		// two or more entities with the same ID
		retval = ID_ENT_HASH_CONFLICTING;
	}

	return retval;
}

TK_Status TK_PSUser_Data::Interpret ( BStreamFileToolkit & tk, HC_KEY dummy, int lod ) {
	outcome o;
	int num_bodies, num_faces, num_edges, num_vertices;
	int index = -1;
	HC_KEY key = INVALID_KEY;
	TK_Status tk_stat = TK_Normal;
	ENTITY_LIST bodies = m_entityList;
	num_bodies = bodies.iteration_count();
	m_size = 0;								
	int counter = 0;
	putdata(&counter, sizeof(long));						//leave room for number of entities
	putdata(&m_mi->m_bPSF, sizeof(m_mi->m_bPSF));
	putdata(&num_bodies, sizeof(long));					//store:number of bodies
	
	ENTITY *body;
	bodies.init();
	for ( int i = 0 ; i < num_bodies ; i++ ) {
		body = bodies.next();
	
		if (is_BODY(body)) {
			BodyTypeInfo bti = BTI_UNKNOWN;
			if (tk.GetTargetVersion() >= HOOPS_VERSION_VERTEX_SUPPORT) {
				if (is_solid_body(body))
					bti = BTI_SOLID_BODY;
				else if (is_wire_body(body))
					bti = BTI_WIRE_BODY;

				putdata(&bti, sizeof(BodyTypeInfo));
			}

			if (HA_Compute_Geometry_Keys(body, 1, &key, "bodies")) {
				if (key >= 0) {
					HC_KEY orig_key_no = key;
					key = HC_KRenumber_Key(key, -1, "global");
					tk_stat = tk.KeyToIndex(key, index);
					assert(tk_stat == TK_Normal);
					HC_Renumber_Key(key, orig_key_no, "global");
				}
				else {
					tk_stat = tk.KeyToIndex(key, index);
					assert(tk_stat == TK_Normal);
				}
			}
			else
				index = 0;
			
			if (m_mi->m_bPSF) {
				IdEntityHashStatus id_ent_hash_status = check_id_validity(body);
				if (id_ent_hash_status != ID_ENT_HASH_OK) {
					display_error_message(id_ent_hash_status);

					return TK_Error;
				}

				ATTRIB_T3D_ID *ts3d_id;
				if (!has_t3d_attribute(body, ts3d_id)) {
					// entity should have a TS3D ID attribute at this point -- something has gone wrong
					return TK_Error;
				}

				int id = ts3d_id->get_ID();
				putdata(&id, sizeof(int));					//store:identifier number if PSF file
			}
			putdata(&index, sizeof(long));					//store:index to HOOPS entity for body
			index = 0;

			counter++; // we added an entity for a body

			if (tk.GetTargetVersion() >= HOOPS_VERSION_VERTEX_SUPPORT && bti == BTI_UNKNOWN)
				continue;

			if (tk.GetTargetVersion() < HOOPS_VERSION_VERTEX_SUPPORT || bti == BTI_SOLID_BODY) {
				ENTITY_LIST faces;
				o = api_get_faces(body, faces);
				CHECK_OUTCOME(o);
				num_faces = faces.iteration_count();
				putdata(&num_faces, sizeof(long));				//store:number of faces in body
				faces.init();
				ENTITY *face = faces.first();
				for ( int j = 0 ; j < num_faces ; j++ ) {
					if (HA_Compute_Geometry_Keys(face, 1, &key, "faces")) {
						if (key >= 0) {
							HC_KEY orig_key_no = key;
							key = HC_KRenumber_Key(key, -1, "global");
							tk_stat = tk.KeyToIndex(key, index);
							assert(tk_stat == TK_Normal);
							HC_Renumber_Key(key, orig_key_no, "global");
						}
						else {
							tk_stat = tk.KeyToIndex(key, index);
							assert(tk_stat == TK_Normal);
						}
					}
					else
						index = 0;

					if (m_mi->m_bPSF) {
						IdEntityHashStatus id_ent_hash_status = check_id_validity(face);
						if (id_ent_hash_status != ID_ENT_HASH_OK) {
							display_error_message(id_ent_hash_status);

							return TK_Error;
						}

						ATTRIB_T3D_ID *ts3d_id;
						if (!has_t3d_attribute(face, ts3d_id)) {
							// entity should have a TS3D ID attribute at this point -- something has gone wrong
							return TK_Error;
						}

						int id = ts3d_id->get_ID();
						putdata(&id, sizeof(int));					//store:identifier number if PSF file
					}
					
					putdata(&index, sizeof(long));					//store:index to HOOPS entity for face			
					index = 0;
					
					counter++; // we added an entity for a face

					ENTITY_LIST	edges;
					o = api_get_edges(face, edges);
					num_edges = edges.iteration_count();
					putdata(&num_edges, sizeof(long));
					edges.init();
					ENTITY *edge = edges.first();
					for ( int k = 0 ; k < num_edges ; k++ ) {
						HC_KEY keys[128];
						char num_keys = (char)HA_Compute_Geometry_Keys(edge, 128, keys, "edges");					
						putdata(&num_keys, sizeof(char));
						if (m_mi->m_bPSF) {
							IdEntityHashStatus id_ent_hash_status = check_id_validity(edge);
							if (id_ent_hash_status != ID_ENT_HASH_OK) {
								display_error_message(id_ent_hash_status);

								return TK_Error;
							}

							ATTRIB_T3D_ID *ts3d_id;
							if (!has_t3d_attribute(edge, ts3d_id)) {
								// entity should have a TS3D ID attribute at this point -- something has gone wrong
								return TK_Error;
							}

							int id = ts3d_id->get_ID();
							putdata(&id, sizeof(int));					//store:identifier number if PSF file
						}
						
						for ( int l = 0 ; l < num_keys ; l++ ) {
							if (keys[l] >= 0) {
								HC_KEY orig_key_no = keys[l];
								keys[l] = HC_KRenumber_Key(keys[l], -1, "global");
								if ((tk_stat = tk.KeyToIndex(keys[l], index)) != TK_Normal) {
									assert(tk_stat == TK_Normal);
									index = 0;
								}
								HC_Renumber_Key(keys[l], orig_key_no, "global");
							}
							else {
								if ((tk_stat = tk.KeyToIndex(keys[l], index)) != TK_Normal) {
									assert(tk_stat == TK_Normal);
									index = 0;
								}
							}
							
							putdata(&index, sizeof(long));
							index = 0;
						}
						
						counter++; // we added an entity for an edge

						ENTITY_LIST	vertices;
						o = api_get_vertices(edge, vertices);
						num_vertices = vertices.iteration_count();
						putdata(&num_vertices, sizeof(long));
						vertices.init();
						ENTITY *vertex = vertices.first();

						for ( int vertInd = 0 ; vertInd < num_vertices ; vertInd++ ) {
							index = 0;
							key = INVALID_KEY;

							if (HA_Compute_Geometry_Keys(vertex, 1, &key, "vertices")) {
								if (key >= 0) {
									HC_KEY orig_key_no = key;
									key = HC_KRenumber_Key(key, -1, "global");
									tk_stat = tk.KeyToIndex(key, index);
									assert(tk_stat == TK_Normal);
									HC_Renumber_Key(key, orig_key_no, "global");
								}
								else {
									tk_stat = tk.KeyToIndex(key, index);
									assert(tk_stat == TK_Normal);
								}
							}
							else
								index = 0;

							if (m_mi->m_bPSF) {
								IdEntityHashStatus id_ent_hash_status = check_id_validity(vertex);
								if (id_ent_hash_status != ID_ENT_HASH_OK) {
									display_error_message(id_ent_hash_status);

									return TK_Error;
								}

								ATTRIB_T3D_ID *ts3d_id;
								if (!has_t3d_attribute(vertex, ts3d_id)) {
									// entity should have a TS3D ID attribute at this point -- something has gone wrong
									return TK_Error;
								}

								int id = ts3d_id->get_ID();
								putdata(&id, sizeof(int));					//store:identifier number if PSF file
							}
							putdata(&index, sizeof(long)); //Put the "index" of Vertex
							index = 0;

							counter++; // we added an entity for a vertex

							vertex = vertices.next();
						} // End of vertex loop
						edge = edges.next();
					} // End of edge loop
					face = faces.next();
				} // End of face loop
			}
			else if (bti == BTI_WIRE_BODY) {
				ENTITY_LIST	edges;
				o = api_get_edges(body, edges);
				num_edges = edges.iteration_count();
				putdata(&num_edges, sizeof(long));
				edges.init();
				ENTITY *edge = edges.first();
				for ( int k = 0 ; k < num_edges ; k++ ) {
					HC_KEY keys[128];
					char num_keys = (char)HA_Compute_Geometry_Keys(edge, 128, keys, "edges");					
					putdata(&num_keys, sizeof(char));
					if (m_mi->m_bPSF) {
						IdEntityHashStatus id_ent_hash_status = check_id_validity(edge);
						if (id_ent_hash_status != ID_ENT_HASH_OK) {
							display_error_message(id_ent_hash_status);

							return TK_Error;
						}

						ATTRIB_T3D_ID *ts3d_id;
						if (!has_t3d_attribute(edge, ts3d_id)) {
							// entity should have a TS3D ID attribute at this point -- something has gone wrong
							return TK_Error;
						}

						int id = ts3d_id->get_ID();
						putdata(&id, sizeof(int));					//store:identifier number if PSF file
					}

					for ( int l = 0 ; l < num_keys ; l++ ) {
						if (keys[l] >= 0) {
							HC_KEY orig_key_no = keys[l];
							keys[l] = HC_KRenumber_Key(keys[l], -1, "global");
							if ((tk_stat = tk.KeyToIndex(keys[l], index)) != TK_Normal) {
								assert(tk_stat == TK_Normal);
								index = 0;
							}
							HC_Renumber_Key(keys[l], orig_key_no, "global");
						}
						else {
							if ((tk_stat = tk.KeyToIndex(keys[l], index)) != TK_Normal) {
								assert(tk_stat == TK_Normal);
								index = 0;
							}
						}

						putdata(&index, sizeof(long));
						index = 0;
					}

					counter++; // we added an entity for an edge

					ENTITY_LIST	vertices;
					o = api_get_vertices(edge, vertices);
					num_vertices = vertices.iteration_count();
					putdata(&num_vertices, sizeof(long));
					vertices.init();
					ENTITY *vertex = vertices.first();

					for ( int vertInd = 0 ; vertInd < num_vertices ; vertInd++ ) {
						index = 0;
						key = INVALID_KEY;

						if (HA_Compute_Geometry_Keys(vertex, 1, &key, "vertices")) {
							if (key >= 0) {
								HC_KEY orig_key_no = key;
								key = HC_KRenumber_Key(key, -1, "global");
								tk_stat = tk.KeyToIndex(key, index);
								assert(tk_stat == TK_Normal);
								HC_Renumber_Key(key, orig_key_no, "global");
							}
							else {
								tk_stat = tk.KeyToIndex(key, index);
								assert(tk_stat == TK_Normal);
							}
						}
						else
							index = 0;

						if (m_mi->m_bPSF) {
							IdEntityHashStatus id_ent_hash_status = check_id_validity(vertex);
							if (id_ent_hash_status != ID_ENT_HASH_OK) {
								display_error_message(id_ent_hash_status);

								return TK_Error;
							}

							ATTRIB_T3D_ID *ts3d_id;
							if (!has_t3d_attribute(vertex, ts3d_id)) {
								// entity should have a TS3D ID attribute at this point -- something has gone wrong
								return TK_Error;
							}

							int id = ts3d_id->get_ID();
							putdata(&id, sizeof(int));					//store:identifier number if PSF file
						}
						putdata(&index, sizeof(long)); //Put the "index" of Vertex
						index = 0;

						counter++; // we added an entity for a vertex

						vertex = vertices.next();
					} // End of vertex loop
					edge = edges.next();
				} // End of edge loop
			}
			else {
				// we should never hit this
				assert(0);
			}
		}
		else if (is_VERTEX(body)) {
			BodyTypeInfo bti = BTI_VERTEX_BODY;
			putdata(&bti, sizeof(BodyTypeInfo));

			if (m_mi->m_bPSF) {
				IdEntityHashStatus id_ent_hash_status = check_id_validity(body);
				if (id_ent_hash_status != ID_ENT_HASH_OK) {
					display_error_message(id_ent_hash_status);

					return TK_Error;
				}

				ATTRIB_T3D_ID *ts3d_id;
				if (!has_t3d_attribute(body, ts3d_id)) {
					// entity should have a TS3D ID attribute at this point -- something has gone wrong
					return TK_Error;
				}

				int id = ts3d_id->get_ID();
				putdata(&id, sizeof(int));					//store:identifier number if PSF file
			}

			HC_KEY keys[1000];
			int num_keys = (int)HA_Compute_Geometry_Keys(body, 1000, keys, "vertices");

			assert(num_keys < 1000);
			
			putdata(&num_keys, sizeof(int));

			for ( int j = 0 ; j < num_keys ; j++ ) {
				index = 0;

				if (keys[j] >= 0) {
					HC_KEY orig_key_no = keys[j];
					keys[j] = HC_KRenumber_Key(keys[j], -1, "global");
					if ((tk_stat = tk.KeyToIndex(keys[j], index)) != TK_Normal) {
						assert(tk_stat == TK_Normal);
						index = 0;
					}
					HC_Renumber_Key(keys[j], orig_key_no, "global");
				}
				else {
					if ((tk_stat = tk.KeyToIndex(keys[j], index)) != TK_Normal) {
						assert(tk_stat == TK_Normal);
						index = 0;
					}
				}

				putdata(&index, sizeof(long));
			}

			counter++; // we added an entity for a vertex
		}
		else {			
			BodyTypeInfo bti = BTI_UNKNOWN;
			putdata(&bti, sizeof(BodyTypeInfo));

			if (m_mi->m_bPSF) {
				IdEntityHashStatus id_ent_hash_status = check_id_validity(body);
				if (id_ent_hash_status != ID_ENT_HASH_OK) {
					display_error_message(id_ent_hash_status);

					return TK_Error;
				}

				ATTRIB_T3D_ID *ts3d_id;
				if (!has_t3d_attribute(body, ts3d_id)) {
					// entity should have a TS3D ID attribute at this point -- something has gone wrong
					return TK_Error;
				}

				int id = ts3d_id->get_ID();
				putdata(&id, sizeof(int));					//store:identifier number if PSF file
			}

			index = 0;
			key = INVALID_KEY;

			if (HA_Compute_Geometry_Keys(body, 1, &key)) {
				if (key >= 0) {
					HC_KEY orig_key_no = key;
					key = HC_KRenumber_Key(key, -1, "global");
					tk_stat = tk.KeyToIndex(key, index);
					assert(tk_stat == TK_Normal);
					HC_Renumber_Key(key, orig_key_no, "global");
				}
				else {
					tk_stat = tk.KeyToIndex(key, index);
					assert(tk_stat == TK_Normal);
				}
			}
			else
				index = 0;

			putdata(&index, sizeof(long));
			index = 0;

			counter++; // we added an entity for a this unhandled type
		}
	}
	
	// rewrite the counter at the beginning where we left the place holder
	int temp = m_size;
	m_size = 0;
	putdata(&counter, sizeof(long));
	m_size = temp;
	
	return TK_Normal;
}

TK_Status   TK_PSUser_Data::InterpretPS(BStreamFileToolkit & tk, HC_KEY dummy, int lod)
{
	// for now set up a limitation of being able to store only one model
	if( m_entityList.iteration_count() < 1 )
	{
		AfxMessageBox(_T("No entities present in this model"));
		return TK_Error;
	}

	// output a temporary file for the given model
	generate_temp_filename(m_psf_tempfilename.GetBuffer(_MAX_PATH));
	m_psf_tempfilename.ReleaseBuffer();

	FILE* fp;
	outcome o;
	fp = _tfopen(m_psf_tempfilename, _T("wb"));
	assert(fp);
	if (!fp)
	{
		TCHAR msg[MVO_BUFFER_SIZE];
		_stprintf(msg, _T("Failed to create a temporary SAT file - %s"), m_psf_tempfilename );
		AfxMessageBox(msg);
		return TK_Error;
	}

	// ACIS 6.3 requires this thing for saving files
	char id_string[MVO_BUFFER_SIZE];
	sprintf(id_string, "HOOPS-ACIS Part Viewer");
	FileInfo info;
	info.set_product_id(id_string);
	info.set_units(1.0);
	api_set_file_info((FileId | FileUnits), info);
	info.reset();
	o = api_save_entity_list(fp, FALSE, m_entityList);
	CHECK_OUTCOME(o);
	fclose(fp);

	// get the size of the temp modeler file - we will dump it during the Write
	FILE * tmp_fh = 0;
	tmp_fh = _tfopen(m_psf_tempfilename, _T("rb"));		assert( tmp_fh);
	int int_fh = _fileno( tmp_fh );
	struct _stat buf;
	int iRes = _fstat( int_fh, &buf );		assert(iRes == 0);
	m_psf_filesize = buf.st_size;			assert(m_psf_filesize != -1L);
	fclose( tmp_fh );

	return TK_Normal;
}

#endif //ACIS


