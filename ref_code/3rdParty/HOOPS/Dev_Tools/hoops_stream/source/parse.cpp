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
// $Header: /files/homes/master/cvs/hoops_master/hoops_stream/source/parse.cpp,v 1.238 2010-10-19 21:36:21 heppe Exp $
// 

#include "HStream.h"
#include "BInternal.h"

// NOTE: this table corresponds to enum TKO_Generic_Size_Units
static char const * generic_units_table[] = {
	"oru", "sru", "wru", "points", "pixels", "%", "wsu",
	""								//
};


#define SKIP_AHEAD(ptr) do {                            \
			int     parens = 0;							\
			char    test;								\
			while ((test = *ptr) != '\0') {             \
				if ((test == ',' || test == ')') &&     \
					parens == 0)                        \
					break;                              \
				++ptr;                                  \
				if (test == '(') ++parens;              \
				else if (test == ')') {                 \
					if (--parens == 0) break;           \
				}                                       \
			}                                           \
		} while (0)                                    //

#define READ_INT(x,cp) do {                     \
			bool    negative = false;			\
			x = 0;                              \
			if (*cp == '-')                     \
				{ negative = true;  ++cp; }     \
			while (*cp >= '0' && *cp <= '9') {  \
				x *= 10;                        \
				x += (*cp++ - '0');             \
			}                                   \
			if (negative) x = -x;               \
		} while (0)                            //


TK_Status HTK_Color_Composite::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            color[4096];
	int             num_parts = 0;
	char const *    clr = color;
	TK_Status       status = TK_Normal;

	HC_Show_Color (color);

	while (*clr) {
		int             bits = 0;

		forever {   // gather geometry types
			char const *    cp = clr;

			while (*cp && *cp != '=' && *cp != ',')
				++cp;

			int             len = (int)(cp - clr);

			if (streqn (clr, "everything", len))
				bits |= TKO_Geo_Every_Colors;
			else if (streqn (clr, "geometry", len))
				bits |= TKO_Geo_Geom_Colors;
			else if (streqn (clr, "polygon", len))
				bits |= TKO_Geo_Face | TKO_Geo_Edge;
			else if (streqn (clr, "face", len))
				bits |= TKO_Geo_Face;
			else if (streqn (clr, "front", len))
				bits |= TKO_Geo_Front;
			else if (streqn (clr, "back", len))
				bits |= TKO_Geo_Back;
			else if (streqn (clr, "edge", len))
				bits |= TKO_Geo_Edge;
			else if (streqn (clr, "line", len))
				bits |= TKO_Geo_Line;
			else if (streqn (clr, "marker", len))
				bits |= TKO_Geo_Marker | TKO_Geo_Vertex;
			else if (streqn (clr, "marker only", len))
				bits |= TKO_Geo_Marker;
			else if (streqn (clr, "vertex", len))
				bits |= TKO_Geo_Vertex;
			else if (streqn (clr, "text", len))
				bits |= TKO_Geo_Text;
			else if (streqn (clr, "window", len))
				bits |= TKO_Geo_Window;
			else if (streqn (clr, "lighting", len))
				bits |= TKO_Geo_Light;
			else if (streqn (clr, "ambient", len)) {
				if (tk.GetTargetVersion() >= 1650)
					bits |= TKO_Geo_Ambient;
				else
					bits |= TKO_Geo_Ambient_Up;
			}
			else if (streqn (clr, "ambient up", len))
				bits |= TKO_Geo_Ambient_Up;
			else if (streqn (clr, "ambient down", len)) {
				if (tk.GetTargetVersion() >= 1650)
					bits |= TKO_Geo_Ambient_Down;
			}
			else if (streqn (clr, "face contrast", len))
				bits |= TKO_Geo_Face_Contrast;
			else if (streqn (clr, "window contrast", len))
				bits |= TKO_Geo_Window_Contrast;
			else if (streqn (clr, "simple reflection", len)) {
				if (tk.GetTargetVersion() >= 1550)
					bits |= TKO_Geo_Simple_Reflection;
			}
			else if (streqn (clr, "cut geometry", len))
				bits |= TKO_Geo_Cut_Face | TKO_Geo_Cut_Edge;
			else if (streqn (clr, "cut face", len))
				bits |= TKO_Geo_Cut_Face;
			else if (streqn (clr, "cut edge", len))
				bits |= TKO_Geo_Cut_Edge;
			else if (streqn (clr, "edge contrast", len))
				bits |= TKO_Geo_Edge_Contrast;
			else if (streqn (clr, "line contrast", len))
				bits |= TKO_Geo_Line_Contrast;
			else if (streqn (clr, "marker contrast", len))
				bits |= TKO_Geo_Marker_Contrast;
			else if (streqn (clr, "vertex contrast", len))
				bits |= TKO_Geo_Vertex_Contrast;
			else if (streqn (clr, "text contrast", len))
				bits |= TKO_Geo_Text_Contrast;
			else
				break;

			clr += len;
			if (*clr == '=')
				++clr;
		}
		if ((bits & TKO_Geo_Extended_Mask) != 0)
			bits |= TKO_Geo_Extended;
		if ((bits & TKO_Geo_Extended_Colors_Mask) != 0)
			bits |= TKO_Geo_Extended_Colors;
		if ((bits & TKO_Geo_Extended2_Mask) != 0)
			bits |= TKO_Geo_Extended2;

		if (*clr == '#') {
			char            buffer[32];
			char alter *    dp = buffer;
			float           value;
			int             truncated;

			++clr;
			while (*clr && *clr != ',')
				*dp++ = *clr++;
			*dp++ = '\0';

			value = read_float (buffer);
			truncated = int (value);

			if (float(truncated) == value) {
				unsigned char opcode;

				if( truncated < 256) 
					opcode = TKE_Color_By_Index;
				else
					opcode = TKE_Color_By_Index_16;
				status = tk.GetOpcodeHandler(opcode)->Clone(tk, &m_parts[num_parts]);
				if( status != TK_Normal )
					return status;
				((TK_Color_By_Index *)m_parts[num_parts])->SetGeometry( bits );
				((TK_Color_By_Index *)m_parts[num_parts])->SetIndex( truncated );
				num_parts++;
			}
			else {
				status = tk.GetOpcodeHandler(TKE_Color_By_FIndex)->Clone(tk, &m_parts[num_parts]);
				if( status != TK_Normal )
					return status;
				((TK_Color_By_FIndex *)m_parts[num_parts])->SetIndex( value );
				num_parts++;
			}
		}
		else {
			char const *	paren = null;
			int				channels = 0;
			char			buffer[TKO_Channel_Count][4096];
			char alter *	dp;
			bool			comma = false;
			char			quote;

			if (*clr == '(') {
				paren = clr++;
			}

			while (*clr) {
				int             channel = TKO_Channel_Diffuse;
				char const *    cp = clr;
				int             nesting = 0;

				while (*cp && *cp != ',' && *cp != '=' && *cp != ')')
					++cp;
				while (cp[-1] == ' ')
					--cp;

				int             len = (int)(cp - clr);

				if (streqn (clr, "diffuse", len))
					channel = TKO_Channel_Diffuse;
				else if (streqn (clr, "specular", len))
					channel = TKO_Channel_Specular;
				else if (streqn (clr, "mirror", len))
					channel = TKO_Channel_Mirror;
				else if (streqn (clr, "transmission", len))
					channel = TKO_Channel_Transmission;
				else if (streqn (clr, "emission", len))
					channel = TKO_Channel_Emission;
				else if (streqn (clr, "environment", len))
					channel = TKO_Channel_Environment;
				else if (streqn (clr, "bump", len))
					channel = TKO_Channel_Bump;
				else if (streqn (clr, "gloss", len))
					channel = TKO_Channel_Gloss;
				else if (streqn (clr, "index", len))
					channel = TKO_Channel_Index;
				else if (channels & (1<<TKO_Channel_Diffuse) ||
						 streqn (clr, "diffuse color", len) ||
						 streqn (clr, "diffuse texture", len)) {
					//color parsing is too complex in this case.  Drop back to the previous 
					//paren and treat the color as one big string
					channels = 0;
					len = 0;
					if (paren) {
						clr = paren;
						paren = null;
					}
				}
				else {
					len = 0; // 'diffuse=' assumed
				}

				if (len > 0) {
					clr += len;
					while (*clr == ' ')
						++clr;
					++clr;       // '='
					while (*clr == ' ')
						++clr;
				}

				channels |= (1 << channel);

				dp = buffer[channel];
				quote = 0;
				while (*clr) {
					if (*clr == '"' || *clr == '\'' || *clr == '`') {
						if (quote) {
							if (*clr == quote)
								/* tjh: no need to handle escaped quotes here, since after the 2nd instance 
								* the state of "quote" is back where we started */
								quote = 0;
						}
						else
							quote = *clr;
					}
					else if (*clr == '(') {
						if (!quote)
							++nesting;
					}
					else if (*clr == ')'){
						if (!quote) {
							if (!nesting)
								break;
							--nesting;
						}
					}
					else if (*clr == ',') {
						if (!quote) {
							comma = true;
							if (!nesting)
								break;
						}
					}
					*dp++ = *clr++;
				}
				*dp++ = '\0';
				dp = buffer[channel];
				if (dp[0] == '(' && dp[strlen(dp)-1] == ')') {
					dp[strlen(dp)-1] ='\0';
					do dp[0] = dp[1];
					while (*dp++ != '\0');
				}

				if (*clr == ')') {
					++clr;
					break;
				}
				else if (*clr == ',') {
					if (paren) {
						++clr;
						while (*clr == ' ')
							++clr;
					}
					else
						break;
				}
			}

			if ((channels & TKO_Channel_Extended_Mask) != 0)
				channels |= (1 << TKO_Channel_Extended);

			if (channels == (1 << TKO_Channel_Diffuse)) { // && !(use_color_names || use_original_form)
				char            sysop[2048];
				float           rgb[3];

				HC_Show_One_System_Option ("errors", sysop);
				HC_Define_System_Options ("no errors");

				if (!comma && HC_Compute_Color (buffer[TKO_Channel_Diffuse], "rgb", rgb)) {
					//old dead code: m_parts[num_parts++] = new HTK_Color_RGB (bits, rgb);
					status = tk.GetOpcodeHandler(TKE_Color_RGB)->Clone(tk, &m_parts[num_parts]);
					((TK_Color_RGB *)m_parts[num_parts])->SetGeometry(bits);
					((TK_Color_RGB *)m_parts[num_parts])->SetRGB(rgb);
					num_parts++;
				}
				else {
					TK_Color *      complex;

					//old dead code: m_parts[num_parts++] = complex = new HTK_Color (bits, channels);
					status = tk.GetOpcodeHandler(TKE_Color)->Clone(tk, &m_parts[num_parts]);
					complex = (TK_Color *)m_parts[num_parts];
					complex->SetGeometry(bits);
					complex->SetChannels(channels);
					complex->SetDiffuseName (buffer[TKO_Channel_Diffuse]);
					num_parts++;
				}

				{
					char		newsysop[2048];

					sprintf (newsysop, "errors=(%s)", sysop);
					HC_Define_System_Options (newsysop);
				}
			}
			else {
				// not diffuse only, or real names or original form desired
				char            sysop[2048];
				TK_Color *      complex;
				float           rgb[3];

				//old dead code: m_parts[num_parts++] = complex = new HTK_Color (bits, channels);
				status = tk.GetOpcodeHandler(TKE_Color)->Clone(tk,&m_parts[num_parts]);
				complex = (TK_Color *)m_parts[num_parts];
				complex->SetGeometry(bits);
				complex->SetChannels(channels);
				num_parts++;

				HC_Show_One_System_Option ("errors", sysop);
				HC_Define_System_Options ("no errors");

				if ((channels & (1 << TKO_Channel_Diffuse)) != 0) {
					if (strchr (buffer[TKO_Channel_Diffuse], ',') == null &&
						HC_Compute_Color (buffer[TKO_Channel_Diffuse], "rgb", rgb))
						complex->SetDiffuse(rgb);
					else
						complex->SetDiffuseName (buffer[TKO_Channel_Diffuse]);
				}
				if ((channels & (1 << TKO_Channel_Specular)) != 0) {
					if (HC_Compute_Color (buffer[TKO_Channel_Specular], "rgb", rgb))
						complex->SetSpecular(rgb);
					else
						complex->SetSpecularName (buffer[TKO_Channel_Specular]);
				}
				if ((channels & (1 << TKO_Channel_Mirror)) != 0) {
					if (HC_Compute_Color (buffer[TKO_Channel_Mirror], "rgb", rgb))
						complex->SetMirror(rgb);
					else
						complex->SetMirrorName (buffer[TKO_Channel_Mirror]);
				}
				if ((channels & (1 << TKO_Channel_Transmission)) != 0) {
					if (HC_Compute_Color (buffer[TKO_Channel_Transmission], "rgb", rgb))
						complex->SetTransmission(rgb);
					else
						complex->SetTransmissionName (buffer[TKO_Channel_Transmission]);
				}
				if ((channels & (1 << TKO_Channel_Emission)) != 0) {
					if (HC_Compute_Color (buffer[TKO_Channel_Emission], "rgb", rgb))
						complex->SetEmission(rgb);
					else
						complex->SetEmissionName (buffer[TKO_Channel_Emission]);
				}

				if ((channels & (1 << TKO_Channel_Gloss)) != 0)
					complex->SetGloss( read_float (buffer[TKO_Channel_Gloss]) );
				if ((channels & (1 << TKO_Channel_Index)) != 0)
					complex->SetIndex( read_float (buffer[TKO_Channel_Index]) );

				if ((channels & (1 << TKO_Channel_Environment)) != 0)
					complex->SetEnvironmentName (buffer[TKO_Channel_Environment]);
				if ((channels & (1 << TKO_Channel_Bump)) != 0)
					complex->SetBumpName (buffer[TKO_Channel_Bump]);

				{
					char		newsysop[2048];

					sprintf (newsysop, "errors=(%s)", sysop);
					HC_Define_System_Options (newsysop);
				}
			}
		}

		if (*clr == ',')
			++clr;
	}

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}



// skip the name, then if an '=' or space skip it & then skip the first letter (always 'o')
// based on the next letter(s), clear & set appropriate mask/value bits
// if string is 'only', force indicates mask to set & bits to clear first

#define INTERPRET_VIS(name, bits, force) do {		\
			m_mask |= bits;							\
			vis += strlen (name);					\
			if (*vis == '=' || *vis == ' ') {		\
				vis += 2;							\
				if (*vis == 'n') {					\
					if (vis[1] == 'l') {			\
						m_mask |= force;			\
						m_value &= ~force;			\
						vis += 2;					\
					}								\
					m_value |= bits;				\
					++vis;							\
				}									\
				else								\
					vis += 2;						\
			}										\
			else if (vis[0] == 'o') {				\
				if (vis[1] == 'n') {				\
					m_value |= bits;				\
					vis += 2;						\
				}									\
				else {								\
					vis += 3;						\
				}									\
			}										\
			else if (set)							\
				m_value |= bits;					\
		} while (0)                                //




TK_Status HTK_Visibility::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            visibility[256];
	char const *    vis = visibility;

	HC_Show_Visibility (visibility);

	m_mask = m_value = 0;

	while (*vis) {
		bool		set = true;

		switch (*vis) {
			case 'o': {
				INTERPRET_VIS ("",                      TKO_Geo_All_Visibles, 0);
			}   break;

			case 'g': {
				INTERPRET_VIS ("geometry",              TKO_Geo_Geom_Visibles, 0);
			}   break;

			case 'p': {
				INTERPRET_VIS ("polygons",              TKO_Geo_Face | TKO_Geo_Edge_Visibles, 0);
			}   break;

			case 'f': {
				INTERPRET_VIS ("faces",                 TKO_Geo_Face, 0);
			}   break;

			case 'm': {
				if (vis[7] == ' ' && vis[8] == 'o')
					INTERPRET_VIS ("markers only",      TKO_Geo_Marker, 0);
				else
					INTERPRET_VIS ("markers",           TKO_Geo_Marker | TKO_Geo_Vertex_Vis, 0);
			}   break;

			case 'v': {
				INTERPRET_VIS ("vertices",              TKO_Geo_Vertex_Vis, 0);
			}   break;

			case 'i': {
				INTERPRET_VIS ("images",                TKO_Geo_Image, 0);
			}   break;

			case 'c': {
				if (vis[4] == 'i')
					INTERPRET_VIS ("cutting planes",    TKO_Geo_Cutting_Plane, 0);
				else if (vis[4] == 'e') // old hoops
					INTERPRET_VIS ("cut edges",         TKO_Geo_Cut_Edge, 0);
				else {
					bool        paren = false;

					vis += 13;  // strlen ("cut geometry=");

					if (*vis == '(') {
						paren = true;
						++vis;
					}

					while (*vis) {
						int     bits = 0;

						set = true;
						if (vis[0] == 'n' && vis[1] == 'o' && vis[2] == ' ') {
							set = false;
							vis += 3;   // strlen ("no ");
						}

						switch (*vis) {
							case 'o': {
								INTERPRET_VIS ("",      TKO_Geo_Cut_Geometry, 0);
							}   break;

							case 'f': {
								vis += 5;   // strlen ("faces");
								bits = TKO_Geo_Cut_Face;
							}   break;

							case 'e': {
								vis += 5;   // strlen ("edges");
								bits = TKO_Geo_Cut_Edge;
							}   break;

							default:
								return tk.Error("interpret parse error");
						}

						m_mask |= bits;
						if (set)
							m_value |= bits;

						if (*vis == ')') {
							++vis;
							break;
						}
						else if (*vis == ',') {
							if (paren)
								++vis;
							else
								break;
						}
					}
				}
			}   break;

			case 't': {
				INTERPRET_VIS ("text",                  TKO_Geo_Text, 0);
			}   break;

			case 'w': {
				INTERPRET_VIS ("windows",               TKO_Geo_Window, 0);
			}   break;

			case 'l': {
				if (vis[2] == 'n')
					INTERPRET_VIS ("lines",             TKO_Geo_Line, 0);
				else {  // lights
					bool        paren = false;

					vis += 7;   // strlen ("lights=");

					if (*vis == '(') {
						paren = true;
						++vis;
					}

					while (*vis) {
						int     bits = 0;

						set = true;
						if (vis[0] == 'n' && vis[1] == 'o' && vis[2] == ' ') {
							set = false;
							vis += 3;   // strlen ("no ");
						}

						switch (*vis) {
							case 'o': {
								INTERPRET_VIS ("",      TKO_Geo_Light_Visibles, 0);
							}   break;

							case 'f': {
								vis += 5;   // strlen ("faces");
								bits = TKO_Geo_Face_Lighting;
							}   break;

							case 'e': {
								vis += 5;   // strlen ("edges");
								bits = TKO_Geo_Edge_Lighting;
							}   break;

							case 'm': {
								vis += 7;   // strlen ("markers");
								bits = TKO_Geo_Marker_Lighting;
							}   break;

							default:
								return tk.Error("interpret parse error");
						}

						m_mask |= bits;
						if (set)
							m_value |= bits;

						if (*vis == ')') {
							++vis;
							break;
						}
						else if (*vis == ',') {
							if (paren)
								++vis;
							else
								break;
						}
					}
				}
			}   break;

			case 's': {
				if (vis[1] == 't')
					INTERPRET_VIS ("string cursors",    TKO_Geo_String_Cursor, 0);
				else {  // shadows
					bool        paren = false;

					vis += 8;   // strlen ("shadows=");

					if (*vis == '(') {
						paren = true;
						++vis;
					}

					while (*vis) {
						int     bits = 0;

						set = true;
						if (vis[0] == 'n' && vis[1] == 'o' && vis[2] == ' ') {
							set = false;
							vis += 3;   // strlen ("no ");
						}

						switch (*vis) {
							case 'o': {
								INTERPRET_VIS ("",      TKO_Geo_Shadow_Visibles, 0);
							}   break;

							case 'e': {
								vis += 8;   // strlen ("emitting");
								bits = TKO_Geo_Shadow_Emit;
							}   break;

							case 'c': {
								vis += 7;   // strlen ("casting");
								bits = TKO_Geo_Shadow_Cast;
							}   break;

							case 'r': {
								vis += 9;   // strlen ("receiving");
								bits = TKO_Geo_Shadow_Receive;
							}   break;

							default:
								return tk.Error("interpret parse error");
						}

						m_mask |= bits;
						if (set)
							m_value |= bits;

						if (*vis == ')') {
							++vis;
							break;
						}
						else if (*vis == ',') {
							if (paren)
								++vis;
							else
								break;
						}
					}
				}
			}   break;

			case 'e': {
				bool        paren = false;

				vis += 6;   // strlen ("edges=");

				if (*vis == '(') {
					paren = true;
					++vis;
				}

				while (*vis) {
					set = true;
					if (vis[0] == 'n' && vis[1] == 'o' && vis[2] == ' ') {
						set = false;
						vis += 3;   // strlen ("no ");
					}

					switch (*vis) {
						case 'o': {
							INTERPRET_VIS ("",                      TKO_Geo_Edge,               0);
						}   break;

						case 'e': {
							INTERPRET_VIS ("everything",			TKO_Geo_Edge_Visibles,		TKO_Geo_Edge_Visibles);
						}   break;

						case 'g': {
							INTERPRET_VIS ("generics",              TKO_Geo_Edge,               0);
						}   break;

						case 'i': {
							INTERPRET_VIS ("interior silhouettes",  TKO_Geo_Silhouette_Edge,    TKO_Geo_Edge_Visibles);
						}   break;

						case 'n': {
							INTERPRET_VIS ("nonculled",				TKO_Geo_NonCulled_Edge,     TKO_Geo_Edge_Visibles);
						}   break;

						case 'm': {
							INTERPRET_VIS ("mesh quads",            TKO_Geo_Mesh_Quad,          TKO_Geo_Edge_Visibles);
						}   break;

						case 'p': {
							INTERPRET_VIS ("perimeters",            TKO_Geo_Perimeter_Edge,     TKO_Geo_Edge_Visibles);
						}   break;

						case 'a': {
							INTERPRET_VIS ("adjacent",				TKO_Geo_Adjacent_Edge,		TKO_Geo_Edge_Visibles);
						}   break;

						case 'h': {
							INTERPRET_VIS ("hard",                  TKO_Geo_Hard_Edge,          TKO_Geo_Edge_Visibles);
						}   break;

						default:
							return tk.Error("interpret parse error");
					}

					if (*vis == ')') {
						++vis;
						break;
					}
					else if (*vis == ',') {
						if (paren)
							++vis;
						else
							break;
					}
				}
			}   break;

			default:
				return tk.Error("interpret parse error");
		}

		if (*vis == ',')
			++vis;
	}

	if ((m_mask & TKO_Geo_Extended2_Mask) != 0)
		m_mask |= TKO_Geo_Extended2;
	if ((m_mask & TKO_Geo_Extended_Mask) != 0)
		m_mask |= TKO_Geo_Extended;

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}



// skip the name, skip an '=', then process the value

#define INTERPRET_SEL(name, bits) do {                      \
			bool        looking = true;         \
			m_mask |= bits;                                 \
			sel += strlen (name);                           \
			++sel;                                          \
			while (looking) switch (*sel++) {               \
				case 'o':                                   \
					if (*sel++ == 'n')  m_down |= bits;     \
					else                ++sel;              \
					break;                                  \
				case 'v':   m_down      |= bits;    break;  \
				case '^':   m_up        |= bits;    break;  \
				case '*':   m_move_down |= bits;    break;  \
				case 'O':   m_move_up   |= bits;    break;  \
				case '!':   m_invisible |= bits;    break;  \
				default:                                    \
					looking = false;        break;          \
			}                                               \
			--sel;                                          \
		} while (0)                                        //




