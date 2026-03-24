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
 * $Id: fixshell.c,v 1.2 2006-08-07 20:38:49 stage Exp $
 */

#include "hc.h"
#include "hpserror.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define	SHELL_ERROR_STRING "Face number %d of shell with key %ld is backward"
#define	TRUE	1
#define FALSE	0
#define MAXFACES 512

/* Global variables */
char  verbose = FALSE;
char  *inname = NULL;
char  *outname = "newshell.hmf";
int   didfaces[MAXFACES];
int   facesdone = 0;
float minnorm = 0.001f;
char  warned = FALSE;
char  pause = FALSE;

#define	streq(a, b)	(strcmp(a, b) == 0)


void correct_face (
  long	skey,
  int	face) {
  int	i;
  int	*flist;
  int	flen, pcnt;
  int	numv = 0;
  float	nx[5], ny[5], nz[5];
  float	pts[3];
  char  face_color[255] = "";
  char  face_pat[100] = "";
  char  face_vis[100] = "";

  HC_Show_Shell_Size (skey, &pcnt, &flen);

  HC_Show_Partial_Shell_Size (skey, face, 1, &flen);
  flist = (int *)malloc (sizeof(int) * flen);
  if (!flist)
    return;

  HC_Show_Partial_Shell (skey, 0, 0, NULL, face, 1, &flen, flist);

  HC_Open_Geometry (skey);

  if (verbose)
    printf ("Correcting face %d\nOriginal facelist: \n", face);
  for (i = 1; i < flen; i++) {
    if (flist[i] < 0) {
      HC_Close_Geometry ();
      return;
    }
    if (verbose)
      printf ("%d ", flist[i]);
    HC_Show_Partial_Shell (skey, flist[i], 1, pts, 0, 0, NULL, NULL);
    HC_Open_Vertex (flist[i]);
       HC_Show_Net_Normal (&nx[numv], &ny[numv], &nz[numv]);
    HC_Close_Vertex ();
    HC_Edit_Shell_Points (skey, -1, 0, 1, pts);
    if (verbose)
      printf ("(Vertex %d) %f %f %f Normal: %f %f %f\n",
	      pcnt-1+i, pts[0], pts[1], pts[2], nx[numv], ny[numv], nz[numv]);
    numv++;
  }

  if (verbose)
    printf ("New Facelist: \n");
  for (i = 0; i < numv; i++) {
    if ((fabs(nx[i])>minnorm) &&
	(fabs(ny[i])>minnorm) &&
	(fabs(nz[i])>minnorm)) {
      HC_Open_Vertex (flist[i+1]);
       	HC_Set_Normal (nx[i], ny[i], nz[i]);
      HC_Close_Vertex ();
      HC_Open_Vertex (pcnt+i);
         HC_Set_Normal (nx[i], ny[i], nz[i]);
      HC_Close_Vertex ();
    }
    flist[i+1] = pcnt+i;
    if (verbose)
      printf ("%d ", flist[i+1]);
    HC_Show_Partial_Shell (skey, flist[i+1], 1, pts, 0, 0, NULL, NULL);
    if (verbose)
      printf ("(Vertex %d) %f %f %f Normal: %f %f %f\n",
	      flist[i+1], pts[0], pts[1], pts[2], nx[i], ny[i], nz[i]);
  }

  HC_Open_Face (face);
    if (HC_Show_Existence ("color")) HC_Show_Color (face_color);
    if (HC_Show_Existence ("face pattern")) HC_Show_Face_Pattern (face_pat);
    if (HC_Show_Existence ("visibility")) HC_Show_Visibility (face_vis);
  HC_Close_Face ();
  
  /* Delete the old face, insert the new face */
  HC_Edit_Shell_Faces (skey, face, 1, flen, flist);
  
  HC_Open_Face (face);
    if (face_color[0]) HC_Set_Color (face_color); 
    if (face_pat[0]) HC_Set_Face_Pattern (face_pat); 
    if (face_vis[0]) HC_Set_Visibility (face_vis); 
  HC_Close_Face ();

  HC_Close_Geometry ();

  free (flist);
}


