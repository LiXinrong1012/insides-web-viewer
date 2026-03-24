#!/usr/bin/perl -w --
# $Id: gen-hch.pl,v 1.22 2009-08-08 01:06:59 trask Exp $

use strict;
use Getopt::Long;


#
# Set defaults, then process option arguments.
#
my $names;
my %defopts;
my %full_options;
undef $names;

%defopts = (
	"names",	"<required>",
	"output",	'-'
);

# this replaces getvars.pl
my $ok;
$ok = GetOptions(
        \%defopts,
	"output=s",
	"names=s", \$names
);

%full_options = (
    "names",  "path to the file containing the names",
    "output", "where you'd like the output to go (use \"-\" for stdout)"
);


#
# deal with bad input
#

my $fail = 0;
# a catch for invalid arguments
if ($ok == 0){
        # GetOptions will print the error
        $fail = 1;
}

# make sure the required arguments are given
if ( !defined($names)) {
        print "\n\'names\' is a required argument\n";
        $fail = 1;
}

if ($fail) {
        &print_usage();
        die "failed to execute $0\n";
}


# 
# get the function names
#
open (NAMES, $names) || die "Cannot open the names file \"$names\"";
($defopts{output} eq "-") ||
    ((open (OUTPUT, ">$defopts{output}") || die "Cannot open the output file \"$defopts{output}\"") &&
     select OUTPUT);

#
# typemap
#
my %expanded_type;

%expanded_type = (
    "a",    "const float *",
    "A",    "float *",
    "b",    "HC_BOOLEAN",
    "c",    "const char *",
    "C",    "char *",
    "i",    "int",
    "I",    "int *",
    "f",    "double",
    "F",    "float *",
    "j",    "const HC_KEY *",
    "J",    "HC_KEY *",
    "k",    "HC_KEY",
    "K",    "HC_KEY *",
    "l",    "long",
    "L",    "long *",
    "m",    "HC_POINTER_SIZED_INT",
    "M",    "HC_POINTER_SIZED_INT *",
    "p",    "const HC_POINT *",
    "P",    "HC_POINT *",
    "q",    "const HC_PLANE *",
    "Q",    "HC_PLANE *",
    "r",    "int (HC_CDECL *)(HC_ANY_ARGS)",
    "R",    "int (HC_CDECL **)(HC_ANY_ARGS)",
    "s",    "const char *",
    "S",    "char *",
    "t",    "void (HC_CDECL *)(HC_ANY_ARGS)",
    "T",    "void (HC_CDECL **)(HC_ANY_ARGS)",
    "u",    "const void *",
    "U",    "void *",
    "v",    "void",
    "x",    "const unsigned short *",
    "X",    "unsigned short *",
    "y",    "const int *",
    "Y",    "int *",
    "z",    "const float *",
    "Z",    "float *",
);

#
# parammap - macro parameter names which show the general type
#
my %macro_param_type;

%macro_param_type = (
    "a",    "float_4x4_in",
    "A",    "float_4x4_out",
#   "b",    "HC_BOOLEAN",
    "c",    "byte_array_in",
    "C",    "byte_array_out",
    "i",    "int_in",
    "I",    "int_out",
    "f",    "double_in",
    "F",    "float_out",
    "j",    "key_array_in",
    "J",    "key_array_out",
    "k",    "key_in",
    "K",    "key_out",
    "l",    "long_in",
    "L",    "long_out",
    "m",    "long_int_in",
    "M",    "long_int_out",
    "p",    "point_array_in",
    "P",    "point_array_out",
    "q",    "plane_array_in",
    "Q",    "plane_array_out",
    "r",    "int_routine_in",
    "R",    "int_routine_out",
    "s",    "string_in",
    "S",    "string_out",
    "t",    "void_routine_in",
    "T",    "void_routine_out",
    "u",    "void_ptr_in",
    "U",    "void_ptr_out",
    "v",    "void",
    "x",    "unsigned_short_in",
    "X",    "unsigned_short_out",
    "y",    "int_array_in",
    "Y",    "int_array_out",
    "z",    "float_array_in",
    "Z",    "float_array_out",
);


&print_header;

#
# generate the body
#
my $zzz;
my $routine; my $param_types; my $return_type; my $longname;
my $param_num; my $param_string;

