#! /usr/bin/perl -w

printhlp() if(!defined @ARGV);

push @ARGV, "-fake";
$filename = shift @ARGV; #filename is the first arg
$outfile = "AVECT.agr";

($av) = ("@ARGV" =~ /.*-a (((\d+ )+) ?|(\d+:\d+ ?)).*/);
if( defined $av) {
  $av =~ s/^\s+//;
  if( $av =~ /:/) {
    ($i1,$i2) = ($av =~ /(\d+):(\d+)/);
#    print "++++ $i1 +++++ $i2 +++++\n";
    (@Eigvct_nr) = ($i1 .. $i2);
  } else {
    (@Eigvct_nr) = split /\s+/, $av;
  }
}
#print "@Eigvct_nr\n";

($kv) = ("@ARGV" =~ /.*-k (((\d+ )+) ?|(\d+:\d+ ?)).*/);
if( defined $kv) {
  $kv =~ s/^\s+//;
  if( $kv =~ /:/) {
    ($i1,$i2) = ($kv =~ /(\d+):(\d+)/);
    (@K_nr) = ($i1 .. $i2);
  } else {
    (@K_nr) = split /\s+/, $kv;
  }
}
#print "@K_nr\n";

open(  IN, "<$filename") || die "Error opening \"$filename\": $!.\n";
open( OUT, ">$outfile" ) || die "Error opening \"$outfile\": $!.\n";

$EigvalCount=0;
$dimeigvect=$cavect=0;
while(<IN>) {
  if( /EIGENVAL/) {
    PrintXmgrace();
    ($eigval) = /EIGENVALUE\s+=\s+(.+)/;
    $EigvalCount++;
    next;
  }
  next if /EIGENVECT/;
  next if /^\#/;
  s/^\s+//;
  ($k,$v) = split /\s+/;
  $EigVect{$k} = $v;
}
$dimeigvect = $k+1;

close IN;
close OUT;

system "xmgrace -geometry 1150x900 $outfile &" unless "@ARGV"=~/-xa/;

if( -e "LEGENDA") {
  my ($key, $name);
  open ( IN, "<LEGENDA");
  while(<IN>) {
    chop;
    s/^\s+//;
    ($key,$name) = split /\s+/;
    $Legend[$key] = $name;
  }
  close IN;
}


if     ("@ARGV" =~ /-m1/) {
  Method1();
} elsif("@ARGV" =~ /-m2/) {
  Method2();
} elsif("@ARGV" =~ /-m3/) {
  Method3();
} elsif("@ARGV" =~ /-m4/) {
  Method4();
} else {
  Method4();
}

exit;

sub Method4 { # nodes are in the same community if max|ev1-ev2|<eps
  my $outf = "COMM@K_nr-$outfile";
  $outf =~ s/\s/_/g;
  $cnode = 0;
  open( OUT, ">$outf" ) || die "Error opening \"COMM-$outfile\": $!.\n";
  foreach my $k1 (@K_nr) {
    print OUT "##### NODE $k1 #####\n";
    print OUT "@    s$cnode legend  \"Node $k1\"\n";
    print OUT "@    s$cnode line linewidth 2.0\n";
    print OUT "@    s$cnode symbol 1\n";
    print OUT "@    s$cnode symbol size 0.50\n";
    print OUT "@    s$cnode symbol fill pattern 1\n";
    ++$cnode;

    #RK1 contains the value of eigv components (or ranks) for node k1
    (@RK1) = split /\s+/, $Ranking{$k1};
    foreach my $k2 (keys %Ranking) {
      (@RK2) = split /\s+/, $Ranking{$k2};
      $dist = 0.0;
      for( my $i=0; $i<=$#RK1; $i++) {
	$dist = abs($RK2[$i]-$RK1[$i]) if( $dist < abs($RK2[$i]-$RK1[$i]) );
      }
#      $Comm{$k2} = $dist*sqrt($dimeigvect);
      $Comm{$k2} = $dist;
    }
    $c=0;
    foreach my $key (sort { $Comm{$a} <=> $Comm{$b} } keys %Comm) {
      if(defined $Legend[$key]) {
	printf OUT "%6d %10g %6d %s\n", $c++, $Comm{$key}, $key, $Legend[$key];
      }else{
	printf OUT "%6d %10g %6d\n", $c++, $Comm{$key}, $key;
      }
    }
    print OUT " \n";
  }
  close OUT;

  system "xmgrace -geometry 1150x900 $outf &" unless "@ARGV"=~/-xk/;

}

sub Method3 {
  my $outf  = "PAIRS.dat";
  my $outf2 = "Avects.dat";
  my ($r12,$r11,$r22,$cosangle);

  open( OUT, ">$outf2" ) || die "Error opening \"$outf\": $!.\n";
  foreach my $k1 (sort {$a<=>$b} keys %Ranking) {
    print OUT "$Ranking{$k1}\n";
  }
  close OUT;

  open( OUT, ">$outf" ) || die "Error opening \"$outf\": $!.\n";
  foreach my $k1 (sort {$a<=>$b} keys %Ranking) {
    (@RK1) = split /\s+/, $Ranking{$k1};
    foreach my $k2 (sort {$a<=>$b} keys %Ranking) {
#      next if($k1>=$k2);
      (@RK2) = split /\s+/, $Ranking{$k2};
      $r12=$r11=$r22=0.0;
      for( my $i=0; $i<=$#RK1; $i++) {
	$r12 += $RK1[$i]*$RK2[$i];
	$r11 += $RK1[$i]*$RK1[$i];
	$r22 += $RK2[$i]*$RK2[$i];
      }
      $cosangle = $r12/sqrt($r11*$r22);
      printf OUT "%5d %5d %10.5f\n", $k1, $k2, $cosangle;
    }
  }
  close OUT;
}

