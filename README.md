[![PyPI version](https://badge.fury.io/py/pyomexmeta.svg)](https://badge.fury.io/py/pyomexmeta)
[![Build Status](https://dev.azure.com/libOmexMeta/libOmexMeta/_apis/build/status/sys-bio.libOmexMeta?branchName=master)](https://dev.azure.com/libOmexMeta/libOmexMeta/_build/latest?definitionId=1&branchName=master)
[![badge](https://img.shields.io/badge/launch-pyomexmeta-F5A252.svg?logo=data:image/png;base64,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)](https://gesis.mybinder.org/binder/v2/gh/aram148/libomexmeta-SI/c095a05cb43b7c32bf5c81e8c28f16c9779d9df9)
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

Use pip. 

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
You can download binaries from the [releases tab](https://github.com/sys-bio/libOmexMeta/release)

## Building from source
See the azure-pipelines.yml file to see how we build libOmexMeta on Azure Pipelines. 

We use vcpkg for acquiring the dependencies that we need on all platforms. Therefore, the following works on windows, linux and macOS. Note that on linux you need gcc-9 or greater. libOmexMeta was developed with gcc-10.2.

```
# set variable to hold vcpkg location: 
VCPKG_INSTALL_PREFIX="/full/path/to/vcpkg"
git clone https://github.com/microsoft/vcpkg.git $VCPKG_INSTALL_PREFIX
cd $VCPKG_INSTALL_PREFIX
./bootstrap-vcpkg.sh
vcpkg integrate install
vcpkg install curl pcre openssl yajl sqlite3 liblzma
```             

Now build libOmexMeta
```
git clone https://github.com/sys-bio/libOmexMeta.git
cd libOmexMeta
mkdir build
cd build
cmake -DVCPKG_ROOT=$VCPKG_INSTALL_PREFIX -DCMAKE_INSTALL_PREFIX="/full/path/to/where/you/want/to/install/libomexmeta" -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release -DBUILD_PYTHON=ON ..
cmake --build . --target install --config Release -j 12
```
