/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.11 2009-10-07 17:10:43 conor Exp $
 */


#ifdef NUTCRACKER
#include <wchar.h>
#endif

#include "hoops.h"


extern "C++" {

#define V_PREFIX HOOPS_3DGS_

#include "utility/vhash.cpp"
#include "utility/vlist.cpp"
#include "utility/vdlist.cpp"
#include "utility/huffman.cpp"
#include "utility/vconf.cpp"

#define UTF_UTILS_API HOOPS_API 

#include "utility/utf_utils.cpp"

}