TK_Status HTK_Selectability::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            selectability[256];
	char const *    sel = selectability;

	HC_Show_Selectability (selectability);

	m_mask = m_down = m_up= m_move_down = m_move_up = m_invisible = 0;

	while (*sel) {
		switch (*sel) {
			case 'e': {
				if (sel[1] == 'v')
					INTERPRET_SEL ("everything",		TKO_Geo_All_Selects);
				else
					INTERPRET_SEL ("edges",				TKO_Geo_Edge);
			}   break;

			case 'g': {
				INTERPRET_SEL ("geometry",				TKO_Geo_Geom_Visibles);
			}   break;

			case 'p': {
				INTERPRET_SEL ("polygons",				TKO_Geo_Face | TKO_Geo_Edge);
			}   break;

			case 'f': {
				INTERPRET_SEL ("faces",					TKO_Geo_Face);
			}   break;

			case 'm': {
				if (sel[7] == ' ' && sel[8] == 'o')
					INTERPRET_SEL ("markers only",		TKO_Geo_Marker);
				else
					INTERPRET_SEL ("markers",			TKO_Geo_Marker | TKO_Geo_Vertex);
			}   break;

			case 'v': {
				INTERPRET_SEL ("vertices",				TKO_Geo_Vertex);
			}   break;

			case 'i': {
				if (sel[1] == 'm')
					INTERPRET_SEL ("images",			TKO_Geo_Image);
				else
					INTERPRET_SEL ("isolines",			TKO_Geo_Isoline);
			}   break;

			case 't': {
				INTERPRET_SEL ("text",					TKO_Geo_Text);
			}   break;

			case 'w': {
				INTERPRET_SEL ("windows",				TKO_Geo_Window);
			}   break;

			case 'l': {
				if (sel[2] == 'n')
					INTERPRET_SEL ("lines",				TKO_Geo_Line);
				else
					INTERPRET_SEL ("lights",			TKO_Geo_Light);
			}   break;

			case 's': {
				INTERPRET_SEL ("string cursors",		TKO_Geo_String_Cursor);
			}   break;

			default:
				return tk.Error("interpret parse error");
		}

		if (*sel == ',')
			++sel;
	}

	if ((m_mask & TKO_Geo_Extended_Mask) != 0)
		m_mask |= TKO_Geo_Extended;

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}



// skip the name, clear & set appropriate mask/value bits

#define INTERPRET_RENDO(name, bits) do {            \
			m_mask[0] |= (bits);                    \
			if (set)                                \
				m_value[0] |= (bits);               \
			rendo += strlen (name);                 \
		} while (0)                                //

#define INTERPRET_RENDO_EXTENDED(name, bits) do {   \
		m_mask[0] |= TKO_Rendo_Extended;	    \
			m_mask[1] |= (bits);                    \
			if (set)                                \
				m_value[1] |= (bits);               \
			rendo += strlen (name);                 \
		} while (0)                                //

#define INTERPRET_RENDO_EXTENDED2(name, bits) do {  \
		m_mask[0] |= TKO_Rendo_Extended;	        \
		m_mask[1] |= TKO_Rendo_Extended2;	        \
			m_mask[2] |= (bits);                    \
			if (set)                                \
				m_value[2] |= (bits);               \
			rendo += strlen (name);                 \
		} while (0)                                //

#define INTERPRET_LOCK(name, bits) do {             \
			m_lock_mask |= (bits);                  \
			if (set)                                \
				m_lock_value |= (bits);             \
			rendo += strlen (name);                 \
		} while (0)                                //

#define INTERPRET_COLOR_LOCK(name, bits) do {       \
			m_lock_color_mask |= (bits);            \
			if (set)                                \
				m_lock_color_value |= (bits);       \
			rendo += strlen (name);                 \
		} while (0)                                //

#define INTERPRET_VIS_LOCK(name, bits) do {         \
			m_lock_visibility_mask |= (bits);       \
			if (set)                                \
				m_lock_visibility_value |= (bits);  \
			rendo += strlen (name);                 \
		} while (0)                                //

#define INTERPRET_FORCED(name, bits) do {           \
			m_forced_mask |= (bits);                \
			if (set)                                \
				m_forced_value |= (bits);           \
			rendo += strlen (name);                 \
		} while (0)                                //

#define INTERPRET_COLOR_FORCED(name, bits) do {     \
			m_forced_color_mask |= (bits);          \
			if (set)                                \
				m_forced_color_value |= (bits);     \
			rendo += strlen (name);                 \
		} while (0)                                //

#define INTERPRET_VIS_FORCED(name, bits) do {       \
			m_forced_visibility_mask |= (bits);     \
			if (set)                                \
				m_forced_visibility_value |= (bits);\
			rendo += strlen (name);                 \
		} while (0)                                //

#define INTERPRET_REFLECTION_VIS(name, bits) do {				\
			m_simple_reflection_visibility_mask |= (bits);		\
			if (set)											\
				m_simple_reflection_visibility_value |= (bits);	\
			rendo += strlen (name);								\
		} while (0)											   //


#define RENDO_NOT_IMPLEMENTED(type) do {                            \
			dprintf ("%s not implemented, skipping...\n", type);    \
			SKIP_AHEAD(rendo);                                      \
		} while (0)                                                //

static char const * line_patterns[] = {
	"-", "-.", "- -", ".", "-..", "-...", "-- --", "center", "phantom", "finedot"
};
// older patterns do not need to mention any trailing patterns that are still the same
static char const * older_line_patterns[] = {
	"---", "-.-", "- -", "..."
};
static char const * numeric_line_patterns[] = {
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
};

