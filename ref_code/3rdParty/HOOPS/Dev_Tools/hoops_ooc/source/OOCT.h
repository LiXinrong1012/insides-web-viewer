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
 * $Id: OOCT.h,v 1.1 2010-05-14 23:18:45 guido Exp $
 */

#ifndef OOCT_H
#define OOCT_H

#ifdef _MSC_VER
#define OOC_API __declspec (dllexport)
#else
#define OOC_API
#endif

#ifndef alter
#define alter
#endif // alter

#include <stdlib.h>

class OOCT_World;
class OOC_API OOCT {
public:
	OOCT ( char const * ooc_file_in );
	void PreProcess ();

private:
	OOCT_World * m_OOCT_World;

};



#endif // OOCT_H

