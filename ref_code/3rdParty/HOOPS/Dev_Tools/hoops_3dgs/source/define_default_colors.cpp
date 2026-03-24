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
 * $Id: obf_tmp.txt 1.28 2010-10-01 16:28:58 jason Exp $
 */

#include "hoops.h"
#include "hc_proto.h"
#include "hi_proto.h"


GLOBAL_FUNCTION void HI_Define_Default_Colors (
	_hoops_AIGPR *		_hoops_RIGC) {
#ifndef DISABLE_COLOR_NAMES
	PUSHNAME(_hoops_RIGC);
	HC_Define_Color_Name ("Apricot",
						  "",
						  "",					"R=1.0 G=0.76 B=0.65");

	HC_Define_Color_Name ("Aquamarine, Aqua",
						  "",
						  "",					"R=0.0 G=0.95 B=0.84");

	HC_Define_Color_Name ("Bittersweet",
						  "",
						  "",					"R=0.81 G=0.04 B=0.0");

	HC_Define_Color_Name ("Black",
						  "Blacker, Dark, Darker, Dim, Dimmer",
						  "Blackish, Darkish",	"H=0.0 L=0.0 S=0.0");

	HC_Define_Color_Name ("Blue Green",
						  "",
						  "",					"R=0.0 G=0.71 B=0.66");

	HC_Define_Color_Name ("Blue Grey",
						  "",
						  "",					"R=0.16 G=0.46 B=0.65");

	HC_Define_Color_Name ("Blue Violet",
						  "",
						  "",					"R=0.1 G=0.0 B=0.25");

	HC_Define_Color_Name ("Blue",
						  "Bluer",
						  "Bluish, Blueish",	"R=0.0 G=0.0 B=1.0");

	HC_Define_Color_Name ("Brick Red",
						  "",
						  "",					"R=0.64 G=0.01 B=0.0");

	HC_Define_Color_Name ("Burnt Orange",
						  "",
						  "",					"R=0.71 G=0.31 B=0.0");

	HC_Define_Color_Name ("Burnt Sienna",
						  "",
						  "",					"R=0.56 G=0.10 B=0.05");

	HC_Define_Color_Name ("Cadet Blue",
						  "",
						  "",					"R=0.31 G=0.31 B=0.56");

	HC_Define_Color_Name ("Carnation Pink, Pink",
						  "Pinker",
						  "Pinkish",			"R=1.0 G=0.35 B=0.52");

	HC_Define_Color_Name ("Copper",
						  "",
						  "Copperish",			"R=0.52 G=0.21 B=0.0");

	HC_Define_Color_Name ("Cornflower",
						  "",
						  "",					"R=0.42 G=0.42 B=1.0");

	HC_Define_Color_Name ("Cyan",
						  "",
						  "",					"R=0.0 G=1.0 B=1.0");

	HC_Define_Color_Name ("Forest Green",
						  "",
						  "",					"R=0.0 G=0.36 B=0.09");

	HC_Define_Color_Name ("Gold",
						  "Golder",
						  "Goldish",			"R=.68 G=0.37 B=0.0");

	HC_Define_Color_Name ("Goldenrod",
						  "",
						  "",					"R=1.0 G=0.36 B=0.0");

	HC_Define_Color_Name ("Gray, Grey",
						  "Grayer, Greyer",
						  "Grayish, Greyish",	"H=0.0 L=0.5 S=0.0");

	HC_Define_Color_Name ("Green Blue",
						  "",
						  "",					"R=0.0 G=0.58 B=0.80");

	HC_Define_Color_Name ("Green Yellow",
						  "",
						  "",					"R=0.90 G=1.0 B=0.0");

	HC_Define_Color_Name ("Green",
						  "Greener",
						  "Greenish",			"R=0.0 G=1.0 B=0.0");

	HC_Define_Color_Name ("Indian Red",
						  "",
						  "",					"R=0.50 G=0.0 B=0.0");

	HC_Define_Color_Name ("Indigo","","", "R=0.29 G=0.0 B=0.50");

	HC_Define_Color_Name ("Lavender",
						  "",
						  "",					"R=1.0 G=0.56 B=0.78");

	HC_Define_Color_Name ("Lemon Yellow",
						  "",
						  "",					"R=1.0 G=0.86 B=0.04");

	HC_Define_Color_Name ("Magenta",
						  "",
						  "",					"R=1.0 G=0.0 B=0.61");

	HC_Define_Color_Name ("Mahogany",
						  "",
						  "",					"R=0.53 G=0.0 B=0.0");

	HC_Define_Color_Name ("Maize",
						  "",
						  "",					"R=1.0 G=0.67 B=0.0");

	HC_Define_Color_Name ("Maroon",
						  "",
						  "",					"R=0.50 G=0.0 B=0.23");

	HC_Define_Color_Name ("Melon",
						  "",
						  "",					"R=0.96 G=0.37 B=0.30");

	HC_Define_Color_Name ("Midnite Blue, Midnight Blue",
						  "",
						  "",					"R=0.0 G=0.0 B=0.36");

	HC_Define_Color_Name ("Brown, Moose Brown",
						  "Browner",
						  "Brownish",			"R=0.20 G=0.032 B=0");

	HC_Define_Color_Name ("Mulberry",
						  "",
						  "",					"R=0.76 G=0.0 B=0.47");

	HC_Define_Color_Name ("Navy Blue",
						  "",
						  "",					"R=0.0 G=0.0 B=0.48");

	HC_Define_Color_Name ("Olive Green",
						  "",
						  "",					"R=0.49 G=0.49 B=0.0");

	HC_Define_Color_Name ("Orange Red",
						  "",
						  "",					"R=0.75 G=0.03 B=0.0");

	HC_Define_Color_Name ("Orange Yellow",
						  "",
						  "",					"R=1.0 G=0.50 B=0.0");

	HC_Define_Color_Name ("Orange",
						  "Oranger",
						  "Orangish",			"R=1.0 G=0.4 B=0.0");

	HC_Define_Color_Name ("Orchid",
						  "",
						  "",					"R=0.95 G=0.22 B=0.81");

	HC_Define_Color_Name ("Peach",
						  "",
						  "",					"R=1.0 G=0.64 B=0.49");

	HC_Define_Color_Name ("Periwinkle",
						  "",
						  "",					"R=0.68 G=0.75 B=1.0");

	HC_Define_Color_Name ("Pine Green",
						  "",
						  "",					"R=0.0 G=0.36 B=0.27");

	HC_Define_Color_Name ("Plum",
						  "",
						  "",					"R=0.54 G=0.0 B=0.44");

	HC_Define_Color_Name ("Raw Sienna",
						  "",
						  "",					"R=0.58 G=0.22 B=0.01");

	HC_Define_Color_Name ("Raw Umber",
						  "",
						  "",					"R=0.32 G=0.15 B=0.0");

	HC_Define_Color_Name ("Red Orange",
						  "",
						  "",					"R=1.0 G=0.04 B=0.0");

	HC_Define_Color_Name ("Red Violet",
						  "",
						  "",					"R=0.62 G=0.0 B=0.55");

	HC_Define_Color_Name ("Red",
						  "Redder",
						  "Reddish",			"R=1.0 G=0.0 B=0.0");

	HC_Define_Color_Name ("Salmon",
						  "",
						  "",					"R=1.0 G=0.49 B=0.37");

	HC_Define_Color_Name ("Sea Green",
						  "",
						  "",					"R=0.16 G=1.0 B=0.16");

	HC_Define_Color_Name ("Sepia",
						  "",
						  "",					"R=0.16 G=0.032 B=0.0");

	HC_Define_Color_Name ("Silver",
						  "",
						  "Silverish",			"R=0.72 G=0.72 B=0.72");

	HC_Define_Color_Name ("Sky Blue",
						  "",
						  "",					"R=0.44 G=0.85 B=1.0");

	HC_Define_Color_Name ("Spring Green",
						  "",
						  "",					"R=0.74 G=1.0 B=0.26");

	HC_Define_Color_Name ("Tan",
						  "",
						  "",					"R=0.71 G=0.16 B=0.0");

	HC_Define_Color_Name ("Thistle",
						  "",
						  "",					"R=0.82 G=0.04 B=0.66");

	HC_Define_Color_Name ("Turquoise Blue, Turquoise",
						  "",
						  "",					"R=0.0 G=0.56 B=0.64");

	HC_Define_Color_Name ("Violet Blue",
						  "",
						  "",					"R=0.04 G=0.0 B=0.16");

	HC_Define_Color_Name ("Violet Red",
						  "",
						  "",					"R=0.64 G=0.0 B=0.25");

	HC_Define_Color_Name ("Violet, Purple",
						  "Purpler",
						  "Purplish",			"R=0.09 G=0.0 B=0.12");

	HC_Define_Color_Name ("White",
						  "Whiter, Light, Lighter, Bright, Brighter",
						  "Whitish, Lightish",	"H=0.0 L=1.0 S=0.0");

	HC_Define_Color_Name ("Yellow Green",
						  "",
						  "",					"R=0.49 G=1.0 B=0.0");

	HC_Define_Color_Name ("Yellow Orange",
						  "",
						  "",					"R=1.0 G=0.23 B=0.0");

	HC_Define_Color_Name ("Yellow",
						  "Yellower",
						  "Yellowish",			"R=1.0 G=1.0 B=0.0");

/* _hoops_CGIPP _hoops_SGIPP */
	HC_Define_Color_Name ("Wild Strawberry, Strawberry",
						  "",
						  "",			"R=0.8 G=0.0 B=0.2");
	HC_Define_Color_Name ("Vivid Tangerine, Tangerine",
						  "",
						  "",			"R=1.0 G=0.4 B=0.0");
	HC_Define_Color_Name ("Dandelion",
						  "",
						  "",			"R=0.9 G=0.75 B=0.0");
	HC_Define_Color_Name ("Jungle Green",
						  "",
						  "",			"R=0.0 G=0.65 B=0.4");
	HC_Define_Color_Name ("Teal Blue, Teal",
						  "",
						  "",			"R=0.0 G=0.4 B=0.32");
	HC_Define_Color_Name ("Cerulean",
						  "",
						  "",			"R=0.0 G=0.32 B=0.4");
	HC_Define_Color_Name ("Royal Purple",
						  "",
						  "",			"R=0.25 G=0.0 B=0.4");
	HC_Define_Color_Name ("Fuchsia",
						  "",
						  "",			"R=0.65 G=0.0 B=0.4");

	POPNAME(_hoops_RIGC);
#endif
}
