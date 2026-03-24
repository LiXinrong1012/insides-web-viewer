#!/usr/bin/perl -w --

# $Id: gen-exp.pl,v 1.4 2006-05-18 19:18:10 stage Exp $

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
	"names",		"<required>",
	"fortran",		1,
);

%full_options = (
    'names',       'path to the file containing the names',
    'fortran',     'if set, write an extra file that includes the fortran functions',

);

my $ok = GetOptions(
        \%defopts,
        "fortran=i",
        "names=s", \$names,
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
if ( !defined($names) )  {
        print "\n\'names\' is a required argument\n";
        $fail = 1;
}

if ($fail) {
        &print_usage();
        die "failed to execute $0\n";
}


#
# Read in the HC calls and build routine lists
#
my $junk;my $routine;
my @c_api = ();
my @fortran_api = ();
my @hi_internal = ();
my @hd_internal = ();
my @hfc_internal = ();

open (NAMES, $names) || die "Cannot open the names file \"$names\"";
while (<NAMES>) {

    next unless /^#/;
    ($junk, $routine, $junk) = split;

    if ($routine =~ /HD_/) {
    	unshift (@hd_internal, $routine);
    	next;
    }
    
    if ($routine =~ /HI_/) {
    	unshift (@hi_internal, $routine);
    	next;    
    }
    
    if ($routine =~ /HC_/) {
    	unshift (@c_api, $routine);
    	$routine =~ s/HC/hf/;
    	$routine =~ s/(\w)/\L$1/g;
    	unshift (@fortran_api, $routine);
    	next;    
    }
    
    if ($routine =~ /HFC_/) {
    	unshift (@hfc_internal, $routine);
    	next;    
    }
}
close NAMES;


#
# write the export file including fortran symbols
#
if ($defopts{fortran}) {

    open (EXPF, ">aixhcf.exp") || die "Cannot open \"aixhcf.exp\" for output\n";

    print EXPF "_HOOPS\n";
    print EXPF "_HOOPS_READ_ONLY\n";

    foreach (@c_api) {
	print EXPF "$_\n";
    }
    foreach (@fortran_api) {
	print EXPF "$_\n";
    }
    foreach (@hd_internal) {
	print EXPF "$_\n";
    }
    foreach (@hi_internal) {
	print EXPF "$_\n";
    }
    foreach (@hfc_internal) {
	print EXPF "$_\n";
    }

    close (EXPF);
}


#
# write the export file without fortran symbols
#
open (EXP, ">aixhc.exp") || die "Cannot open \"aixhc.exp\" for output\n";

print EXP "_HOOPS\n";
print EXP "_HOOPS_READ_ONLY\n";

foreach (@c_api) {
    print EXP "$_\n";
}
foreach (@hd_internal) {
    print EXP "$_\n";
}
foreach (@hi_internal) {
    print EXP "$_\n";
}
foreach (@hfc_internal) {
    print EXP "$_\n";
}

close (EXP);

#
# write the opengl export file
# 
open (EXP, ">openglhdi.exp") || die "Cannot open \"openglhdi.exp\" for output\n";
print EXP "HD_OpenGL_Driver\n";
close (EXP);

#
# write the pdf export file
# 
open (EXP, ">pdfhdi.exp") || die "Cannot open \"pdfhdi.exp\" for output\n";
print EXP "HD_PDF_Driver\n";
close (EXP);


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
}









