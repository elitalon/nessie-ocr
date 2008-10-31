#!/usr/bin/perl

$result = `doxygen 2>&1`;

$result =~ s/\n/<br \/>/g;
$result =~ s/\t/<span style="padding-left:40px" \/>/g;

print $result;
