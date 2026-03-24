//
// Copyright (c) 2005 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hoops_dwf/source/HW3DStream.h,v 1.8 2009-03-03 14:44:33 mustafa Exp $
//


#ifndef _HDWFSTREAM_H
#define _HDWFSTREAM_H

#include "hc.h"


#ifdef _MSC_VER

	#ifndef HW3D_STREAM_STATIC_LIB
		#ifdef HW3D_STREAM
			#    define HW3D_STREAM_API  __declspec (dllexport)
		#else
			#    define HW3D_STREAM_API  __declspec (dllimport)
		#endif
	#else
 		#define HW3D_STREAM_API
	#endif
#else
    #define HW3D_STREAM_API
#endif



#endif	// _HDWFSTREAM_H


