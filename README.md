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
    

   

