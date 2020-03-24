# LibCombine

## Dependencies
This library requires libSBML to be present, as its XML parsing layer will be used. for that either expat, xerces-c or libXML2 needs to be available. 

## Building 
This library uses [CMake](http://cmake.org) to build the library, so from an initial checkout all you would need todo is to run: 


    mkdir build  
    cd build
    cmake -DLIBSBML_LIBRARY=< path to libsbml lib> -DLIBSBML_INCLUDE_DIR=< path to includes > ... -DEXTRA_LIBS= < comma separated list of xml libraries> 
    make  
    make install
    
Should libSBML be installed in a default location it will be found automatically. Note that you do need to list the xml libraries that libSBML was linked against. In most cases libSBML is compiled against libXML and have compression enabled, so your `EXTRA_LIBS` would be:

	EXTRA_LIBS=xml2;bz2;z;iconv

note the semicolon denoting the listing of several libraries. Of course you could also enter the full path to each individual file, just to give an example, on windows I use: 

	EXTRA_LIBS=D:/dependencies/lib/expat.lib

for linking against `expat` and indicating, that libSBML was compiled without compression.

## License 
This project is open source and freely available under 