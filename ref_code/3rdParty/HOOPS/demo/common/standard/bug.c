/*
 * $Id: bug.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 *
 * This is the Tech Soft 3D bug reporting template. Please supply
 * the requested information, provide a small test program, and electronically
 * submit this to support@tsoftamerica.com.
 * 
 * Thanks,
 * Technical Support
 *
 */

/*
A. SUBMITTER INFORMATION:
NAME: <Your Name>
ORGANIZATION: <Your Company or Institution>
PROJECT: <Project within your Company - Optional>
E-MAIL ADDRESS: <Your E-mail Address>
PHONE: <Your Phone Number>

B. HOOPS INFORMATION:
VERSION: <Your HOOPS MAJOR.MINOR-XX (e.g. 3.22-34)>
PLATFORM: <Your Platform (e.g. Solaris)>
OS VERSION: <Your OS Version (e.g. 2.1)>
PICTURE: <Your HOOPS_PICTURE setting>
DISPLAY: <M by N pixels, N colors>

C. CUSTOMER INFORMATION:
SUPPORT LEVEL: <Priority Service, Developer Support, Update Fees>
PRODUCT RELEASE DATE: <dd-mm-yy>

D. BUG PROGRAM DESCRIPTION:
ONE LINE DESCRIPTION TO BE USED AS TITLE OF CASE:
(45 characters if possible, please)
<A one line description of the problem demonstrated by the test case program>

FULL DESCRIPTION:
<Description of the actual output of the test case program versus
what the output should be>

TEST CASE:
a simple C program which demonstrates the problem
*/

#include "hc.h"

int main () {
    HC_Open_Segment ("?picture");
	/* insert your code here */
    HC_Close_Segment ();
    HC_Pause ();
    HC_Exit_Program ();
    return 0;
}

/*
 * METAFILE:
<A simple HOOPS metafile that when read, demonstrates the
 problem -- Optional>
 */
