## Installation

### Using CMake

CMake uses a separate build directory for storing compiled object files and intermediate configure files. See [the CMake manual](https://cmake.org/runningcmake/).

### macOS

Make sure [git](https://git-scm.com/) is installed and clone the libsemgen source:

```bash
git clone https://github.com/sys-bio/libsemgen.git
```

#### Dependencies

Make sure you have [homebrew](https://brew.sh/) installed and install the following dependencies:

```bash
brew install zlib raptor rasqal redland
```

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