void shell_error_handler (
  int	category,
  int	specific,
  int	severity,
  int	msgc,
  char	**msgv,
  int	stackc,
  char	**stackv) {
  int	face = 0;
  long	skey = 0;
  int   i;

  if ((category == HEC_GEOMETRY_OR_SEGMENT) &&
      (specific == HES_NON_UNIFORM_HANDEDNESS)) {
    sscanf (msgv[0], SHELL_ERROR_STRING, &face, &skey);

    if (warned == FALSE) facesdone=0;
    warned = TRUE;

    if (verbose) {
      printf ("\nShell error -- correcting\n");
      printf ("Message: %s\n", msgv[0]);
    }

    for (i = 0; i < facesdone; i++) if (didfaces[i] == face) return;
    
    if (facesdone == MAXFACES) return;
    
    didfaces[facesdone++]=face;

    if ((face > -1) && skey)
      correct_face (skey, face);
 }
 else
   HC_Report_Error (category, specific, severity, msgc, msgv, stackc, stackv);
}


int main (
    int		argc,
    char	**argv) {
    float	minpt[3], maxpt[3];

/* Parse command line arguments */
    while (--argc>0) {
       ++argv;
       if streq (*argv, "-v")
	 verbose = TRUE;
       else if streq (*argv, "-p")
	 pause = TRUE;
       else if (*argv[0]!='-')
         if (inname == (char *)0)
	   inname = *argv;
         else
	   outname = *argv;
    }

/* Display usage statement if arguments are wrong */
    if ((inname==(char *)NULL) || (outname[0]=='-')) {
      printf ("Usage: fixshell [-v] [-p] infile [outfile]\n");
      printf ("\t-v       Verbose output of progress\n");
      printf ("\t-p       Pause after completion\n");
      printf ("\tinfile   HOOPS input metafile filename\n");
      printf ("\toutfile  HOOPS output metafile filename\n");
      exit (1);
    }

    printf ("Processing input file %s to output %s\n", inname, outname);

/* Redefine HOOPS error handler to intercept shell errors */
    HC_UnDefine_Error_Handler (HC_Report_Error);
    HC_Define_Error_Handler (shell_error_handler);

/* Setup picture */
    HC_Open_Segment ("?picture");
	HC_Set_Color ("faces=red");
        HC_Set_Visibility ("faces=on, edges=off, markers=off");
	HC_Set_Selectability ("everything=on");
    HC_Close_Segment ();

    HC_Create_Segment ("?picture/metafile");
    HC_Read_Metafile (inname, "?picture/metafile",
		      "read, restore state=(color names, textures)");

    if (HC_Compute_Circumcuboid ("?picture/metafile", minpt, maxpt))
       HC_QSet_Camera_By_Volume ("?picture", "Orthographic",
				 minpt[0], maxpt[0], minpt[1], maxpt[1]);

    HC_Update_Display ();
    while (warned) {
      warned = FALSE;
      HC_Write_Metafile ("?picture/metafile",
      			 outname,
      			 "no read, write, save state=(color names, textures), use color names, follow cross-references, overwrite");
      HC_Flush_Contents ("?picture/metafile", "everything");
      HC_Flush_Contents ("?include library/*", "everything");
      printf ("Iterating\n");
      HC_Read_Metafile (outname, "?picture/metafile",
			"read, restore state=(color names, texture)");
      HC_Update_Display ();
    }

    printf ("Done.\n");
    HC_Write_Metafile ("?picture/metafile",
		       outname,
		       "no read, write, save state=(color names, textures), use color names, follow cross-references, overwrite");

    if (pause)
      HC_Pause();
    else
      HC_Update_Display();

    printf ("\nProcessing completed to output file: %s\n", outname);

    HC_Exit_Program ();
    return 0;
}
