[![Build Status](https://travis-ci.org/sys-bio/libOmexMeta.svg?branch=master)](https://travis-ci.org/sys-bio/libOmexMeta) 
[![PyPI version](https://badge.fury.io/py/pyomexmeta.svg)](https://badge.fury.io/py/pyomexmeta)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://GitHub.com/Naereen/StrapDown.js/graphs/commit-activity)

# libOmexMeta
LibOMEXmeta is a library aimed at providing developer-level support for reading, writing, editing and managing semantic annotations for biosimulation models.  The [COMBINE modeling community](http://co.mbine.org/)  has developed consensus around how best to annotate models and how to package these models into archives (OMEX files) that include the modeling source code, the annotations, files that describe parameters and settings needed for simulations (in a SEDML file), and potentially the data used for these modeling efforts. This consensus was initially described in the  publication ["Harmonizing semantic annotations for computational models in biology" (Briefings in Bioinformatics, 2018)](https://academic.oup.com/bib/article/20/2/540/5164345).

The goal of semantic annotations are to make explicit the biology that underlies the semantics of biosimulation models. By using standard knowledge resources about biology and biological processes (such as CheBI, Uniprot, and ontologies of anatomy), we can make the models more understandable, reusable and reproducible. More information can be found at the [OMEX Metadata Specification web page](http://co.mbine.org/standards/omex-metadata). 

Libsemsim is a C++ library with a C interface that is used to build a Python front end (pyomexmeta). Libsemsim uses [RDF](https://www.w3.org/RDF/) as a framework for representing these annotations. At the core of libOmexMeta are the [Redland libraries](http://librdf.org/):
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

# Documentation

https://sys-bio.github.io/libOmexMeta/

Note: documentation is being written presently 

# Installation
## Python

On linux, grab some dependencies:

    $ sudo apt install libxml2 libxml2-dev libxslt1-dev libpq-dev

Windows is self-contained.

Now use pip. 

    $ pip install pyomexmeta
    # verify its worked
    $ ipython -c "import pyomexmeta"
    
Python 3 only - if you're not using Python 3, I recommend you upgrade. 

## Docker
You can get a docker image using 

    $ docker pull ciaranwelsh/libomexmeta:v1.1.0
    
This is an Ubuntu 18.04 based container that has libOmexMeta prebuilt and installed under `/libOmexMeta/install-docker`. See [dockerfile](https://github.com/sys-bio/libOmexMeta/blob/master/Dockerfile) for full set of commands to build libOmexMeta on ubuntu. 
Conda is preconfigured and pyomexmeta is installed. 

## Downloading Binaries
You can download binaries from the [releases tab](https://github.com/sys-bio/libOmexMeta/releases/tag/v0.1.10)

## Building from source
See above for docker image which does this for you already on linux builds. The build process is similar on both windows and linux, but linux has some additional dependencies installed via `apt-get`. 

### On Linux only, install some dependencies using apt
Note, the build process is not yet fully optimized for linux and will be improved

Pick up some dependencies
```
$ sudo apt-get install -y sqlite3 libsqlite3-dev libxml2 libxml2-dev \
                      libxslt1-dev postgresql postgresql-contrib  libdb-dev \
                      libdb-dev gcc-10 g++-10 flex bison doxygen python3-sphinx\
                      libpthread-stubs0-dev libltdl-dev git
                      
```
Switch default gcc to version 10.1: 
```
update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10  100
```

### On both Linux and Windows
Get `vcpkg`
```
$ git clone https://github.com/microsoft/vcpkg.git 
$ cd vcpkg 
```
#### Configure vcpkg and install dependencies on Linux
```
$ ./bootstrap-vcpkg.sh 
$ vcpkg integrate install 
$ vcpkg install libxml2 curl libiconv pcre openssl yajl libpq sqlite3
```
Note: this is where the linux build is not optimized. 
#### Configure vcpkg and install dependencies on Windows
```
> bootstrap-vcpkg.bat 
> vcpkg integrate install 
> vcpkg install libxml2:x64-windows curl:x64-windows libiconv:x64-windows pcre:x64-windows openssl:x64-windows yajl:x64-windows libpq:x64-windows sqlite3:x64-windows
```
### Build `libOmexMeta`
Use [CMake > 15.7](https://github.com/Kitware/CMake/releases/download/v3.15.7/cmake-3.15.7-Linux-x86_64.tar.gz)
```
git clone https://github.com/sys-bio/libOmexMeta.git 
cd libOmexMeta 
mkdir build && cd build 
cmake -DVCPKG_ROOT=/vcpkg -DCMAKE_INSTALL_PREFIX=../install-linux -DBUILD_TESTS=ON -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release .. 
make -j 8 
make install # or sudo if installing to default location (i.e. omit the `-DCMAKE_INSTALL_PREFIX`)
```

