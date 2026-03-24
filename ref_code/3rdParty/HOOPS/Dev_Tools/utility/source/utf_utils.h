
#ifndef _UTF_UTILS
#define _UTF_UTILS

#ifdef H_PACK_8
#pragma pack(push)
#pragma pack(8)
#endif

#ifdef _WIN32_WCE
#	define NEEDS_STR_CASE_CMP
#	define NEEDS_WCS_CASE_CMP
#endif // _WIN32_WCE
#ifdef SOLARIS_SYSTEM
#	define NEEDS_WCS_CASE_CMP
#endif // SOLARIS_SYSTEM
#ifdef OSX_SYSTEM
#	define NEEDS_WCS_CASE_CMP
#endif // OSX_SYSTEM
#ifdef HPUX_SYSTEM
#	define NEEDS_WCS_CASE_CMP
#endif // HPUX_SYSTEM


#ifndef UTF_UTILS_API
#define UTF_UTILS_API
#endif


#ifdef V_PREFIX

#define VNAME_TMP_2(_x2_,_y2_) _x2_##_y2_
#define VNAME_TMP_1(_x1_,_y1_) VNAME_TMP_2(_x1_,_y1_)
#define VNAME(_x_) VNAME_TMP_1(V_PREFIX,_x_)

/* remap the names for special prefix */
#define H_URI VNAME(H_URI)
#define H_UTF8 VNAME(H_UTF8)
#define H_UTF16 VNAME(H_UTF16)
#define H_UTF32 VNAME(H_UTF32)
#define H_WCS VNAME(H_WCS)
#define H_FORMAT_TEXT VNAME(H_FORMAT_TEXT)
#define HUtilityUnicodeStr VNAME(HUtilityUnicodeStr)
#define HUtilityAsciiStr VNAME(HUtilityAsciiStr)
#define KeyToCharPtr VNAME(KeyToCharPtr)

#ifndef _MSC_VER
#define wfopen VNAME(wfopen)
#define wremove VNAME(wremove)
#define wmkdir VNAME(wmkdir)
#define wopendir VNAME(wopendir)
#endif

#ifdef NEEDS_STR_CASE_CMP
#define strcasecmp VNAME(strcasecmp)
#endif
#ifdef NEEDS_WCS_CASE_CMP
#define wcscasecmp VNAME(wcscasecmp)
#endif

#endif

#include <stdio.h>
#include <memory.h>
#include <stdarg.h>
#include <wchar.h>

#ifndef _MSC_VER
#define __wchar_t wchar_t
#include <dirent.h>
#include <sys/types.h>
#else
#ifndef H_DISABLE_USHORT_OVERLOAD
#define H_USHORT_OVERLOAD
#endif
#endif


#ifdef NEEDS_STR_CASE_CMP
int strcasecmp (char const *string1, char const *string2);
#endif
#ifdef NEEDS_WCS_CASE_CMP
int wcscasecmp (__wchar_t const *string1, __wchar_t const *string2);
#endif

typedef unsigned char utf8_char;

class UTF_UTILS_API H_UTF32;
class UTF_UTILS_API H_UTF16;
class UTF_UTILS_API H_UTF8;
class UTF_UTILS_API H_URI;

#ifdef _MSC_VER
typedef H_UTF16 H_WCS;
typedef unsigned int utf32_char;
typedef wchar_t utf16_char;
#define wfopen _wfopen
#define wremove _wremove
#define wmkdir _wmkdir
#else
typedef H_UTF32 H_WCS;
typedef wchar_t utf32_char;
typedef unsigned short utf16_char;
FILE *wfopen (wchar_t const *, wchar_t const *);
int wremove (wchar_t const *);
int wmkdir (wchar_t const *, int);
DIR * wopendir(wchar_t const *);
#endif

