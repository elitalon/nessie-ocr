#!/usr/bin/perl

use strict;
use warnings;


my $codeNo = '01';
for ( my $k = 1; $k <= 33; ++$k )
{
	my $text	= "training/elPais/text$codeNo";
	my $image	= "training/elPais/clip$codeNo.png";
	`../src/ocrtest -t $text $image`;

	$codeNo++;
}

