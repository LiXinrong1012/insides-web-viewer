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
// $Header: /files/homes/master/cvs/hoops_master/hoops_stream/source/pattern.cpp,v 1.46 2010-01-21 23:37:54 covey Exp $
//

#include "HStream.h"
#include "BInternal.h"


////////////////////////////////////////
// These arrays must match the lists in TKO_Enumerations

static char const * line_patterns[] = {
	"-", "-.", "- -", ".", "-..", "-...", "-- --", "center", "phantom", "finedot"
};
// older patterns do not need to mention any trailing patterns that are still the same
static char const * older_line_patterns[] = {
    "---", "-.-", "- -", "..."
};

static char const * fill_patterns[] = {
    "#", "|", "=", "/", "\\", "<>", ":", "[]", "solid", "clear",
    "n", "ne", "e", "se", "s", "sw", "w", "nw",
    "blend", "invisible"
};

static char const * marker_symbols[] = {
    "o",            "(.)",  "(+)",  "(x)",  "(())", "@",
                    ".",    "+",    "x",            "*",
    "[]",           "[.]",          "[x]",          "[*]",
    "<>",           "<.>",  "<+>",                  "<*>",
    "/\\",  "^/\\", "/.\\",                         "/*\\",     "^/*\\",
    "\\/",  "v\\/", "\\./",                         "\\*/",     "v\\*/",
    "|>",   ">|>",  "|.>",                          "|*>",      ">|*>",
    "<|",   "<<|",  "<.|",                          "<*|",      "<<*|",

    "#",    "++",   "/ \\", "/_\\",
    "|",    "/",    "\\",   "/__\\",    "/_^_\\",
    "y",    "z",
};

// old type alignments just an enumerated array
static char const * text_alignments[] = {
    "v<", "^<", "*<", "v>", "^>", "*>", "v*", "^*", "**", ".<", ".>", ".*"
};

static char const * text_justifications[] = {
    "unspecified", "[", "|", "]"
};

#if 0
static char const * booleans[] = {
    "off", "on"
};
#endif

static char const * window_frames[] = {
    "off", "on", "single", "off, inset", "on, inset", "single, inset", "off, no inset",
	"on, decorative", "single, decorative", "on, inset, decorative", "single, inset, decorative",
};

static char const * handedness[] = {
    "left", "right"
};

////////////////////////////////////////


TK_Status HTK_Enumerated::Execute (BStreamFileToolkit & tk) alter {
    HStreamFileToolkit &    htk = *(HStreamFileToolkit *)&tk;
    TK_Status       status = TK_Normal;

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

    switch (Opcode()) {
        case TKE_Face_Pattern:
            HC_Set_Face_Pattern (fill_patterns[(int)m_index]);
            break;

        case TKE_Window_Pattern:
            if (htk.GetHoopsVersion() < 850 && m_index > 9)
                HC_Set_Window_Pattern ("solid");    // can't handle gradients
            else
                HC_Set_Window_Pattern (fill_patterns[(int)m_index]);
            break;

        case TKE_Marker_Symbol:
            HC_Set_Marker_Symbol (marker_symbols[(int)m_index]);
            break;

        case TKE_Text_Alignment:
			if ((m_index & TKO_Text_Alignment_New_Format) != 0) {
				if ((m_index & TKO_Text_Alignment_Unspecified) != TKO_Text_Alignment_Unspecified) {
					char	a[8];
					char *	ap = a;

					if ((m_index & TKO_Text_Alignment_Point) != 0)
						*ap++ = '.';

					if ((m_index & TKO_Text_Alignment_Left) != 0)
						*ap++ = '<';
					else if ((m_index & TKO_Text_Alignment_Right) != 0)
						*ap++ = '>';
					else
						*ap++ = '*';

					if ((m_index & TKO_Text_Alignment_Bottom) != 0)
						*ap++ = 'v';
					else if ((m_index & TKO_Text_Alignment_Top) != 0)
						*ap++ = '^';
					else
						*ap++ = '*';

					*ap++ = '\0';
					HC_Set_Text_Alignment (a);
				}

				int		j = (m_index & TKO_Text_Justification_Mask) >> TKO_Text_Justification_Shift;

				if (j != 0)
					HC_Set_Text_Alignment (text_justifications[j]);
			}
			else {
				if ((m_index & 0x0F) < countof (text_alignments))
					HC_Set_Text_Alignment (text_alignments[m_index & 0x0F]);
				if (((m_index >> 4) & 0x0F) != 0)
					HC_Set_Text_Alignment (text_justifications[(m_index >> 4) & 0x0F]);
			}
            break;

        case TKE_Window_Frame:
            HC_Set_Window_Frame (window_frames[(int)m_index]);
            break;

        case TKE_Handedness:
            HC_Set_Handedness (handedness[(int)m_index]);
            break;

        default:
            status = tk.Error();
            break;
    }

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

    return status;
}

