/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: line.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"

/*
 * This is usually the first program that HDI driver writers
 * execute when trying out their newly written HOOPS
 * driver.
 */
int main () {
    HC_Open_Segment ("?picture");
	HC_Insert_Line (-1.0, -1.0, 0.0, 1.0, 1.0, 0.0);
    HC_Close_Segment ();
    HC_Pause ();
    HC_Exit_Program ();
    return 0;
}
