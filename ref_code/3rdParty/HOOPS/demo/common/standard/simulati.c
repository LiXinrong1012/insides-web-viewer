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
 * $Id: simulati.c,v 1.3 2010-10-26 21:29:09 jason Exp $
 */

#include "hc.h"
#include "hc_standalone.h"
#include <stdio.h>
#include <stdlib.h>

float	get_random_number(void);

#define SEATTLE         0
#define SAN_FRANCISCO   1
#define LOS_ANGELES     2
#define MIAMI           3
#define CHICAGO         4
#define CORPUS_CHRISTI  5
#define NUM_CITIES      6
#define NUM_CONNECTIONS 15
#define NUM_LOOPS       100

typedef struct {
   int      city1,
            city2;
   float    usage;
}  Connection;

typedef struct {
   char     name[64];
   float    latitude,
            longitude;
   char     alignment[4];
}  City;

City cities[NUM_CITIES] = {
   {"Seattle",        1.18f, 6.36f, ">v", },
   {"San Francisco",  0.44f, 3.66f, "<v", },
   {"Los Angeles",    1.06f, 2.65f, ">^", },
   {"Miami",          8.6f,  0.81f, "<^", },
   {"Chicago",        6.5f,  4.4f,  "<*", },
   {"Corpus Christi", 4.98f, 0.75f, "<^", }
};

Connection   connections[NUM_CONNECTIONS] = {
   {SEATTLE,       SAN_FRANCISCO,  0.1f},
   {SEATTLE,       LOS_ANGELES,    0.2f},
   {SEATTLE,       MIAMI,          0.3f},
   {SEATTLE,       CHICAGO,        0.4f},
   {SEATTLE,       CORPUS_CHRISTI, 0.5f},
   {SAN_FRANCISCO, LOS_ANGELES,    0.6f},
   {SAN_FRANCISCO, MIAMI,          0.7f},
   {SAN_FRANCISCO, CHICAGO,        0.8f},
   {SAN_FRANCISCO, CORPUS_CHRISTI, 0.9f},
   {LOS_ANGELES,   MIAMI,          0.0f},
   {LOS_ANGELES,   CHICAGO,        0.1f},
   {LOS_ANGELES,   CORPUS_CHRISTI, 0.2f},
   {MIAMI,         CHICAGO,        0.3f},
   {MIAMI,         CORPUS_CHRISTI, 0.4f},
   {CHICAGO,       CORPUS_CHRISTI, 0.5f}
};

float get_random_number () {
   return (((int) rand() % 32767) / 32767.0f - 0.5f) * 2.0f;
}

int main () {
   int     i, j;

   HC_Open_Segment ("?picture/usa");
      HC_Read_Metafile ("usa", ".", "");
      HC_Open_Segment ("?picture/title");
         HC_Set_Camera_Projection ("stretched");
      	 HC_Insert_Text (0.0, 0.8, 0.0, "Network Usage in the USA");
      HC_Close_Segment ();
      HC_Set_Camera_By_Volume ("stretched", 0.0, 10.0, 0.0, 8.0);
      HC_Open_Segment ("cities");
         HC_Set_Marker_Symbol ("@");
         HC_Set_Text_Font ("size = 0.02 sru");
         for (i = 0; i < NUM_CITIES; ++i) {
            HC_Open_Segment (cities[i].name);
               HC_Insert_Marker ((double)cities[i].latitude,
                                 (double)cities[i].longitude,
				 0.0);
               HC_Set_Text_Alignment (cities[i].alignment);
               HC_Insert_Text ((double)cities[i].latitude,
                               (double)cities[i].longitude,
			       0.0,
                               cities[i].name);
            HC_Close_Segment ();
         }
      HC_Close_Segment ();

      HC_Open_Segment ("connections");
         for (i = 0; i < NUM_CONNECTIONS; ++i) {
            char     name[100];
            int      c1 = connections[i].city1;
            int      c2 = connections[i].city2;

            sprintf (name, "%s %s", cities[c1].name,
                                    cities[c2].name);
            HC_Open_Segment (name);
               HC_Insert_Line ((double)cities[c1].latitude,
			       (double)cities[c1].longitude,
			       0.0,
                               (double)cities[c2].latitude,
                               (double)cities[c2].longitude,
			       0.0);
	    HC_Close_Segment ();
         }
      HC_Close_Segment ();

      for (j = 0; j < NUM_LOOPS; ++j) {
         for (i = 0; i < 15; ++i) {
                     char   name[100];
                     int    c1 = connections[i].city1;
                     int    c2 = connections[i].city2;

            sprintf (name, "connections/%s %s",
                     cities[c1].name, cities[c2].name);

            connections[i].usage += get_random_number ();

            if (connections[i].usage > 1.0f)
               connections[i].usage = 1.0f;
            else if (connections[i].usage < 0.0f)
               connections[i].usage = 0.0f;

            if (connections[i].usage > 0.8f)
               HC_QSet_Color (name, "red");
            else if (connections[i].usage > 0.5f)
               HC_QSet_Color (name, "green");
            else if (connections[i].usage > 0.3f)
               HC_QSet_Color (name, "blue");
            else
               HC_QSet_Color (name, "black");
         }
         HC_Get_Wakeup (1.0);
      }

   HC_Close_Segment ();
   HC_Exit_Program ();
   return 0;
}
