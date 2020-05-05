# LibCombine
LibCombine implements a C++ API library providing support for the [Combine Archive](http://co.mbine.org/documents/archive). The library is written after the likeness of libSBML (and in fact some classes have been generated using DEVISER). Thus even thought he core is written in C++, the classes can be accessed via SWIG from .NET, Java and Python. 

[![License](http://img.shields.io/:license-BSD-blue.svg)](http://opensource.org/licenses/BSD-2-Clause)  [![Latest version](https://img.shields.io/badge/Latest_version-0.1.0-brightgreen.svg)](http://shields.io) [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.154158.svg)](https://doi.org/10.5281/zenodo.154158)

----
*Authors*:      [Sarah M. Keating](http://www.ebi.ac.uk/about/people/sarah-keating), and [Frank T. Bergmann](http://www.cos.uni-heidelberg.de/index.php/f.bergmann?l=_e).

*License*:      This code is licensed under the 2 Clause BSD.  Please see the file [../LICENSE.md](https://raw.githubusercontent.com/sbmlteam/libCombine/master/LICENSE.md) for details.

*Repository*:   [https://github.com/sbmlteam/libCombine](https://github.com/sbmlteam/libCombine)

*Documentation*:   [API Documentation](https://sbmlteam.github.io/libCombine/html/class_combine_archive.html)


## Dependencies
This library requires libSBML to be present, as its XML parsing layer will be used. for that either expat, xerces-c or libXML2 needs to be available. Additionally you will need zlib as well as the zipper library that can be obtained from: 

* <https://github.com/fbergmann/zipper>

The zipper library no longer requires c++ 17, or qt or boost but instead uses file system functions developed by the [COPASI](http://copasi.org) project.

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

To make it easier all dependencies can be installed into a directory with a `bin`, `include` and `lib` folder. If that is passed to cmake using the variable `-DCOMBINE_DEPENDENCY_DIR=<directory>` all dependencies are easily found. 

## How to use
The library is centered around the class `CombineArchive`.  Once you created an instance of the class, you can add files and content to it using either `addFile` with a filename, or with an input stream in case it is an in memory element. To add metadata you would use `addMetadata`. The actual combine archive will only be created upon a call to `writeToFile`. 

To read a combine archive, you would use the function `initializeFromArchive`. At that point you can retrieve all the locations inside the archive using `getAllLocations()`. For each of the location you could then request metadata using: `getMetadataForLocation`, the entry in form of a string using `extractEntryToString`, have it stored to a file / folder using `extractEntry`. You can also have the whole archive written to a directory using `extractTo`.  

We have some examples using the library in the [examples folder](./examples) that demonstrate the use of the library for reading / writing.

## License 
This project is open source and freely available under the [Simplified BSD](http://opensource.org/licenses/BSD-2-Clause) license. Should that license not meet your needs, please contact me. 


  Copyright (c) 2016, Sarah M. Keating & Frank T. Bergmann 
  All rights reserved.
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met: 
  
  1. Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer. 
  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution. 
  
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
