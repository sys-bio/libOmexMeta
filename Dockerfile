FROM ciaranwelsh/ubuntu-base

# install the dependency shared libraries for pyomexmeta
# we also install the gcc 10.1 compilers, and documentation libraries
# and set gcc-10.1 to default.
RUN apt-get install -y yajl-tools flex bison sqlite3 libsqlite3-dev libxml2 libxml2-dev libxslt1-dev postgresql postgresql-contrib libdb-dev libdb-dev gcc-10 g++-10 gcc-9 g++-9 flex bison doxygen python3-sphinx libldap-dev libpthread-stubs0-dev libltdl-dev git slapd ldap-utils graphviz libssl-dev libpq-dev\
    && apt-get install -y curl unzip tar \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10  100 \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10  100


# create conda environment, install some python deps and pyomexmeta
RUN conda init bash \
    && . ~/.bashrc \
    && conda create --name omex python=3.7 \
    && conda activate omex \
    && pip install cpp-coveralls gcovr ipython codecov nose graphviz coverage sphinx breathe python-libcombine tellurium \
    && pip install --index-url https://test.pypi.org/simple/ pyomexmeta

# install cmake
ENV PATH="$PATH:/cmake-3.15.7-Linux-x86_64/bin"
RUN wget https://github.com/Kitware/CMake/releases/download/v3.15.7/cmake-3.15.7-Linux-x86_64.tar.gz \
    && tar -xvf cmake-3.15.7-Linux-x86_64.tar.gz




# get the libOmexMeta source and docs-build
RUN git clone https://github.com/sys-bio/libOmexMeta.git \
    && cd libOmexMeta \
    && mkdir build && cd build \
    && cmake -DVCPKG_ROOT=/vcpkg -DCMAKE_INSTALL_PREFIX=$install_dir -DBUILD_TESTS=ON -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release .. \
    && make -j 8 \
    && make install

