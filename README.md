[![PyPI version](https://badge.fury.io/py/pyomexmeta.svg)](https://badge.fury.io/py/pyomexmeta)
[![Build Status](https://dev.azure.com/libOmexMeta/libOmexMeta/_apis/build/status/sys-bio.libOmexMeta?branchName=master)](https://dev.azure.com/libOmexMeta/libOmexMeta/_build/latest?definitionId=1&branchName=master)
[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/sys-bio/pyomexmeta-binder-notebook/HEAD)

# libOmexMeta
LibOmexMeta is a library aimed at providing developer-level support for reading, writing, editing and managing semantic annotations for biosimulation models.  The [COMBINE modeling community](http://co.mbine.org/)  has developed consensus around how best to annotate models and how to package these models into archives (OMEX files) that include the modeling source code, the annotations, files that describe parameters and settings needed for simulations (in a SEDML file), and potentially the data used for these modeling efforts. This consensus was initially described in the  publication ["Harmonizing semantic annotations for computational models in biology" (Briefings in Bioinformatics, 2018)](https://academic.oup.com/bib/article/20/2/540/5164345).

The goal of semantic annotations are to make explicit the biology that underlies the semantics of biosimulation models. By using standard knowledge resources about biology and biological processes (such as CheBI, Uniprot, and ontologies of anatomy), we can make the models more understandable, reusable and reproducible. More information can be found at the [OMEX Metadata Specification web page](http://co.mbine.org/standards/omex-metadata). 

LibOmexMeta is a C++ library with a C interface that is used to build a Python front end (pyomexmeta). LibOmexMeta uses [RDF](https://www.w3.org/RDF/) as a framework for representing these annotations. At the core of libOmexMeta are the [Redland libraries](http://librdf.org/):
    - [raptor2](http://librdf.org/raptor/) for parsing RDF syntax into RDF graphs and serializing the output
    - [rasqal](http://librdf.org/rasqal/) for querying RDF graphs
    - [librdf](http://librdf.org/) as a front end to raptor2 and rasqal and for triple stores. 

## Live demonstration

An interactive demonstration of pyomexmeta via Jupyter notebook is available via the launch binder badge above or by following this [direct link](https://mybinder.org/v2/gh/sys-bio/pyomexmeta-binder-notebook/HEAD). The source for this live demonstration is available here: https://github.com/sys-bio/pyomexmeta-binder-notebook.

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