while (<NAMES>) {
    next unless /^#/ && /HC_/;
	next if (/HC_DCompute_/ || /HC_DQK/ || /HC_DEdit_/ || /HC_DShow_/ || /HC_DMove_/ || /HC_DSet_/ || /HC_DZoom_/ || /HC_DOrbit_/ || /HC_DRoll_/ || /HC_DQSet_/ || /HC_DQShow_/ || /HC_DFlush_/ || /HC_DReset_/ || /HC_DDelete_/ || /DKCompute_/);

    ($zzz, $routine, $zzz, $param_types, $return_type, $zzz, $zzz, $longname, $zzz) = split;
    
    print "HC_EXTERNAL $expanded_type{$return_type} HC_CDECL $routine HC_PROTO ((\n\t\t";
    $param_num = 0;
    foreach (split (//, $param_types)) {
	print ", " if $param_num++;
	print $expanded_type{$_};
    }
    print "));\n";

    if ($longname) {
	$param_num = 0;
	$param_string = "(";
	foreach (split (//, $param_types)) {
	    $param_string .= ", " if $param_num++;
	    $param_string .= $macro_param_type{$_} . $param_num;
	}
	$param_string .= ")";
	
	foreach (split (/,/, $longname)) {
	    print "#define  ", $_, $param_string, " \\\n\t\t\t", $routine, $param_string, "\n";
	}
    }
}
close NAMES;

&print_footer;
exit;

#
# subroutines
#
sub print_usage {

        my $description;my $name;my $default;

        # perl5 may die if you try to indent the format
format top =
Name             Description                                Default Value
---------------  -----------------------------------------  -------------
.
format STDOUT =
^<<<<<<<<<<<<<<  ^<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  ^>>>>>>>>>>>>
$name,           $description,                              $default
~~               ^<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ^>>>>>>>>>>>>
                  $description,                          $default
.

        print "\nValid options to $0 are:\n\n";
        foreach (sort (keys %full_options)) {
                $name = $_;
                $description = $full_options{$_};
                if (defined ($defopts{$name})) {
                        $default = $defopts{$name};
                }
                write;
        }
        print "\nOption assigments must take the form \"-option=value\"\n";
        # autoabbrev is on by default in Getopts::Long
        print "Option names may be abbreviated.\n";
} # print_usage


sub print_header {
    print <<EOF;

#ifndef HC_DEFINED

#ifdef __cplusplus
#   define		HC_EXTERNAL	extern "C"
#   define		HC_ANY_ARGS	...
#else
#   define		HC_EXTERNAL	extern
#   define		HC_ANY_ARGS
#   ifndef __STDC__
#	ifndef _MSC_VER
#	    define	const
#	endif
#   endif
#   ifdef sun
#	ifndef __STDC__
#	    define	NO_PROTOTYPES
#	endif
#   endif
#endif

#ifdef NO_PROTOTYPES
#   define HC_PROTO(a) ()
#else
#   define HC_PROTO(a) a
#endif


#ifndef HC_CDECL
#   ifdef _MSC_VER
#       define HC_CDECL __cdecl
#   else
#       define HC_CDECL
#   endif
#endif


#ifndef HC_POINT
#	ifdef SWIG
typedef float HC_POINT;
#	else
#   	define	HC_POINT	void
    /*
     * NOTE: if you want a real definition for "HC_POINT", put
     *		typedef	struct {float x, y, z;}	Point;
     *	        #define	HC_POINT	Point
     *	     in your program before including <hc.h>.
     */
#	endif
#endif


#ifndef HC_PLANE
#	ifdef SWIG
typedef float HC_PLANE;
#	else
#   define	HC_PLANE	void
    /*
     * NOTE: if you want a real definition for "HC_PLANE", put
     *		typedef	struct {float a, b, c, d;} Plane;
     *	        #define	HC_PLANE	Plane
     *	     in your program before including <hc.h>.
     */
#	endif
#endif


#ifndef HC_BOOLEAN
#	ifdef __cplusplus
#	define	HC_BOOLEAN	bool
#	else
#	define	HC_BOOLEAN	char
#endif
#endif


#ifndef HC_POINTER_SIZED_INT
#if defined(_M_IA64) || defined(_M_AMD64) || defined(WIN64) || defined(_WIN64) || defined(_M_X64)
#   define  HC_POINTER_SIZED_INT    __int64
#else
#   define  HC_POINTER_SIZED_INT    long
#endif
#endif


#ifndef HC_KEY
#   define  HC_KEY      HC_POINTER_SIZED_INT
#endif


#ifndef HC_PIXEL
    /* (This definition probably shouldn't be changed) */
#   define	HC_PIXEL	void
#endif

EOF
} # print_header



sub print_footer {
    print <<EOF;

#define HC_DEFINED
#endif /* HC_DEFINED */

EOF
}