class UTF_UTILS_API H_UTF32
{
public:
	H_UTF32 (H_UTF32 const &rhs);
	H_UTF32 const &operator = (H_UTF32 const &rhs);
	H_UTF32 (__wchar_t const *text);
#ifdef _MSC_VER
	H_UTF32 (unsigned short const *text);
#endif
	H_UTF32 (char const *text);
	H_UTF32 ();

	/* Conversion constructors. */
	H_UTF32 (H_UTF16 const &unicode_text);
	H_UTF32 (H_UTF8 const &unicode_text);
	H_UTF32 (H_URI const &unicode_text);
	~H_UTF32 ();

	size_t length () const;

	template < typename T > T length (size_t const s)
	{
		if (s > m_size) {
			delete[]m_utf32;
			m_utf32 = new utf32_char[m_size = s + 1];
			m_utf32[0] = 0;
		}
		return reinterpret_cast < T > (m_utf32);
	}

	template < typename T > H_UTF32 const &encodedText (T * text_in)
	{
		delete[]m_utf32;
		m_utf32 = 0;
		m_size = 0;
		utf32_char const *text = reinterpret_cast < utf32_char const *>(text_in);
		if (text) {
			while (text[m_size++] != 0);
			m_utf32 = new utf32_char[m_size];
			memcpy (m_utf32, text, m_size * sizeof (utf32_char));
		}
		return *this;
	}

	utf32_char const *encodedText () const
	{
		return m_utf32;
	};

	H_UTF32 & format (__wchar_t const *fmt,...);
#ifdef _MSC_VER
	H_UTF32 & format (unsigned short const *fmt, ...);
#endif
	H_UTF32 & format (char const *fmt, ...);

	H_UTF32 & append (__wchar_t const *txt);
#ifdef _MSC_VER
	H_UTF32 & append (unsigned short const *txt);
#endif
	H_UTF32 & append (char const *txt);

	H_UTF32 & insert (int loc, __wchar_t const *txt);
#ifdef _MSC_VER
	H_UTF32 & insert (int loc, unsigned short const *txt);
#endif
	H_UTF32 & insert (int loc, char const *txt);

	H_UTF32 & remove (int loc, int count);
	H_UTF32 & flush ();
	H_UTF32 & trunc (int loc);

	H_UTF32 & replace (int loc, __wchar_t const *txt);
#ifdef _MSC_VER
	H_UTF32 & replace (int loc, unsigned short const *txt);
#endif
	H_UTF32 & replace (int loc, char const *txt);

	int find (__wchar_t const *txt) const;
#ifdef _MSC_VER
	int find (unsigned short const *txt) const;
#endif
	int find (char const *txt) const;

	class iterator
	{
	private:
		mutable utf32_char const *m_text;
		int get_and_advance (utf32_char const *&text) const;
	public:
		iterator (utf32_char const *text = 0);
		iterator operator ++ () const;
		iterator operator ++ (int) const;
		int operator * () const;
		operator  bool () const;
		bool operator != (iterator const &rhs) const
		{
			return m_text != rhs.m_text;
		}
	};

	iterator begin () const;
	iterator end () const;

	bool operator == (H_UTF32 const &rhs) const;
	bool operator != (H_UTF32 const &rhs) const
	{
		return !operator== (rhs);
	};

private:
	utf32_char * m_utf32;
	size_t m_size;
};

class UTF_UTILS_API H_UTF16
{
public:

	H_UTF16 (H_UTF16 const &rhs);
	H_UTF16 const &operator = (H_UTF16 const &rhs);
	H_UTF16 (__wchar_t const *text);
#ifdef _MSC_VER
	H_UTF16 (unsigned short const *text);
#endif
	H_UTF16 (char const *text);
	H_UTF16 ();

	/* Conversion constructors. */
	H_UTF16 (H_UTF32 const &unicode_text);
	H_UTF16 (H_UTF8 const &unicode_text);
	H_UTF16 (H_URI const &unicode_text);
	~H_UTF16 ();

	size_t length () const;