TK_Status HTK_Enumerated::Interpret (BStreamFileToolkit & tk, ID_Key key, int variant) alter {
    UNREFERENCED(key);
    UNREFERENCED(variant);
#ifndef HSTREAM_READONLY
    TK_Status       status = TK_Normal;
    char            value[32];
    int             i;

    switch (Opcode()) {
        case TKE_Face_Pattern: {
            HC_Show_Face_Pattern (value);
            for (i = 0; i < countof(fill_patterns); ++i) {
                if (streq (value, fill_patterns[i])) {
                    m_index = (char)i;
                    break;
                }
            }
        }   break;

        case TKE_Window_Pattern: {
            HC_Show_Window_Pattern (value);
            for (i = 0; i < countof(fill_patterns); ++i) {
                if (streq (value, fill_patterns[i])) {
                    m_index = (char)i;
                    break;
                }
            }
        }   break;

        case TKE_Marker_Symbol: {
            HC_Show_Marker_Symbol (value);
            for (i = 0; i < countof(marker_symbols); ++i) {
                if (streq (value, marker_symbols[i])) {
                    m_index = (char)i;
                    break;
                }
            }
        }   break;

        case TKE_Text_Alignment: {
            char const *    cp = value;

            HC_Show_Text_Alignment (value);

			if (tk.GetTargetVersion() >= 1780) {
				if (*cp == '.' || *cp == '<' || *cp == '*' || *cp == '>') {	// any normal alignment should start with one of these
					m_index = TKO_Text_Alignment_Center;

					if (*cp == '.') {
						m_index |= TKO_Text_Alignment_Point;
						++cp;
					}

					if (*cp == '<') {
						m_index |= TKO_Text_Alignment_Left;
						++cp;
					}
					else if (*cp == '>') {
						m_index |= TKO_Text_Alignment_Right;
						++cp;
					}
					else	// '*'
						++cp;

					if (*cp == 'v') {
						m_index |= TKO_Text_Alignment_Bottom;
						++cp;
					}
					else if (*cp == '^') {
						m_index |= TKO_Text_Alignment_Top;
						++cp;
					}
					else	// '*'
						++cp;
				}
				else
					m_index = TKO_Text_Alignment_Unspecified;

				if (*cp) {
					for (i = 1; i < countof(text_justifications); ++i) {
						if (streq (cp, text_justifications[i])) {
							m_index |= i << TKO_Text_Justification_Shift;
							break;
						}
					}
				}

				m_index |= TKO_Text_Alignment_New_Format;
			}
			else {
				// old enum format
				for (i = 0; i < countof(text_alignments); ++i) {
					if (streqn (cp, text_alignments[i], strlen (text_alignments[i]))) {
						m_index = (char)i;
						cp += strlen (text_alignments[i]);
						break;
					}
				}
				if (i == countof(text_alignments)) {
					if (streqn (cp, ".", 1))
						m_index = TKO_Text_Alignment_Insertion_Left;
					else
						m_index = 0x0F;
				}

				if (*cp) {
					for (i = 1; i < countof(text_justifications); ++i) {
						if (streq (cp, text_justifications[i])) {
							m_index |= i << 4;
							break;
						}
					}
				}
			}
        }   break;

        case TKE_Window_Frame: {
            HC_Show_Window_Frame (value);
            for (i = 0; i < countof(window_frames); ++i) {
                if (streq (value, window_frames[i])) {
                    m_index = (char)i;
                    break;
                }
            }
        }   break;

        case TKE_Handedness: {
            HC_Show_Handedness (value);
            for (i = 0; i < countof(handedness); ++i) {
                if (streq (value, handedness[i])) {
                    m_index = (char)i;
                    break;
                }
            }
        }   break;

        default:
            return tk.Error();
    }

    return status;
#else
    return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE_OPCODE (HTK_Enumerated);

////////////////////////////////////////

TK_Status HTK_Linear_Pattern::Execute (BStreamFileToolkit & tk) alter {
    TK_Status       status = TK_Normal;
    char            assembled[32];

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

    assembled[0] = '\0';
    switch ((m_pattern >> 8) & 0x0F) {
        case 0:                                 break;
        case 1:     strcat (assembled, "(");    break;
        case 2:     strcat (assembled, "[");    break;
        default:    status = tk.Error();        break;
    }
    strcat (assembled, line_patterns[m_pattern & 0x00FF]);
    switch ((m_pattern >> 12) & 0x0F) {
        case 0:                                 break;
        case 1:     strcat (assembled, ")");    break;
        case 2:     strcat (assembled, "|");    break;
        default:    status = tk.Error();        break;
    }

    switch (Opcode()) {
        case TKE_Line_Pattern:
            HC_Set_Line_Pattern (assembled);
            break;

        case TKE_Edge_Pattern:
            HC_Set_Edge_Pattern (assembled);
            break;

        default:
            return tk.Error();
    }

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

    return status;
}

TK_Status HTK_Linear_Pattern::Interpret (BStreamFileToolkit & tk, ID_Key key, int variant) alter {
    UNREFERENCED(key);
    UNREFERENCED(variant);
#ifndef HSTREAM_READONLY
    TK_Status       status = TK_Normal;
    char            * value = new char[1024*32];
    char *			p = value;
    int             i;

    switch (Opcode()) {
        case TKE_Line_Pattern:
            HC_Show_Line_Pattern (value);
            break;

        case TKE_Edge_Pattern:
            HC_Show_Edge_Pattern (value);
            break;

        default:
			delete [] value;
            return tk.Error();
    }

    m_pattern = 0;

	// any cap specified?
    if (p[0] == '(') {
        m_pattern |= 1 << 8;
        ++p;
    }
    else if (p[0] == '[') {
        m_pattern |= 2 << 8;
        ++p;
    }

	// any join specified?
	i = (int)strlen (p) - 1;
    if (p[i] == ')') {
        m_pattern |= 1 << 12;
		p[i] = '\0';
	}
    else if (p[i] == '|') {
        m_pattern |= 2 << 12;
		p[i] = '\0';
	}

	// anything left must be a pattern
	for (i = 0; i < countof(older_line_patterns); ++i) {
		if (streq (p, older_line_patterns[i])) {
			m_pattern |= i;
			break;
		}
	}
    if (i == countof(older_line_patterns)) {
		for (i = 0; i < countof(line_patterns); ++i) {
			if (streq (p, line_patterns[i])) {
				m_pattern |= i;
				break;
			}
		}
    }

	delete [] value;
    return status;
#else
    return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE_OPCODE (HTK_Linear_Pattern);

////////////////////////////////////////

TK_Status HTK_Named::Execute (BStreamFileToolkit & tk) alter {
    TK_Status       status = TK_Normal;

	if (tk.GeometryIsOpen()) {
		HC_KEY					last_key;

		if ((status = tk.GetLastKey(last_key)) != TK_Normal)
			return status;
		HC_Open_Geometry (last_key);
	}

    if (m_name_length > 0) switch (Opcode()) {
        case TKE_Marker_Symbol:
			HC_Set_Marker_Symbol (m_name);
			break;

        case TKE_Line_Pattern:
			if (m_index == -1)
				HC_Set_Line_Pattern (m_name);
			else //if (m_index == -2)
				HC_Set_Line_Pattern_Explicit (m_name);
			break;

        case TKE_Edge_Pattern:
			if (m_index == -1)
				HC_Set_Edge_Pattern (m_name);
			else //if (m_index == -2)
				HC_Set_Edge_Pattern_Explicit (m_name);
			break;
    }
    else switch (Opcode()) {
        case TKE_Line_Pattern:
        case TKE_Edge_Pattern: {
			char            assembled[32];

			assembled[0] = '\0';
			switch ((m_index >> 8) & 0x0F) {
				case 0:                                 break;
				case 1:     strcat (assembled, "(");    break;
				case 2:     strcat (assembled, "[");    break;
				default:    status = tk.Error();        break;
			}
			strcat (assembled, line_patterns[m_index & 0x00FF]);
			switch ((m_index >> 12) & 0x0F) {
				case 0:                                 break;
				case 1:     strcat (assembled, ")");    break;
				case 2:     strcat (assembled, "|");    break;
				default:    status = tk.Error();        break;
			}

			if (Opcode() == TKE_Line_Pattern)
				HC_Set_Line_Pattern (assembled);
			else
				HC_Set_Edge_Pattern (assembled);
		}   break;

        case TKE_Marker_Symbol: {
			HC_Set_Marker_Symbol (marker_symbols[m_index]);
		}   break;

        default:
            return tk.Error();
    }

	if (tk.GeometryIsOpen())
		HC_Close_Geometry ();

    return status;
}

TK_Status HTK_Named::Interpret (BStreamFileToolkit & tk, ID_Key key, int variant) alter {
	UNREFERENCED (key);
	UNREFERENCED (variant);
#ifndef HSTREAM_READONLY
    TK_Status       status = TK_Normal;
    char *			value = new char[1024*32];
    char *			p = value;
    int             i;

    UNREFERENCED (tk);

    if (Opcode() == TKE_Marker_Symbol) {
        HC_Show_Marker_Symbol (value);
        for (i = 0; i < countof(marker_symbols); ++i) {
            if (streq (value, marker_symbols[i])) {
                m_index = (char)i;
                break;
            }
        }

		// if we didn't find an old form we recognize
		if (i == countof(marker_symbols)) {
			SetName (value);
			m_index = -1;
		}
    }
    else {
		bool		found = false;

		value[0] = '\0';

		if (Opcode() == TKE_Line_Pattern)
			HC_Show_Line_Pattern (value);
		else
			HC_Show_Edge_Pattern (value);

		if (value[0]) {
			m_index = 0;

			// any cap specified?
			if (p[0] == '(') {
				m_index |= 1 << 8;
				++p;
			}
			else if (p[0] == '[') {
				m_index |= 2 << 8;
				++p;
			}

			// any join specified?
			i = (int)strlen (p) - 1;
			if (p[i] == ')') {
				m_index |= 1 << 12;
				p[i] = '\0';
			}
			else if (p[i] == '|') {
				m_index |= 2 << 12;
				p[i] = '\0';
			}

			// anything left should be a pattern
			for (i = 0; i < countof(line_patterns); ++i) {
				if (streq (p, line_patterns[i])) {
					m_index |= i;
					found = true;
					break;
				}
			}
			if (!found) {	// not new, try old
				for (i = 0; i < countof(older_line_patterns); ++i) {
					if (streq (p, older_line_patterns[i])) {
						m_index |= i;
						found = true;
						break;
					}
				}
			}

			// if we didn't find a form we recognise
			if (!found) {
				// recover in case we damaged it
				if (Opcode() == TKE_Line_Pattern)
					HC_Show_Line_Pattern (value);
				else
					HC_Show_Edge_Pattern (value);

				SetName (value);
				m_index = -1;
			}
		}
		else {
			if (Opcode() == TKE_Line_Pattern)
				HC_Show_Line_Pattern_Explicit (value);
			else
				HC_Show_Edge_Pattern_Explicit (value);

			SetName (value);
			m_index = -2;
		}
    }

	delete [] value;
    return status;
#else
    return tk.Error (stream_readonly);
#endif
}

IMPLEMENT_CLONE_OPCODE (HTK_Named);

