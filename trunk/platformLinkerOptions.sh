if [ "$1" == "-t" ] # library type
then
	if [ `uname -s` == "Darwin" ]
	then
		echo "libNessieOcr.dylib\c"
	else
		echo "libNessieOcr.so\c"
	fi
elif [ "$1" == "-o" ] # linker options
then
	if [ `uname -s` == "Darwin" ]
	then
		LIBRARY=libNessieOcr.dylib
		echo "-shared -Wl,-dylib_install_name,$LIBRARY\c"
	else
		LIBRARY=libNessieOcr.so
		echo "-shared -Wl,-soname,$LIBRARY\c"
	fi
else
	echo "\c"
fi
