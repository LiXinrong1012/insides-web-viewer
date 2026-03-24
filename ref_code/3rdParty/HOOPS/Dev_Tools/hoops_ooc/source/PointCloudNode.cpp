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
 * $Id: PointCloudNode.cpp,v 1.6 2009-10-13 22:21:36 chad Exp $
 */

#include "PointCloudNode.h"

#include "StreamFilePointContainer.h"

#include <string.h>

/*****************************************************************************************************/

TK_Point_Cloud_Node::TK_Point_Cloud_Node () {}

TK_Point_Cloud_Node::~TK_Point_Cloud_Node () {}

TK_Status TK_Point_Cloud_Node::Read ( BStreamFileToolkit & tk ) alter {
	TK_Status status = TK_Normal;
	
	switch (m_stage) {
		case 0: {
			if ((status = GetData(tk, m_num_points)) != TK_Normal)
				return status;
			
			if (m_num_points == 0) {
				// this shouldn't happen
				return tk.Error("File says it contains zero points");
			}
			
			m_current_point = 0;
			m_sub_stage = 0;
			m_stage++;
		} nobreak;
			
		case 1: {
			while (m_current_point < m_num_points) {
				switch (m_sub_stage) {
					case 0: {
						if ((status = GetData(tk, reinterpret_cast<float *>(&(m_point_list[m_current_point].pt)), 3)) != TK_Normal)
							return status;
						
						m_sub_stage++;
					} nobreak;
					
					case 1: {
						if ((status = GetData(tk, m_point_list[m_current_point].intensity)) != TK_Normal)
							return status;
						
						m_sub_stage++;
					} nobreak;
					
					case 2: {
						if ((status = GetData(tk, reinterpret_cast<float *>(&(m_point_list[m_current_point].rgb_color)), 3)) != TK_Normal)
							return status;
						
						m_sub_stage++;
					} nobreak;

					case 3: {
						if ((status = GetData(tk, reinterpret_cast<unsigned int &>(m_point_list[m_current_point].vfield))) != TK_Normal)
							return status;

#ifndef POINT_CLOUD_VERTEX_NORMALS
						m_current_point++;
						m_sub_stage = 0;
					} break;
#else
						m_sub_stage++;
					} nobreak;

					case 4: {
						if ((status = GetData(tk, reinterpret_cast<float *>(&(m_point_list[m_current_point].normal)), 3)) != TK_Normal)
							return status;

						m_current_point++;
						m_sub_stage = 0;
					} break;
#endif // POINT_CLOUD_VERTEX_NORMALS
						
					default:
						return tk.Error("Problem reading in points for a particular node");
				}
			}
			
			m_stage++;
		} nobreak;
			
		case 2: {
			unsigned char stop_code;
			if ((status = GetData(tk, stop_code)) != TK_Normal)
				return status;
			
			if (stop_code != TKE_Stop_User_Data)
				return tk.Error("Corrupt/invalid file");
			
			m_stage = -1;
		} break;
			
		default:
			status = TK_Error;
	}
	
	return status;
}

TK_Status TK_Point_Cloud_Node::Execute ( BStreamFileToolkit & tk ) alter {
	return TK_Normal;
}

TK_Status TK_Point_Cloud_Node::Write ( BStreamFileToolkit & tk ) alter {
	TK_Status status = TK_Normal;
	
	switch (m_stage) {
		case 0: {
			if ((status = PutOpcode(tk, 0)) != TK_Normal)
				return status;
			
			m_stage++;
		} nobreak;
			
		case 1: {
			// write out number of points
			if ((status = PutData(tk, m_num_points)) != TK_Normal)
				return status;
			
			m_current_point = 0;
			m_sub_stage = 0;
			m_stage++;
		} nobreak;
			
		case 2: {
			while (m_current_point < m_num_points) {
				switch (m_sub_stage) {
					case 0: {
						if ((status = PutData(tk, reinterpret_cast<float const *>(&(m_point_list[m_current_point].pt)), 3)) != TK_Normal)
							return status;
						
						m_sub_stage++;
					} nobreak;
					
					case 1: {
						if ((status = PutData(tk, m_point_list[m_current_point].intensity)) != TK_Normal)
							return status;
						
						m_sub_stage++;
					} nobreak;
					
					case 2: {
						if ((status = PutData(tk, reinterpret_cast<float const *>(&(m_point_list[m_current_point].rgb_color)), 3)) != TK_Normal)
							return status;
						
						m_sub_stage++;
					} nobreak;
					
					case 3: {
						if ((status = PutData(tk, reinterpret_cast<unsigned int &>(m_point_list[m_current_point].vfield))) != TK_Normal)
							return status;

#ifndef POINT_CLOUD_VERTEX_NORMALS
						m_current_point++;
						m_sub_stage = 0;
					} break;
#else
						m_sub_stage++;
					} nobreak;

					case 4: {
						if ((status = PutData(tk, reinterpret_cast<float const *>(&(m_point_list[m_current_point].normal)), 3)) != TK_Normal)
							return status;
						
						m_current_point++;
						m_sub_stage = 0;
					} break;
#endif // POINT_CLOUD_VERTEX_NORMALS
					default:
						return TK_Error;
				}
			}
			
			m_stage++;
		} nobreak;
			
		case 3: {
            if ((status = PutData (tk, (unsigned char)TKE_Stop_User_Data)) != TK_Normal)
                return status;
			
            m_stage = -1;
        } break;
			
		default:
			status = TK_Error;
	}
	
	return status;
}

TK_Status TK_Point_Cloud_Node::Interpret ( BStreamFileToolkit & tk, ID_Key key, int variant ) alter {
	return TK_Normal;
}

void TK_Point_Cloud_Node::Reset () alter {
	TK_User_Data::Reset();
}