	template < typename T > T length (size_t const s)
	{
		if (s > m_size) {
			delete[]m_utf16;
			m_utf16 = new utf16_char[m_size = s + 1];
			m_utf16[0] = 0;
		}
		return reinterpret_cast < T > (m_utf16);
	}

	template < typename T > H_UTF16 const &encodedText (T const *text_in)
	{
		delete[]m_utf16;
		m_utf16 = 0;
		m_size = 0;
		utf16_char const *text = reinterpret_cast < utf16_char const *>(text_in);
		if (text) {
			while (text[m_size++] != 0);
			m_utf16 = new utf16_char[m_size];
			memcpy (m_utf16, text, m_size * sizeof (utf16_char));
		}
		return *this;
	}

	utf16_char const *encodedText () const
	{
		return m_utf16;
	};

	H_UTF16 & format (__wchar_t const *fmt,...);
#ifdef _MSC_VER
	H_UTF16 & format (unsigned short const *fmt, ...);
#endif
	H_UTF16 & format (char const *fmt, ...);

	H_UTF16 & append (__wchar_t const *txt);
#ifdef _MSC_VER
	H_UTF16 & append (unsigned short const *txt);
#endif
	H_UTF16 & append (char const *txt);

	H_UTF16 & insert (int loc, __wchar_t const *txt);
#ifdef _MSC_VER
	H_UTF16 & insert (int loc, unsigned short const *txt);
#endif
	H_UTF16 & insert (int loc, char const *txt);

	H_UTF16 & remove (int loc, int count);
	H_UTF16 & flush ();
	H_UTF16 & trunc (int loc);

	H_UTF16 & replace (int loc, __wchar_t const *txt);
#ifdef _MSC_VER
	H_UTF16 & replace (int loc, unsigned short const *txt);
#endif
	H_UTF16 & replace (int loc, char const *txt);

	int find (__wchar_t const *txt) const;
#ifdef _MSC_VER
	int find (unsigned short const *txt) const;
#endif
	int find (char const *txt) const;

	class iterator
	{
	private:
		mutable utf16_char const *m_text;
		int get_and_advance (utf16_char const *&text) const;
	public:
		iterator (utf16_char const *text = 0);
		iterator operator ++ () const;
		iterator operator ++ (int) const;
		int operator * () const;
		operator  bool () const;
		bool operator != (iterator const &rhs) const
		{
			return m_text != rhs.m_text;
		}
	};

	iterator begin () const;
	iterator end () const;

	bool operator == (H_UTF16 const &rhs) const;
	bool operator != (H_UTF16 const &rhs) const
	{
		return !operator== (rhs);
	};

private:
	utf16_char * m_utf16;
	size_t m_size;
};

class UTF_UTILS_API H_UTF8
{
public:
	H_UTF8 (H_UTF8 const &rhs);
	H_UTF8 const &operator = (H_UTF8 const &rhs);
	H_UTF8 (__wchar_t const *text);
#ifdef _MSC_VER
	H_UTF8 (unsigned short const *text);
#endif
	H_UTF8 (char const *text);
	H_UTF8 ();

	/* Constructors for conversion */
	H_UTF8 (H_UTF32 const &unicode_text);
	H_UTF8 (H_UTF16 const &unicode_text);
	H_UTF8 (H_URI const &unicode_text);
	~H_UTF8 ();

	size_t length () const;

	template < typename T > T length (size_t const s)
	{
		if (s > m_size) {
			delete[]m_utf8;
			m_utf8 = new utf8_char[m_size = s + 1];
			m_utf8[0] = 0;
		}
		return reinterpret_cast < T > (m_utf8);
	}

	template < typename T > H_UTF8 const &encodedText (T * text_in)
	{
		delete[]m_utf8;
		m_utf8 = 0;
		m_size = 0;
		utf8_char const *text = reinterpret_cast < utf8_char const *>(text_in);
		if (text) {
			while (text[m_size++] != 0);
			m_utf8 = new utf8_char[m_size];
			memcpy (m_utf8, text, m_size * sizeof (utf8_char));
		}
		return *this;
	}

