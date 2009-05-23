#!/usr/bin/perl

use strict;
use warnings;


#for ( my $k = 1; $k <= 9; $k += 2 )
#{
	#my $hitRate = 0.0;
	#my $codeNo = '01';
	#my $nSamples = 0;

	# Classify each press clip
	my $programOutput = 0.0;
	for (my $i = 0; $i < 100; ++$i)
	{
		$programOutput += `../src/ocrtest training/elPais/clip*.png`;
		#$programOutput =~ s/\s*- Hit rate\s+:\s*(\d*)\.(\d*)\s* %/$1.$2/;

		#$hitRate += $programOutput;

		#$codeNo++;
		#$nSamples++;
	}

	$programOutput = $programOutput / 100.0;
	print "$programOutput\n";

	# Report hit rate for every K
	#$hitRate = $hitRate/$nSamples;
	#print "$k: $hitRate\n";

	# Delete samples from the database
	#if ( $k != 9 )
	#{
		#system("psql 'dbname=db_nessieocr user=nessieocr password=nessieocr' -c 'delete from samples where id_sample > 1503023;' -q");
	#}
#}

