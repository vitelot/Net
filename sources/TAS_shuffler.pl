#! /usr/bin/perl -w

use strict;

{ #main
  print "Starting program TAS_shuffler:\n";
  die "  Missing file name to parse. Exiting.\n" if($#ARGV<0);
  my $projname = pop;
  $projname =~ s/\.in$//;
  my ($post_id, $tag_id, $user_id, $resource_id);
  my $old_post_id;
  my $linecount=0;
  my $post_len=0;
  my ($t,$u) = (0,0);
  my (@TAGS, @USERS, @RES, @POSTLEN);

  $old_post_id = 3.1415;
  open IN, "<$projname.tas" or die "  Can't open \"$projname.tas\": $!";
  print "  File \"$projname.tas\" opened.\n";
  while(<IN>) {
    ++$linecount;
    next if /^#/; # skip comment lines
    ($post_id, $tag_id, $user_id, $resource_id) = split /\s+/;
    push @TAGS, $tag_id;

    if($post_id==$old_post_id) {
      $post_len++;
    } else {
      push @POSTLEN, $post_len if($post_len);
      push @USERS, $user_id;
      push @RES, $resource_id;
      $post_len = 1;
    }
    $old_post_id = $post_id;
#    print "$post_id, $tag_id, $user_id, $resource_id\n";
  }

  push @POSTLEN, $post_len if($post_len); # empty last buffer

  close IN;

  print "  $linecount lines read.\n";

  print "  Reshuffling tags: ";
  Reshuffle(\@TAGS);
  print "  Reshuffling users: ";
  Reshuffle(\@USERS);
  print "  Reshuffling resources: ";
  Reshuffle(\@RES);

  open OUT, ">$projname.reshuffled.tas";
  print OUT "#post_id tag_id user_id resource_id : RESHUFFLED\n";
  $post_id = 0;
  for my $postlen (@POSTLEN) {
    ++$post_id;
    $user_id = pop @USERS;
    $resource_id = pop @RES;
    for my $i (1..$postlen) {
      $tag_id = pop @TAGS;
      print OUT "$post_id $tag_id $user_id $resource_id\n";
    }
  }
  close OUT;

  print "  Reshuffled Tag ASsignments saved into file\n";
  print "       \"$projname.reshuffled.tas\"\n";

  print "TAS_shuffler terminated.\n";
} #end main


exit;

sub Reshuffle {

  my $vref = pop;
  my $dim = $#$vref +1;
  my ($a, $rn);
  my @Work = @$vref;
  my $inidim = $dim;

  print "$dim items.\n";
#  print "####@Work\n";
  @$vref=();
  for (my $i=0; $i<$inidim; $i++) {
    $rn = int(rand($dim--));

    push @$vref, $Work[$rn];
    $a = pop @Work;
    if($rn<$dim) { $Work[$rn] = $a; }
  }
}