TK_Status HTK_Rendering_Options::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            rendering_options[4096];
	char const *    rendo = rendering_options;

	HC_Show_Rendering_Options (rendering_options);

	m_mask[0] = m_mask[1] = m_mask[2] = m_value[0] = m_value[1] = m_value[2] = 0;
	m_hsr = m_tq = 0;
	m_lock_mask = m_lock_value = 0;
	m_lock_color_mask = m_lock_color_value = 0;
	m_lock_color_mask = m_lock_color_value = TKO_Geo_All_Colors;
	m_lock_color_face_mask = m_lock_color_face_value = 
	m_lock_color_edge_mask = m_lock_color_edge_value = 
	m_lock_color_line_mask = m_lock_color_line_value = 
	m_lock_color_marker_mask = m_lock_color_marker_value = 
	m_lock_color_text_mask = m_lock_color_text_value = 
	m_lock_color_window_mask = m_lock_color_window_value = 
	m_lock_color_face_contrast_mask = m_lock_color_face_contrast_value = 
	m_lock_color_window_contrast_mask = m_lock_color_window_contrast_value = 
	m_lock_color_back_mask = m_lock_color_back_value = 
	m_lock_color_vertex_mask = m_lock_color_vertex_value = 
	m_lock_color_edge_contrast_mask = m_lock_color_edge_contrast_value = 
	m_lock_color_line_contrast_mask = m_lock_color_line_contrast_value = 
	m_lock_color_marker_contrast_mask = m_lock_color_marker_contrast_value = 
	m_lock_color_vertex_contrast_mask = m_lock_color_vertex_contrast_value = 
	m_lock_color_text_contrast_mask = m_lock_color_text_contrast_value = 0;
	m_lock_color_simple_reflection_mask = m_lock_color_simple_reflection_value = 0;
	m_lock_color_cut_face_mask = m_lock_color_cut_face_value = 0;
	m_lock_color_cut_edge_mask = m_lock_color_cut_edge_value = 0;
	m_lock_visibility_mask = m_lock_visibility_value = 0;
	m_forced_mask = m_forced_value = 0;
	m_forced_color_mask = m_forced_color_value = 0;
	m_forced_color_mask = m_forced_color_value = TKO_Geo_All_Colors;
	m_forced_color_face_mask = m_forced_color_face_value = 
	m_forced_color_edge_mask = m_forced_color_edge_value = 
	m_forced_color_line_mask = m_forced_color_line_value = 
	m_forced_color_marker_mask = m_forced_color_marker_value = 
	m_forced_color_text_mask = m_forced_color_text_value = 
	m_forced_color_window_mask = m_forced_color_window_value = 
	m_forced_color_face_contrast_mask = m_forced_color_face_contrast_value = 
	m_forced_color_window_contrast_mask = m_forced_color_window_contrast_value = 
	m_forced_color_back_mask = m_forced_color_back_value = 
	m_forced_color_vertex_mask = m_forced_color_vertex_value = 
	m_forced_color_edge_contrast_mask = m_forced_color_edge_contrast_value = 
	m_forced_color_line_contrast_mask = m_forced_color_line_contrast_value = 
	m_forced_color_marker_contrast_mask = m_forced_color_marker_contrast_value = 
	m_forced_color_vertex_contrast_mask = m_forced_color_vertex_contrast_value = 
	m_forced_color_text_contrast_mask = m_forced_color_text_contrast_value = 0;
	m_forced_color_simple_reflection_mask = m_forced_color_simple_reflection_value = 0;
	m_forced_color_cut_face_mask = m_forced_color_cut_face_value = 0;
	m_forced_color_cut_edge_mask = m_forced_color_cut_edge_value = 0;
	m_forced_visibility_mask = m_forced_visibility_value = 0;
	m_tessellations = 0;
	m_mask_transform = 0;
	m_geometry_options = 0;
	m_transparency_options = 0;
	m_antialias = 0;
	m_dihedral = 0.0f;
	m_simple_reflection_visibility_mask = 0;
	m_simple_reflection_visibility_value = 0;
	m_contour_options = 0;
	m_isoline_options = 0;
	m_tint_options = 0;
	m_isoline_position_count = 0;
	m_isoline_color_count = 0;
	m_isoline_pattern_count = 0;
	m_isoline_weight_count = 0;

	while (*rendo) {
		bool            set = true;

		if (streqn (rendo, "no ", 3)) {
			set = false;
			rendo += 3; // strlen ("no ");
		}

		switch (*rendo) {
			case 'a': {
				if (rendo[1] == 'n') {      // anti-alias
					INTERPRET_RENDO_EXTENDED ("anti-alias",	TKO_Rendo_Antialias);
					if (set) {
						if (*rendo != '=')
							m_antialias = TKO_Antialias_All_On;
						else {
							bool        paren = false;

							++rendo;
							if (*rendo == '(') {
								paren = true;
								++rendo;
							}

							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								switch (*rendo) {
									case 's': {
										if (set)
											m_antialias |= TKO_Antialias_Screen_On;
										else
											m_antialias |= TKO_Antialias_Screen_Off;
										rendo += 6;	// strlen ("screen");
									}   break;

									case 'l': {
										if (set)
											m_antialias |= TKO_Antialias_Lines_On;
										else
											m_antialias |= TKO_Antialias_Lines_Off;
										rendo += 5;	// strlen ("lines");
									}   break;

									case 't': {
										if (set)
											m_antialias |= TKO_Antialias_Text_On;
										else
											m_antialias |= TKO_Antialias_Text_Off;
										rendo += 4;	// strlen ("text");
									}   break;

									case 'o': {		// "off" improperly generated in some cases
										m_antialias = 0;
										rendo += 3;	// strlen ("off");
									}   break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*rendo == ')') {
									if (paren)
										++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (paren)
										++rendo;
									else
										break;
								}
							}
						}
					}
				}
				else if (rendo[1] == 'm') {		// ambient up vector
					INTERPRET_RENDO_EXTENDED ("ambient up vector",	TKO_Rendo_Ambient_Up_Vector);
					if (set) {
						m_value[1] |= TKO_Rendo_Ambient_Up_Vector;
						rendo += 2; // strlen ("=(")
						m_ambient_up_vector[0] = read_float (rendo, &rendo);
						++rendo;	// strlen (",")
						m_ambient_up_vector[1] = read_float (rendo, &rendo);
						++rendo;	// strlen (",")
						m_ambient_up_vector[2] = read_float (rendo, &rendo);
						++rendo;	// strlen (")")
					}
				}
				else if (rendo[2] == 't') { // attribute lock
					INTERPRET_RENDO ("attribute lock",              TKO_Rendo_Attribute_Lock);

					if (set) {
						if (*rendo != '=') {
							m_lock_mask = m_lock_value = TKO_Lock_All;
							m_lock_color_mask = m_lock_color_value = TKO_Geo_All_Colors;
							m_lock_visibility_mask = m_lock_visibility_value = TKO_Geo_All_Visibles;
						}
						else {
							bool        paren = false;

							++rendo;
							if (*rendo == '(') {
								paren = true;
								++rendo;
							}

							m_lock_mask = m_lock_value = 0;
							m_lock_color_mask = m_lock_color_value = 0;
							m_lock_visibility_mask = m_lock_visibility_value = 0;
							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								switch (*rendo) {
									case 'c': {
										if (rendo[1] == 'a' && rendo[2] == 'm')
											INTERPRET_LOCK ("camera",               TKO_Lock_Camera);
										else if (rendo[1] == 'a' && rendo[2] == 'l')
											INTERPRET_LOCK ("callback",             TKO_Lock_Callback);
										else if (rendo[1] == 'l')
											SKIP_AHEAD(rendo);//INTERPRET_LOCK ("clip region",          TKO_Lock_Clip_Region);
										else if (rendo[5] == ' ' && rendo[6] == 'm')
											INTERPRET_LOCK ("color map",            TKO_Lock_Color_Map);
										else {
											INTERPRET_LOCK ("color",                TKO_Lock_Color);

											if (set) {
												if (*rendo != '=') {
													m_lock_color_mask = m_lock_color_value = TKO_Geo_All_Colors;
													m_lock_color_face_mask = m_lock_color_face_value = 
													m_lock_color_edge_mask = m_lock_color_edge_value = 
													m_lock_color_line_mask = m_lock_color_line_value = 
													m_lock_color_marker_mask = m_lock_color_marker_value = 
													m_lock_color_text_mask = m_lock_color_text_value = 
													m_lock_color_window_mask = m_lock_color_window_value = 
													m_lock_color_face_contrast_mask = m_lock_color_face_contrast_value = 
													m_lock_color_window_contrast_mask = m_lock_color_window_contrast_value = 
													m_lock_color_back_mask = m_lock_color_back_value = 
													m_lock_color_vertex_mask = m_lock_color_vertex_value = 
													m_lock_color_edge_contrast_mask = m_lock_color_edge_contrast_value = 
													m_lock_color_line_contrast_mask = m_lock_color_line_contrast_value = 
													m_lock_color_marker_contrast_mask = m_lock_color_marker_contrast_value = 
													m_lock_color_vertex_contrast_mask = m_lock_color_vertex_contrast_value = 
													m_lock_color_text_contrast_mask = m_lock_color_text_contrast_value = 
													m_lock_color_simple_reflection_mask = m_lock_color_simple_reflection_value = 
													m_lock_color_cut_face_mask = m_lock_color_cut_face_value = 
													m_lock_color_cut_edge_mask = m_lock_color_cut_edge_value = 
													TKO_Lock_Channel_ALL;
												}
												else {
													bool        cparen = false;

													++rendo;
													if (*rendo == '(') {
														cparen = true;
														++rendo;
													}

													while (*rendo) {
														int	    which = 0;

														set = true;

														if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
															set = false;
															rendo += 3; // strlen ("no ");
														}

														switch (*rendo) {
															case 'a': {
																rendo += 7;	// strlen ("ambient");
																if (*rendo == ' ') {
																	++rendo;
																	if (*rendo == 'u')
																		INTERPRET_COLOR_LOCK ("up",		TKO_Geo_Ambient_Up);
																	else
																		INTERPRET_COLOR_LOCK ("down",	TKO_Geo_Ambient_Down);
																}
																else
																	INTERPRET_COLOR_LOCK ("ambient",	TKO_Geo_Ambient);
															}   break;

															case 'b': {
																rendo += 4; // strlen ("back");

																if (rendo[0] == ' ' && rendo[1] == 'c') {
																	rendo += 9;		// strlen (" contrast");
																	//which = TKO_Geo_Back_Contrast;
																}
																else
																	which = TKO_Geo_Back;
															}   break;

															case 'c': {
																if (rendo[4] == 'g') {
																	rendo += 12; // strlen ("cut geometry");
																	if (rendo[0] == ' ' && rendo[1] == 'c') {
																		rendo += 9;	// strlen (" contrast");
																		//which = TKO_Geo_Cut_Geometry_Contrast;
																	}
																	else
																		which = TKO_Geo_Cut_Geometry;
																}
																else if (rendo[4] == 'f') {
																	rendo += 8;	// strlen ("cut face");
																	if (rendo[0] == ' ' && rendo[1] == 'c') {
																		rendo += 9;	// strlen (" contrast");
																		//which = TKO_Geo_Cut_Face_Contrast;
																	}
																	else
																		which = TKO_Geo_Cut_Face;
																}
																else {
																	rendo += 8; // strlen ("cut edge");
																	if (rendo[0] == ' ' && rendo[1] == 'c') {
																		rendo += 9;	// strlen (" contrast");
																		//which = TKO_Geo_Cut_Edge_Contrast;
																	}
																	else
																		which = TKO_Geo_Cut_Edge;
																}
															}   break;

															case 'e': {
																if (rendo[4] == ' ' && rendo[5] == 'c') {
																	which = TKO_Geo_Edge_Contrast;
																	rendo += 13; // strlen ("edge contrast");
																	m_lock_color_edge_contrast_mask = 0;
																}
																else {
																	which = TKO_Geo_Edge;
																	rendo += 4; // strlen ("edge");
																}
															}   break;

															case 'f': {
																if (rendo[1] == 'r') {
																	rendo += 5; // strlen ("front");

																	if (rendo[0] == ' ' && rendo[1] == 'c') {
																		rendo += 9;	// strlen (" contrast");
																		which = TKO_Geo_Face_Contrast;	///
																	}
																	else
																		which = TKO_Geo_Front;
																}
																else {
																	rendo += 4;	// strlen ("dace");
																	if (rendo[0] == ' ' && rendo[1] == 'c') {
																		which = TKO_Geo_Face_Contrast;
																		rendo += 9; // strlen (" contrast");
																	}
																	else
																		which = TKO_Geo_Face;
																}
															}   break;

															case 'g': {
																which = TKO_Geo_Geom_Colors;
																rendo += 8; // strlen ("geometry");
															}   break;

															case 'l': {
																if (rendo[2] == 'g')
																	INTERPRET_COLOR_LOCK ("lighting",TKO_Geo_Light_Visibles);
																else if (rendo[4] == ' ' && rendo[5] == 'c') {
																	which = TKO_Geo_Line_Contrast;
																	rendo += 13; // strlen ("line contrast");
																}
																else {
																	which = TKO_Geo_Line;
																	rendo += 4; // strlen ("line");
																}
															}   break;

															case 'm': {
																if (rendo[6] == ' ' && rendo[7] == 'o') {
																	which = TKO_Geo_Marker;
																	rendo += 11; //strlen ("marker only");
																}
																else if (rendo[6] == ' ' && rendo[7] == 'c') {
																	which = TKO_Geo_Marker_Contrast;
																	rendo += 15; //strlen ("marker contrast");
																}
																else {
																	which = TKO_Geo_Marker | TKO_Geo_Vertex;
																	rendo += 6; //strlen ("marker");
																}
															}   break;

															case 'v': {
																if (rendo[6] == ' ' && rendo[7] == 'c') {
																	which = TKO_Geo_Vertex_Contrast;
																	rendo += 15; //strlen ("vertex contrast");
																}
																else {
																	which = TKO_Geo_Vertex;
																	rendo += 6; //strlen ("vertex");
																}
															}   break;

															case 'p': {
																which = TKO_Geo_Face | TKO_Geo_Edge;
																rendo += 7; //strlen ("polygon");
															}   break;

															case 's': {
																which = TKO_Geo_Simple_Reflection;
																rendo += 17; //strlen ("simple reflection");
															}   break;

															case 't': {
																if (rendo[4] == ' ' && rendo[5] == 'c') {
																	which = TKO_Geo_Text_Contrast;
																	rendo += 13; //strlen ("text contrast");
																}
																else {
																	which = TKO_Geo_Text;
																	rendo += 4; //strlen ("text");
																}
															}   break;

															case 'w': {
																if (rendo[6] == ' ' && rendo[7] == 'c') {
																	which = TKO_Geo_Window_Contrast;
																	rendo += 15; //strlen ("window contrast");
																}
																else {
																	which = TKO_Geo_Window;
																	rendo += 6; //strlen ("window");
																}
															}   break;

															default:
																return tk.Error("interpret parse error");
														}

														if (which) {
															int	    channel_bits = 0;
															int	    keep_bits = ~0;
															int	    set_bits = 0;

															m_lock_color_mask |= which;

															if (set) {
																m_lock_color_value |= which;

																if (*rendo != '=') {
																	channel_bits = ~0;
																	keep_bits = ~0;
																	set_bits = ~0;
																}
																else {
																	bool        chparen = false;

																	++rendo;
																	if (*rendo == '(') {
																		chparen = true;
																		++rendo;
																	}

																	while (*rendo) {
																		int		channel;

																		set = true;

																		if (rendo[0] == 'n' && rendo[1] == 'o' &&
																			rendo[2] == ' ') {
																			set = false;
																			rendo += 3; // strlen ("no ");
																		}

																		switch (*rendo) {
																			case 'b':
																				channel = TKO_Lock_Channel_Bump;
																				rendo += 4; // strlen ("bump");
																			break;

																			case 'd':
																				channel = TKO_Lock_Channel_Diffuse;
																				rendo += 7; // strlen ("diffuse");
																			break;

																			case 'e':
																				if (rendo[1] == 'm') {
																					channel = TKO_Lock_Channel_Emission;
																					rendo += 8; // strlen ("emission");
																				}
																				else {
																					channel = TKO_Lock_Channel_Environment;
																					rendo += 11; // strlen ("environment");
																				}
																			break;

																			case 'g':
																				channel = TKO_Lock_Channel_Gloss;
																				rendo += 5; // strlen ("gloss");
																			break;

																			case 'i':
																				channel = TKO_Lock_Channel_Index;
																				rendo += 5; // strlen ("index");
																			break;

																			case 'm':
																				channel = TKO_Lock_Channel_Mirror;
																				rendo += 6; // strlen ("mirror");
																			break;

																			case 's':
																				channel = TKO_Lock_Channel_Specular;
																				rendo += 8; // strlen ("specular");
																			break;

																			case 't':
																				channel = TKO_Lock_Channel_Transmission;
																				rendo += 12; // strlen ("transmission");
																			break;

																			default:
																				return tk.Error("interpret parse error");
																		}

																		channel_bits |= channel;
																		if (set)
																			set_bits |= channel;
																		else
																			keep_bits &= ~channel;


																		if (*rendo == ')') {
																			if (chparen)
																				++rendo;
																			break;
																		}
																		else if (*rendo == ',') {
																			if (chparen)
																				++rendo;
																			else
																				break;
																		}
																	}
																}
															}
															else {
																m_lock_color_value &= ~which;

																channel_bits = ~0;
																keep_bits = 0;
																set_bits = 0;
															}



#define PROCESS_CHANNELS(_w_,field)			    \
		do if ((which & _w_) != 0) {		    \
		m_lock_color_##field##_mask = (short)channel_bits; \
		m_lock_color_##field##_value = (short)set_bits;   \
		} while (0)					   //

															PROCESS_CHANNELS (TKO_Geo_Face,   face);
															PROCESS_CHANNELS (TKO_Geo_Face,   back);

															PROCESS_CHANNELS (TKO_Geo_Front,  face);
															PROCESS_CHANNELS (TKO_Geo_Back,   back);
															PROCESS_CHANNELS (TKO_Geo_Edge,   edge);
															PROCESS_CHANNELS (TKO_Geo_Line,   line);
															PROCESS_CHANNELS (TKO_Geo_Text,   text);
															PROCESS_CHANNELS (TKO_Geo_Marker, marker);
															PROCESS_CHANNELS (TKO_Geo_Vertex, vertex);
															PROCESS_CHANNELS (TKO_Geo_Window, window);
															PROCESS_CHANNELS (TKO_Geo_Face_Contrast,   face_contrast);
															PROCESS_CHANNELS (TKO_Geo_Edge_Contrast,   edge_contrast);
															PROCESS_CHANNELS (TKO_Geo_Line_Contrast,   line_contrast);
															PROCESS_CHANNELS (TKO_Geo_Text_Contrast,   text_contrast);
															PROCESS_CHANNELS (TKO_Geo_Marker_Contrast, marker_contrast);
															PROCESS_CHANNELS (TKO_Geo_Vertex_Contrast, vertex_contrast);
															PROCESS_CHANNELS (TKO_Geo_Window_Contrast, window_contrast);
															PROCESS_CHANNELS (TKO_Geo_Simple_Reflection, simple_reflection);
															PROCESS_CHANNELS (TKO_Geo_Cut_Face, cut_face);
															PROCESS_CHANNELS (TKO_Geo_Cut_Edge, cut_edge);
														}

														else if (*rendo == '=')
															SKIP_AHEAD (rendo);

														if (*rendo == ')') {
															if (cparen)
																++rendo;
															break;
														}
														else if (*rendo == ',') {
															if (cparen)
																++rendo;
															else
																break;
														}
													}
												}
											}
										}
									}   break;

									case 'd': {
										if (rendo[6] == ' ' && rendo[7] == 'o')
											INTERPRET_LOCK ("driver options",   TKO_Lock_Driver_Options);
										else
											INTERPRET_LOCK ("driver",           TKO_Lock_Driver);
									}   break;

									case 'e': {
										if (rendo[5] == 'p')
											INTERPRET_LOCK ("edge pattern",     TKO_Lock_Edge_Pattern);
										else
											INTERPRET_LOCK ("edge weight",      TKO_Lock_Edge_Weight);
									}   break;

									case 'f': {
										INTERPRET_LOCK ("face pattern",         TKO_Lock_Face_Pattern);
									}   break;

									case 'h': {
										if (rendo[1] == 'a')
											INTERPRET_LOCK ("handedness",       TKO_Lock_Handedness);
										else
											INTERPRET_LOCK ("heuristics",       TKO_Lock_Heuristics);
									}   break;

									case 'l': {
										if (rendo[5] == 'p')
											INTERPRET_LOCK ("line pattern",     TKO_Lock_Line_Pattern);
										else
											INTERPRET_LOCK ("line weight",      TKO_Lock_Line_Weight);
									}   break;

									case 'm': {
										if (rendo[1] == 'o')
											INTERPRET_LOCK ("modelling matrix", TKO_Lock_Modelling_Matrix);
										else if (rendo[1] == 'e')
											INTERPRET_LOCK ("metafile",         TKO_Lock_Metafile);
										else if (rendo[8] == 'i')
											INTERPRET_LOCK ("marker size",      TKO_Lock_Marker_Size);
										else
											INTERPRET_LOCK ("marker symbol",    TKO_Lock_Marker_Symbol);
									}   break;

									case 'r': {
										INTERPRET_LOCK ("rendering options",    TKO_Lock_Rendering_Options);
									}   break;

									case 's': {
										if (rendo[1] == 'e')
											INTERPRET_LOCK ("selectability",    TKO_Lock_Selectability);
										else
											INTERPRET_LOCK ("style",            TKO_Lock_Styles);
									}   break;

									case 't': {
										if (rendo[5] == 'a')
											INTERPRET_LOCK ("text alignment",       TKO_Lock_Text_Alignment);
										else if (rendo[5] == 'f')
											INTERPRET_LOCK ("text font",            TKO_Lock_Text_Font);
										else if (rendo[5] == 'p')
											INTERPRET_LOCK ("text path",            TKO_Lock_Text_Path);
										else if (rendo[5] == 's')
											INTERPRET_LOCK ("text spacing",         TKO_Lock_Text_Spacing);
										else
											INTERPRET_LOCK ("texture matrix",       TKO_Lock_Texture_Matrix);
									}   break;

									case 'u': {
										if (rendo[5] == 'o')
											INTERPRET_LOCK ("user options",     TKO_Lock_User_Options);
										else
											INTERPRET_LOCK ("user value",       TKO_Lock_User_Value);
									}   break;

									case 'v': {
										INTERPRET_LOCK ("visibility",           TKO_Lock_Visibility);

										if (set) {
											if (*rendo != '=') {
												m_lock_visibility_mask = m_lock_visibility_value = TKO_Geo_All_Visibles;
											}
											else {
												bool        vparen = false;

												++rendo;
												if (*rendo == '(') {
													vparen = true;
													++rendo;
												}

												while (*rendo) {
													set = true;

													if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
														set = false;
														rendo += 3; // strlen ("no ");
													}

													switch (*rendo) {
														case 'c': {
															if (rendo[3] == 't')
																INTERPRET_VIS_LOCK ("cutting plane",	TKO_Geo_Cutting_Plane);
															else
																INTERPRET_VIS_LOCK ("cut geometry",		TKO_Geo_Cut_Geometry);
														}   break;

														case 'e': {
															INTERPRET_VIS_LOCK ("edge",         TKO_Geo_Edge);
														}   break;

														case 'f': {
															INTERPRET_VIS_LOCK ("face",         TKO_Geo_Face);
														}   break;

														case 'g': {
															INTERPRET_VIS_LOCK ("geometry",     TKO_Geo_Geom_Visibles);
														}   break;

														case 'i': {
															INTERPRET_VIS_LOCK ("image",        TKO_Geo_Image);
														}   break;

														case 'l': {
															if (rendo[2] == 'g')
																INTERPRET_VIS_LOCK ("lighting", TKO_Geo_Light_Visibles);
															else
																INTERPRET_VIS_LOCK ("line",     TKO_Geo_Line);
														}   break;

														case 'm': {
															if (rendo[6] == ' ' && rendo[7] == 'o')
																INTERPRET_VIS_LOCK ("marker only",  TKO_Geo_Marker);
															else
																INTERPRET_VIS_LOCK ("marker",       TKO_Geo_Marker | TKO_Geo_Vertex_Vis);
														}   break;

														case 'v': {
															INTERPRET_VIS_LOCK ("vertex",       TKO_Geo_Vertex_Vis);
														}   break;

														case 'p': {
															INTERPRET_VIS_LOCK ("polygon",      TKO_Geo_Face | TKO_Geo_Edge);
														}   break;

														case 's': {
															if (rendo[1] == 'h')
																INTERPRET_VIS_LOCK ("shadows",  TKO_Geo_Shadow_Visibles);
															else
																INTERPRET_VIS_LOCK ("string cursor",
																								TKO_Geo_String_Cursor);
														}   break;

														case 't': {
															INTERPRET_VIS_LOCK ("text",         TKO_Geo_Text);
														}   break;

														case 'w': {
															INTERPRET_VIS_LOCK ("window",       TKO_Geo_Window);
														}   break;

														default:
															return tk.Error("interpret parse error");
													}

													if (*rendo == ')') {
														if (vparen)
															++rendo;
														break;
													}
													else if (*rendo == ',') {
														if (vparen)
															++rendo;
														else
															break;
													}
												}
											}
										}
									}   break;

									case 'w': {
										if (rendo[6] == ' ' && rendo[7] == 'f')
											INTERPRET_LOCK ("window frame",     TKO_Lock_Window_Frame);
										else if (rendo[6] == ' ' && rendo[7] == 'p')
											INTERPRET_LOCK ("window pattern",   TKO_Lock_Window_Pattern);
										else
											INTERPRET_LOCK ("window",           TKO_Lock_Window);
									}   break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*rendo == ')') {
									++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (paren)
										++rendo;
									else
										break;
								}
							}
						}
					}
				}
				else {                  // atmospheric attenuation
					INTERPRET_RENDO ("atmospheric attenuation",     TKO_Rendo_Fog);

					if (set) {
						rendo += 9; // strlen ("=(hither=");
						m_fog_limits[0] = read_float (rendo, &rendo);
						rendo += 5; // strlen (",yon=");
						m_fog_limits[1] = read_float (rendo, &rendo);
						++rendo;    // ')'
					}
				}
			}   break;

			case 'c': {
				if (rendo[1] == 'u') {         // cut geometry options
					INTERPRET_RENDO_EXTENDED ("cut geometry options",	TKO_Rendo_Cut_Geometry);

					if (set) {  // should be...
						bool        paren = false;

						++rendo;    // '='

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						m_cut_geometry = 0;
						while (*rendo) {
							set = true;

							if (streqn (rendo, "no ", 3)) {
								set = false;
								rendo += 3; // strlen ("no ");
							}

							switch (*rendo) {
								case 'l': {
									m_cut_geometry |= TKO_Cut_Geometry_Level;
									rendo += 6;     // strlen ("level=");

									if (streqn (rendo, "segment tree", 12))
										m_cut_geometry_level = TKO_Cut_Geometry_Level_Segment_Tree;
									else if (streqn (rendo, "segment", 7))
										m_cut_geometry_level = TKO_Cut_Geometry_Level_Segment;
									else if (streqn (rendo, "entity", 6))
										m_cut_geometry_level = TKO_Cut_Geometry_Level_Entity;
									else
										return tk.Error("unknown cut geometry level");
									SKIP_AHEAD (rendo);
								}   break;

								case 'm': {
									rendo += 11;    // strlen ("match color");
									m_cut_geometry |= TKO_Cut_Geometry_Match_Color;
									if (set) {
										m_cut_geometry_match = TKO_Cut_Geometry_Match_Color_Current;
										if (*rendo == '=') {
											++rendo;
											if (*rendo == 'f') {
												rendo += 5; // strlen ("first");
												m_cut_geometry_match = TKO_Cut_Geometry_Match_Color_First;
											}
											else {
												rendo += 4; // strlen ("last");
												m_cut_geometry_match = TKO_Cut_Geometry_Match_Color_Last;
											}
										}
									}
									else
										m_cut_geometry_match = TKO_Cut_Geometry_Match_Color_Off;
								}   break;

								case 't': {
									m_cut_geometry |= TKO_Cut_Geometry_Tolerance;
									rendo += 10;    // strlen ("tolerance=");
									m_cut_geometry_tolerance = read_float (rendo, &rendo);
									if (*rendo == '%') {
										m_cut_geometry_tolerance = -m_cut_geometry_tolerance;
										++rendo;
									}
								}   break;

								default:
									return tk.Error("unknown cut geometry option");
							}

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}
					}
				}
				else if (rendo[8] == 't') {     // color interpolation
					// Not this way, it sets all bits even if we have a single option
					//INTERPRET_RENDO ("color interpolation",         TKO_Interp_Color);
					rendo += 19;	//strlen ("color interpolation");

					if (set) {
						bool        paren = false;

						if (*rendo == '=') {
							++rendo;    // '='

							if (*rendo == '(') {
								paren = true;
								++rendo;
							}

							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								switch (*rendo) {
									case 'f': {
										INTERPRET_RENDO ("faces",       TKO_Interp_Color_Faces);
									}   break;

									case 'e': {
										INTERPRET_RENDO ("edges",       TKO_Interp_Color_Edges);
									}   break;

									case 'm': {
										INTERPRET_RENDO ("markers",     TKO_Interp_Color_Markers);
									}   break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*rendo == ')') {
									++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (paren)
										++rendo;
									else
										break;
								}
							}
						}
						else {
							m_mask[0] |= TKO_Interp_Color;
							m_value[0] |= TKO_Interp_Color;
						}
					}
					else {
						m_mask[0] |= TKO_Interp_Color;
					}
				}
				else {                          // color index interpolation [options]
					// Not this way, it sets all bits even if we have a single option
					//INTERPRET_RENDO ("color index interpolation",   TKO_Interp_Index_FE);
					rendo += 25;	//strlen ("color index interpolation");

					if (*rendo == ' ') {     // color index interpolation options
						bool        paren = false;

						m_mask[2] |= TKO_Rendo_Contour_Options;
						m_value[2] |= TKO_Rendo_Contour_Options;
						rendo += 9;	//strlen (" options=");

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						while (*rendo) {
							set = true;

							if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
								set = false;
								rendo += 3; // strlen ("no ");
							}

							switch (*rendo) {
								case 'v': {
									if (rendo[1] == 'a') {	// value adjustment
										m_contour_options |= TKO_Contour_Value_Adjustment;
										rendo += 17;	// strlen ("value adjustment=");

										if (*rendo == 'n') {
											if (rendo[2] == 'n') {
												m_contour_value_adjustment = TKO_Contour_Adjustment_None;
												rendo += 4;		// strlen ("none");
											}
											else {
												m_contour_value_adjustment = TKO_Contour_Adjustment_Normalized;
												rendo += 10;		// strlen ("normalized");
											}
										}
										else {
											m_contour_value_adjustment = TKO_Contour_Adjustment_Explicit;
											rendo += 16;	// strlen ("explicit=(scale=");
											m_contour_value_scale = read_float (rendo, &rendo);
											rendo += 11;	// strlen (",translate=");
											m_contour_value_translate = read_float (rendo, &rendo);
											rendo++;		// ')'
										}
									}
									else {					// visibility
										//bool        vparen = false;

										rendo += 10;	// strlen ("visibility");

										if (set)
											m_contour_options |= TKO_Contour_Face_Visibility_On;
										else
											m_contour_options |= TKO_Contour_Face_Visibility_Off;

#if 0
										if (*rendo == '(') {
											vparen = true;
											++rendo;
										}

										while (*rendo) {
											set = true;

											if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
												set = false;
												rendo += 3; // strlen ("no ");
											}

											switch (*rendo) {
												case 'f': {
													rendo += 5;		// strlen ("faces");
													if (set)
														m_contour_options |= TKO_Contour_Face_Visibility_On;
													else
														m_contour_options |= TKO_Contour_Face_Visibility_Off;
												}	break;

												case 'i': {
													rendo += 8;		// strlen ("isolines");
													if (set)
														m_contour_options |= TKO_Contour_Isoline_Visibility_On;
													else
														m_contour_options |= TKO_Contour_Isoline_Visibility_Off;
												}	break;

												default:
													return tk.Error("unknown contour visibility option");
											}

											if (*rendo == ')') {
												++rendo;
												break;
											}
											else if (*rendo == ',') {
												if (vparen)
													++rendo;
												else
													break;
											}
										}
#endif
									}
								}	break;

								default:
									return tk.Error("unknown contour option");
							}

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}
					}
					else if (set) {		// color index interpolation
						bool        paren = false;

						if (*rendo == '=') {
							++rendo;    // '='

							if (*rendo == '(') {
								paren = true;
								++rendo;
							}

							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								switch (*rendo) {
									case 'f': {
										INTERPRET_RENDO ("faces",       TKO_Interp_Index_Faces);
									}   break;

									case 'e': {
										INTERPRET_RENDO ("edges",       TKO_Interp_Index_Edges);
									}   break;

									case 'm': {
										INTERPRET_RENDO_EXTENDED ("markers",	TKO_Interp_Index_Markers);
									}   break;

									case 'i': {
										INTERPRET_RENDO_EXTENDED ("isolines",	TKO_Interp_Index_Face_Isolines);
									}   break;

									case 'o': {
										if (rendo[1] == 'n') {
											INTERPRET_RENDO ("on",       TKO_Interp_Index_FE);
											m_mask[1] |= TKO_Interp_Index_Markers;
											m_value[1] |= TKO_Interp_Index_Markers;
										}
										else {
											set = false;
											INTERPRET_RENDO ("off",      TKO_Interp_Index_FE);
											m_mask[1] |= TKO_Interp_Index_Markers;
										}
									}   break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*rendo == ')') {
									++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (paren)
										++rendo;
									else
										break;
								}
							}
						}
						else {
							m_mask[0] |= TKO_Interp_Index_FE;
							m_mask[1] |= TKO_Interp_Index_Markers;
							m_value[0] |= TKO_Interp_Index_FE;
							m_value[1] |= TKO_Interp_Index_Markers;
						}
					}
					else {
						m_mask[0] |= TKO_Interp_Index_FE;
						m_mask[1] |= TKO_Interp_Index_Markers;
					}
				}
			}   break;

			case 'd': {
				if (rendo[2] == 'b') {  // debug
					INTERPRET_RENDO ("debug",               TKO_Rendo_Debug);

					if (set) {
						rendo++;    // '='
						READ_INT (m_debug, rendo);
					}
				}
				else if (rendo[2] == 'p') {  // depth range
					INTERPRET_RENDO_EXTENDED ("depth range",	TKO_Rendo_Depth_Range);

					if (set) {
						rendo += 2; // strlen ("=(");
						m_depth_range[0] = read_float (rendo, &rendo);
						++rendo;    // ','
						m_depth_range[1] = read_float (rendo, &rendo);
						++rendo;    // ')'
					}
				}
				else if (rendo[2] == 'f') {
					if (rendo[8] == 't') {
						INTERPRET_RENDO_EXTENDED2 ("diffuse texture tint",    TKO_Rendo_Diffuse_Texture_Tint);

						char		string[256];
						char *		sp = string;
						char        sysop[2048];

						rendo++; 

						if (*rendo == '\'') {
							++rendo;    // initial '
							do *sp++ = *rendo++;
							while (*rendo != '\'');
								++rendo;    // final '
							*sp = '\0';
						}
						else {
							do *sp++ = *rendo++;
							while (*rendo != ',' && *rendo != ')');
							*sp = '\0';
						}

						// should be a valid color, but guard just in case...
						HC_Show_One_System_Option ("errors", sysop);
						HC_Define_System_Options ("no errors");

						HC_Compute_Color (string, "rgb", m_texture_tint_color);

						{
							char		newsysop[2048];

							sprintf (newsysop, "errors=(%s)", sysop);
							HC_Define_System_Options (newsysop);
						}
					}
					else {		// diffuse color tint
						bool        paren = false;

						m_mask[2] |= TKO_Rendo_Diffuse_Color_Tint;
						m_value[2] |= TKO_Rendo_Diffuse_Color_Tint;
						rendo += 19;	//strlen ("diffuse color tint=");

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						while (*rendo) {
							set = true;

							if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
								set = false;
								rendo += 3; // strlen ("no ");
							}

							switch (*rendo) {
								case 'c': {
									m_tint_options |= TKO_Tint_Color;
									rendo += 6;	// strlen ("color=");

									rendo += 2;	// strlen ("R=");
									m_tint_color[0] = read_float (rendo, &rendo);
									rendo += 3;	// strlen (" G=");
									m_tint_color[1] = read_float (rendo, &rendo);
									rendo += 3;	// strlen (" B=");
									m_tint_color[2] = read_float (rendo, &rendo);
								}	break;

								case 'e': {
									m_tint_options |= TKO_Tint_Effect;
									rendo += 7;	// strlen ("effect=");

									switch (*rendo) {
										case 'g': {
											rendo += 9;			// strlen ("grayscale");
											m_tint_effect = TKO_Tint_Effect_Grayscale;
										}	break;
										case 'm': {
											rendo += 8;			// strlen ("modulate");
											if (*rendo == ' ') {
												rendo += 10;	// strlen (" grayscale");
												m_tint_effect = TKO_Tint_Effect_Modulate_Gray;
											}
											else
												m_tint_effect = TKO_Tint_Effect_Modulate;
										}	break;
										case 't': {
											rendo += 4;			// strlen ("tone");
											m_tint_effect = TKO_Tint_Effect_Tone;
										}	break;
									}
								}	break;

								case 'o': {
									if (rendo[1] == 'n') {
										m_tint_options |= TKO_Tint_On;
										rendo += 2;	// strlen ("on");
									}
									else {
										m_tint_options |= TKO_Tint_Off;
										rendo += 3;	// strlen ("off");
									}
								}	break;

								case 'r': {
									m_tint_options |= TKO_Tint_Range;
									rendo += 7; // strlen ("range=(");
									m_tint_range[0] = read_float (rendo, &rendo);
									++rendo;	// ','
									m_tint_range[1] = read_float (rendo, &rendo);
									++rendo;    // ')'
								}	break;
							}

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}
					}
				}
				else {                  // display lists
					INTERPRET_RENDO ("display lists",           TKO_Rendo_Display_Lists);

					if (set) {
						if (*rendo == '=') {	// "=segment" or "=segment tree"
							rendo += 8;	// strlen ("=segment");

							if (*rendo == ' ') {
								rendo += 5;	// strlen (" tree");
								m_display_list_level = TKO_Display_List_Level_Segment_Tree;
							}
							else
								m_display_list_level = TKO_Display_List_Level_Segment;
						}
						else
							m_display_list_level = TKO_Display_List_Level_Entity;
					}
				}
			}   break;

			case 'f': {
				if (rendo[1] == 'a') {	// face displacement
					INTERPRET_RENDO ("face displacement",           TKO_Rendo_Face_Displacement);

					if (set) {
						rendo++;    // '='
						READ_INT (m_face_displacement, rendo);
					}
				}
				else if (rendo[1] == 'o') {					// force grayscale
					INTERPRET_RENDO_EXTENDED ("force grayscale",	TKO_Rendo_Force_Grayscale);
				}
				else {
					INTERPRET_RENDO_EXTENDED2 ("frame buffer effects",	TKO_Rendo_Frame_Buffer_Effects);
				}
			}   break;

			case 'g': {
				if (rendo[1] == 'e') {
					if (rendo[2] == 'o') { // geometry options
						INTERPRET_RENDO_EXTENDED ("geometry options",	TKO_Rendo_Geometry_Options);

						if (set) {
							bool        paren = false;

							rendo++;    // '='

							if (*rendo == '(') {
								paren = true;
								++rendo;
							}

							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								switch (*rendo) {
									case 'h': {
										rendo += 16;	// strlen ("hard edge angle=");
										m_geometry_options |= TKO_Geometry_Options_Dihedral;
										m_dihedral = read_float (rendo, &rendo);
									}   break;

									case 'i': {
										rendo += 20;	// strlen ("invert polycylinders");
										if (set) {
											if (*rendo != '=') {
												m_geometry_options |= TKO_Geometry_Options_Reverse_PolyCylinder_Radii |
																	  TKO_Geometry_Options_Reverse_PolyCylinder_Colors;
											}
											else {
												bool        iparen = false;

												rendo++;    // '='

												if (*rendo == '(') {
													iparen = true;
													++rendo;
												}

												while (*rendo) {
													set = true;

													if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
														set = false;
														rendo += 3; // strlen ("no ");
													}

													if (*rendo == 'r') {
														rendo += 5;	// strlen ("radii");
														if (set)
															m_geometry_options |= TKO_Geometry_Options_Reverse_PolyCylinder_Radii;
														else
															m_geometry_options |= TKO_Geometry_Options_No_Reverse_PolyCylinder_Radii;
													}
													else if (*rendo == 'c') {
														rendo += 6;	// strlen ("colors");
														if (set)
															m_geometry_options |= TKO_Geometry_Options_Reverse_PolyCylinder_Colors;
														else
															m_geometry_options |= TKO_Geometry_Options_No_Reverse_PolyCylinder_Colors;
													}

													if (*rendo == ')') {
														if (iparen)
															++rendo;
														break;
													}
													else if (*rendo == ',') {
														if (iparen)
															++rendo;
														else
															break;
													}
												}
											}
										}
										else
											m_geometry_options |= TKO_Geometry_Options_No_Reverse_PolyCylinder_Radii |
																  TKO_Geometry_Options_No_Reverse_PolyCylinder_Colors;
									}   break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*rendo == ')') {
									++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (paren)
										++rendo;
									else
										break;
								}
							}
						}
					}
					else if (rendo[8] == 'd') { // general displacement
						INTERPRET_RENDO_EXTENDED ("general displacement",    TKO_Rendo_General_Displacement);

						if (set) {
							rendo++;    // '='
							READ_INT (m_general_displacement, rendo);
						}
					}
					else {						// general curve (aka nurbs curve)
						INTERPRET_RENDO ("general curve",     TKO_Rendo_NURBS_Curve_Options);

						if (set) {
							bool        paren = false;

							rendo++;        // '='

							if (*rendo == '(') {
								paren = true;
								++rendo;
							}

							m_nurbs_options_mask &= ~TKO_NURBS_Curve_Mask;
							m_nurbs_options_value &= ~TKO_NURBS_Curve_Mask;

							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								switch (*rendo) {
									case 'b': {
										m_nurbs_options_mask |= TKO_NURBS_Curve_Budget;
										rendo += 7;     // strlen ("budget=");
										if (set) {
											m_nurbs_options_value |= TKO_NURBS_Curve_Budget;
											READ_INT (m_curve_budget, rendo);
										}
									}   break;

									case 'c': {
										m_nurbs_options_mask |= TKO_NURBS_Curve_Continued_Budget;
										rendo += 16;    // strlen ("continued budget");
										if (set) {
											++rendo;    // '='
											m_nurbs_options_value |= TKO_NURBS_Curve_Continued_Budget;
											READ_INT (m_curve_continued_budget, rendo);
										}
									}   break;

									case 'm': {
										if (rendo[4] == 'a') {
											m_nurbs_options_mask |= TKO_NURBS_Curve_Max_Angle;
											rendo += 10;     // strlen ("max angle=");
											m_nurbs_options_value |= TKO_NURBS_Curve_Max_Angle;
											m_curve_max_angle = read_float (rendo, &rendo);
										}
										else if (rendo[4] == 'd') {
											m_nurbs_options_mask |= TKO_NURBS_Curve_Max_Deviation;
											rendo += 14;     // strlen ("max deviation=");
											m_nurbs_options_value |= TKO_NURBS_Curve_Max_Deviation;
											m_curve_max_deviation = read_float (rendo, &rendo);
										}
										else if (rendo[4] == 'l') {
											m_nurbs_options_mask |= TKO_NURBS_Curve_Max_Length;
											rendo += 11;     // strlen ("max length=");
											m_nurbs_options_value |= TKO_NURBS_Curve_Max_Length;
											m_curve_max_length = read_float (rendo, &rendo);
										}
									}   break;

									case 'v': {
										m_nurbs_options_mask |= TKO_NURBS_Curve_View_Dependent;
										if (set)
											m_nurbs_options_value |= TKO_NURBS_Curve_View_Dependent;
										SKIP_AHEAD (rendo);
									}   break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*rendo == ')') {
									++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (paren)
										++rendo;
									else
										break;
								}
							}
						}

						if ((m_nurbs_options_mask & TKO_NURBS_Extended_Mask) != 0)
							m_nurbs_options_mask |= TKO_NURBS_Extended;
					}
				}
				else if (rendo[1] == 'o') {  //gooch options
					bool paren = false;
					rendo += 14;

					if (*rendo == '(') {
						++rendo;
						paren = true;
					}
					while (*rendo) {
						set = true;

						if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
							set = false;
							rendo += 3; // strlen ("no ");
						}

						switch (*rendo) {
							case 'c': { 
								if (rendo[6] == 'r') {	//color range
									m_mask[1] |= TKO_Rendo_Gooch_Color_Range;
									if(set) {										
										m_value[1] |= TKO_Rendo_Gooch_Color_Range;
										rendo += 13;     // strlen ("color range=(");
										m_gooch_color_range[0] = read_float (rendo, &rendo);
										rendo++;         // strlen (",");
										m_gooch_color_range[1] = read_float (rendo, &rendo);
										rendo++;         // strlen (")");
									}
									else 
										rendo += 11;     // strlen ("color range");
								}
								else if (rendo[6] == 'm') {	//color map segment
									m_mask[1] |= TKO_Rendo_Gooch_Color_Map;
									if(set) {										
										m_value[1] |= TKO_Rendo_Gooch_Color_Map;
										rendo += 18;     // strlen ("color map segment=");

										const char * tmp = rendo;
										do {
											++tmp;
										} while (*tmp!= '\0' && *tmp!=')' && *tmp!=',');
										
										m_gooch_color_map_segment_length=(int)(tmp-rendo);
										m_gooch_color_map_segment= new char [m_gooch_color_map_segment_length+1];

										memcpy(m_gooch_color_map_segment, rendo, m_gooch_color_map_segment_length);
										m_gooch_color_map_segment[m_gooch_color_map_segment_length]='\0';
										rendo=tmp;
									}
									else
										rendo += 17;     // strlen ("color map segment");
								}
							}   break;
							case 'd': { //diffuse weight
								m_mask[1] |= TKO_Rendo_Gooch_Diffuse_Weight;
								m_value[1] |= TKO_Rendo_Gooch_Diffuse_Weight;
								rendo += 15;     // strlen ("diffuse weight=");
								m_gooch_diffuse_weight = read_float (rendo, &rendo);
							}   break;
						}
						if (*rendo == ')') {
							++rendo;
							break;
						}
						else if (*rendo == ',') {
							if (paren)
								++rendo;
							else
								break;
						}					
					}
				}
			}   break;

			case 'h': {
				if (rendo[7] == 'l') {  // hidden line removal options
					INTERPRET_RENDO ("hidden line removal options",         TKO_Rendo_Hidden_Line_Options);

					if (set) {
						bool        paren = false;

						rendo++;        // '='

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						m_hlr_options = 0;
						while (*rendo) {
							set = true;

							if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
								set = false;
								rendo += 3; // strlen ("no ");
							}

							if (streqn (rendo, "vis", 3)) {
								rendo += 10;    // strlen ("visibility");
								if (set) {
									if (*rendo == '=') {    // watch for older form "=on/off"
									if (rendo[2] == 'n')
										m_hlr_options |= TKO_Hidden_Line_Visibility_On;
									else
										m_hlr_options |= TKO_Hidden_Line_Visibility_Off;
									SKIP_AHEAD (rendo);
									}
													else
									m_hlr_options |= TKO_Hidden_Line_Visibility_On;
								}
								else
									m_hlr_options |= TKO_Hidden_Line_Visibility_Off;
							}
							else if (streqn (rendo, "pat", 3)) {
								m_hlr_options |= TKO_Hidden_Line_Pattern;
								rendo += 7;     // strlen ("pattern");
								if (set) {
									char		pattern[256];
									int			i;
									bool		found = false;

									rendo++;	// '='

									// copy out pattern so we can do accurate string compares
									i = 0;
									while (1) {
										pattern[i] = rendo[i];
										if (pattern[i] == ',' || pattern[i] == ')' || pattern[i] == '\0')
											break;
										i++;
									}
									pattern[i] = '\0';

									for (i = 0; i < countof(line_patterns); ++i) {
										if (streq (pattern, line_patterns[i])) {
											m_hlr_line_pattern = i;
											rendo += strlen (pattern);
											found = true;
											break;
										}
									}
									if (!found) {	// not new, try old
										for (i = 0; i < countof(older_line_patterns); ++i) {
											if (streq (pattern, older_line_patterns[i])) {
												m_hlr_line_pattern = i;
												rendo += strlen (pattern);
												found = true;
												break;
											}
										}
									}
									if (!found) {	// not old, try numbers
										for (i = 0; i < countof(numeric_line_patterns); ++i) {
											if (streq (pattern, numeric_line_patterns[i])) {
												m_hlr_line_pattern = i;
												rendo += strlen (pattern);
												found = true;
												break;
											}
										}
									}
								}
								else
									m_hlr_line_pattern = -1;
							}
							else if (streqn (rendo, "fac", 3)) {
								m_hlr_options |= TKO_Hidden_Line_Face_Displacement;
								rendo += 18;    // strlen ("face displacement=");
								m_hlr_face_displacement = read_float (rendo, &rendo);
							}
							else if (streqn (rendo, "tra", 3)) {
								m_hlr_options |= TKO_Hidden_Line_Transparency_Cutoff;
								rendo += 20;    // strlen ("transparency cutoff=");
								m_hlr_transparency_cutoff = read_float (rendo, &rendo);
							}
							else if (streqn (rendo, "dim", 3)) {
								m_hlr_options |= TKO_Hidden_Line_Dim_Factor;
								rendo += 11;    // strlen ("dim factor=");
								m_hlr_dim_factor = read_float (rendo, &rendo);
							}
							else if (streqn (rendo, "rendered", 8)) {
								rendo += 32;    // strlen ("rendered face sorting algorithm=");
								m_hlr_options |= TKO_Hidden_Line_HSR_Algorithm;
								if (*rendo == 'h')
									m_hlr_hsr_algorithm = TKO_HSR_Hardware;
								else if (*rendo == 's')
									m_hlr_hsr_algorithm = TKO_HSR_SZB;
								else if (*rendo == 'p')
									m_hlr_hsr_algorithm = TKO_HSR_Painters;
								else if (*rendo == 'z')
									m_hlr_hsr_algorithm = TKO_HSR_Z_Sort_Only;
								else if (*rendo == 'n')
									m_hlr_hsr_algorithm = TKO_HSR_None;
								SKIP_AHEAD (rendo);
							}
							else if (streqn (rendo, "ren", 3)) {
								rendo += 7;    // strlen ("render ");
								switch (*rendo) {
									case 'f': {
										rendo += 5;    // strlen ("faces");
										if (set)
											m_hlr_options |= TKO_Hidden_Line_Render_Faces_On;
										else
											m_hlr_options |= TKO_Hidden_Line_Render_Faces_Off;
									}	break;

									case 't': {
										rendo += 4;    // strlen ("text");
										if (set)
											m_hlr_options |= TKO_Hidden_Line_Render_Text_On;
										else
											m_hlr_options |= TKO_Hidden_Line_Render_Text_Off;
									}	break;

									default:
										return tk.Error("interpret parse error");
								}
							}
							else if (streqn (rendo, "sil", 3)) {
								rendo += 18;    // strlen ("silhouette cleanup");
								if (set)
									m_hlr_options |= TKO_Hidden_Line_Silhouette_Cleanup_On;
								else
									m_hlr_options |= TKO_Hidden_Line_Silhouette_Cleanup_Off;
							}
							else if (streqn (rendo, "wei", 3)) {
								rendo += 6;     // strlen ("weight");
								m_hlr_options |= TKO_Hidden_Line_Weight;

								if (set) {
									int		i;

									rendo++;	// '='
									m_hlr_weight = read_float (rendo, &rendo);

									for (i = 0; i < (int)countof(generic_units_table); ++i) {
										if (streqn (rendo, generic_units_table[i], strlen(generic_units_table[i]))) {
											m_hlr_weight_units = (unsigned char)i;
											break;
										}
									}
									if (i == countof(generic_units_table))
										m_hlr_weight_units = 255;
								}
								else
									m_hlr_weight = -1.0f;
							}
							else if (streqn (rendo, "col", 3)) {
								rendo += 5;     // strlen ("color");
								m_hlr_options |= TKO_Hidden_Line_Color;

								if (set) {
									rendo += 3;	// '=R='
									m_hlr_color[0] = read_float (rendo, &rendo);
									rendo += 3;	// ' G='
									m_hlr_color[1] = read_float (rendo, &rendo);
									rendo += 3;	// ' B='
									m_hlr_color[2] = read_float (rendo, &rendo);
								}
								else
									m_hlr_color[0] = m_hlr_color[1] = m_hlr_color[2] = -1.0f;
							}
							else if (streqn (rendo, "ima", 3)) {
								rendo += 13;    // strlen ("image outline");
								if (set)
									m_hlr_options |= TKO_Hidden_Line_Image_Outline_On;
								else
									m_hlr_options |= TKO_Hidden_Line_Image_Outline_Off;
							}
							else
								return tk.Error("interpret parse error");

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}

						if ((m_hlr_options & TKO_Hidden_Line_Extended2_Mask) != 0)
							m_hlr_options |= TKO_Hidden_Line_Extended2;
						if ((m_hlr_options & TKO_Hidden_Line_Extended_Mask) != 0)
							m_hlr_options |= TKO_Hidden_Line_Extended;
					}
				}
				else {                  // hidden surface removal algorithm
					bool        paren = false;

					rendo += 33;    // strlen ("hidden surface removal algorithm=");

					if (*rendo == '(') {
						paren = true;
						++rendo;
					}

					while (*rendo) {
						int         shift;
						int         value;

						if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ' && rendo[3] == 't') {
							rendo += 14;    // strlen ("no transparent");
							m_mask[0] |= TKO_Rendo_THSR_Algorithm;
							m_value[0] |= TKO_Rendo_THSR_Algorithm;
							shift = 4;
							value = TKO_HSR_None;
						}
						else {
							if (*rendo == 't') {
								rendo += 12;    // strlen ("transparent=");
								m_mask[0] |= TKO_Rendo_THSR_Algorithm;
								m_value[0] |= TKO_Rendo_THSR_Algorithm;
								shift = 4;
							}
							else {
								m_mask[0] |= TKO_Rendo_HSR_Algorithm;
								m_value[0] |= TKO_Rendo_HSR_Algorithm;
								shift = 0;
							}

							if (streqn (rendo, "fas", 3)) {
								rendo += 16;    // strlen ("fast hidden line");
								value = TKO_HSR_Fast_Hidden_Line;
							}
							else if (streqn (rendo, "har", 3)) {
								rendo += 17;    // strlen ("hardware z buffer");
								value = TKO_HSR_Hardware;
							}
							else if (streqn (rendo, "sof", 3)) {
								rendo += 17;    // strlen ("software z buffer");
								value = TKO_HSR_SZB;
							}
							else if (streqn (rendo, "pai", 3)) {
								rendo += 8;     // strlen ("painters");
								value = TKO_HSR_Painters;
							}
							else if (streqn (rendo, "z s", 3)) {
								rendo += 11;    // strlen ("z sort only");
								value = TKO_HSR_Z_Sort_Only;
							}
							else if (streqn (rendo, "pri", 3)) {
								rendo += 8;     // strlen ("priority");
								value = TKO_HSR_Priority;
							}
							else if (streqn (rendo, "spi", 3)) {
								rendo += 10;    // strlen ("spider web");
								value = TKO_HSR_Z_Sort_Only;
							}
							else if (streqn (rendo, "hid", 3)) {
								rendo += 11;    // strlen ("hidden line");
								value = TKO_HSR_Hidden_Line;
							}
							else
								return tk.Error("interpret parse error");
						}

						m_hsr |= value << shift;

						if (*rendo == ')') {
							++rendo;
							break;
						}
						else if (*rendo == ',') {
							if (paren)
								++rendo;
							else
								break;
						}
					}
				}
			}   break;

			case 'i': {
				if (rendo[1] == 'g') { // ignore subsegment lock
					INTERPRET_RENDO_EXTENDED2 ("ignode subsegment lock",		TKO_Rendo_Forced_Lock);

					if (set) {
						if (*rendo != '=') {
							m_forced_mask = m_forced_value = TKO_Lock_All;
							m_forced_color_mask = m_forced_color_value = TKO_Geo_All_Colors;
							m_forced_visibility_mask = m_forced_visibility_value = TKO_Geo_All_Visibles;
						}
						else {
							bool        paren = false;

							++rendo;
							if (*rendo == '(') {
								paren = true;
								++rendo;
							}

							m_forced_mask = m_forced_value = 0;
							m_forced_color_mask = m_forced_color_value = 0;
							m_forced_visibility_mask = m_forced_visibility_value = 0;
							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								switch (*rendo) {
									case 'c': {
										if (rendo[1] == 'a' && rendo[2] == 'm')
											INTERPRET_FORCED ("camera",               TKO_Lock_Camera);
										else if (rendo[1] == 'a' && rendo[2] == 'l')
											INTERPRET_FORCED ("callback",             TKO_Lock_Callback);
										else if (rendo[1] == 'l')
											SKIP_AHEAD(rendo);//INTERPRET_FORCED ("clip region",          TKO_Lock_Clip_Region);
										else if (rendo[5] == ' ' && rendo[6] == 'm')
											INTERPRET_FORCED ("color map",            TKO_Lock_Color_Map);
										else {
											INTERPRET_FORCED ("color",                TKO_Lock_Color);

											if (set) {
												if (*rendo != '=') {
													m_forced_color_mask = m_forced_color_value = TKO_Geo_All_Colors;
													m_forced_color_face_mask = m_forced_color_face_value = 
													m_forced_color_edge_mask = m_forced_color_edge_value = 
													m_forced_color_line_mask = m_forced_color_line_value = 
													m_forced_color_marker_mask = m_forced_color_marker_value = 
													m_forced_color_text_mask = m_forced_color_text_value = 
													m_forced_color_window_mask = m_forced_color_window_value = 
													m_forced_color_face_contrast_mask = m_forced_color_face_contrast_value = 
													m_forced_color_window_contrast_mask = m_forced_color_window_contrast_value = 
													m_forced_color_back_mask = m_forced_color_back_value = 
													m_forced_color_vertex_mask = m_forced_color_vertex_value = 
													m_forced_color_edge_contrast_mask = m_forced_color_edge_contrast_value = 
													m_forced_color_line_contrast_mask = m_forced_color_line_contrast_value = 
													m_forced_color_marker_contrast_mask = m_forced_color_marker_contrast_value = 
													m_forced_color_vertex_contrast_mask = m_forced_color_vertex_contrast_value = 
													m_forced_color_text_contrast_mask = m_forced_color_text_contrast_value = 
													m_forced_color_simple_reflection_mask = m_forced_color_simple_reflection_value = 
													m_forced_color_cut_face_mask = m_forced_color_cut_face_value = 
													m_forced_color_cut_edge_mask = m_forced_color_cut_edge_value = 
													TKO_Lock_Channel_ALL;
												}
												else {
													bool        cparen = false;

													++rendo;
													if (*rendo == '(') {
														cparen = true;
														++rendo;
													}

													while (*rendo) {
														int	    which = 0;

														set = true;

														if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
															set = false;
															rendo += 3; // strlen ("no ");
														}

														switch (*rendo) {
															case 'a': {
																rendo += 7;	// strlen ("ambient");
																if (*rendo == ' ') {
																	++rendo;
																	if (*rendo == 'u')
																		INTERPRET_COLOR_FORCED ("up",		TKO_Geo_Ambient_Up);
																	else
																		INTERPRET_COLOR_FORCED ("down",	TKO_Geo_Ambient_Down);
																}
																else
																	INTERPRET_COLOR_FORCED ("ambient",	TKO_Geo_Ambient);
															}   break;

															case 'b': {
																which = TKO_Geo_Back;
																rendo += 4; // strlen ("back");
															}   break;

															case 'c': {
																if (rendo[4] == 'g') {
																	which = TKO_Geo_Cut_Geometry;
																	rendo += 12; // strlen ("cut geometry");
																}
																else if (rendo[4] == 'f') {
																	which = TKO_Geo_Cut_Face;
																	rendo += 8;	// strlen ("cut face");
																}
																else {
																	which = TKO_Geo_Cut_Edge;
																	rendo += 8; // strlen ("cut edge");
																}
															}   break;

															case 'e': {
																if (rendo[4] == ' ' && rendo[5] == 'c') {
																	which = TKO_Geo_Edge_Contrast;
																	rendo += 13; // strlen ("edge contrast");
																	m_forced_color_edge_contrast_mask = 0;
																}
																else {
																	which = TKO_Geo_Edge;
																	rendo += 4; // strlen ("edge");
																}
															}   break;

															case 'f': {
																if (rendo[1] == 'r') {
																	which = TKO_Geo_Front;
																	rendo += 5; // strlen ("front");
																}
																else if (rendo[4] == ' ' && rendo[5] == 'c') {
																	which = TKO_Geo_Face_Contrast;
																	rendo += 13; // strlen ("face contrast");
																}
																else {
																	which = TKO_Geo_Face;
																	rendo += 4; // strlen ("face");
																}
															}   break;

															case 'g': {
																which = TKO_Geo_Geom_Colors;
																rendo += 8; // strlen ("geometry");
															}   break;

															case 'l': {
																if (rendo[2] == 'g')
																	INTERPRET_COLOR_FORCED ("lighting",TKO_Geo_Light_Visibles);
																else if (rendo[4] == ' ' && rendo[5] == 'c') {
																	which = TKO_Geo_Line_Contrast;
																	rendo += 13; // strlen ("line contrast");
																}
																else {
																	which = TKO_Geo_Line;
																	rendo += 4; // strlen ("line");
																}
															}   break;

															case 'm': {
																if (rendo[6] == ' ' && rendo[7] == 'o') {
																	which = TKO_Geo_Marker;
																	rendo += 11; //strlen ("marker only");
																}
																else if (rendo[6] == ' ' && rendo[7] == 'c') {
																	which = TKO_Geo_Marker_Contrast;
																	rendo += 15; //strlen ("marker contrast");
																}
																else {
																	which = TKO_Geo_Marker | TKO_Geo_Vertex;
																	rendo += 6; //strlen ("marker");
																}
															}   break;

															case 'v': {
																if (rendo[6] == ' ' && rendo[7] == 'c') {
																	which = TKO_Geo_Vertex_Contrast;
																	rendo += 15; //strlen ("vertex contrast");
																}
																else {
																	which = TKO_Geo_Vertex;
																	rendo += 6; //strlen ("vertex");
																}
															}   break;

															case 'p': {
																which = TKO_Geo_Face | TKO_Geo_Edge;
																rendo += 7; //strlen ("polygon");
															}   break;

															case 's': {
																which = TKO_Geo_Simple_Reflection;
																rendo += 17; //strlen ("simple reflection");
															}   break;

															case 't': {
																if (rendo[4] == ' ' && rendo[5] == 'c') {
																	which = TKO_Geo_Text_Contrast;
																	rendo += 13; //strlen ("text contrast");
																}
																else {
																	which = TKO_Geo_Text;
																	rendo += 4; //strlen ("text");
																}
															}   break;

															case 'w': {
																if (rendo[6] == ' ' && rendo[7] == 'c') {
																	which = TKO_Geo_Window_Contrast;
																	rendo += 15; //strlen ("window contrast");
																}
																else {
																	which = TKO_Geo_Window;
																	rendo += 6; //strlen ("window");
																}
															}   break;

															default:
																return tk.Error("interpret parse error");
														}

														if (which) {
															int	    channel_bits = 0;
															int	    keep_bits = ~0;
															int	    set_bits = 0;

															m_forced_color_mask |= which;

															if (set) {
																m_forced_color_value |= which;

																if (*rendo != '=') {
																	channel_bits = ~0;
																	keep_bits = ~0;
																	set_bits = ~0;
																}
																else {
																	bool        chparen = false;

																	++rendo;
																	if (*rendo == '(') {
																		chparen = true;
																		++rendo;
																	}

																	while (*rendo) {
																		int		channel;

																		set = true;

																		if (rendo[0] == 'n' && rendo[1] == 'o' &&
																			rendo[2] == ' ') {
																			set = false;
																			rendo += 3; // strlen ("no ");
																		}

																		switch (*rendo) {
																			case 'b':
																				channel = TKO_Lock_Channel_Bump;
																				rendo += 4; // strlen ("bump");
																			break;

																			case 'd':
																				channel = TKO_Lock_Channel_Diffuse;
																				rendo += 7; // strlen ("diffuse");
																			break;

																			case 'e':
																				if (rendo[1] == 'm') {
																					channel = TKO_Lock_Channel_Emission;
																					rendo += 8; // strlen ("emission");
																				}
																				else {
																					channel = TKO_Lock_Channel_Environment;
																					rendo += 11; // strlen ("environment");
																				}
																			break;

																			case 'g':
																				channel = TKO_Lock_Channel_Gloss;
																				rendo += 5; // strlen ("gloss");
																			break;

																			case 'i':
																				channel = TKO_Lock_Channel_Index;
																				rendo += 5; // strlen ("index");
																			break;

																			case 'm':
																				channel = TKO_Lock_Channel_Mirror;
																				rendo += 6; // strlen ("mirror");
																			break;

																			case 's':
																				channel = TKO_Lock_Channel_Specular;
																				rendo += 8; // strlen ("specular");
																			break;

																			case 't':
																				channel = TKO_Lock_Channel_Transmission;
																				rendo += 12; // strlen ("transmission");
																			break;

																			default:
																				return tk.Error("interpret parse error");
																		}

																		channel_bits |= channel;
																		if (set)
																			set_bits |= channel;
																		else
																			keep_bits &= ~channel;


																		if (*rendo == ')') {
																			if (chparen)
																				++rendo;
																			break;
																		}
																		else if (*rendo == ',') {
																			if (chparen)
																				++rendo;
																			else
																				break;
																		}
																	}
																}
															}
															else {
																m_forced_color_value &= ~which;

																channel_bits = ~0;
																keep_bits = 0;
																set_bits = 0;
															}



#define PROCESS_CHANNELS_F(_w_,field)			    \
		do if ((which & _w_) != 0) {		    \
		m_forced_color_##field##_mask = (short)channel_bits; \
		m_forced_color_##field##_value = (short)set_bits;   \
		} while (0)					   //

															PROCESS_CHANNELS_F (TKO_Geo_Face,   face);
															PROCESS_CHANNELS_F (TKO_Geo_Face,   back);

															PROCESS_CHANNELS_F (TKO_Geo_Front,  face);
															PROCESS_CHANNELS_F (TKO_Geo_Back,   back);
															PROCESS_CHANNELS_F (TKO_Geo_Edge,   edge);
															PROCESS_CHANNELS_F (TKO_Geo_Line,   line);
															PROCESS_CHANNELS_F (TKO_Geo_Text,   text);
															PROCESS_CHANNELS_F (TKO_Geo_Marker, marker);
															PROCESS_CHANNELS_F (TKO_Geo_Vertex, vertex);
															PROCESS_CHANNELS_F (TKO_Geo_Window, window);
															PROCESS_CHANNELS_F (TKO_Geo_Face_Contrast,   face_contrast);
															PROCESS_CHANNELS_F (TKO_Geo_Edge_Contrast,   edge_contrast);
															PROCESS_CHANNELS_F (TKO_Geo_Line_Contrast,   line_contrast);
															PROCESS_CHANNELS_F (TKO_Geo_Text_Contrast,   text_contrast);
															PROCESS_CHANNELS_F (TKO_Geo_Marker_Contrast, marker_contrast);
															PROCESS_CHANNELS_F (TKO_Geo_Vertex_Contrast, vertex_contrast);
															PROCESS_CHANNELS_F (TKO_Geo_Window_Contrast, window_contrast);
															PROCESS_CHANNELS_F (TKO_Geo_Simple_Reflection, simple_reflection);
															PROCESS_CHANNELS_F (TKO_Geo_Cut_Face, cut_face);
															PROCESS_CHANNELS_F (TKO_Geo_Cut_Edge, cut_edge);
														}

														if (*rendo == ')') {
															if (cparen)
																++rendo;
															break;
														}
														else if (*rendo == ',') {
															if (cparen)
																++rendo;
															else
																break;
														}
													}
												}
											}
										}
									}   break;

									case 'd': {
										if (rendo[6] == ' ' && rendo[7] == 'o')
											INTERPRET_FORCED ("driver options",   TKO_Lock_Driver_Options);
										else
											INTERPRET_FORCED ("driver",           TKO_Lock_Driver);
									}   break;

									case 'e': {
										if (rendo[5] == 'p')
											INTERPRET_FORCED ("edge pattern",     TKO_Lock_Edge_Pattern);
										else
											INTERPRET_FORCED ("edge weight",      TKO_Lock_Edge_Weight);
									}   break;

									case 'f': {
										INTERPRET_FORCED ("face pattern",         TKO_Lock_Face_Pattern);
									}   break;

									case 'h': {
										if (rendo[1] == 'a')
											INTERPRET_FORCED ("handedness",       TKO_Lock_Handedness);
										else
											INTERPRET_FORCED ("heuristics",       TKO_Lock_Heuristics);
									}   break;

									case 'l': {
										if (rendo[5] == 'p')
											INTERPRET_FORCED ("line pattern",     TKO_Lock_Line_Pattern);
										else
											INTERPRET_FORCED ("line weight",      TKO_Lock_Line_Weight);
									}   break;

									case 'm': {
										if (rendo[1] == 'o')
											INTERPRET_FORCED ("modelling matrix", TKO_Lock_Modelling_Matrix);
										else if (rendo[1] == 'e')
											INTERPRET_FORCED ("metafile",         TKO_Lock_Metafile);
										else if (rendo[8] == 'i')
											INTERPRET_FORCED ("marker size",      TKO_Lock_Marker_Size);
										else
											INTERPRET_FORCED ("marker symbol",    TKO_Lock_Marker_Symbol);
									}   break;

									case 'r': {
										INTERPRET_FORCED ("rendering options",    TKO_Lock_Rendering_Options);
									}   break;

									case 's': {
										if (rendo[1] == 'e')
											INTERPRET_FORCED ("selectability",    TKO_Lock_Selectability);
										else
											INTERPRET_FORCED ("style",            TKO_Lock_Styles);
									}   break;

									case 't': {
										if (rendo[5] == 'a')
											INTERPRET_FORCED ("text alignment",       TKO_Lock_Text_Alignment);
										else if (rendo[5] == 'f')
											INTERPRET_FORCED ("text font",            TKO_Lock_Text_Font);
										else if (rendo[5] == 'p')
											INTERPRET_FORCED ("text path",            TKO_Lock_Text_Path);
										else if (rendo[5] == 's')
											INTERPRET_FORCED ("text spacing",         TKO_Lock_Text_Spacing);
										else
											INTERPRET_FORCED ("texture matrix",       TKO_Lock_Texture_Matrix);
									}   break;

									case 'u': {
										if (rendo[5] == 'o')
											INTERPRET_FORCED ("user options",     TKO_Lock_User_Options);
										else
											INTERPRET_FORCED ("user value",       TKO_Lock_User_Value);
									}   break;

									case 'v': {
										INTERPRET_FORCED ("visibility",           TKO_Lock_Visibility);

										if (set) {
											if (*rendo != '=') {
												m_forced_visibility_mask = m_forced_visibility_value = TKO_Geo_All_Visibles;
											}
											else {
												bool        vparen = false;

												++rendo;
												if (*rendo == '(') {
													vparen = true;
													++rendo;
												}

												while (*rendo) {
													set = true;

													if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
														set = false;
														rendo += 3; // strlen ("no ");
													}

													switch (*rendo) {
														case 'c': {
															if (rendo[3] == 't')
																INTERPRET_VIS_FORCED ("cutting plane",	TKO_Geo_Cutting_Plane);
															else
																INTERPRET_VIS_FORCED ("cut geometry",		TKO_Geo_Cut_Geometry);
														}   break;

														case 'e': {
															INTERPRET_VIS_FORCED ("edge",         TKO_Geo_Edge);
														}   break;

														case 'f': {
															INTERPRET_VIS_FORCED ("face",         TKO_Geo_Face);
														}   break;

														case 'g': {
															INTERPRET_VIS_FORCED ("geometry",     TKO_Geo_Geom_Visibles);
														}   break;

														case 'i': {
															INTERPRET_VIS_FORCED ("image",        TKO_Geo_Image);
														}   break;

														case 'l': {
															if (rendo[2] == 'g')
																INTERPRET_VIS_FORCED ("lighting", TKO_Geo_Light_Visibles);
															else
																INTERPRET_VIS_FORCED ("line",     TKO_Geo_Line);
														}   break;

														case 'm': {
															if (rendo[6] == ' ' && rendo[7] == 'o')
																INTERPRET_VIS_FORCED ("marker only",  TKO_Geo_Marker);
															else
																INTERPRET_VIS_FORCED ("marker",       TKO_Geo_Marker | TKO_Geo_Vertex_Vis);
														}   break;

														case 'v': {
															INTERPRET_VIS_FORCED ("vertex",       TKO_Geo_Vertex_Vis);
														}   break;

														case 'p': {
															INTERPRET_VIS_FORCED("polygon",      TKO_Geo_Face | TKO_Geo_Edge);
														}   break;

														case 's': {
															if (rendo[1] == 'h')
																INTERPRET_VIS_FORCED ("shadows",  TKO_Geo_Shadow_Visibles);
															else
																INTERPRET_VIS_FORCED ("string cursor",
																								TKO_Geo_String_Cursor);
														}   break;

														case 't': {
															INTERPRET_VIS_FORCED ("text",         TKO_Geo_Text);
														}   break;

														case 'w': {
															INTERPRET_VIS_FORCED ("window",       TKO_Geo_Window);
														}   break;

														default:
															return tk.Error("interpret parse error");
													}

													if (*rendo == ')') {
														if (vparen)
															++rendo;
														break;
													}
													else if (*rendo == ',') {
														if (vparen)
															++rendo;
														else
															break;
													}
												}
											}
										}
									}   break;

									case 'w': {
										if (rendo[6] == ' ' && rendo[7] == 'f')
											INTERPRET_FORCED ("window frame",     TKO_Lock_Window_Frame);
										else if (rendo[6] == ' ' && rendo[7] == 'p')
											INTERPRET_FORCED ("window pattern",   TKO_Lock_Window_Pattern);
										else
											INTERPRET_FORCED ("window",           TKO_Lock_Window);
									}   break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*rendo == ')') {
									++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (paren)
										++rendo;
									else
										break;
								}
							}
						}
					}
				}
				else if (rendo[1] == 's') {		// isoline options
					bool        paren = false;
					float		values[300];

					m_mask[2] |= TKO_Rendo_Isoline_Options;
					m_value[2] |= TKO_Rendo_Isoline_Options;
					rendo += 16;	//strlen ("isoline options=");

					if (*rendo == '(') {
						paren = true;
						++rendo;
					}

					while (*rendo) {
						set = true;

						if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
							set = false;
							rendo += 3; // strlen ("no ");
						}

						switch (*rendo) {
							case 'c': {
								m_isoline_options |= TKO_Isoline_Colors;
								rendo += 6;	// strlen ("colors");
								if (set) {
									bool        cparen = false;

									++rendo;	// '='

									if (*rendo == '(') {
										cparen = true;
										++rendo;
									}

									while (*rendo) {
										if (*rendo == '*') {
											values[3*m_isoline_color_count+0] = -1.0f;
											values[3*m_isoline_color_count+1] = -1.0f;
											values[3*m_isoline_color_count+2] = -1.0f;
											++m_isoline_color_count;
										}
										else if (*rendo == '-') {
											values[3*m_isoline_color_count+0] = -2.0f;
											values[3*m_isoline_color_count+1] = -2.0f;
											values[3*m_isoline_color_count+2] = -2.0f;
											++m_isoline_color_count;
										}
										else {
											rendo += 2;	// strlen ("R=");
											values[3*m_isoline_color_count+0] = read_float (rendo, &rendo);
											rendo += 3;	// strlen (" G=");
											values[3*m_isoline_color_count+1] = read_float (rendo, &rendo);
											rendo += 3;	// strlen (" B=");
											values[3*m_isoline_color_count+2] = read_float (rendo, &rendo);
										}
										++m_isoline_color_count;

										if (*rendo == ')') {
											++rendo;
											break;
										}
										else if (*rendo == ',') {
											if (cparen)
												++rendo;
											else
												break;
										}
									}

									m_isoline_colors = new float [3*m_isoline_color_count];
									memcpy (m_isoline_colors, values, 3*m_isoline_color_count * sizeof(float));
								}
							}	break;

							case 'l': {
								rendo += 8;	// strlen ("lighting");
								if (set)
									m_isoline_options |= TKO_Isoline_Lighting_On;
								else
									m_isoline_options |= TKO_Isoline_Lighting_Off;
							}	break;

							case 'p': {
								if (rendo[1] == 'a') {	// patterns
									char *		strings[256];
									char		one[1024];

									m_isoline_options |= TKO_Isoline_Patterns;
									rendo += 8;	// strlen ("patterns");
									if (set) {
										bool		pparen = false;

										++rendo;	// '='

										if (*rendo == '(') {
											pparen = true;
											++rendo;
										}

										while (*rendo) {
											char *		cp = one;

											while (*rendo && *rendo != ',' && *rendo != ')')
												*cp++ = *rendo++;
											*cp++ = '\0';

											strings[m_isoline_pattern_count] = new char [cp - one];
											strcpy (strings[m_isoline_pattern_count++], one);

											if (*rendo == ')') {
												++rendo;
												break;
											}
											else if (*rendo == ',') {
												if (pparen)
													++rendo;
												else
													break;
											}
										}

										m_isoline_patterns = new char * [m_isoline_pattern_count];
										memcpy (m_isoline_patterns, strings, m_isoline_pattern_count * sizeof(char *));
									}
								}
								else {					// positions
									m_isoline_options |= TKO_Isoline_Positions;
									rendo += 9;	// strlen ("position=");

									if (*rendo == 'd') {
										m_isoline_position_type = TKO_Isoline_Positions_Default;
										rendo += 7;	// strlen ("default");
									}
									else if (*rendo == 'r') {
										m_isoline_position_type = TKO_Isoline_Positions_Repeat;
										rendo += 17;	// strlen ("repeat=(interval=");
										m_isoline_position_count = 2;
										m_isoline_positions = new float [2];
										m_isoline_positions[0] = read_float (rendo, &rendo);
										rendo += 8;	// strlen (",offset=");
										m_isoline_positions[1] = read_float (rendo, &rendo);
										++rendo;	// ')'
									}
									else {
										bool		pparen = false;

										m_isoline_position_type = TKO_Isoline_Positions_Explicit;
										rendo += 9;	// strlen ("explicit=");
										if (*rendo == '(') {
											pparen = true;
											++rendo;
										}

										while (*rendo) {
											values[m_isoline_position_count++] = read_float (rendo, &rendo);

											if (*rendo == ')') {
												++rendo;
												break;
											}
											else if (*rendo == ',') {
												if (pparen)
													++rendo;
												else
													break;
											}
										}

										m_isoline_positions = new float [m_isoline_position_count];
										memcpy (m_isoline_positions, values, m_isoline_position_count * sizeof(float));
									}
								}
							}	break;

							case 'v': {
								rendo += 10;	// strlen ("visibility");

								m_mask[2] |= TKO_Rendo_Contour_Options;
								m_value[2] |= TKO_Rendo_Contour_Options;

								if (set)
									m_contour_options |= TKO_Contour_Isoline_Visibility_On;
								else
									m_contour_options |= TKO_Contour_Isoline_Visibility_Off;
							}	break;

							case 'w': {
								unsigned char	units[300];

								m_isoline_options |= TKO_Isoline_Weights;
								rendo += 7;	// strlen ("weights");
								if (set) {
									bool		wparen = false;

									++rendo;	// '='

									if (*rendo == '(') {
										wparen = true;
										++rendo;
									}

									while (*rendo) {
										if (*rendo == '*') {
											values[m_isoline_weight_count] = 0.0f;
											units[m_isoline_weight_count] = 255;
										}
										else {
											values[m_isoline_weight_count] = read_float (rendo, &rendo);

											for (int i = 0; i < (int)countof(generic_units_table); ++i) {
												if (streqn (rendo, generic_units_table[i], strlen(generic_units_table[i]))) {
													units[m_isoline_weight_count] = (unsigned char)i;
													break;
												}
											}
										}
										m_isoline_weight_count++;

										if (*rendo == ')') {
											++rendo;
											break;
										}
										else if (*rendo == ',') {
											if (wparen)
												++rendo;
											else
												break;
										}
									}

									m_isoline_weights_value = new float [m_isoline_weight_count];
									m_isoline_weights_unit = new unsigned char [m_isoline_weight_count];
									memcpy (m_isoline_weights_value, values, m_isoline_weight_count * sizeof(float));
									memcpy (m_isoline_weights_unit, units, m_isoline_weight_count * sizeof(unsigned char));
								}
							}	break;
						}

						if (*rendo == ')') {
							++rendo;
							break;
						}
						else if (*rendo == ',') {
							if (paren)
								++rendo;
							else
								break;
						}
					}
				}
				else if (rendo[6] == 's') {
					INTERPRET_RENDO_EXTENDED ("image scale",    TKO_Rendo_Image_Scale);

					if (set) {
						rendo += 2; // strlen ("=(");
						m_image_scale[0] = read_float (rendo, &rendo);
						++rendo;    // ','
						m_image_scale[1] = read_float (rendo, &rendo);
						++rendo;    // ')'
					}
				}
				else {
					INTERPRET_RENDO_EXTENDED ("image tint",    TKO_Rendo_Image_Tint);

					char		string[256];
					char *		sp = string;
					char        sysop[2048];

					rendo++; 

					if (*rendo == '\'') {
						++rendo;    // initial '
						do *sp++ = *rendo++;
						while (*rendo != '\'');
							++rendo;    // final '
						*sp = '\0';
					}
					else {
						do *sp++ = *rendo++;
						while (*rendo != ',' && *rendo != ')');
						*sp = '\0';
					}

					// should be a valid color, but guard just in case...
					HC_Show_One_System_Option ("errors", sysop);
					HC_Define_System_Options ("no errors");

					HC_Compute_Color (string, "rgb", m_image_tint_color);

					{
						char		newsysop[2048];

						sprintf (newsysop, "errors=(%s)", sysop);
						HC_Define_System_Options (newsysop);
					}
				}
			}   break;


			case 'j': {
				//INTERPRET_RENDO_EXTENDED ("join cutoff angle",    TKO_Rendo_Join_Cutoff_Angle);
				rendo += strlen ("join cutoff angle");

				if (set) {
					rendo++;    // '='
					//READ_INT (m_join_cutoff_angle, rendo);
					if ('0' <= *rendo && *rendo <= '9' || *rendo == '-') {
						m_mask[0] |= TKO_Rendo_Extended;
						m_mask[1] |= TKO_Rendo_Join_Cutoff_Angle | TKO_Rendo_Extended2;
						m_mask[2] |= TKO_Rendo_Edge_Join_Cutoff_Angle;
						m_value[1] |= TKO_Rendo_Join_Cutoff_Angle;
						m_value[2] |= TKO_Rendo_Edge_Join_Cutoff_Angle;

						READ_INT (m_join_cutoff_angle, rendo);
						m_edge_join_cutoff_angle = m_join_cutoff_angle;
					}
					else {
						bool        paren = false;

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						while (*rendo) {
							set = true;

							if (streqn (rendo, "no ", 3)) {
								set = false;
								rendo += 3;  // strlen ("no ");
							}

							switch (*rendo) {
								case 'e': {
									INTERPRET_RENDO_EXTENDED2 ("edge",	TKO_Rendo_Edge_Join_Cutoff_Angle);
									if (set) {
										rendo++;    // '='
										READ_INT (m_edge_join_cutoff_angle, rendo);
									}
								}   break;
								case 'l': {
									INTERPRET_RENDO_EXTENDED ("line",	TKO_Rendo_Join_Cutoff_Angle);
									if (set) {
										rendo++;    // '='
										READ_INT (m_join_cutoff_angle, rendo);
									}
								}   break;
							}

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}
					}
				}
				else {
					m_mask[0] |= TKO_Rendo_Extended;
					m_mask[1] |= TKO_Rendo_Join_Cutoff_Angle | TKO_Rendo_Extended2;
					m_mask[2] |= TKO_Rendo_Edge_Join_Cutoff_Angle;
				}
			}   break;

			case 'l': {
				if (rendo[2] == 'c') {
					if (rendo[6] == 'c')
						INTERPRET_RENDO_EXTENDED ("local cutting planes",   TKO_Rendo_Local_Cutting_Planes);
					else
						INTERPRET_RENDO ("local viewer",	    TKO_Rendo_Local_Viewer);
				}
				else if (rendo[2] == 'd') { // lod
					INTERPRET_RENDO ("lod",                     TKO_Rendo_LOD);
				}
				else if (rendo[2] == 'v') { // level of detail options
					INTERPRET_RENDO ("level of detail options",  TKO_Rendo_LOD_Options);

					if (set) {
						bool        paren = false;

						++rendo;    // '='

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						m_lod_options_mask = m_lod_options_value = 0;
						while (*rendo) {
							set = true;

							if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
								set = false;
								rendo += 3; // strlen ("no ");
							}

							switch (*rendo) {
								case 'a': {         // algorithm
									rendo += 10;    // strlen ("algorithm=");
									m_lod_options_mask |= TKO_LOD_Algorithm;
									m_lod_options_value |= TKO_LOD_Algorithm;
									if (*rendo == 'f')
										m_lod_algorithm = TKO_LOD_Algorithm_Fast;
									else
										m_lod_algorithm = TKO_LOD_Algorithm_Nice;
									rendo += 4;     // "fast" or "nice"
								}   break;

								case 'b': {         // bounding
									m_lod_options_mask |= TKO_LOD_Bounding_Current | TKO_LOD_Bounding_Explicit;
									rendo += 8;     // strlen ("bounding");
									if (set) {
										++rendo;    // '='
										if (*rendo == 'c') {
											m_lod_options_value |= TKO_LOD_Bounding_Current;
											rendo += 7; // strlen ("current");
										}
										else {
											int         index;

											m_lod_options_value |= TKO_LOD_Bounding_Explicit;
											++rendo;    // '('
											for (index = 0; index < 6; ++index) {
												m_bounding[index] = read_float (rendo, &rendo);
												while (*rendo == ',' || *rendo == ' ')
													++rendo;
											}
											++rendo;    // ')'
										}
									}
								}   break;

								case 'c': {
									if (rendo[1] == 'a') {      // calculation usefulness cutoff
										bool        local_paren = false;

										m_lod_options_mask |= TKO_LOD_Calculation_Cutoff;
										rendo += 29;    // strlen ("calculation usefulness cutoff");
										if (set) {
											m_lod_options_value |= TKO_LOD_Calculation_Cutoff;
											if (*++rendo == '(') {
												local_paren = true;
												++rendo;
											}

											m_num_cutoffs = 0;
											while (1) {
												m_cutoff[(int)m_num_cutoffs++] = read_float (rendo, &rendo);
												if (local_paren) {
													if (*rendo++ == ')')
														break;
													// otherwise we should have just skipped a ','
												}
												else
													break;
											}
										}
									}
									else if (rendo[1] == 'l') { // clamp
										m_lod_options_mask |= TKO_LOD_Clamp;
										rendo += 5; // strlen ("clamp");
										if (set) {
											int	    clamp;

											++rendo;    // '='
											m_lod_options_value |= TKO_LOD_Clamp;
											READ_INT (clamp, rendo);
											m_clamp = (unsigned char)clamp;
										}
									}
									else if (rendo[2] == 'l') { // collapse duplicate vertices
										m_lod_options_mask |= TKO_LOD_Collapse_Vertices;
										if (set)
											m_lod_options_value |= TKO_LOD_Collapse_Vertices;
										rendo += 27;    // strlen ("collapse duplicate vertices");
									}
									else if (rendo[2] == 'n') { // conserve memory
										m_lod_options_mask |= TKO_LOD_Conserve_Memory;
										if (set)
											m_lod_options_value |= TKO_LOD_Conserve_Memory;
										rendo += 15;    // strlen ("conserve memory");
									}
								}   break;

								case 'f': {         // fallback
									m_lod_options_mask |= TKO_LOD_Fallback;
									rendo += 8;     // strlen ("fallback");
									if (set) {
										m_lod_options_value |= TKO_LOD_Fallback;
										++rendo;        // '='
										if (*rendo == 'b') {
											rendo += 8; // strlen ("bounding");
											if (*rendo == ' ') {
												m_fallback = TKO_LOD_Fallback_Bounding_None;
												rendo += 5; // strlen (" none");
											}
											else 
												m_fallback = TKO_LOD_Fallback_Bounding;
										}
										else if (*rendo == 'c') {
											rendo += 8; // strlen ("coarsest");
											if (*rendo == ' ') {
												++rendo;
												if (*rendo == 'b') {
													m_fallback = TKO_LOD_Fallback_Coarsest_Bounding;
													rendo += 8; // strlen ("bounding");
												}
												else {
													m_fallback = TKO_LOD_Fallback_Coarsest_None;
													rendo += 4; // strlen ("none");
												}
											}
											else
												m_fallback = TKO_LOD_Fallback_Coarsest;
										}
										else {
											rendo += 4; // strlen ("none");
											m_lod_options_value &= ~TKO_LOD_Fallback;
										}
									}
								}   break;

								case 'm': {
									if (rendo[1] == 'a') {      // max degree
										m_lod_options_mask |= TKO_LOD_Max_Degree;
										rendo += 10;    // strlen ("max degree");
										if (set) {
											++rendo;    // '='
											m_lod_options_value |= TKO_LOD_Max_Degree;
											READ_INT (m_max_degree, rendo);
										}
									}
									else if (rendo[1] == 'i') { // min tringles
										m_lod_options_mask |= TKO_LOD_Min_Triangle_Count;
										m_lod_options_value |= TKO_LOD_Min_Triangle_Count;
										rendo += 19;    // strlen ("min triangle count=");
										READ_INT (m_min_triangle_count, rendo);
									}
									else if (rendo[1] == 'o') { // mode
										m_lod_options_mask |= TKO_LOD_Mode_Segment;
										rendo += 5;     // strlen ("mode=");
										if (rendo[0] == 's') {
											m_lod_options_value |= TKO_LOD_Mode_Segment;
											rendo += 7; // strlen ("segment");
										}
										else {
											m_lod_options_value &= ~TKO_LOD_Mode_Segment;
											rendo += 8; // strlen ("geometry");
										}
									}
								}   break;

								case 'n': {         // num levels
									int	    levels;

									m_lod_options_mask |= TKO_LOD_Num_Levels;
									m_lod_options_value |= TKO_LOD_Num_Levels;
									rendo += 11;    // strlen ("num levels=");
									READ_INT (levels, rendo);
									m_num_levels = (unsigned char)levels;
								}   break;

								case 'p': {         // preprocess
									m_lod_options_mask |= TKO_LOD_Preprocess;
									if (set)
										m_lod_options_value |= TKO_LOD_Preprocess;
									rendo += 10;    // strlen ("preprocess");
								}   break;

								case 'r': {         // ratio
									bool        local_paren = false;

									rendo += 6;     // strlen ("ratio=");
									m_lod_options_mask |= TKO_LOD_Ratio;
									m_lod_options_value |= TKO_LOD_Ratio;
									if (*rendo == '(') {
										local_paren = true;
										++rendo;
									}

									m_num_ratios = 0;
									while (1) {
										m_ratio[(int)m_num_ratios++] = read_float (rendo, &rendo);
										if (local_paren) {
											if (*rendo++ == ')')
												break;
											// otherwise we should have just skipped a ','
										}
										else
											break;
									}
								}   break;

								case 't': {         // threshold
									bool        local_paren = false;

									rendo += 10;    // strlen ("threshold=");
									m_lod_options_mask |= TKO_LOD_Threshold;
									m_lod_options_value |= TKO_LOD_Threshold;
									if (*rendo == '(') {
										local_paren = true;
										++rendo;
									}

									m_num_thresholds = 0;
									m_threshold_type = TKO_LOD_Threshold_Distance;

									while (1) {
										m_threshold[(int)m_num_thresholds++] = read_float (rendo, &rendo);
										while (*rendo == ' ')
											++rendo;
										if (*rendo == 't') {
											if (rendo[2] == 'p') {
												m_threshold_type = TKO_LOD_Threshold_Tris_Per_Pix_Sq;
												rendo += 6; // strlen ("tppix2");
											}
											else {
												m_threshold_type = TKO_LOD_Threshold_Tris_Per_CM_Sq;
												rendo += 5; // strlen ("tpcm2");
											}
										}
										else if (*rendo == '%') {
											m_threshold_type = TKO_LOD_Threshold_Percent_Area;
											rendo += 6; // strlen ("% area");
										}
										if (local_paren) {
											if (*rendo++ == ')')
												break;
											// otherwise we should have just skipped a ','
										}
										else
											break;
									}
								}   break;

								case 'u': {         // usefulness heuristic
									rendo += 20;    // strlen ("usefulness heuristic");
									m_lod_options_mask |= TKO_LOD_Usefulness_Heuristic;
									if (set) {
										m_lod_options_value |= TKO_LOD_Usefulness_Heuristic;
										++rendo;    // '='
										if (*rendo == 't') {   // triangle size
											m_heuristic = TKO_LOD_Heur_Triangle_Size;
											rendo += 13;    // strlen ("triangle size");
										}
										else {
											if (*rendo == 'd') {        // diagonal [something]
												rendo += 8; // strlen ("diagonal");
												m_heuristic = TKO_LOD_Heur_Is_Diagonal;
											}
											else {
												rendo += 6; // strlen ("volume");
												m_heuristic = TKO_LOD_Heur_Is_Volume;
											}

											if (*rendo == ' ') {
												if (*++rendo == 'r') {
													m_heuristic |= TKO_LOD_Heur_Is_Ratio;
													rendo += 5; // strlen ("ratio");
													if (*rendo == ' ')
														++rendo;
												}

												if (*++rendo == 'p') {
													m_heuristic |= TKO_LOD_Heur_Is_Per_Triangle;
													rendo += 12;    // strlen ("per triangle");
												}
											}
										}
									}
								}   break;

								default:
									return tk.Error("interpret parse error");
							}

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}
					}
				}
				else {                      // lighting interpolation
					// Not this way, it sets all bits even if we have a single option
 					//INTERPRET_RENDO ("lighting interpolation",  TKO_Interp_Lighting);
					rendo += 22;	// strlen (lighting interpolation");

					if (set) {
						bool        paren = false;

						if (*rendo == '=') {
							++rendo;    // '='

							if (*rendo == '(') {
								paren = true;
								++rendo;
							}

							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								switch (*rendo) {
									case 'g': {
										switch (rendo[2]) {
											case 'o': {
												INTERPRET_RENDO_EXTENDED ("gooch", TKO_Interp_Lighting_Gooch);
											} break;

											case 'u': {
												INTERPRET_RENDO ("gouraud",   TKO_Interp_Lighting_Gouraud);
											} break;

											default:    return tk.Error("interpret parse error");
										}
									} break;
									case 'f': {
										if (!set)
											INTERPRET_RENDO ("faces",   TKO_Interp_Lighting_Faces);
										else {
											rendo += 6; // strlen ("faces=");

											switch (*rendo) {
												case 'g': {
													switch (rendo[2]) {
														case 'o': {
															INTERPRET_RENDO_EXTENDED ("gooch", TKO_Interp_Lighting_Faces_Gooch);
														} break;

														case 'u': {
															INTERPRET_RENDO ("gouraud",   TKO_Interp_Lighting_Faces_Gouraud);
														} break;

														default:    return tk.Error("interpret parse error");
													}
												} break;

												case 'p': {
													INTERPRET_RENDO ("phong",   TKO_Interp_Lighting_Faces_Phong);
												} break;

												default:    return tk.Error("interpret parse error");
											}
										}
									}   break;

									case 'e': {
										if (!set)
											INTERPRET_RENDO ("edges",   TKO_Interp_Lighting_Edges);
										else {
											rendo += 6; // strlen ("edges=");

											switch (*rendo) {
												case 'g': {
													switch (rendo[2]) {
														case 'o': {
															INTERPRET_RENDO_EXTENDED ("gooch", TKO_Interp_Lighting_Edges_Gooch);
														} break;

														case 'u': {
															INTERPRET_RENDO ("gouraud",   TKO_Interp_Lighting_Edges_Gouraud);
														} break;

														default:    return tk.Error("interpret parse error");
													}
												} break;

												case 'p': {
													INTERPRET_RENDO ("phong",   TKO_Interp_Lighting_Edges_Phong);
												} break;

												default:    return tk.Error("interpret parse error");
											}
										}
									}   break;

									case 'p': {
										INTERPRET_RENDO ("phong",   TKO_Interp_Lighting_Phong);
									} break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*rendo == ')') {
									++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (paren)
										++rendo;
									else
										break;
								}
							}
						}
						else {
							m_mask[0] |= TKO_Interp_Lighting;
							m_value[0] |= TKO_Interp_Lighting_Gouraud;
						}
					}
					else {
						m_mask[0] |= TKO_Interp_Lighting;
					}
				}
			}   break;

			case 'm': {
				INTERPRET_RENDO_EXTENDED ("mask transform", TKO_Rendo_Mask_Transform);

				if (set) {
					if (*rendo != '=')
						m_mask_transform = TKO_Mask_All;
					else {
						bool        paren = false;

						rendo++;        // '='

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						m_mask_transform = TKO_Mask_None;
						while (*rendo) {
							switch (*rendo) {
								case 'c': {
									rendo += 6;     // strlen ("camera");

									if (*rendo != '=')
										m_mask_transform |= TKO_Mask_Camera;
									else {
										bool        cparen = false;

										rendo++;        // '='

										if (*rendo == '(') {
											cparen = true;
											++rendo;
										}

										while (*rendo) {
											switch (*rendo) {
												case 'p': {
													rendo += 11;    // strlen ("perspective");
													m_mask_transform |= TKO_Mask_Camera_Perspective;
												}   break;

												case 'r': {
													rendo += 8;     // strlen ("rotation");
													m_mask_transform |= TKO_Mask_Camera_Rotation;
												}   break;

												case 's': {
													rendo += 5;     // strlen ("scale");
													m_mask_transform |= TKO_Mask_Camera_Scale;
												}   break;

												case 't': {
													rendo += 11;    // strlen ("tranlsation");
													m_mask_transform |= TKO_Mask_Camera_Translation;
												}   break;

												default:
													return tk.Error("interpret parse error");
											}

											if (*rendo == ')') {
												if(cparen)
													++rendo;
												break;
											}
											else if (*rendo == ',') {
												if (cparen)
													++rendo;
												else
													break;
											}
										}
									}
								}   break;

								case 'm': {
									rendo += 5;     // strlen ("model");

									if (*rendo != '=')
										m_mask_transform |= TKO_Mask_Model;
									else {
										bool        mparen = false;

										rendo++;        // '='

										if (*rendo == '(') {
											mparen = true;
											++rendo;
										}

										while (*rendo) {
											switch (*rendo) {
												case 'r': {
													rendo += 8;     // strlen ("rotation");
													m_mask_transform |= TKO_Mask_Model_Rotation;
												}   break;

												case 's': {
													rendo += 5;     // strlen ("scale");
													m_mask_transform |= TKO_Mask_Model_Scale;
												}   break;

												case 't': {
													rendo += 11;    // strlen ("tranlsation");
													m_mask_transform |= TKO_Mask_Model_Translation;
												}   break;

												default:
													return tk.Error("interpret parse error");
											}

											if (*rendo == ')') {
												if (mparen) 
													++rendo;
												break;
											}
											else if (*rendo == ',') {
												if (mparen)
													++rendo;
												else
													break;
											}
										}
									}
								}   break;

								default:
									return tk.Error("interpret parse error");
							}

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}
					}
				}
			}   break;

			case 'n': {
				if (rendo[6] == 'c') {              // nurbs curve
					INTERPRET_RENDO ("nurbs curve",     TKO_Rendo_NURBS_Curve_Options);

					if (set) {
						bool        paren = false;

						rendo++;        // '='

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						m_nurbs_options_mask &= ~TKO_NURBS_Curve_Mask;
						m_nurbs_options_value &= ~TKO_NURBS_Curve_Mask;

						while (*rendo) {
							set = true;

							if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
								set = false;
								rendo += 3; // strlen ("no ");
							}

							switch (*rendo) {
								case 'b': {
									m_nurbs_options_mask |= TKO_NURBS_Curve_Budget;
									rendo += 7;     // strlen ("budget=");
									if (set) {
										m_nurbs_options_value |= TKO_NURBS_Curve_Budget;
										READ_INT (m_curve_budget, rendo);
									}
								}   break;

								case 'c': {
									m_nurbs_options_mask |= TKO_NURBS_Curve_Continued_Budget;
									rendo += 16;    // strlen ("continued budget");
									if (set) {
										++rendo;    // '='
										m_nurbs_options_value |= TKO_NURBS_Curve_Continued_Budget;
										READ_INT (m_curve_continued_budget, rendo);
									}
								}   break;

								case 'm': {
									if (rendo[4] == 'a') {
										m_nurbs_options_mask |= TKO_NURBS_Curve_Max_Angle;
										rendo += 10;     // strlen ("max angle=");
										m_nurbs_options_value |= TKO_NURBS_Curve_Max_Angle;
										m_curve_max_angle = read_float (rendo, &rendo);
									}
									else if (rendo[4] == 'd') {
										m_nurbs_options_mask |= TKO_NURBS_Curve_Max_Deviation;
										rendo += 14;     // strlen ("max deviation=");
										m_nurbs_options_value |= TKO_NURBS_Curve_Max_Deviation;
										m_curve_max_deviation = read_float (rendo, &rendo);
									}
									else if (rendo[4] == 'l') {
										m_nurbs_options_mask |= TKO_NURBS_Curve_Max_Length;
										rendo += 11;     // strlen ("max length=");
										m_nurbs_options_value |= TKO_NURBS_Curve_Max_Length;
										m_curve_max_length = read_float (rendo, &rendo);
									}
								}   break;

								case 'v': {
									m_nurbs_options_mask |= TKO_NURBS_Curve_View_Dependent;
									if (set)
										m_nurbs_options_value |= TKO_NURBS_Curve_View_Dependent;
									SKIP_AHEAD (rendo);
								}   break;

								default:
									return tk.Error("interpret parse error");
							}

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}
					}
				}
				else if (rendo[6] == 's') {         // nurbs surface
					INTERPRET_RENDO ("nurbs surface",   TKO_Rendo_NURBS_Surface_Options);

					if (set) {
						bool        paren = false;

						rendo++;        // '='

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						m_nurbs_options_mask &= ~TKO_NURBS_Surface_Mask;
						m_nurbs_options_value &= ~TKO_NURBS_Surface_Mask;

						while (*rendo) {
							set = true;

							if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
								set = false;
								rendo += 3; // strlen ("no ");
							}

							switch (*rendo) {
								case 'b': {
									m_nurbs_options_mask |= TKO_NURBS_Surface_Budget;
									rendo += 7;     // strlen ("budget=");
									m_nurbs_options_value |= TKO_NURBS_Surface_Budget;
									READ_INT (m_surface_budget, rendo);
								}   break;

								case 'm': {
									if (rendo[4] == 'f') {
										if (rendo[10] == 'a') {
											m_nurbs_options_mask |= TKO_NURBS_Surface_Max_Facet_Angle;
											rendo += 16;     // strlen ("max facet angle=");
											m_nurbs_options_value |= TKO_NURBS_Surface_Max_Facet_Angle;
											m_surface_max_facet_angle = read_float (rendo, &rendo);
										}
										else if (rendo[10] == 'd') {
											m_nurbs_options_mask |= TKO_NURBS_Surface_Max_Facet_Deviation;
											rendo += 20;     // strlen ("max facet deviation=");
											m_nurbs_options_value |= TKO_NURBS_Surface_Max_Facet_Deviation;
											m_surface_max_facet_deviation = read_float (rendo, &rendo);
										}
										else if (rendo[10] == 'w') {
											m_nurbs_options_mask |= TKO_NURBS_Surface_Max_Facet_Width;
											rendo += 16;     // strlen ("max facet width=");
											m_nurbs_options_value |= TKO_NURBS_Surface_Max_Facet_Width;
											m_surface_max_facet_width = read_float (rendo, &rendo);
										}
									}
									else if (rendo[4] == 't') {
										m_nurbs_options_mask |= TKO_NURBS_Surface_Max_Trim_Curve_Deviation;
										rendo += 25;    // strlen ("max trim curve deviation=")
										m_nurbs_options_value |= TKO_NURBS_Surface_Max_Trim_Curve_Deviation;
										m_surface_max_trim_curve_deviation = read_float (rendo, &rendo);
									}
								}   break;

								case 't': {
									m_nurbs_options_mask |= TKO_NURBS_Surface_Trim_Budget;
									if (rendo[5] == 'b')    // handle both forms shown by different Hoops versions
										rendo += 12;    // strlen ("trim budget=");
									else
										rendo += 18;    // strlen ("trim curve budget=");
									m_nurbs_options_value |= TKO_NURBS_Surface_Trim_Budget;
									READ_INT (m_surface_trim_budget, rendo);
								}   break;

								default:
									return tk.Error("interpret parse error");
							}

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}
					}
				}

				if ((m_nurbs_options_mask & TKO_NURBS_Extended_Mask) != 0)
					m_nurbs_options_mask |= TKO_NURBS_Extended;
			}   break;

			case 'p': {
				INTERPRET_RENDO ("perspective correction",  TKO_Rendo_Perspective_Correction);
			}   break;

			case 'q': {
				// quantization
				INTERPRET_RENDO ("quantization",            TKO_Rendo_Quantization);

				if (set) {
					rendo++;        // '='

					switch (*rendo) {
						case 't': {
							rendo += 9;     // strlen ("threshold");
							m_tq |= TKO_Quantization_Threshold;
						}   break;

						case 'd': {
							rendo += 6;     // strlen ("dither");
							m_tq |= TKO_Quantization_Dither;
						}   break;

						case 'e': {
							rendo += 15;    // strlen ("error diffusion");
							m_tq |= TKO_Quantization_Error_Diffusion;
						}   break;

						default:
							return tk.Error("interpret parse error");
					}
				}
			}   break;

			case 'r': {
				// radiosity or ray-trace (these we can just skip past for now)
				RENDO_NOT_IMPLEMENTED ("A.I.R. options");
			}   break;

			case 's': {
				if (rendo[1] == 'c') {  
					if (rendo[2] == 'r'){// screen range
						INTERPRET_RENDO_EXTENDED ("screen range",	TKO_Rendo_Screen_Range);

						if (set) {
							rendo += 2; // strlen ("=(");
							m_screen_range[0] = read_float (rendo, &rendo);
							++rendo;    // ','
							m_screen_range[1] = read_float (rendo, &rendo);
							++rendo;    // ','
							m_screen_range[2] = read_float (rendo, &rendo);
							++rendo;    // ','
							m_screen_range[3] = read_float (rendo, &rendo);
							++rendo;    // ')'
						}
					}
					else if(rendo[2] == 'a') {
						INTERPRET_RENDO_EXTENDED2("scaled displacement", TKO_Rendo_Scaled_Displacement);
					}
				}
				else if (rendo[1] == 'i') {		// simple shadow
					if (rendo[7] == 's') {
						INTERPRET_RENDO_EXTENDED ("simple shadow",	TKO_Rendo_Simple_Shadow);

						if (set) {
							bool        paren = false;

							rendo++;        // '='

							if (*rendo == '(') {
								paren = true;
								++rendo;
							}

							m_simple_shadow = 0;
							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								switch (*rendo) {
									case 'a': {
										m_simple_shadow |= TKO_Simple_Shadow_Auto;
										rendo += 4; // strlen ("auto");
									}   break;

									case 'b': {
										int	    blur;

										m_simple_shadow |= TKO_Simple_Shadow_Blur;
										rendo += 9;	    // strlen ("blurring=");
										READ_INT (blur, rendo);
										m_simple_shadow_blur = (unsigned char)blur;
									}   break;

									case 'c': {
										char		string[256];
										char *		sp = string;
										char        sysop[2048];

										rendo += 6;	    // strlen ("color=");
										if (*rendo == '\'') {
											++rendo;    // initial '
											do *sp++ = *rendo++;
											while (*rendo != '\'');
												++rendo;    // final '
											*sp = '\0';
										}
										else {
											do *sp++ = *rendo++;
											while (*rendo != ',' && *rendo != ')');
											*sp = '\0';
										}

										// should be a valid color, but guard just in case...
										HC_Show_One_System_Option ("errors", sysop);
										HC_Define_System_Options ("no errors");

										if (HC_Compute_Color (string, "rgb", m_simple_shadow_color))
											m_simple_shadow |= TKO_Simple_Shadow_Color;

										{
											char		newsysop[2048];

											sprintf (newsysop, "errors=(%s)", sysop);
											HC_Define_System_Options (newsysop);
										}
									}   break;

									case 'i': {
										rendo += 19;	// strlen ("ignore transparency");
										if (set)
											m_simple_shadow |= TKO_Simple_Shadow_Ignore_Transparency;
										else
											m_simple_shadow |= TKO_Simple_Shadow_Use_Transparency;
									}   break;

									case 'l': {
										m_simple_shadow |= TKO_Simple_Shadow_Light_Direction;
										rendo += 7;     // strlen ("light=(");
										m_simple_shadow_light[0] = read_float (rendo, &rendo);
										++rendo;	    // ','
										m_simple_shadow_light[1] = read_float (rendo, &rendo);
										++rendo;	    // ','
										m_simple_shadow_light[2] = read_float (rendo, &rendo);
										++rendo;	    // ')'
									}   break;

									case 'o': {
										if (rendo[1] == 'p') {
											m_simple_shadow |= TKO_Simple_Shadow_Opacity;
											rendo += 8; // strlen ("opacity=");
											m_simple_shadow_opacity = read_float (rendo, &rendo);
										}
										else if (rendo[1] == 'n') {
											m_simple_shadow |= TKO_Simple_Shadow_On;
											rendo += 2; // strlen ("on");
										}
										else {
											m_simple_shadow |= TKO_Simple_Shadow_Off;
											rendo += 3; // strlen ("off");
										}
									}   break;

									case 'p': {
										m_simple_shadow |= TKO_Simple_Shadow_Plane;
										rendo += 7;     // strlen ("plane=(");
										m_simple_shadow_plane[0] = read_float (rendo, &rendo);
										++rendo;	    // ','
										m_simple_shadow_plane[1] = read_float (rendo, &rendo);
										++rendo;	    // ','
										m_simple_shadow_plane[2] = read_float (rendo, &rendo);
										++rendo;	    // ','
										m_simple_shadow_plane[3] = read_float (rendo, &rendo);
										++rendo;	    // ')'
									}   break;

									case 'r': {
										int	    res;

										m_simple_shadow |= TKO_Simple_Shadow_Resolution;
										rendo += 11;    // strlen ("resolution=");
										READ_INT (res, rendo);
										m_simple_shadow_resolution = (unsigned short)res;
									}   break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*rendo == ')') {
									++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (paren)
										++rendo;
									else
										break;
								}
							}
							if ((m_simple_shadow & 0xFF00) != 0)
								m_simple_shadow |= TKO_Simple_Shadow_Extended;
						}
						else
							m_simple_shadow = TKO_Simple_Shadow_Off;
					}
					else {
						INTERPRET_RENDO_EXTENDED ("simple reflection",	TKO_Rendo_Simple_Reflection);

						if (set) {
							bool        paren = false;

							rendo++;        // '='

							if (*rendo == '(') {
								paren = true;
								++rendo;
							}

							m_simple_reflection = 0;
							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								switch (*rendo) {
									case 'a': { // attenuation
										m_simple_reflection |= TKO_Simple_Reflection_Attenuation;
										rendo += 11; // strlen ("attenuation");
										if (set) {
											rendo += 9; // strlen ("=(hither=");
											m_simple_reflection_hither = read_float (rendo, &rendo);
											rendo += 5; // strlen (",yon=");
											m_simple_reflection_yon = read_float (rendo, &rendo);
											++rendo;    // ')'
										}
										else 
											m_simple_reflection_hither = m_simple_reflection_yon = 0;
									} break;

									case 'b': {
										m_simple_reflection |= TKO_Simple_Reflection_Blur;
										rendo += 4; // strlen ("blur");
										if (set) {
											rendo++;        // '='
											READ_INT (m_simple_reflection_blur, rendo);
										}
										else
											m_simple_reflection_blur = 0;
									}   break;

									case 'f': {
										if (set)
											m_simple_reflection |= TKO_Simple_Reflection_Fading_On;
										else
											m_simple_reflection |= TKO_Simple_Reflection_Fading_Off;
										rendo += 6; // strlen ("fading");
									}   break;

									case 'o': {
										if (rendo[1] == 'p') {
											m_simple_reflection |= TKO_Simple_Reflection_Opacity;
											rendo += 8; // strlen ("opacity=");
											m_simple_reflection_opacity = read_float (rendo, &rendo);
										}
										else if (rendo[1] == 'n') {
											m_simple_reflection |= TKO_Simple_Reflection_On;
											rendo += 2; // strlen ("on");
										}
										else {
											m_simple_reflection |= TKO_Simple_Reflection_Off;
											rendo += 3; // strlen ("off");
										}
									}   break;

									case 'p': {
										m_simple_reflection |= TKO_Simple_Reflection_Plane;
										rendo += 7;     // strlen ("plane=(");
										m_simple_reflection_plane[0] = read_float (rendo, &rendo);
										++rendo;	    // ','
										m_simple_reflection_plane[1] = read_float (rendo, &rendo);
										++rendo;	    // ','
										m_simple_reflection_plane[2] = read_float (rendo, &rendo);
										++rendo;	    // ','
										m_simple_reflection_plane[3] = read_float (rendo, &rendo);
										++rendo;	    // ')'
									}   break;

									case 'v': {
										m_simple_reflection |= TKO_Simple_Reflection_Visibility;
										rendo += 10;     // strlen ("visibility");

										if (set) {
											if (*rendo != '=') {
												m_simple_reflection_visibility_mask =
													m_simple_reflection_visibility_value = TKO_Geo_All_Visibles;
											}
											else {
												bool        vparen = false;

												++rendo;
												if (*rendo == '(') {
													vparen = true;
													++rendo;
												}

												while (*rendo) {
													set = true;

													if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
														set = false;
														rendo += 3; // strlen ("no ");
													}

													switch (*rendo) {
														case 'c': {
															if (rendo[3] == 't')
																INTERPRET_REFLECTION_VIS ("cutting plane",	TKO_Geo_Cutting_Plane);
															else
																INTERPRET_REFLECTION_VIS ("cut geometry",	TKO_Geo_Cut_Geometry);
														}   break;

														case 'e': {
															INTERPRET_REFLECTION_VIS ("edge",         TKO_Geo_Edge);
														}   break;

														case 'f': {
															INTERPRET_REFLECTION_VIS ("face",         TKO_Geo_Face);
														}   break;

														case 'g': {
															INTERPRET_REFLECTION_VIS ("geometry",     TKO_Geo_Geom_Visibles);
														}   break;

														case 'i': {
															INTERPRET_REFLECTION_VIS ("image",        TKO_Geo_Image);
														}   break;

														case 'l': {
															if (rendo[2] == 'g')
																INTERPRET_REFLECTION_VIS ("lighting", TKO_Geo_Light_Visibles);
															else
																INTERPRET_REFLECTION_VIS ("line",     TKO_Geo_Line);
														}   break;

														case 'm': {
															if (rendo[6] == ' ' && rendo[7] == 'o')
																INTERPRET_REFLECTION_VIS ("marker only",  TKO_Geo_Marker);
															else
																INTERPRET_REFLECTION_VIS ("marker",       TKO_Geo_Marker | TKO_Geo_Vertex_Vis);
														}   break;

														case 'v': {
															INTERPRET_REFLECTION_VIS ("vertex",       TKO_Geo_Vertex_Vis);
														}   break;

														case 'p': {
															INTERPRET_REFLECTION_VIS ("polygon",      TKO_Geo_Face | TKO_Geo_Edge);
														}   break;

														case 's': {
															if (rendo[1] == 'h')
																INTERPRET_REFLECTION_VIS ("shadows",  TKO_Geo_Shadow_Visibles);
															else
																INTERPRET_REFLECTION_VIS ("string cursor",
																								TKO_Geo_String_Cursor);
														}   break;

														case 't': {
															INTERPRET_REFLECTION_VIS ("text",         TKO_Geo_Text);
														}   break;

														case 'w': {
															INTERPRET_REFLECTION_VIS ("window",       TKO_Geo_Window);
														}   break;

														default:
															return tk.Error("interpret parse error");
													}

													if (*rendo == ')') {
														if (vparen)
															++rendo;
														break;
													}
													else if (*rendo == ',') {
														if (vparen)
															++rendo;
														else
															break;
													}
												}
											}
										}
										else {
											m_simple_reflection_visibility_mask = TKO_Geo_Geom_Visibles;
											m_simple_reflection_visibility_value = 0;
										}
									}   break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*rendo == ')') {
									++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (paren)
										++rendo;
									else
										break;
								}
							}
						}
						else
							m_simple_reflection = TKO_Simple_Reflection_Off;
					}
				}
				else if (rendo[1] == 'h') {		// shadow map
					INTERPRET_RENDO_EXTENDED ("shadow map",	TKO_Rendo_Shadow_Map);

					if (set) {
						bool        paren = false;

						rendo++;        // '='

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						m_shadow_map = 0;
						while (*rendo) {
							set = true;

							if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
								set = false;
								rendo += 3; // strlen ("no ");
							}

							switch (*rendo) {
								case 'o': {
									if (rendo[1] == 'n') {
										m_shadow_map |= TKO_Shadow_Map_On;
										rendo += 2; // strlen ("on");
									}
									else {
										m_shadow_map |= TKO_Shadow_Map_Off;
										rendo += 3; // strlen ("off");
									}
								}   break;

								case 'j': {
									if (set)
										m_shadow_map |= TKO_Shadow_Map_Jitter_On;
									else
										m_shadow_map |= TKO_Shadow_Map_Jitter_Off;
									rendo += 6; // strlen ("jitter");
								}   break;

								case 'r': {
									int	    res;

									m_shadow_map |= TKO_Shadow_Map_Resolution;
									rendo += 11;    // strlen ("resolution=");
									READ_INT (res, rendo);
									m_shadow_map_resolution = (unsigned short)res;
								}   break;

								case 's': {
									int	    samples;

									m_shadow_map |= TKO_Shadow_Map_Samples;
									rendo += 8;    // strlen ("samples=");
									READ_INT (samples, rendo);
									m_shadow_map_samples = (unsigned char)samples;
								}   break;

								case 'v': {
									if (rendo[5] == 'd') {
										m_shadow_map |= TKO_Shadow_Map_View_Depedent_On;
										rendo += 14;    // strlen ("view dependent");
									}
									else {
										m_shadow_map |= TKO_Shadow_Map_View_Depedent_Off;
										rendo += 16;    // strlen ("view independent");
									}
								}   break;

								default:
									return tk.Error("interpret parse error");
							}

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}
					}
					else
						m_shadow_map = TKO_Shadow_Map_Off;
				}
				else if (rendo[1] == 'o') {                     // software frame buffer options
					INTERPRET_RENDO ("software frame buffer options",   TKO_Rendo_Buffer_Options);

					if (set) {
						bool        paren = false;

						rendo++;        // '='

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						m_buffer_options_mask = 0;
						m_buffer_options_value = 0;

						while (*rendo) {
							set = true;

							if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
								set = false;
								rendo += 3; // strlen ("no ");
							}

							switch (*rendo) {
								case 'c': {
									int         choice;

									rendo += 12;    // strlen ("color depth=");
									if (*rendo == 'm')
										choice = TKO_Buffer_Color_Depth_Match;
									else
										choice = TKO_Buffer_Color_Depth_Full;

									m_buffer_options_mask |= choice;
									m_buffer_options_value |= choice;
									SKIP_AHEAD (rendo);
								}   break;

								case 'r': {
									m_buffer_options_mask |= TKO_Buffer_Retention;
									if (set)
										m_buffer_options_value |= TKO_Buffer_Retention;
									SKIP_AHEAD (rendo);
								}   break;

								case 's': {
									m_buffer_options_mask |= TKO_Buffer_Size_Limit;
									rendo += 10;    // strlen ("size limit");
									if (set) {
										m_buffer_options_value |= TKO_Buffer_Size_Limit;
										++rendo;    // '='
										READ_INT (m_buffer_size_limit, rendo);
										++rendo;    // ' '
										if (*rendo == 'b')
											m_buffer_size_limit = -m_buffer_size_limit;
									}
									SKIP_AHEAD (rendo);
								}   break;

								default:
									return tk.Error("interpret parse error");
							}

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}
					}
				}
				else if (rendo[6] == ' ' && rendo[7] == 's') {  // stereo separation
					INTERPRET_RENDO ("stereo separation",   TKO_Rendo_Stereo_Separation);

					if (set) {
						++rendo;    // '='
						m_stereo_separation = read_float (rendo, &rendo);
					}
				}
				else if (rendo[6] == ' ' && rendo[7] == 'd') {  // stereo distance
					INTERPRET_RENDO_EXTENDED ("stereo distance",   TKO_Rendo_Stereo_Distance);

					if (set) {
						++rendo;    // '='
						m_stereo_distance = read_float (rendo, &rendo);
					}
				}
				else {                                          // stereo
					INTERPRET_RENDO ("stereo",              TKO_Rendo_Stereo);
				}
			}   break;

			case 't': {
				if (rendo[2] == 'c') {  // technology
					INTERPRET_RENDO ("technology",          TKO_Rendo_Technology);

					if (set) {
						bool        paren = false;

						rendo++;        // '='

						if (*rendo == '(') {
							paren = true;
							++rendo;
						}

						while (*rendo) {
							if (streqn (rendo, "sta", 3)) {
								rendo += 8;     // strlen ("standard");
								m_tq |= TKO_Technology_Standard;
							}
							else if (streqn (rendo, "sof", 3)) {
								rendo += 21;    // strlen ("software frame buffer");
								m_tq |= TKO_Technology_Soft_Frame_Buffer;
							}
							else if (streqn (rendo, "rad", 3)) {
								rendo += 9;     // strlen ("radiosity");
								m_tq |= TKO_Technology_Radiosity;
							}
							else if (streqn (rendo, "ray", 3)) {
								rendo += 9;     // strlen ("ray-trace");
								m_tq |= TKO_Technology_Ray_Trace;
							}
							else
									return tk.Error("interpret parse error");

							if (*rendo == ')') {
								++rendo;
								break;
							}
							else if (*rendo == ',') {
								if (paren)
									++rendo;
								else
									break;
							}
						}
					}
				}
				else if (rendo[2] == 's') {  // tessellation
					bool        paren = false;

					INTERPRET_RENDO_EXTENDED ("tessellation",	TKO_Rendo_Tessellation);

					m_tessellations = 0;

					rendo++;        // '='

					if (*rendo == '(') {
						paren = true;
						++rendo;
					}

					while (*rendo) {
						switch (*rendo) {
							case 'c': {         // cylinder
								bool        local_paren = false;

								rendo += 9; // strlen ("cylinder=");
								m_tessellations |= TKO_Tessellation_Cylinder;
								if (*rendo == '(') {
									local_paren = true;
									++rendo;
								}

								m_num_cylinder = 0;
								while (1) {
									int             ct;

									READ_INT (ct, rendo);
									m_cylinder[(int)m_num_cylinder++] = (char)ct;

									if (local_paren) {
										if (*rendo++ == ')')
											break;
										// otherwise we should have just skipped a ','
									}
									else
										break;
								}
							}   break;

							case 's': {         // cylinder
								bool        local_paren = false;

								rendo += 7; // strlen ("sphere=");
								m_tessellations |= TKO_Tessellation_Sphere;
								if (*rendo == '(') {
									local_paren = true;
									++rendo;
								}

								m_num_sphere = 0;
								while (1) {
									int             ct;

									READ_INT (ct, rendo);
									m_sphere[(int)m_num_sphere++] = (char)ct;

									if (local_paren) {
										if (*rendo++ == ')')
											break;
										// otherwise we should have just skipped a ','
									}
									else
										break;
								}
							}   break;


							default:
								return tk.Error("interpret parse error");
						}

						if (*rendo == ')') {
							++rendo;
							break;
						}
						else if (*rendo == ',') {
							if (paren)
								++rendo;
							else
								break;
						}
					}
				}
				else  if (rendo[2] == 'x') {    // texture interpolation
					// Not this way, it sets all bits even if we have a single option
					//INTERPRET_RENDO ("texture interpolation",   TKO_Interp_Texture);
					rendo += 21;	// strlen ("texture interpolation");

					if (set) {
						bool        paren = false;

						if (*rendo == '=') {
							++rendo;    // '='

							if (*rendo == '(') {
								paren = true;
								++rendo;
							}

							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								switch (*rendo) {
									case 'f': {
										INTERPRET_RENDO ("faces",       TKO_Interp_Texture_Faces);
									}   break;

									case 'e': {
										INTERPRET_RENDO ("edges",       TKO_Interp_Texture_Edges);
									}   break;

									case 'm': {
										INTERPRET_RENDO ("markers",     TKO_Interp_Texture_Markers);
									}   break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*rendo == ')') {
									++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (paren)
										++rendo;
									else
										break;
								}
							}
						}
						else {
							m_mask[0] |= TKO_Interp_Texture;
							m_value[0] |= TKO_Interp_Texture;
						}
					}
					else {
						m_mask[0] |= TKO_Interp_Texture;
					}
				}
				else {      // transparency options
					bool        paren = false;

					rendo += 21;    // strlen ("transparency options=");

					if (*rendo == '(') {
						paren = true;
						++rendo;
					}

					while (*rendo) {
						set = true;

						if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
							set = false;
							rendo += 3; // strlen ("no ");
						}

						if (streqn (rendo, "style", 5)) {
							INTERPRET_RENDO_EXTENDED ("style",       TKO_Rendo_Transparency_Style);
							++rendo;	// "=");

							m_transparency_options &= ~TKO_Transparency_Style_Mask;
							if (streqn (rendo, "ble", 3)) {
								rendo += 8;     // strlen ("blending");
								m_transparency_options |= TKO_Transparency_Blending;
							}
							else if (streqn (rendo, "scr", 3)) {
								rendo += 11;    // strlen ("screen door");
								m_transparency_options |= TKO_Transparency_Screen_Door;
							}
							else if (streqn (rendo, "off", 3)) {
								rendo += 3;     // strlen ("off");
								m_transparency_options |= TKO_Transparency_None;
							}
							else
								return tk.Error("interpret parse error");
						}
						else if (streqn (rendo, "hardware", 8)) {
							INTERPRET_RENDO_EXTENDED ("hardware acceleration",	TKO_Rendo_Transparency_Hardware);
						}
						else if (streqn (rendo, "depth writing", 13)) {
							INTERPRET_RENDO_EXTENDED ("depth writing",	TKO_Rendo_Transparency_Depth_Writing);
						}
						else if (streqn (rendo, "hsr ", 4)) {
							INTERPRET_RENDO ("hsr algorithm",	TKO_Rendo_THSR_Algorithm);
							++rendo;	// "="

							m_hsr &= ~TKO_Rendo_THSR_Algorithm;
							if (streqn (rendo, "pai", 3)) {
								rendo += 8;     // strlen ("painters");
								m_hsr |= TKO_HSR_Painters << 4;
							}
							else if (streqn (rendo, "z s", 3)) {
								rendo += 11;    // strlen ("z sort only");
								m_hsr |= TKO_HSR_Z_Sort_Only << 4;
							}
							else if (streqn (rendo, "non", 3)) {
								rendo += 4;     // strlen ("none");
								m_hsr |= TKO_HSR_None << 4;
							}
							else if (streqn (rendo, "dep", 3)) {
								rendo += 13;    // strlen ("depth peeling");
								m_hsr |= TKO_HSR_Depth_Peeling << 4;
							}
							else
								return tk.Error("interpret parse error");
						}
						else if (streqn (rendo, "depth", 5)) {
							bool        dpparen = false;

							INTERPRET_RENDO_EXTENDED ("depth peeling options",	TKO_Rendo_Transparency_Options);
							++rendo;	// "="

							if (*rendo == '(') {
								dpparen = true;
								++rendo;
							}

							while (*rendo) {
								set = true;

								if (rendo[0] == 'n' && rendo[1] == 'o' && rendo[2] == ' ') {
									set = false;
									rendo += 3; // strlen ("no ");
								}

								if (rendo[0] == 'l') {
									int			layers;

									m_transparency_options |= TKO_Transparency_Peeling_Layers;
									rendo += 7;	// strlen ("layers=");
									READ_INT (layers, rendo);
									m_depth_peeling_layers = (unsigned char)layers;
								}
								else if (rendo[0] == 'm') {
									m_transparency_options |= TKO_Transparency_Peeling_Min_Area;
									rendo += 12;	// strlen ("minimum area");
									if (set) {
										++rendo;	// "="
										m_depth_peeling_min_area = read_float (rendo, &rendo);
										if (*rendo == '%')
											++rendo;
										else {
											rendo += 7;	// strlen (" pixels");
											m_depth_peeling_min_area = -m_depth_peeling_min_area;
										}
									}
									else
										m_depth_peeling_min_area = 0.0f;
								}
								else
									return tk.Error("interpret parse error");

								if (*rendo == ')') {
									if (dpparen)
										++rendo;
									break;
								}
								else if (*rendo == ',') {
									if (dpparen)
										++rendo;
									else
										break;
								}
							}
						}
						else if (streqn (rendo, "zsort", 5)) {
							INTERPRET_RENDO_EXTENDED ("zsort options=",	TKO_Rendo_Transparency_Options);
							if (rendo[0] == 'f') {
								rendo += 7;    // strlen ("fastest");
								m_transparency_options |= TKO_Transparency_ZSort_Fast;
							}
							else if (rendo[0] == 'n') {
								rendo += 6;    // strlen ("nicest");
								m_transparency_options |= TKO_Transparency_ZSort_Nice;
							}
							else
								return tk.Error("interpret parse error");
						}
						else
							return tk.Error ("unrecognised transparency option");

						if (*rendo == ')') {
							++rendo;
							break;
						}
						else if (*rendo == ',') {
							if (paren)
								++rendo;
							else
								break;
						}
					}

					if ((m_transparency_options & TKO_Transparency_Extended_Mask) != 0)
						m_transparency_options |= TKO_Transparency_Extended;
				}
			}   break;

			case 'v': {
				if (rendo[8] == 'e') {
					INTERPRET_RENDO_EXTENDED ("vertex decimation",     TKO_Rendo_Vertex_Decimation);

					if (set) {
						++rendo; // "="
						m_vertex_decimation = read_float (rendo, &rendo);
					}
				}
				else {
					INTERPRET_RENDO_EXTENDED ("vertex displacement",   TKO_Rendo_Vertex_Displacement);

					if (set) {
						rendo++;    // '='
						READ_INT (m_vertex_displacement, rendo);
					}
				}
			}   break;

			default:
				return tk.Error("interpret parse error");
		}

		if (*rendo == ',')
			++rendo;
	}

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}


