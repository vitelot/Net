#! /usr/bin/perl -w

use strict;

{ #main block
  my $inifile = "SUB.INI";
  my $netfile = pop;
  my (@sublist);
  my @void=();

  if(!defined($netfile)) {
    die "Please provide the name of the file containing the net.\n";
  }

  open (INI, "<$inifile") || die "Error opening \"$inifile\": $!.\n";

  @sublist = ();
  while(<INI>) {
    chomp;
    s/^\s+//;
    push @sublist, split /\s+/;
  }
  close INI;

  @sublist = Uniq(@sublist);
#  for (@sublist) { printf "SSSSSSSSSSSSSS %6d\n", $_;  }

  open (NET, "<$netfile") || die "Error opening \"$netfile\": $!.\n";
  my ($in, $out);

  while(<NET>) {
    next if /^\#/;
    chomp;
    s/^\s+//;
    ($in,$out,@void) = split /\s+/;
    next if(!defined($in) || !defined($out));

    if( IsIn($in, @sublist) || IsIn( $out, @sublist)) {
      printf "%6d %6d\n", $in,$out;    }
  }
  close NET;
} #end main block

exit;

sub Uniq {
  my @in = @_;
  my @out;

  @in = sort {$a <=> $b} @in;

  push @out, $in[0];
  for( my $i=1; $i<= $#in; $i++) {
    push @out, $in[$i] unless $in[$i]==$in[$i-1];
  }
  return @out;
}

sub IsIn {
  my ($elem, @array) = @_;

  for (@array) {
    return 1 if ($_==$elem);
  }
  return 0;
}
