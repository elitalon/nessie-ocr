foreach (readpipe("svn info $ARGV[0]"))
{
	if($_ =~/^Last Changed Rev: ([0-9]+)/)
	{
		print $1;
	}
}