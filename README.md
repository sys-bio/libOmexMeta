# libsemsim (aka libOmexMeta)
Libsemsim is a C++ library for annotating systems biology models that 
use xml for serialization. Libsemsim uses RDF as a framework for
representing these annotations. 

In addition to the C++ backend there is a C API which is exported into a shared
library for importing libsemsim into other languages, as well as a Python front 
end library. 

This is a pre-release version of libsemsim and should be considered as such. 
Its primary purpose is to get feedback from collaborators on how to 
improve the software. Suggested improvements should be turned into coherent 
github issues. 

As a side note, the name `libsemsim` is due to change to `libOmexMeta` before release. 

# Platform
Due to the Redland library dependencies being linux only, libsemsim has been 
developed on Ubuntu 18.04 and is presently still linux only. Support for Windows 
and macos is a work in progress. 

# Installation
## Python front end
You can get up and running quickly using pip

    $ pip install --index-url https://test.pypi.org/simple pysemsim

Note that "pysemsim" is only available on pypi test. It has been tested with Python
version 3.8, but should work on other Python 3 versions. 

## Building from source
**tl;dr**
Optionally become `sudo`er.
```
$ sudo -i
```
You will be prompted for password and will then need to `cd` back into the directory
where you downloded libsemsim. If you do not do this, then the cmake 
script will ask for a password during install. 

```
$ git clone https://github.com/sys-bio/libsemsim.git
$ cd libsemsim
$ mkdir build && cd build
$ cmake -DHAVE_DEPENDENCIES=OFF -DBUILD_TESTS=ON -DBUILD_SHARED=ON -DBUILD_WRAPPER_TESTS=ON -DBUILD_DOCS=OFF -DWITH_ADDRESS_SANITIZER=OFF ..
$ make -j 8 #or however may processes you want to yse
# sudo make install
```

Remember you can set
```
-DCMAKE_INSTALL_PREFIX="/path/to/install/location"  
```
i.e. 
```
-DCMAKE_INSTALL_PREFIX=$(pwd)/install-ubuntu  
```
to install to somewhere non-standard. 

Disclaimer: The build system for me but is untested on other computers. Expect some turbulence 
to begin with. Feedback on build errors will help stablize the build system. 

### The superbuild
libsemsim uses a "superbuild" system to fully automate the acquisition of dependencies. The main dependencies of 
libsemsim is are the Redland libraries: raptor2, rasqal and librdf. For convenience, the sources of these packages 
are distributed with libsemsim and are pulled into a single binary called `redland-combined.a` for linking. Furthermore, 
included in the superbuild are both `libsbml` and `libcombine`. These dependencies are deliberately not 
used and will soon become optional in the libsemsim build that is set to `OFF` by default.  

To control the superbuild, there is a CMake variable called `HAVE_DEPENDENCIES`. 
The first time you run cmake, you will probably want to have the `HAVE_DEPENDENCIES=ON` 
but if you rebuild you can set `HAVE_DEPENDENCIES=OFF`. 

# Documentation

https://sys-bio.github.io/libsemsim-docs/

Note: documentation is currently out of date but being updated presently 

# Manually install dependencies
The superbuild tries to run the following command for you automatically. This 
feature is experimental, so if it doesn't work you will need to run it yourself: 

```
$ sudo apt install -y dialog apt-utils make build-essential checkinstall zlib1g-dev libltdl-dev lzma libpcre3 libpcre3-dev uuid-dev libxml2 libxml2-dev libxslt1-dev yajl-tools libgss-dev libmpfr-dev idn2 libpthread-stubs0-dev curl mysql-server
```
and then proceed with the build instructions. 