	utf8_char const *encodedText () const
	{
		return m_utf8;
	};

	H_UTF8 & format (__wchar_t const *fmt,...);
#ifdef _MSC_VER
	H_UTF8 & format (unsigned short const *fmt, ...);
#endif
	H_UTF8 & format (char const *fmt, ...);

	H_UTF8 & append (__wchar_t const *txt);
#ifdef _MSC_VER
	H_UTF8 & append (unsigned short const *txt);
#endif
	H_UTF8 & append (char const *txt);

	H_UTF8 & insert (int loc, __wchar_t const *txt);
#ifdef _MSC_VER
	H_UTF8 & insert (int loc, unsigned short const *txt);
#endif
	H_UTF8 & insert (int loc, char const *txt);

	H_UTF8 & remove (int loc, int count);
	H_UTF8 & flush ();
	H_UTF8 & trunc (int loc);

	H_UTF8 & replace (int loc, __wchar_t const *txt);
#ifdef _MSC_VER
	H_UTF8 & replace (int loc, unsigned short const *txt);
#endif
	H_UTF8 & replace (int loc, char const *txt);

	int find (__wchar_t const *txt) const;
#ifdef _MSC_VER
	int find (unsigned short const *txt) const;
#endif
	int find (char const *txt) const;

	class iterator
	{
	private:
		mutable utf8_char const *m_text;
		int get_and_advance (utf8_char const *&text) const;
	public:
		iterator (utf8_char const *text = 0);
		iterator operator ++ () const;
		iterator operator ++ (int) const;
		int operator * () const;
		operator  bool () const;
		bool operator != (iterator const &rhs) const
		{
			return m_text != rhs.m_text;
		}
	};

	iterator begin () const;
	iterator end () const;

	bool operator == (H_UTF8 const &rhs) const;
	bool operator != (H_UTF8 const &rhs) const
	{
		return !operator== (rhs);
	};

private:
	utf8_char * m_utf8;
	size_t m_size;
};

/* H_URI encodes a utf8 encoded string.  It replaces all non-ascii chars with percent encodings.
 * so the string "AA" could be URI encoded as "%65%65" (but as the chars are ascii, it will be
 * encoded as "AA". */
class UTF_UTILS_API H_URI
{
public:
	H_URI (H_URI const &rhs);
	H_URI const &operator = (H_URI const &rhs);
	H_URI (__wchar_t const *text);
#ifdef _MSC_VER
	H_URI (unsigned short const *text);
#endif
	H_URI (char const *text);
	H_URI ();

	/* Constructors for conversion */
	H_URI (H_UTF32 const &unicode_text);
	H_URI (H_UTF16 const &unicode_text);
	H_URI (H_UTF8 const &unicode_text);
	~H_URI ();

	size_t length () const;

	template < typename T > T length (size_t const s)
	{
		if (s > m_size) {
			delete[]m_uri;
			m_uri = new utf8_char[m_size = s + 1];
			m_uri[0] = 0;
		}
		return reinterpret_cast < T > (m_uri);
	}

	template < typename T > H_URI const &encodedText (T * text_in)
	{
		delete[]m_uri;
		m_uri = 0;
		m_size = 0;
		utf8_char const *text = reinterpret_cast < utf8_char const *>(text_in);
		if (text) {
			while (text[m_size++] != 0);
			m_uri = new utf8_char[m_size];
			memcpy (m_uri, text, m_size * sizeof (utf8_char));
		}
		return *this;
	}

	utf8_char const *encodedText () const
	{
		return m_uri;
	};

	H_URI & format (__wchar_t const *fmt,...);
#ifdef _MSC_VER
	H_URI & format (unsigned short const *fmt, ...);
#endif
	H_URI & format (char const *fmt, ...);

	H_URI & append (__wchar_t const *txt);
#ifdef _MSC_VER
	H_URI & append (unsigned short const *txt);
#endif
	H_URI & append (char const *txt);

