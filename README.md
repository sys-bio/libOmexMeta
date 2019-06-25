## Installation

### Using CMake

CMake uses a separate build directory for storing compiled object files and intermediate configure files. See [the CMake manual](https://cmake.org/runningcmake/).

### macOS

Make sure [git](https://git-scm.com/) is installed and clone the libsemgen source:

```bash
git clone https://github.com/sys-bio/libsemgen.git
```

Make sure you have [homebrew](https://brew.sh/) installed and install the following dependencies:

```bash
brew install pugixml libzip raptor rasqal redland
```

Next, you will need to build and install libSBML 5.18.0 or later. Refer to the [libSBML building instructions](http://sbml.org/Software/libSBML). You may use the stable or experimental version.

Create an empty "build" directory for intermediate CMake files and compiled object files. Where you put this directory is up to you. Change to the directory and run the following command:

```bash
CMAKE_PREFIX_PATH=/path/to/libsbml-installtion:$CMAKE_PREFIX_PATH PKG_CONFIG_PATH=/usr/local/Cellar/redland/1.0.17_1/lib/pkgconfig:$_PKG_CONFIG_PATH cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/path/to/libsemgen-install /path/to/libsemgen-src
make -j4 install
```

### Linux

Make sure [git](https://git-scm.com/) is installed and clone the libsemgen source:

```bash
git clone https://github.com/sys-bio/libsemgen.git
```

Install pugixml libzip raptor rasqal, and redland using your package manager. Instructions vary by distribution. On Fedora:

```bash
dnf -y install pugixml pugixml-devel libzip libzip-devel raptor2 raptor2-devel rasqal rasqal-devel redland redland-devel
```

Create an empty "build" directory for intermediate CMake files and compiled object files. Where you put this directory is up to you. Change to the directory and run the following command:

Next, you will need to build and install libSBML 5.18.0 or later. Refer to the [libSBML building instructions](http://sbml.org/Software/libSBML). You may use the stable or experimental version.

```bash
CMAKE_PREFIX_PATH=/path/to/libsbml-installtion:$CMAKE_PREFIX_PATH cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/path/to/libsemgen-install /path/to/libsemgen-src
make -j4 install
```

 ## Pre-requisites
    cmake
    swig (http://macappstore.org/swig/)
    libsbml
    libcellml
    libzip (http://macappstore.org/libzip/)
    LibXml2 (http://macappstore.org/libxml2/)
    automake
    aclocal
    autoconf
    autoheader
    libtoolize
    gtkdocize (http://macappstore.org/gtk-doc/)
    librdf
    raptor
    rasqal
    glibtoolize (required if installing on MAC OSX)
        - Update libtoolize in autogen.sh configuration files for Raptor and Rasqal
        - Replace libtoolize with glibtoolize
        - GLIBTOOLIZE=/usr/local/bin/glibtoolize ./autogen.sh



## Usage
    mkdir build
    cd build
    cmake ..
    make
