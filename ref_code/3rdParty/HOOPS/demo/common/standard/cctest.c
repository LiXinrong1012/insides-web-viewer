/* things to check with various compilers/run-time environments */

/****************************** compile-time ******************************/

/*================================= VMS =================================*/
#ifdef __VMS
# ifndef VMS
#  define VMS		/* not normally defined if "strict" ANSI mode */
# endif
#endif
#ifdef VMS
# ifdef VAX
#   define	signed
#   define NO_ASSERT
# endif
# define NO_STRCASECMP
#endif
#ifdef WINDOWS_SYSTEM
# define NO_STRCASECMP
#endif
/*---------------------------- Notes on VMS -----------------------------*/
/* VMS run-time does not include strcasecmp() functions			 */
/* VAXC does not seem to have assert(), though mentioned in help manual. */
/* VAXC does not accept explicit use of "signed"			 */
/*=======================================================================*/



/* what headers are required for "builtin" functions */

#ifndef NO_ASSERT
# include <assert.h>
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef VMS
#include <unixio.h>
#endif

#if 0
# include <memory.h>	/* ? things maybe not in string.h */
#endif




/* do we care about support for 16-bit systems */
/* what "int" type is pointer-sized */
/* should we use bool,true,false and define them on systems that don't */



/* does compiler have trouble with certain typedefs or prototypes? */
void dummy_with_name (int int_arg);
void dummy_without_name (int);

typedef void (*typedef_with_name) (int i_arg);
typedef void (*typedef_without_name) (int);

typedef struct simple_struct {
    int		a;
    float	b;
} Simple;

int global_function (Simple * arg);





int main (int argc, char const ** argv) {
    char const *	cp;
    signed int		si;
    float		f = 0.0f;	/* or is  "(float)0.0"  required */
    char		buffer[256];
    char *		mp;
    size_t		len;

    void		(*function_with_names) (int int_arg);
    void		(*function_without_names) (int);

    union {
	int		i;
	short		s[2];
    }			overlay;

    printf ("\n");
    (void)function_with_names; /* avoid compiler warnings */
    (void)function_without_names;

    /* although we have never encountered a system that *doesn't* use
     * normal 2's complement signed integers, check that this one is */
    si = ~0;
    if (si != -1) {
	printf ("System is NOT 2's complement!\n");
	return 0;
    }


    /* determine endianism of system */
    overlay.i = 1;
    if (overlay.s[0] == 1 && overlay.s[1] == 0)
	printf ("System is Little-Endian\n");
    else if (overlay.s[0] == 0 && overlay.s[1] == 1)
	printf ("System is Big-Endian\n");
    else {
	printf ("System Endianism not understood!\n");
	return 0;
    }

    /* size of common base types */
    printf ("\n");
    printf ("int:\t%d\n", sizeof (int));
    printf ("long:\t%d\n", sizeof (long));
    printf ("void *:\t%d\n", sizeof (void *));
    printf ("\n");


#ifndef NO_ASSERT
    assert (sizeof (long) == sizeof (void *));
#endif

    /* functions referenced to make sure headers are included &
	appropriate libraries linked */

    /* str functions work on zero-terminated arrays of chars */
    len = strlen (cp = argv[0]);
    sprintf (buffer, "%d", len);
    strcat (buffer, argv[0]);
    strcpy (buffer, argv[0]);
    strncpy (buffer, argv[0], len);
    cp = strchr (buffer, '.');
    cp = strrchr (buffer, '/');
    cp = strstr (buffer, ".hmf");
    si = strcmp (buffer, argv[0]);
    si = strncmp (buffer, argv[0], len);
#ifndef NO_STRCASECMP
    si = strcasecmp (buffer, argv[0]);
    si = strncasecmp (buffer, argv[0], len);
#endif


    /* mem functions work on counted arrays of chars */
    memset (buffer, 0, len);
    memcpy (buffer, argv[0], len);
    si = memcmp (buffer, argv[0], len);


    /* math functions */
    f = (float) (sin (f) * cos (f) + ceil (f) + floor (f));
    f = (float) (pow (f, 2.0f) + atan2 (1.0f, 1.0f));
    f = (float) (sqrt (fabs (f)));


    /* raw memory management */
    mp = (char *)malloc (len);
    free (mp);
    mp = (char *)calloc (len, sizeof (char));
    mp = (char *)realloc (mp, 2*len);
    free (mp);

/* timing tests (are any functions implemented very poorly) */
/*	memcpy, cast to int	*/

    return 0;
}



int global_function (Simple * argument) {
    argument->a = 0;
    argument->b = 1.0f;

    return 3;
}
