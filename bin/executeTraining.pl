#!/usr/bin/perl

use strict;
use warnings;


my $codeNo = '01';
for ( my $k = 1; $k <= 6; ++$k )
{
	my $text	= "training/elMundo/elMundo$codeNo";
	my $image	= "training/elMundo/elmundo$codeNo.png";
	`../src/ocrtest -s -f samples.dataset -t $text $image`;

	$codeNo++;
}