	H_URI & insert (int loc, __wchar_t const *txt);
#ifdef _MSC_VER
	H_URI & insert (int loc, unsigned short const *txt);
#endif
	H_URI & insert (int loc, char const *txt);

	H_URI & remove (int loc, int count);
	H_URI & flush ();
	H_URI & trunc (int loc);

	H_URI & replace (int loc, __wchar_t const *txt);
#ifdef _MSC_VER
	H_URI & replace (int loc, unsigned short const *txt);
#endif
	H_URI & replace (int loc, char const *txt);

	int find (__wchar_t const *txt) const;
#ifdef _MSC_VER
	int find (unsigned short const *txt) const;
#endif
	int find (char const *txt) const;

	class iterator
	{
	private:
		mutable utf8_char const *m_text;
		int get_and_advance (utf8_char const *&text) const;
	public:
		iterator (utf8_char const *text = 0);
		iterator operator ++ () const;
		iterator operator ++ (int) const;
		int operator * () const;
		operator  bool () const;
	};

	iterator begin () const;
	iterator end () const;

	bool operator == (H_URI const &rhs) const;
	bool operator != (H_URI const &rhs) const
	{
		return !operator== (rhs);
	};
	static bool unreserved_char (int c);

private:
	utf8_char * m_uri;
	size_t m_size;

};

/* H_FORMAT_TEXT is by far, hands down, the awesomest C++ class ever written. */
/*! H_FORMAT_TEXT is used to format text printf style in HOOPS functions that take char* args.
	One example of this is: Set_Rendering_Options(H_FORMAT_TEXT("size = (%f, %f)", width, height")).
*/
class UTF_UTILS_API H_FORMAT_TEXT
{
private:
	char *m_str;		//! formatted string

	/*! This is a portable version of vsnprintf */
	static int const h_vsnprintf (char *const buf, size_t const n, char const *const format, va_list valist);
public:

	/*! Use this constructor as a cast for format a string.  Do *NOT* set this equal to a
	   variable.  char * s = H_FORMAT_TEXT("") is a bug and s will point to freed memory.
	   The only acceptable uses of this class is casting in a function parameter or initializing
	   a static or automatic H_FORMAT_TEXT variable.
	   An example of using this as a function argument:
	   HC_Set_Driver_Options(H_FORMAT_TEXT("%d, %f, %s", (int)i, (float)j, "text"));
	   An example of creating an automatic variable:
	   H_FORMAT_TEXT color("faces = %s, edges = %s", face_color, edge_color);
	   HC_Set_Color(color);

	 */
	H_FORMAT_TEXT (char const *const format, ...);
	H_FORMAT_TEXT & Append (char const *format, ...);
	~H_FORMAT_TEXT ();

	/*! This returns the memory when the class is in scope. */
	operator char * () const;
	H_FORMAT_TEXT const &operator= (H_FORMAT_TEXT const &rhs);
	H_FORMAT_TEXT (H_FORMAT_TEXT const &rhs);
	H_FORMAT_TEXT ();
};
#define HFT(...) ((char const*)H_FORMAT_TEXT(__VA_ARGS__))


/*! KeyToCharPtr is used to format HC_KEY as a string for better portability (64-bit Windows treats %lx
	differently than all the other 64-bit systems).  Do not call KeyToCharPtr directly, instead use the
	casting macro ktoa.  The return value will ALWAYS be lower case, will ALWAYS be hex and will NEVER
	be prepending with 0x.
	Example: HC_Insert_Text(0, 0, 0, H_FORMAT_TEXT("%s", ktoa(m_pHView->GetModelKey()));
*/
class UTF_UTILS_API KeyToCharPtr
{
private:
	void * key;
	mutable char * p;
	mutable char str[24];
	bool trim;