sub Method2 {
  my $outf = "COMM-$outfile";
  $cnode = 0;
  open( OUT, ">$outf" ) || die "Error opening \"COMM-$outfile\": $!.\n";
  foreach my $k1 (@K_nr) {
    print OUT "##### NODE $k1 #####\n";
    print OUT "@    s$cnode legend  \"Node $k1\"\n";
    print OUT "@    s$cnode line linewidth 2.0\n";
    print OUT "@    s$cnode symbol 1\n";
    print OUT "@    s$cnode symbol size 0.50\n";
    print OUT "@    s$cnode symbol fill pattern 1\n";
    ++$cnode;
    (@RK1) = split /\s+/, $Ranking{$k1};
    foreach my $k2 (keys %Ranking) {
      (@RK2) = split /\s+/, $Ranking{$k2};
      $Ratio = 0.0;
      for( my $i=0; $i<=$#RK1; $i++) { $Ratio += FUNCTION( $RK2[$i], $RK1[$i]); }
      $Ratio /= $#RK2+1;
      $Comm{$k2} = $Ratio;
    }
    $c=0;
    foreach my $key (sort { $Comm{$b} <=> $Comm{$a} } keys %Comm) {
      if(defined $Legend[$key]) {
	printf OUT "%6d %10g %6d %s\n", $c++, $Comm{$key}, $key, $Legend[$key];
      }else{
	printf OUT "%6d %10g %6d\n", $c++, $Comm{$key}, $key;
      }
    }
    print OUT " \n";
  }
  close OUT;

  system "xmgrace -geometry 1150x900 $outf &" unless "@ARGV"=~/-xk/;

}

sub FUNCTION {
  my ($a,$b) = @_;
  my $s=1;
  my $m=1.0;
  my $r=$a/$b;

  return exp(-($r-$m)**2/(2*$s*$s));
}

sub Method1 {
foreach my $k1 (@K_nr) {
  open( OUT, ">COMM-$k1-$outfile" ) || die "Error opening \"COMM-$outfile\": $!.\n";
  (@RK1) = split /\s+/, $Ranking{$k1};
  $x = Mean(@RK1); # <x>

  $x2=Mean2(@RK1); # <x^2>

  foreach my $k2 (keys %Ranking) {
    (@RK2) = split /\s+/, $Ranking{$k2};
    $y = Mean(@RK2); # <y>

    $y2=Mean(@RK2);  # <y^2>

    $xy=0;
    for( my $i=0; $i<=$#RK1; $i++) { $xy += $RK1[$i]*$RK2[$i]; }
    $xy /= $#RK1+1; # <xy>

    $corr = ($xy-$x*$y)/(sqrt(($x2-$x*$x))*sqrt(($y2-$y*$y))); # <xy>-<x><y>/<x2>-<x>2

    $Comm{$k2} = $corr;
  }
  $c=0;
  foreach my $key (sort { $Comm{$b} <=> $Comm{$a} } keys %Comm) {
    if(defined $Legend[$key]) {
      printf OUT "%6d %10g %6d %s\n", $c++, $Comm{$key}, $key, $Legend[$key];
    }else{
      printf OUT "%6d %10g %6d\n", $c++, $Comm{$key}, $key;
    }
  }
  close OUT;
}
}

sub Mean {
  my ($c, $mean);

  $c = $mean = 0;
  foreach my $i (@_) {
    $mean += $i;
    ++$c;
  }
  return $mean/$c;
}
sub Mean2 {
  my ($c, $mean);

  $c = $mean = 0;
  foreach my $i (@_) {
    $mean += $i*$i;
    ++$c;
  }
  return $mean/$c;
}

sub IsIn {
  my ($a, @A) = @_;
  foreach my $i (@A) {
    if($i==$a) {return 1;}
  }
  return 0;
}

sub PrintXmgrace {

  if( $EigvalCount && IsIn($EigvalCount, @Eigvct_nr)==1 ) {
    if("@ARGV" =~ /-p/) {
      print OUT "##### $EigvalCount $eigval\n";
      foreach my $key (sort {$a<=>$b} (keys %EigVect)) {
	printf OUT "%6d %10g\n", $key, $EigVect{$key};
      }
      print OUT " \n";
    } else {
      print OUT "##### $EigvalCount $eigval\n";
      print OUT "@    s$cavect legend  \"\\f{12}l\\f{} = $eigval\"\n";
      print OUT "@    s$cavect line linewidth 3.0\n";
      ++$cavect;
      $c=0;
      foreach my $key
	(sort { $EigVect{$b} <=> $EigVect{$a} } keys %EigVect)
	  {
	    printf OUT "%6d %10g %6d\n", $c++, $EigVect{$key}, $key;
	    #$Ranking{$key} .= "$EigVect{$key} ";
	    $Ranking{$key} .= "$c ";
	  }
      print OUT " \n";
    }
  }
}

sub printhlp {
    print "Usage:\n";
    print " $0 filename -a nr_of_eigvects -k nr_of_nodes\n";
    print "   --------------------------------------------------------------\n";
    print "   \n";
    print "   \n";
    print "   --------------------------------------------------------------\n";
    print "   Options:\n";
    print "    -a       work on these eigenvectors\n";
    print "    -k       find communities to which k belongs\n";
    print "    -p       plain eigenvectors as output\n";
    print "    -xa      do not run xmgrace on eigenvectors\n";
    print "    -xk      do not run xmgrace on communities\n";
    print "    -m{1234} use method 1 or 2 or 3.\n";
    print "    -h       this Help.\n\n";
    exit;
}