// skip the name, clear & set appropriate mask/value bits

#define INTERPRET_HEUR(name, bits) do {             \
			m_mask |= (bits);                       \
			if (set)                                \
				m_value |= (bits);                  \
			heur += strlen (name);                  \
		} while (0)                                //


TK_Status HTK_Heuristics::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            heuristics[2048];
	char const *    heur = heuristics;

	HC_Show_Heuristics (heuristics);

	m_mask = m_value = 0;
	m_extras = 0;
	m_ordered_weights_mask = 0;
	m_culling = 0;

	while (*heur) {
		bool            set = true;

		if (streqn (heur, "no ", 3)) {
			set = false;
			heur += 3;  // strlen ("no ");
		}

		switch (*heur) {
			case 'b': {
				INTERPRET_HEUR ("backplane culls",                  TKO_Heuristic_Backplane_Cull);
			}   break;

			case 'c': {
				if (heur[1] == 'l')
					INTERPRET_HEUR ("clipping",                     TKO_Heuristic_Clipping);
				else if (heur[1] == 'o')
					INTERPRET_HEUR ("concave polygons",             TKO_Heuristic_Concave_Polygons);
				else {
					INTERPRET_HEUR ("culling",                      TKO_Heuristic_Culling);

					if (set) {
						if (*heur == '=') {
							bool        paren = false;

							++heur;    // '='

							if (*heur == '(') {
								paren = true;
								++heur;
							}

							m_culling = 0;
							while (*heur) {
								set = true;

								// not sure if these can be negated
								if (heur[0] == 'n' && heur[1] == 'o' && heur[2] == ' ') {
									set = false;
									heur += 3; // strlen ("no ");
								}

								switch (*heur) {
									case 'o': {
										heur += 11; //strlen ("obscuration");
										m_pixel_threshold = 0;
										if (set) {
											m_culling |= TKO_Heur_Obscuration_Culling;
											if (*heur == '=') {
												bool		cparen = false;

												++heur;    // '='

												if (*heur == '(') {
													cparen = true;
													++heur;
												}

												while (*heur) {
													set = true;

													// not sure if these can be negated
													if (heur[0] == 'n' && heur[1] == 'o' && heur[2] == ' ') {
														set = false;
														heur += 3; // strlen ("no ");
													}

													switch (*heur) {
														case 'p': {
															heur += 16;	//strlen ("pixel threshold=");
															READ_INT (m_pixel_threshold, heur);
														}	break;
														case 'u': {
															heur += 10;	//strlen ("use octree");
															if (set)
																m_culling |= TKO_Heur_Obscuration_Use_Octree;
														}	break;

														default:
															return tk.Error("interpret parse error");
													}

													if (*heur == ')') {
														if (cparen)
															++heur;
														break;
													}
													else if (*heur == ',') {
														if (cparen)
															++heur;
														else
															break;
													}
												}
											}
										}
										else
											m_culling |= TKO_Heur_Obscuration_Culling_Off;
									}   break;

									case 'h': {
										heur += 11;	//strlen ("hard extent");
										if (set) {
											m_culling |= TKO_Heur_Hard_Extent_Culling;
											if (*heur == '=') {
												++heur;	// '='
												READ_INT (m_hard_extent, heur);
											}
											else
												m_hard_extent = 1;
										}
										else
											m_culling |= TKO_Heur_Extent_Culling_Off;
									}   break;


									case 'm': {
										heur += 14;	//strlen ("maximum extent");
										if (*heur == ' ' && heur[1] == 'm') {
											heur += 5; //strlen (" mode");
											m_culling |= TKO_Heur_Maximum_Extent_Mode;
											if (*heur == '=') {
												++heur; // '='
											}
											switch (*heur) {
												case 'b':
													heur += 8; //strlen ("bounding")
													m_maximum_extent_mode = TKO_Heur_Max_Extent_Mode_Bounding;
													break;
												case 'd':
													if (heur[1] == 'e') {
														heur += 5; //strlen ("defer")
														m_maximum_extent_mode = TKO_Heur_Max_Extent_Mode_Defer;
													}
													else {
														heur += 3; //strlen ("dot")
														m_maximum_extent_mode = TKO_Heur_Max_Extent_Mode_Dot;
													}
													break;
												case 'n':
													heur += 4; //strlen ("none")
													m_maximum_extent_mode = TKO_Heur_Max_Extent_Mode_None;
													break;
												default:
													m_maximum_extent_mode = 0;
											} 
											break;
										}
										else if (*heur == ' ' && heur[1] == 'l') {
											heur += 6; //strlen (" level");
											m_culling |= TKO_Heur_Maximum_Extent_Level;
											m_maximum_extent_level = TKO_Heur_Max_Extent_Level_All;

											if (*heur == '=') {
												++heur; // '='
												m_maximum_extent_level = TKO_Heur_Max_Extent_Level_None;

												bool        lparen = false;

												if (*heur == '(') {
													lparen = true;
													++heur;
												}

												while (*heur) {
													set = true;

													// not sure if these can be negated
													if (heur[0] == 'n' && heur[1] == 'o' && heur[2] == ' ') {
														set = false;
														heur += 3; // strlen ("no ");
													}

													switch (*heur) {
														case 's':
															heur += 7; //strlen ("segment")
															m_maximum_extent_level = TKO_Heur_Max_Extent_Level_Segment;
															break;
														case 'g':
															heur += 9; //strlen ("geometry")
															m_maximum_extent_level = TKO_Heur_Max_Extent_Level_Geometry;
															break;
														case 'p':
															heur += 9; //strlen ("primitive")
															m_maximum_extent_level = TKO_Heur_Max_Extent_Level_Primitive;
															break;
														case 'd':
															heur += 7; //strlen ("default")
															m_maximum_extent_level = TKO_Heur_Max_Extent_Level_All;
															break;
														default:
															m_maximum_extent_mode = 0;
													} 

													if (*heur == ')') {
														++heur;
														break;
													}
													else if (*heur == ',') {
														if (lparen)
															++heur;
														else
															break;
													}
												}
											}
											break;
										}
										else if (set) {
											m_culling |= TKO_Heur_Extent_Culling;
											if (*heur == '=') {
												++heur;	// '='
												READ_INT (m_maximum_extent, heur);
											}
											else
												m_maximum_extent = 1;
										}
										else
											m_culling |= TKO_Heur_Extent_Culling_Off;
									}   break;

									case 'v': {
										if (heur[1] == 'i') {
											heur += 12; //strlen ("view frustum");
											if (set)
												m_culling |= TKO_Heur_View_Frustum_Culling;
											else
												m_culling |= TKO_Heur_View_Frustum_Culling_Off;
										}
										else {
											heur += 6; // strlen ("vector")
											if (heur[0] == ' ' && heur[1] == 't') {
												heur += 10; // strlen (" tolerance")
												if (heur[0] == '=') {
													++heur;
													m_vector_tolerance = read_float(heur, &heur);
													m_culling |= TKO_Heur_Vector_Tolerance;
												}
												else {
													m_culling |= TKO_Heur_Vector_Tolerance_Off;
												}	
											}
											else {
												if (heur[0] == '=') {
													heur += 2; // strlen ("=(")
													m_vector[0] = read_float(heur, &heur);
													++heur; // ','
													m_vector[1] = read_float(heur, &heur);
													++heur; // ','
													m_vector[2] = read_float(heur, &heur);
													++heur; // ')'
													m_culling |= TKO_Heur_Vector_Culling;
												}
												else {
													m_culling |= TKO_Heur_Vector_Culling_Off;
												}
											}

										}
									}   break;

									default:
										return tk.Error("interpret parse error");
								}

								if (*heur == ')') {
									++heur;
									break;
								}
								else if (*heur == ',') {
									if (paren)
										++heur;
									else
										break;
								}
							}
						}
						else {
							m_culling = TKO_Heur_View_Frustum_Culling|
										TKO_Heur_Obscuration_Culling|
										TKO_Heur_Extent_Culling;
							m_pixel_threshold = 0;
							m_maximum_extent = 1;
						}
					}
				}
			}   break;

			case 'd': {
				INTERPRET_HEUR ("detail selection",                 TKO_Heuristic_Detail_Selection);
			}   break;

			case 'e': {
				INTERPRET_HEUR ("exclude bounding",                 TKO_Heuristic_Exclude_Bounding);
			}   break;

			case 'f': {
				INTERPRET_HEUR ("force defer batch",				TKO_Heuristic_Force_Defer);
				if (set) {
					heur++;    // '='
					READ_INT (m_force_defer, heur);
				}
			}   break;

			case 'h': {
				INTERPRET_HEUR ("hidden surfaces",                  TKO_Heuristic_Hidden_Surfaces);
			}   break;

			case 'i': {
				if (heur[2] == 'c')
					INTERPRET_HEUR ("incremental updates",          TKO_Heuristic_Incremental_Updates);
				else if (heur[5] == 's')
					INTERPRET_HEUR ("intersecting polygons",        TKO_Heuristic_Intersecting_Polygons);
				else {
					heur += 24;	// strlen ("internal selection limit");

					if (set) {
						heur++;    // '='
						if ('0' <= *heur && *heur <= '9' || *heur == '-') {
							m_mask |= TKO_Heuristic_Internal_Select_Limit;
							m_value |= TKO_Heuristic_Internal_Select_Limit;

							READ_INT (m_internal_shell, heur);
							m_internal_polyline = m_internal_shell;
						}
						else {
							bool        paren = false;

							if (*heur == '(') {
								paren = true;
								++heur;
							}

							while (*heur) {
								set = true;

								if (streqn (heur, "no ", 3)) {
									set = false;
									heur += 3;  // strlen ("no ");
								}

								switch (*heur) {
									case 'p': {
										INTERPRET_HEUR ("polyline",	TKO_Heuristic_Internal_Polyline_Limit);
										heur += 8;	// strlen ("polyline");
										if (set) {
											heur++;    // '='
											READ_INT (m_internal_polyline, heur);
										}
									}   break;
									case 's': {
										INTERPRET_HEUR ("shell",	TKO_Heuristic_Internal_Shell_Limit);
										if (set) {
											heur++;    // '='
											READ_INT (m_internal_shell, heur);
										}
									}   break;
								}

								if (*heur == ')') {
									++heur;
									break;
								}
								else if (*heur == ',') {
									if (paren)
										++heur;
									else
										break;
								}
							}
						}
					}
					else {
						m_mask |= TKO_Heuristic_Internal_Select_Limit;
					}
				}
			}   break;

			case 'm': {
				if (heur[1] == 'e')
					INTERPRET_HEUR ("memory purge",					TKO_Heuristic_Memory_Purge);
				else {
					INTERPRET_HEUR ("model type=",					TKO_Heuristic_Model_Type);
					if (heur[0] == 'd') {
						m_model_type = TKO_Heur_Model_Type_Default;
						heur += 7;	// strlen ("default");
					}
					else /* if (heur[0] == 'l') */ {
						m_model_type = TKO_Heur_Model_Type_LMV;
						heur += 3;	// strlen ("lmv");
					}
				}
			}   break;

			case 'o': {
				if (heur[8] == 'd') {
					INTERPRET_HEUR ("ordered drawing",				TKO_Heuristic_Ordered_Drawing);
					if (*heur == '=') {
						if (heur[1] == 'u') {						
							m_mask |= TKO_Heuristic_Ordered_Unit;
							m_value |= TKO_Heuristic_Ordered_Unit;
						}
						else {
							m_mask |= TKO_Heuristic_Ordered_Grid;
							m_value |= TKO_Heuristic_Ordered_Grid;

						}
						heur += 5;	// strlen ("=unit") or strlen ("=grid");
					}
				}
				else {
					bool        paren = false;

					m_mask |= TKO_Heuristic_Ordered_Weights;
					m_value |= TKO_Heuristic_Ordered_Weights;
					heur += 16;	// strlen ("ordered weights=");

					if (*heur == '(') {
						paren = true;
						++heur;
					}

					while (*heur) {
						int			weights_mask, i;
						float		value;

						switch (*heur) {
							case 'd': {
								if (heur[2] == 's') {
									weights_mask = 1<<TKO_Heur_Order_Distance;
									heur += 9;	// strlen ("distance=");
								}
								else if (heur[2] == 'v') {
									weights_mask = 1<<TKO_Heur_Order_Divergence;
									heur += 11;	// strlen ("divergence=");
								}
								else /* if (heur[2] == 'n') */ {
									weights_mask = 1<<TKO_Heur_Order_Density;
									heur += 8;	// strlen ("density=");
								}
							}   break;

							case 'e': {
								weights_mask = (1<<TKO_Heur_Order_Count)-1;
								heur += 11;	// strlen ("everything=");
							}   break;

							case 'p': {
								weights_mask = 1<<TKO_Heur_Order_Priority;
								heur += 9;	// strlen ("priority=");
							}   break;

							case 's': {
								weights_mask = 1<<TKO_Heur_Order_Screen_Extent;
								heur += 14;	// strlen ("screen extent=");
							}   break;

							case 'w': {
								weights_mask = 1<<TKO_Heur_Order_World_Volume;
								heur += 13;	// strlen ("world volume=");
							}   break;

							default:
								return tk.Error("interpret parse error");
						}

						value = read_float (heur, &heur);

						m_ordered_weights_mask |= weights_mask;
						for (i=0; i<TKO_Heur_Order_Count; i++)
							if (weights_mask & (1<<i))
								m_ordered_weights[i] = value;


						if (*heur == ')') {
							++heur;
							break;
						}
						else if (*heur == ',') {
							if (paren)
								++heur;
							else
								break;
						}
					}
				}
			}   break;

			case 'p': {
				if (heur[1] == 'a')
					INTERPRET_HEUR ("partial erase",                TKO_Heuristic_Partial_Erase);
				else if (heur[8] == 'c')
					INTERPRET_HEUR ("polygon crossings",            TKO_Heuristic_Polygon_Crossings);
				else {
					INTERPRET_HEUR ("polygon handedness",           TKO_Heuristic_Polygon_Handedness);

					if (set) {
						heur++;    // '='
						if (*heur == 'l') {
							m_extras |= TKO_Heur_Extra_Left_Handed_Polys;
							heur += 4;  // strlen ("left");
						}
						else
							heur += 5;  // strlen ("right");
					}
				}
			}   break;

			case 'q': {
				INTERPRET_HEUR ("quick moves",                      TKO_Heuristic_Quick_Moves);

				if (set && *heur == '=') {
					heur += 9;  // strlen ("=spriting");
					m_extras |= TKO_Heur_Extra_Quick_Move_Spriting;
				}
			}   break;

			case 'r': {
				INTERPRET_HEUR ("related selection limit",          TKO_Heuristic_Related_Select_Limit);

				if (set) {
					heur++;    // '='
					READ_INT (m_related, heur);
				}
			}   break;

			case 's': {
				if (heur[1] == 'e') {
					if (heur[10] == 'l') {
						INTERPRET_HEUR ("selection level",			TKO_Heuristic_Selection_Level);

						heur++;    // '='
						if (streqn (heur, "segment tree", 12))
							m_selection_level = TKO_Heur_Selection_Level_Segment_Tree;
						else if (streqn (heur, "segment", 7))
							m_selection_level = TKO_Heur_Selection_Level_Segment;
						else if (streqn (heur, "entity", 6))
							m_selection_level = TKO_Heur_Selection_Level_Entity;
						SKIP_AHEAD (heur);
					}
					else
						INTERPRET_HEUR ("selection sorting",		TKO_Heuristic_Selection_Sorting);
				}
				else
					INTERPRET_HEUR ("static model",					TKO_Heuristic_Static);
			}   break;

			case 't': {
				INTERPRET_HEUR ("transformations",					TKO_Heuristic_Transformations);
			}   break;

			case 'v': {
				SKIP_AHEAD (heur);  // visual selection
			}   break;

			default:
				return tk.Error("interpret parse error");
		}

		if (*heur == ',')
			++heur;
	}

	if ((m_mask & TKO_Heuristic_Extended_Mask) != 0)
		m_mask |= TKO_Heuristic_Extended;

	if ((m_culling & TKO_Heur_Culling_Extended2_Mask) != 0)
		m_culling |= TKO_Heur_Culling_Extended2;
	if ((m_culling & TKO_Heur_Culling_Extended_Mask) != 0)
		m_culling |= TKO_Heur_Culling_Extended;

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}