	char * format_key() const;

public:
	KeyToCharPtr(void * k, bool trim_0x);
	operator char const * () const;
	operator char * () const;

};
#define ktoa(x) ((char const*)(KeyToCharPtr((void *)(x), true)))
#define kto0xa(x) ((char const*)(KeyToCharPtr((void *)(x), false)))




// HUtilityUnicodeStr ////////////////////////////////////////////////////////
// Converts both 8-bit (foreign) and 16-bit (native) strings to 16-bit wideness

/*!
	HUtilityUnicodeStr takes a regular (8bit - char*) or UNICODE (16 bit - wchar*) string and converts
	to a UNICODE string. This UNICODE string can be used for later operations. The converted UNICODE
	string can only be used as long as the HUtilityUnicodeStr object exists.
*/
class UTF_UTILS_API HUtilityUnicodeStr
{
public:

	/*! Constructor
	   \param p8    char* pointing to an 8-bit string */
	HUtilityUnicodeStr (const char *p8);

	/*! Constructor
	   \param p16   wchar_t* pointing to an 16-bit string */
	HUtilityUnicodeStr (const __wchar_t * p16);
#ifdef _MSC_VER
	HUtilityUnicodeStr (const unsigned short *p16);
#endif

	/*! destructor - A Non-virtual destructor (this class is concrete) */
	~HUtilityUnicodeStr ();

	/*! conversion operator to UNICODE */
	operator  const __wchar_t *(void) const;
#ifdef _MSC_VER
	operator  const unsigned short *(void) const;
#endif

private:
	/*! protect against assignment!
	   \param str2 Reference to another HUtilityUnicodeStr object */
	HUtilityUnicodeStr (const HUtilityUnicodeStr & str2);

	/*! protect against assignment!
	   \param str2 Reference to another HUtilityUnicodeStr object */
	  HUtilityUnicodeStr & operator= (const HUtilityUnicodeStr & str2);

	H_WCS m_wcs;
};

/*!
	HUtilityAsciiStr takes a regular (8bit - char*) or UNICODE (16 bit - wchar*) string and converts
	to a regular 8-bit string. This string can be used for later operations. The converted
	string can only be used as long as the HUtilityAsciiStr object exists.
*/
class UTF_UTILS_API HUtilityAsciiStr
{
public:

	/*! Constructor
	   \param p8    char* pointing to an 8-bit string */
	HUtilityAsciiStr (const char *p8);

	/*! Constructor
	   \param p16   wchar_t* pointing to an 16-bit string */
	HUtilityAsciiStr (const __wchar_t * p16);
#ifdef _MSC_VER
	HUtilityAsciiStr (const unsigned short *p16);
#endif

	/*! destructor - A Non-virtual destructor (this class is concrete) */
	~HUtilityAsciiStr (void);

	/*! conversion operator to ASCII */
	operator  const char *(void) const;


private:

	char *m_sz;		/*!< The 8-bit string */

	// protect against assignment!
	HUtilityAsciiStr (const HUtilityAsciiStr &);
	HUtilityAsciiStr & operator= (const HUtilityAsciiStr &);

};


/*! \def H_TEXT - use this macro where-ever the api itself takes different type of argument
    during compilation depending upon preprocessor
*/
#ifdef _UNICODE
typedef HUtilityUnicodeStr H_TEXT;
#else
typedef HUtilityAsciiStr H_TEXT;
#endif

/*! \def H_UNICODE_TEXT  Converts any string (UNICODE or ASCII) to UNICODE string */
//typedef HUtilityUnicodeStr    H_UNICODE_TEXT;

#define H_UNICODE_TEXT(_x_) (const wchar_t *)HUtilityUnicodeStr(_x_)

/*! \def H_ASCII_TEXT Converts any string (UNICODE or ASCII) to ASCII string */
//typedef HUtilityAsciiStr      H_ASCII_TEXT;

#define H_ASCII_TEXT(_x_) (const char *)HUtilityAsciiStr(_x_)


#ifdef H_PACK_8
#pragma pack(pop)
#endif

#endif
