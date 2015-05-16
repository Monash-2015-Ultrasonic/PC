
Fox-toolkit for MinGW can be re-built with the following:

unzip fox-1.6.37.zip
cd fox-1.6.37
CPPFLAGS="-I${PWD}/../../libpng/include -I${PWD}/../../zlib/include" LDFLAGS="-mno-cygwin -no-undefined -L${PWD}/../../libpng/lib -L${PWD}/../../zlib/lib" ./configure --enable-png
make clean all
cp src/.libs/libFOX-*.dll ../../
cp src/.libs/libFOX-*.a ../../fox/lib
strip --strip-debug ../../libFOX* ../../fox/lib/libFOX*

to build the binaries for Cygwin, do the same ./configure as Mingw, but add:
	--program-prefix=cygwin-
Then make sure to account for the prefix when you run the strip command as above.
