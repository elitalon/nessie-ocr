if [ "$1" = "-e" ] # library extension
then
	if [ `uname -s` = "Darwin" ]
	then
		echo ".dylib\c"
	else
		echo ".so\c"
	fi
elif [ "$1" = "-o" ] # linker options
then
	if [ `uname -s` = "Darwin" ]
	then
		echo "-dylib_install_name\c"
	else
		echo "-soname\c"
	fi
else
	echo "\c"
fi
