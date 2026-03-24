#!/usr/bin/perl -w --
# $Id: gen-rc.pl,v 1.19 2010-05-20 17:36:11 trask Exp $

use strict;
use Getopt::Long;

#
# Set defaults, then process option arguments.
#

my $revision;
my %defopts;
my %full_options;

%defopts = (
	"revision",	"<required>"
);

%full_options = (
    "revision",    "version of Hoops you'd like to build them for"
);

# this replaces getvars.pl
my $ok;
$ok = GetOptions(
        \%defopts,
	"revision=s", \$revision
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
if ( !defined($revision) ) {
        print "\n\'revision\' is a required argument\n";
        $fail = 1;
}

if ($fail) {
        &print_usage();
        die "failed to execute $0\n";
}


#
# get the HOOPS version and subversion
#
my $junk;my $symbol;my $definition;
my $major_minor;my $dash_part;my $beta;
my $version;

($major_minor, $dash_part, $beta) = ('', '', '');
open (VERSION, "hversion.h") or  die "Can't open hversion.h.\n";
while (<VERSION>) {
    next unless /#define/;
	($junk, $symbol, $definition, $junk) = split;
	($symbol eq "HOOPS_VERSION") && ($major_minor .= $definition);
	($symbol eq "HOOPS_SUBVERSION") && ($dash_part .= $definition);
	($symbol eq "BETA_TEST") &&
	    ($definition eq "TRUE") && ($beta .= " BETA");
    }

my $major = int($major_minor/100);
my $minor = $major_minor%100;
$version = sprintf ("%1d.%02d.%02d%s",
		    $major_minor/100,
		    $major_minor%100,
		    $dash_part,
		    $beta);
close (VERSION);

#
# make the rc file for the HOOPS 32 DLL itself
#
&createmrc ($version, $major_minor, $dash_part, $beta, "HOOPS", "hoops32", $major, $minor);


#
# make an rc file for each of the separate HDI driver DLLs
#
my $file_revision;

#
#$file_revision = &read_file_revision ("direct3d_driver.cpp");
#&createrc ($version, $major_minor, $dash_part, $beta,
#	   "DIRECT3D", $file_revision, "direct3d", $major, $minor);

#
$file_revision = &read_file_revision ("cgm_driver.cpp");
&createrc ($version, $major_minor, $dash_part, $beta,
	   "CGM", $file_revision, "cgm", $major, $minor);
#
$file_revision = &read_file_revision ("hpgl_driver.cpp");
&createrc ($version, $major_minor, $dash_part, $beta,
	   "HPGL", $file_revision, "hpgl", $major, $minor);
#
$file_revision = &read_file_revision ("hpgl2_driver.cpp");
&createrc ($version, $major_minor, $dash_part, $beta,
	   "HPGL2", $file_revision, "hpgl2", $major, $minor);
#
$file_revision = &read_file_revision ("msw_driver.cpp");
&createrc ($version, $major_minor, $dash_part, $beta,
	   "MSW", $file_revision, "msw", $major, $minor);
#
$file_revision = &read_file_revision ("ogl_wgl.cpp");
&createrc ($version, $major_minor, $dash_part, $beta,
		"OPENGL", $file_revision, "opengl", $major, $minor);
#
$file_revision = &read_file_revision ("postscript_driver.cpp");
&createrc ($version, $major_minor, $dash_part, $beta,
	   "POSTSCRI", $file_revision, "postscri", $major, $minor);
#
$file_revision = &read_file_revision ("printf_driver.cpp");
&createrc ($version, $major_minor, $dash_part, $beta,
	   "PRINTF", $file_revision, "printf", $major, $minor);
#
$file_revision = &read_file_revision ("pdf_driver.cpp");
&createrc ($version, $major_minor, $dash_part, $beta,
	   "PDF", $file_revision, "pdf", $major, $minor);
#
$file_revision = &read_file_revision ("qt_driver.cpp");
&createrc ($version, $major_minor, $dash_part, $beta,
	   "QT", $file_revision, "qt", $major, $minor);
#
$file_revision = &read_file_revision ("whip2d_driver.cpp");
&createrc ($version, $major_minor, $dash_part, $beta,
	   "WHIP2D", $file_revision, "whip2d", $major, $minor);

#
$file_revision = &read_file_revision ("dx9_driver.cpp");
&createrc ($version, $major_minor, $dash_part, $beta,
	   "DX9", $file_revision, "dx9", $major, $minor);


#
# subroutines
#
sub read_file_revision {

    my $src = shift @_;

    if( !open (FB, $src) )
    {
        die "Couldn't open FB file '$src'";
    }

    while (<FB>) {
        /\$Id:.+,v\s+([\d.]+)/ &&
        close FB &&
        return $1; # on a separate line to prevent $-delimited Id replacement
    }
    close FB;
    return 0;
}


#
# generate the rc file for the HOOPS library
#
sub createmrc {
    my $version;my $major_minor;my $dash_part;
    my $beta;my $dll_file_name;my $output_file_name;

    ($version,
    $major_minor,
    $dash_part,
    $beta,
    $dll_file_name,
    $output_file_name,
    $major,
    $minor) = @_;

#   print ("version = $version\n");
#   print ("hoops major/minor version = $major_minor\n");
#   print ("hoops subversion = $dash_part\n");
#   print ("hoops beta = $beta\n");
#   print ("dll file name = $dll_file_name\n");
#   print ("output file name = $output_file_name\n");

$dll_file_name = $dll_file_name.$major_minor;
my $verstr = "$major,$minor,0,0";

    open (DRIVERRC, ">$output_file_name.rc") ||
        die "Could not open $output_file_name.rc.\n";

    print DRIVERRC<<EOF;
#include <winver.h>

HoopsIcon ICON hoops.ico

VS_VERSION_INFO   VERSIONINFO
FILEVERSION       $verstr
PRODUCTVERSION    $verstr
FILEFLAGSMASK     VS_FFI_FILEFLAGSMASK
EOF
    if ($beta eq " BETA") {
        print DRIVERRC<<EOF;
FILEFLAGS         VS_FF_DEBUG|VS_FF_PRIVATEBUILD|VS_FF_PRERELEASE
EOF
    }
    else {
        print DRIVERRC<<EOF;
FILEFLAGS         0    // final version
EOF
    }
    print DRIVERRC<<EOF;
FILEOS            VOS_NT_WINDOWS32
FILETYPE          VFT_DLL
FILESUBTYPE       0    // not used
BEGIN
    BLOCK "VarFileInfo"
    BEGIN
        VALUE "Translation", 0x0409, 1252
    END
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040904E4"
        BEGIN
            VALUE "Company Name",     "Tech Soft 3D, Inc.\\0"
            VALUE "FileDescription",  "HOOPS 3D Graphics DLL\\0"
            VALUE "FileVersion",      "$verstr\\0"
            VALUE "InternalName",     "$dll_file_name\\0"
            VALUE "LegalCopyright",   "Copyright 1986-2000 Tech Soft 3D, Inc.\\0"
            VALUE "LegalTrademarks",  "HOOPS is a registered trademark of Tech Soft 3D, LLC\\0"
            VALUE "OriginalFilename", "$dll_file_name.DLL\\0"
            VALUE "ProductName",      "HOOPS\\0"
            VALUE "ProductVersion",   "$verstr\\0"
        END
    END
END
EOF
    close (DRIVERRC);
} #createmrc


#
# generate an rc file for a driver
#
sub createrc {

    my $version;my $major_minor;my $dash_part;
    my $beta;my $dll_file_name;my $driver_version;my $output_file_name;

    ($version,
     $major_minor,
     $dash_part,
     $beta,
     $dll_file_name,
     $driver_version,
     $output_file_name,
     $major,
     $minor) = @_;

#   print ("version = $version\n");
#   print ("hoops major/minor version = $major_minor\n");
#   print ("hoops subversion = $dash_part\n");
#   print ("hoops beta = $beta\n");
#   print ("dll file name = $dll_file_name\n");
#   print ("driver version = $driver_version\n");
#   print ("output file name = $output_file_name\n");

my $verstr = "$major,$minor,0,0";
$driver_version ||= $verstr;
$dll_file_name = $dll_file_name.$major_minor;

    open (DRIVERRC, ">$output_file_name.rc") ||
        die "Could not open $output_file_name.rc.\n";

    print DRIVERRC<<EOF;
#include <winver.h>

HoopsIcon ICON hoops.ico

VS_VERSION_INFO   VERSIONINFO
FILEVERSION       $verstr
PRODUCTVERSION    $verstr
FILEFLAGSMASK     VS_FFI_FILEFLAGSMASK
EOF
    if ($beta eq " BETA") {
        print DRIVERRC<<EOF;
FILEFLAGS         VS_FF_DEBUG|VS_FF_PRIVATEBUILD|VS_FF_PRERELEASE
EOF
    }
    else {
        print DRIVERRC<<EOF;
FILEFLAGS         0    // final version
EOF
    }
    print DRIVERRC<<EOF;
FILEOS            VOS_NT_WINDOWS32
FILETYPE          VFT_DLL
FILESUBTYPE       0    // not used
BEGIN
    BLOCK "VarFileInfo"
    BEGIN
        VALUE "Translation", 0x0409, 1252
    END
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040904E4"
        BEGIN
            VALUE "Company Name",     "Tech Soft 3D, Inc.\\0"
            VALUE "FileDescription",  "HOOPS Device Driver DLL - compliant with the HOOPS Device Interface (HDI)\\0"
            VALUE "FileVersion",      "$driver_version\\0"
            VALUE "InternalName",     "$dll_file_name\\0"
            VALUE "LegalCopyright",   "Copyright 1986-2000 Tech Soft 3D, Inc.\\0"
            VALUE "LegalTrademarks",  "HOOPS is a registered trademark of Tech Soft 3D, LLC\\0"
            VALUE "OriginalFilename", "$dll_file_name.HDI\\0"
            VALUE "ProductName",      "HOOPS\\0"
            VALUE "ProductVersion",   "$verstr\\0"
        END
    END
END
EOF
    close (DRIVERRC);
} # createrc


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
}

