#!/usr/bin/perl

# sprite2c.pl by Travis Goodspeed

# This is an ugly hack for converting PNM sprites to C.  I'd rather
# use the GIMP's exporter, but it prefers 24-bit color, which can't be
# afforded for embedded applications.

# N.B., that this expects some GIMP-specific crap.


print "// ZombieGotcha Sprite Translator \n\n";

my $pnmtype, $line;

#First, verify the filetype
$pnmtype=<>;
print STDERR "ERROR: Type is not P3.  Use ASCII GIMP PNM in RGB!." if $pnmtype ne "P3\n";

#    P1 Portable bitmap ASCII
#    P2 Portable graymap ASCII
#    P3 Portable pixmap ASCII
#    P4 Portable bitmap Binary
#    P5 Portable graymap Binary
#    P6 Portable pixmap Binary

#Next, find the file dimensions.  Comments should be printed in C.
do{
    $line=<>;
    chomp $line;
    print STDOUT "  // $line\n" if $line=~m/^#/;
}while($line=~m/^#/);

#$line still has the dimensions, parse it.
$line=~ s/ /,/;
print "  $line, //Width, Height\n";

$max=<>;
chomp $max;
print "  //Max $max\n\n";

#Now handle all the pixels in B&W.
my $atbit=0;
my $byte=5;
print "  //Pixels\n";
while (<STDIN>){
    chomp;
    $bit=int($_)?0:1;
    $byte=$byte>>1;;
    $byte=$byte|($bit?0x80:0);
    
    #Waste two bits.
    <STDIN>;
    <STDIN>;
    
    #Advance the bit counter and print byte if needed.
    $atbit++;
    if ($atbit%8 ==0) {
	$byte&=0xFF;
	printf("  0x%02x,",$byte);
	print "\n" if $atbit%192==0;
    }
}


print "\n  // done.\n";