// skip the name, clear & set appropriate mask/value bits

#define INTERPRET_GEOPT(name, bits) do {             \
			m_mask |= (bits);                       \
			opt += strlen (name);                  \
		} while (0)                                //


TK_Status HTK_Geometry_Options::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            options[2048];
	char const *    opt = options;

	HC_Show_Geometry_Options (key, options);

	m_mask = 0;
	m_value = 0;
	m_orientation_count = 0;

	while (*opt) {
		bool            set = true;

		if (streqn (opt, "no ", 3)) {
			set = false;
			opt += 3;  // strlen ("no ");
		}

		switch (*opt) {
			case 'c': {
				INTERPRET_GEOPT ("camera relative", TKO_Geometry_Options_Camera_Relative);
				if (set)
					m_value |= TKO_Geometry_Options_Camera_Relative;
			}   break;

			case 'o': {
				INTERPRET_GEOPT ("orientation", TKO_Geometry_Options_Orientation);
				opt += 2;	// strlen ("=(");
				do {
					m_orientation[(int)m_orientation_count++] = read_float (opt, &opt);
				} while (*opt++ != ')');	// skips each ',' or final ')'

				if (m_orientation_count != 3 && m_orientation_count != 6)
					return tk.Error("interpret parse error, unexpected orientation count");
			}   break;

			default:
				return tk.Error("interpret parse error");
		}

		if (*opt == ',')
			++opt;
	}

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}



