## Installation

### Using CMake

CMake uses a separate build directory for storing compiled object files and intermediate configure files. See [the CMake manual](https://cmake.org/runningcmake/).

### macOS

Install [git](https://git-scm.com/), CMake 3.14 or greater, Homebrew. Clone the sources:

```bash
git clone https://github.com/sys-bio/libsemgen.git
```

Create and change to a build directory from which to run CMake. libsemsim requires the following dependencies:

* libSBML (with namespaces enabled)
* libCombine
* Raptor2
* Rasqal
* Swig
* Catch2 (optional, for building tests)
* libCellML (optional, not used)

On Mac, some of these can be installed as follows:

```bash
brew install zlib raptor rasqal redland
```

See the respective project pages for how to build and install these packages. Once these packages are install, invoke CMake with the following signature:

```bash
CMAKE_PREFIX_PATH=/path/to/libsbml/lib/cmake:/path/to/libcellml/lib/cmake:/path/to/libcombine/lib/cmake:/path/to/catch2/lib/cmake/Catch2:$CMAKE_PREFIX_PATH cmake -DCMAKE_INSTALL_PREFIX=/path/to/install/libsemsim /path/to/src/libsemsim
```

Then build the release target using XCode. libSemSim will automatically find the currently active Python interpreter (if available) and use it to generate bindings. If you want to use another Python interpreter, add it to your PATH.

Finally, to build the documentation, make sure you have the following packages installed: `sphinx breathe sphinxcontrib-bibtex sphinx_rtd_theme`.

#### SBML Support

In order to support loading SBML models, you will need to build and install libSBML 5.18.0 or later. Refer to the [libSBML building instructions](http://sbml.org/Software/libSBML). You may use the stable or experimental version.

#### CellML Support

In order support loading CellML models (not implemented yet), you will need to build and install libCellML from source. Refer to the [libCellML](https://libcellml.readthedocs.io/en/latest/) documentation for building instructions.

#### Building libSemSim

Create an empty "build" directory for intermediate CMake files and compiled object files. Where you put this directory is up to you. Change to the directory and run the following command (making sure to substitute the appropriate paths for your machine):

```bash
CMAKE_PREFIX_PATH=/path/to/libsbml/lib/cmake:/path/to/libcellml/lib/cmake:/path/to/libcombine/lib/cmake:$CMAKE_PREFIX_PATH PKG_CONFIG_PATH=/usr/local/Cellar/redland/1.0.17_1/lib/pkgconfig:$_PKG_CONFIG_PATH cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/path/to/libsemgen-install /path/to/libsemgen-src
make -j4 install
```

### Linux

Make sure [git](https://git-scm.com/) is installed and clone the libsemgen source:

```bash
git clone https://github.com/sys-bio/libsemgen.git
```

#### Dependencies

Install raptor, rasqal, and redland using your package manager. Instructions vary by distribution. On Fedora:

```bash
sudo dnf -y install raptor2 raptor2-devel rasqal rasqal-devel redland redland-devel
```

#### SBML Support

In order to support loading SBML models, you will need to build and install libSBML 5.18.0 or later. Refer to the [libSBML building instructions](http://sbml.org/Software/libSBML). You may use the stable or experimental version.

#### CellML Support

In order support loading CellML models (not implemented yet), you will need to build and install libCellML from source. Refer to the [libCellML](https://libcellml.readthedocs.io/en/latest/) documentation for building instructions.

#### Building libSemSim

Create an empty "build" directory for intermediate CMake files and compiled object files. Where you put this directory is up to you. Change to the directory and run the following command (making sure to substitute the appropriate paths for your machine):

```bash
CMAKE_PREFIX_PATH=/path/to/libsbml/lib/cmake:/path/to/libcellml/lib/cmake:/path/to/libcombine/lib/cmake:$CMAKE_PREFIX_PATH cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/path/to/install/libsemgen /path/to/src/libsemgen
make -j4 install
```
