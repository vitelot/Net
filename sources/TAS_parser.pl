#! /usr/bin/perl -w

use strict;

my %wlink; # global var

{ #main
  print "Starting program TAS_parser:\n";
  die "  Missing file name to parse. Exiting.\n" if($#ARGV<0);
  my $projname = pop;
  $projname =~ s/\.in$//;
  my ($post_id, $tag_id, $user_id, $resource_id);
  my $old_post_id;
  my $linecount=0;
  my ($t,$u) = (0,0);
  my @tags_in_post = ();
  my %alltags;
#  my %allusers;

  $old_post_id = 3.1415;
  open IN, "<$projname.tas" or die "  Can't open \"$projname.tas\": $!";
  print "  File \"$projname.tas\" opened.\n";
  while(<IN>) {
    ++$linecount;
    next if /^#/; # skip comment lines
    ($post_id, $tag_id, $user_id, $resource_id) = split /\s+/;

    $alltags {$tag_id}  = $t++ unless(exists $alltags {$tag_id});
#    $allusers{$user_id} = $u++ unless(exists $allusers{$user_id});

    if($post_id==$old_post_id) {
      push @tags_in_post, $alltags{$tag_id};
    } else {
      LinkTagsinPost(\@tags_in_post);
      @tags_in_post = ($alltags{$tag_id});
    }
    $old_post_id = $post_id;
#    print "$post_id, $tag_id, $user_id, $resource_id\n";
  }
  LinkTagsinPost(\@tags_in_post); # empty last buffer

  close IN;
  print "  $linecount lines read.\n";

  open OUT, ">$projname.tag_cooccurrence.in";
  print OUT "# ", scalar(keys %alltags)," nodes, ",scalar(keys %wlink), " links\n";
  for (keys %wlink) {
    print OUT "$_ $wlink{$_}\n";
  }
  print OUT "#\n#\n# Legend follows (old_tag_id new_tag_id):\n";
  for (sort {$a<=>$b} keys %alltags) {
    print OUT "#$_ $alltags{$_}\n";
  }
  close OUT;
  print "  Tag co-occurrence weighted network saved into file\n";
  print "       \"$projname.tag_cooccurrence.in\"\n";

  print "TAS_parser terminated.\n";
} #end main


exit;

sub LinkTagsinPost {

  my $vref = pop;
  my $dim = $#$vref +1;
  my ($a,$b);

#  print "***$dim\n";
  return if($dim<1);

  for (my $i=0; $i<$dim; $i++) {
    for (my $j=0; $j<$i; $j++) {
      $a= $$vref[$i];
      $b= $$vref[$j];
      if($a<=$b) {$wlink{"$a $b"}++;}
      else       {$wlink{"$b $a"}++;}
    }
  }
}
