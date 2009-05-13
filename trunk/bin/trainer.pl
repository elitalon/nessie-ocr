#!/usr/bin/perl

use strict;
use warnings;


for ( my $k = 1; $k <= 9; $k += 2 )
{
	my $hitRate = 0.0;
	my $codeNo = '01';
	my $nSamples = 0;

	# Classify each press clip
	for (my $i = 1; $i <= 6; ++$i)
	{
		my $programOutput = `../src/ocrtest -s -k $k -t texts/text$codeNo clips/elMundo$codeNo.png | grep -e '- Hit'`;
		$programOutput =~ s/\s*- Hit rate\s+:\s*(\d*)\.(\d*)\s* %/$1.$2/;

		$hitRate += $programOutput;

		$codeNo++;
		$nSamples++;
	}

	# Report hit rate for every K
	$hitRate = $hitRate/$nSamples;
	print "$k: $hitRate\n";

	# Delete samples from the database
	if ( $k != 9 )
	{
		system("psql 'dbname=db_nessieocr user=nessieocr password=nessieocr' -c 'delete from samples where id_sample > 1503023;' -q");
	}
}