TK_Status HTK_Text_Font::Interpret (BStreamFileToolkit & tk, HC_KEY key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
	char            text_font[4096];
	char const *    font = text_font;
	char            buffer[4096];
	int             i;

	HC_Show_Text_Font (text_font);

	m_mask = m_value = 0;
	m_renderers[0] = m_renderers[1] = -1;
	m_preferences[0] = m_preferences[1] = -1;
	m_renderer_cutoff = -1.0f;
	m_preference_cutoff = -1.0f;

	while (*font) {
		bool            set = true;

		if (streqn (font, "no ", 3)) {
			set = false;
			font += 3;  // strlen ("no ");
		}

		switch (*font) {
			case 'b': {
				// bold
				m_mask |= TKO_Font_Bold;
				font += 4; // strlen ("bold");
				if (set)
					m_value |= TKO_Font_Bold;
			}   break;

			case 'e': {
				// extra space
				m_mask |= TKO_Font_Extra_Space;
				m_value |= TKO_Font_Extra_Space;
				font += 12; // strlen ("extra space=");
				m_extra_space = read_float (font, &font);
				++font; // ' '
				i = 0;
				while (*font && *font != ',')
					buffer[i++] = *font++;
				buffer[i] = '\0';

				for (i = 0; i < (int)countof(generic_units_table); ++i) {
					if (streq (buffer, generic_units_table[i])) {
						m_space_units = (unsigned char)i;
						break;
					}
				}
			}   break;

			case 'f': {
				// fill edges
				m_mask |= TKO_Font_Fill_Edges;
				font += 10; // strlen ("fill edges");
				if (set)
					m_value |= TKO_Font_Fill_Edges;
			}   break;

			case 'g': {
				// greeking limit, greeking mode
				font += 9;	// strlen ("greeking ");
				switch (*font) {
					case 'l': {	// greeking limit
						m_mask |= TKO_Font_Greeking_Limit;
						font += 5; // strlen ("limit");
						if (set) {
							m_value |= TKO_Font_Greeking_Limit;
							++font;    // skip '='
							m_greeking_limit = read_float (font, &font);
							++font; // ' '
							i = 0;
							while (*font && *font != ',')
								buffer[i++] = *font++;
							buffer[i] = '\0';

							for (i = 0; i < (int)countof(generic_units_table); ++i) {
								if (streq (buffer, generic_units_table[i])) {
									m_greeking_units = (unsigned char)i;
									break;
								}
							}
						}
					}	break;
					case 'm': {	// greeking mode
						m_mask |= TKO_Font_Greeking_Mode;
						m_value |= TKO_Font_Greeking_Mode;
						font += 5; // strlen ("mode=");
						switch (*font) {
							case 'n': {
								m_greeking_mode = TKO_Font_Greeking_Mode_None;
								font += 4;	// strlen ("none");
							}	break;
							case 'l': {
								m_greeking_mode = TKO_Font_Greeking_Mode_Lines;
								font += 5;	// strlen ("lines");
							}	break;
							case 'b': {
								m_greeking_mode = TKO_Font_Greeking_Mode_Box;
								font += 3;	// strlen ("box");
							}	break;
						}
					}	break;
				}
			}   break;

			case 'i': {
				// italic
				m_mask |= TKO_Font_Italic;
				font += 6; // strlen ("italic");
				if (set)
					m_value |= TKO_Font_Italic;
			}   break;

			case 'l': {
				// line spacing
				m_mask |= TKO_Font_Line_Spacing;
				font += 12; // strlen ("line spacing");
				m_value |= TKO_Font_Line_Spacing;
				++font;    // skip '='
				m_line_spacing = read_float (font, &font);
			}   break;

			case 'n': {
				// name
				m_mask |= TKO_Font_Names;
				m_value |= TKO_Font_Names;
				font += 5;  // strlen ("name=");

				bool        paren = false;

				if (*font == '(') {
					paren = true;
					++font;
				}
				i = 0;
				while (*font && (paren || *font != ',')) {
					if (*font == ')') {
						++font;
						break;
					}
					buffer[i++] = *font++;
				}
				buffer[i] = '\0';
				set_names (buffer);
			}   break;

			case 'o': {
				// outline, overline
				switch (font[1]) {
					case 'u': {
						m_mask |= TKO_Font_Outline;
						font += 7;  // strlen ("outline");
						if (set)
							m_value |= TKO_Font_Outline;
					}   break;

					case 'v': {
						m_mask |= TKO_Font_Overline;
						font += 8;  // strlen ("overline");
						if (set)
							m_value |= TKO_Font_Overline;
					}   break;

					default:
						return tk.Error("interpret parse error");
				}
			}   break;

			case 'p': {
				// preference
				bool        paren = false;

				m_mask |= TKO_Font_Preference;
				m_value |= TKO_Font_Preference;
				font += 11;	// strlen ("preference=");

				if (*font == '(') {
					paren = true;
					++font;
				}

				while (*font) {
					if (streqn (font, "default", 7)) {
						m_preferences[0] = m_preferences[1] = TKO_Font_Preference_Default;
						font += 7;
					}
					else if (streqn (font, "outline", 7)) {
						m_preferences[0] = m_preferences[1] = TKO_Font_Preference_Outline;
						font += 7;
					}
					else if (streqn (font, "bitmap", 6)) {
						m_preferences[0] = m_preferences[1] = TKO_Font_Preference_Bitmap;
						font += 6;
					}
					else if (streqn (font, "exterior", 8)) {
						m_preferences[0] = m_preferences[1] = TKO_Font_Preference_Exterior;
						font += 8;
					}
					else if (streqn (font, "cutoff", 6)) {
						font += 7;	// strlen ("cutoff=");
						m_preference_cutoff = read_float (font, &font);
						++font; // ' '
						i = 0;
						while (*font && *font != ',' && *font != ')')
							buffer[i++] = *font++;
						buffer[i] = '\0';

						for (i = 0; i < (int)countof(generic_units_table); ++i) {
							if (streq (buffer, generic_units_table[i])) {
								m_preference_cutoff_units = (unsigned char)i;
								break;
							}
						}
					}
					else if (streqn (font, "no cutoff", 9)) {
						m_preference_cutoff = 0.0f;
						m_preference_cutoff_units = 0;
						font += 9;
					}
					else if (streqn (font, "smaller", 7)) {
						font += 8;	// strlen ("smaller=");
						if (streqn (font, "default", 7)) {
							m_preferences[0] = TKO_Font_Preference_Default;
							font += 7;
						}
						else if (streqn (font, "outline", 7)) {
							m_preferences[0] = TKO_Font_Preference_Outline;
							font += 7;
						}
						else if (streqn (font, "bitmap", 6)) {
							m_preferences[0] = TKO_Font_Preference_Bitmap;
							font += 6;
						}
						else if (streqn (font, "exterior", 8)) {
							m_preferences[0] = TKO_Font_Preference_Exterior;
							font += 8;
						}
						else
							return tk.Error("interpret parse error");
					}
					else if (streqn (font, "larger", 6)) {
						font += 7;	// strlen ("larger=");
						if (streqn (font, "default", 7)) {
							m_preferences[1] = TKO_Font_Preference_Default;
							font += 7;
						}
						else if (streqn (font, "outline", 7)) {
							m_preferences[1] = TKO_Font_Preference_Outline;
							font += 7;
						}
						else if (streqn (font, "bitmap", 6)) {
							m_preferences[1] = TKO_Font_Preference_Bitmap;
							font += 6;
						}
						else if (streqn (font, "exterior", 6)) {
							m_preferences[1] = TKO_Font_Preference_Exterior;
							font += 8;
						}
						else
							return tk.Error("interpret parse error");
					}
					else
						return tk.Error("interpret parse error");


					if (*font == ')') {
						++font;
						break;
					}
					else if (*font == ',') {
						if (paren)
							++font;
						else
							break;
					}
				}
			}   break;

			case 'r': {
				// renderer,rotation
				if (font[1] == 'e') {	// renderer
					bool        paren = false;

					m_mask |= TKO_Font_Renderer;
					m_value |= TKO_Font_Renderer;
					font += 9;	// strlen ("renderer=");

					if (*font == '(') {
						paren = true;
						++font;
					}

					while (*font) {
						if (streqn (font, "default", 7)) {
							m_renderers[0] = m_renderers[1] = TKO_Font_Renderer_Default;
							font += 7;
						}
						else if (streqn (font, "driver", 6)) {
							m_renderers[0] = m_renderers[1] = TKO_Font_Renderer_Driver;
							font += 6;
						}
						else if (streqn (font, "truetype", 8)) {
							m_renderers[0] = m_renderers[1] = TKO_Font_Renderer_Truetype;
							font += 8;
						}
						else if (streqn (font, "defined", 7)) {
							m_renderers[0] = m_renderers[1] = TKO_Font_Renderer_Defined;
							font += 7;
						}
						else if (streqn (font, "cutoff", 6)) {
							font += 7;	// strlen ("cutoff=");
							m_renderer_cutoff = read_float (font, &font);
							++font; // ' '
							i = 0;
							while (*font && *font != ',')
								buffer[i++] = *font++;
							buffer[i] = '\0';

							for (i = 0; i < (int)countof(generic_units_table); ++i) {
								if (streq (buffer, generic_units_table[i])) {
									m_renderer_cutoff_units = (unsigned char)i;
									break;
								}
							}
						}
						else if (streqn (font, "no cutoff", 9)) {
							m_renderer_cutoff = 0.0f;
							m_renderer_cutoff_units = 0;
							font += 9;
						}
						else if (streqn (font, "smaller", 7)) {
							font += 8;	// strlen ("smaller=");
							if (streqn (font, "default", 7)) {
								m_renderers[0] = TKO_Font_Renderer_Default;
								font += 7;
							}
							else if (streqn (font, "driver", 6)) {
								m_renderers[0] = TKO_Font_Renderer_Driver;
								font += 6;
							}
							else if (streqn (font, "truetype", 8)) {
								m_renderers[0] = TKO_Font_Renderer_Truetype;
								font += 8;
							}
							else if (streqn (font, "defined", 7)) {
								m_renderers[0] = TKO_Font_Renderer_Defined;
								font += 7;
							}
							else
								return tk.Error("interpret parse error");
						}
						else if (streqn (font, "larger", 6)) {
							font += 7;	// strlen ("larger=");
							if (streqn (font, "default", 7)) {
								m_renderers[1] = TKO_Font_Renderer_Default;
								font += 7;
							}
							else if (streqn (font, "driver", 6)) {
								m_renderers[1] = TKO_Font_Renderer_Driver;
								font += 6;
							}
							else if (streqn (font, "truetype", 8)) {
								m_renderers[1] = TKO_Font_Renderer_Truetype;
								font += 8;
							}
							else if (streqn (font, "defined", 7)) {
								m_renderers[1] = TKO_Font_Renderer_Defined;
								font += 7;
							}
							else
								return tk.Error("interpret parse error");
						}
						else
							return tk.Error("interpret parse error");


						if (*font == ')') {
							++font;
							break;
						}
						else if (*font == ',') {
							if (paren)
								++font;
							else
								break;
						}
					}
				}
				else {					// rotation
					m_mask |= TKO_Font_Rotation;
					font += 8;  // strlen ("rotation");
					if (set) {
						m_value |= TKO_Font_Rotation;
						++font;    // skip '='
						if (*font == 'f') {
							m_rotation = -1.0f;                 // follow path flagged by negative buffer
							SKIP_AHEAD (font);
						}
						else
							m_rotation = read_float (font, &font);
					}
				}
			}   break;

			case 's': {
				// size, size tolerance, slant, strikethrough
				switch (font[4]) {
					case '=': {
						// size
						m_mask |= TKO_Font_Size;
						m_value |= TKO_Font_Size;
						font += 5;  // strlen ("size=");
						m_size = read_float (font, &font);
						++font; // ' '
						i = 0;
						while (*font && *font != ',')
							buffer[i++] = *font++;
						buffer[i] = '\0';

						for (i = 0; i < (int)countof(generic_units_table); ++i) {
							if (streq (buffer, generic_units_table[i])) {
								m_size_units = (unsigned char)i;
								break;
							}
						}
					}   break;

					case ' ': {
						// size tolerance
						m_mask |= TKO_Font_Size_Tolerance;
						m_value |= TKO_Font_Size_Tolerance;
						font += 15; // strlen ("size tolerance=");
						m_tolerance = read_float (font, &font);
						++font; // ' '
						i = 0;
						while (*font && *font != ',')
							buffer[i++] = *font++;
						buffer[i] = '\0';

						for (i = 0; i < (int)countof(generic_units_table); ++i) {
							if (streq (buffer, generic_units_table[i])) {
								m_tolerance_units = (unsigned char)i;
								break;
							}
						}
					}   break;

					case 'k': {
						// strikethrough
						m_mask |= TKO_Font_Strikethrough;
						font += 13; // strlen ("strikethrough");
						if (set)
							m_value |= TKO_Font_Strikethrough;
					}   break;

					case 't': {
						// slant
						m_mask |= TKO_Font_Slant;
						font += 5;  // strlen ("slant");
						if (set) {
							m_value |= TKO_Font_Slant;
							++font;    // skip '='
							m_slant = read_float (font, &font);

							if (*font == ' ') { // should be " degrees", just skip
								++font;
								while (*font && *font != ',')
									++font;
							}
						}
					}   break;

					default:
						return tk.Error("interpret parse error");
				}
			}   break;

			case 't': {
				// transforms
				m_mask |= TKO_Font_Transforms;
				font += 10; // strlen ("transforms");
				if (set) {
					m_value |= TKO_Font_Transforms;
					if (*font == '=')
						m_transforms = TKO_Font_Transform_Position_Only;
					else
						m_transforms = TKO_Font_Transform_Full;
					SKIP_AHEAD (font);
				}
			}   break;

			case 'u': {
				// underline, uniform spacing
				switch (font[2]) {
					case 'd': {
						m_mask |= TKO_Font_Underline;
						font += 9;  // strlen ("underline");
						if (set)
							m_value |= TKO_Font_Underline;
					}   break;

					case 'i': {
						m_mask |= TKO_Font_Uniform_Spacing;
						font += 15; // strlen ("uniform spacing");
						if (set)
							m_value |= TKO_Font_Uniform_Spacing;
					}   break;

					default:
						return tk.Error("interpret parse error");
				}
			}   break;

			case 'w': {
				// width scale
				m_mask |= TKO_Font_Width_Scale;
				font += 11; // strlen ("width scale");
				if (set) {
					m_value |= TKO_Font_Width_Scale;
					++font;    // skip '='
					m_width_scale = read_float (font, &font);
				}
			}   break;

			default:
				return tk.Error("interpret parse error");
		}

		if (*font == ',')
			++font;
	}

	if ((m_mask & TKO_Font_Extended2_Mask) != 0)
		m_mask |= TKO_Font_Extended2;
	if ((m_mask & TKO_Font_Extended_Mask) != 0)
		m_mask |= TKO_Font_Extended;

	return TK_Normal;
#else
	return tk.Error (stream_readonly);
#endif
}

