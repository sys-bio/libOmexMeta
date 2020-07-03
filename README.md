[![Build Status](https://travis-ci.org/sys-bio/libOmexMeta.svg?branch=master)](https://travis-ci.org/sys-bio/libOmexMeta)
# libOmexMeta
Libsemsim is a C++ library for annotating models in systems biology. Libsemsim uses [RDF](https://www.w3.org/RDF/) as a framework for representing these annotations. At the core of libOmexMeta are the [Redland libraries](http://librdf.org/):
    - [raptor2](http://librdf.org/raptor/) for parsing RDF syntax into RDF graphs and serializing the output
    - [rasqal](http://librdf.org/rasqal/) for querying RDF graphs
    - [librdf](http://librdf.org/) as a front end to raptor2 and rasqal and for triple stores. 


## Features
### [Parsers](http://librdf.org/raptor/api-1.4/raptor-parsers.html)
  - rdfxml, ntriples, turtle, trig, rss-tag-soup, grddl, guess, rdfa, nquads, guess
### [Serializers](http://librdf.org/raptor/api-1.4/raptor-serializers.html)
  - ntriples, turtle, rdfxml-xmp, rdfxml-abbrev, rdfxml, rss-1.0, atom, dot, json-triples, json, nquads, html
  
### [Querying](http://librdf.org/rasqal/docs/api/)
  - Languages
    - [SPARQL](https://www.w3.org/TR/sparql11-query/), [LAQRS](https://www.dajobe.org/2007/04/laqrs/) 
  - Query result formats: 
    - xml, json, table, csv, mkr, tsv, html, turtle, rdfxml,

### [Storages modules](http://librdf.org/docs/api/redland-storage-modules.html)
  - hashes, memory, file, mysql, sqlite, uri, tstore (may be supported on request), postgresql (supported but not tested), virtuoso (may be supported on request), 


# Platform
  - Windows
  - Linux Ubuntu 18.04, untested on other flavours. 
  
libOmexMeta has not been tested on a Mac.  


# Installation
## Python front end
You can get up and running quickly using pip

    $ sudo apt install libxslt1-dev libltdl-dev  yajl-tools
    $ pip install --index-url https://test.pypi.org/simple/ pyomexmeta
    # verify its worked
    $ ipython -c "import pyomexmeta"

Note that "pyomexmeta" is only available on pypi test. It has been tested with Python
version 3.8, but should work on other Python 3 versions. 

## Downloading Binaries
You can download binaries from the [releases tab](https://github.com/sys-bio/libomexmeta/releases/tag/v0.0.2)

## Building from source
**tl;dr**

Optionally become `sudo`er.
```
$ sudo -i
```
You will be prompted for password and will then need to `cd` back into the directory
where you downloded libomexmeta. If you do not do this, then the cmake 
script will ask for a password during install. 

```
$ git clone https://github.com/sys-bio/libomexmeta.git
$ cd libomexmeta
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
-DCMAKE_INSTALL_PREFIX=install-ubuntu  
```
to install to somewhere non-standard. 

Disclaimer: The build system for me but is untested on other computers. Expect some turbulence 
to begin with. Feedback on build errors will help stablize the build system. 

### The superbuild
libomexmeta uses a "superbuild" system to fully automate the acquisition of dependencies. The main dependencies of 
libomexmeta is are the Redland libraries: raptor2, rasqal and librdf. For convenience, the sources of these packages 
are distributed with libomexmeta and are pulled into a single binary called `redland-combined-static.a` for linking. Furthermore, 
included in the superbuild are both `libsbml` and `libcombine`. These dependencies are deliberately not 
used and will soon become optional in the libomexmeta build that is set to `OFF` by default.  

To control the superbuild, there is a CMake variable called `HAVE_DEPENDENCIES`. 
The first time you run cmake, you will probably want to have the `HAVE_DEPENDENCIES=ON` 
but if you rebuild you can set `HAVE_DEPENDENCIES=OFF`. 

# Documentation

https://sys-bio.github.io/libomexmeta-docs/

Note: documentation is currently out of date but being updated presently 

# Manually install dependencies
The superbuild tries to run the following command for you automatically. This 
feature is experimental, so if it doesn't work you will need to run it yourself: 

```
$ sudo apt install -y icu-devtools dialog apt-utils make build-essential checkinstall zlib1g-dev libltdl-dev lzma libpcre3 libpcre3-dev uuid-dev libxml2 libxml2-dev libxslt1-dev yajl-tools libgss-dev libmpfr-dev idn2 libpthread-stubs0-dev curl mysql-server
```
and then proceed with the build instructions. 

# Still to do
- Support for modifying existing annotations 
    - deleting a triple works but memory related problems when
      removing a set of triples like a physical entity
- documentation
- support for removing triples based on metaid (sparql?)
- Bug in multiplier of participants, when 0, it should not default to x^-315. Use integers instead??
- Remove second namespace map in RDF class in favour of the one in Predicate class
- Double check Predicate.cpp. Do we have everything that we want to include? (my guess is no)
- Statically link all dependency libraries. 


Things that could (and maybe should) change in future versions
--------------------------------------------------------------
- Redland package could be reintegrated with the rest of libomexmeta code. 
  The original plan was to write a full C++ wrapper around the three redland libraries. 
  Due to difficulties, this didn't really materialize so it might make more sense to 
  pull that code back into the semsim folder. 
