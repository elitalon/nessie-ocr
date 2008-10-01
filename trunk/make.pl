#!/usr/bin/perl

$result = `make`;

$result =~ s/\n/<br \/>/g;
$result =~ s/\t/<span style="padding-left:40px" \/>/g;

print $result;
