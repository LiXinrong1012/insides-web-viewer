#!/usr/bin/perl --
# $Id: make-obf.pl,v 1.36 2010-10-28 20:39:59 trask Exp $

use strict;
use Getopt::Long;

#exit;

my $filemap        = 'filemap';
my $exception_path = './';
my $obfuscator_binary = 'obf';

my $ok = GetOptions(
        "filemap=s", \$filemap,
        "exception_path=s", \$exception_path,
        "obfuscator_binary=s", \$obfuscator_binary,
        );

my @PROTECT_CMDS = qw/ HOOPS_ HC_ HD_ HI_ HF_ HFC_ HIC_ FT_ X GL gl WGL wgl OGL UV_ D3 d3 DX dx VK_ B_ H3D PFD WM_ ID LPD _0 _1 _2 _3 _4 _5 _6 _7 _8 _9 Q qtz agl AGL kEvent WT WD DWF CF png_ PNG_ CGL kCGL /;

# -------------------------------------------------------------------------- #
#
# check sanity
#
die "This script requires obf, a program that currently only runs on linux!\n"
    unless (`uname` =~/Linux/ );

# open the file map and push it into a hash keyed by letter code (i.e. C or O)
open (FILEMAP, $filemap) or die "Cannot open filemap file '$filemap'\n";
my %fmh = ();
while(<FILEMAP>) {
    next if /^\s*\#/;    # ignore comments
    my ($long,undef,$rule) = split;
    next unless $long =~ /\w\.c|\w\.h|\w\.cpp|\w\.mm/;
    push @{$fmh{uc($rule)}}, $long;
}
close(FILEMAP);


# open and write to commands file
print "making obfuscator command file\n";
open (COMMANDS, ">commands.obf") or die "Cannot open commands.obf\n";

print COMMANDS "VERBOSE\n";
print COMMANDS "PREFIX _hoops_\n";
print COMMANDS "ENCODING GRAPHICS\n";
print COMMANDS "ID target\n";

print COMMANDS "READ exceptions ".$exception_path."exceptions\n";

# print out all the 'PROTECT' files
print COMMANDS map { "PROTECT $_\n" } sort @PROTECT_CMDS;
print COMMANDS "DATE 2\n";

# print out the 'EXCEPT' files
print COMMANDS map { "EXCEPT $_\n" } sort @{$fmh{'C'}} unless !defined $fmh{'C'};
print COMMANDS "DATE 0\n";

# print out the the ones to skip
print COMMANDS map { "\# skip $_\n" } sort @{$fmh{'X'}} unless !defined $fmh{'X'};

# print out the files to 'OBFUSCATE'
print COMMANDS map { "OBFUSCATE $_ $_\n" } sort @{$fmh{'O'}} unless !defined $fmh{'O'};

# print last commands and close command file
print COMMANDS "WRITE exceptions exceptions.obf\n";
print COMMANDS "WRITE obfuscations obfuscations.obf\n";
print COMMANDS "WRITE protects protects.obf\n";
close(COMMANDS);

# Execute the command file
print "executing obfuscator commands\n";
system "$obfuscator_binary commands.obf";
