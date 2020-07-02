FROM ubuntu:18.04
# update apt and collect a few essential tools
# then add the gcc repository before updating apt again.
# now we can install gcc 10 compiler.
# we also download miniconda.
RUN apt-get update \
	&& apt-get install -y wget lsb-release binutils software-properties-common \
	&& wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh \
	&& add-apt-repository -y ppa:ubuntu-toolchain-r/test \
	&& apt-get update

# install miniconda
ENV PATH="/root/miniconda3/bin:$PATH"
ENV DEBIAN_FRONTEND noninteractive
ENV site_packages /root/miniconda3/envs/pyomexmeta-test/lib/python3.7/site-packages
ENV pyomexmeta_dir ${site_packages}/pyomexmeta
RUN mkdir /root/.conda && bash Miniconda3-latest-Linux-x86_64.sh -b

# install the dependency shared libraries for pyomexmeta
# we also install the gcc 10.1 compilers, and documentation libraries
# and set gcc-10.1 to default.
RUN apt-get install -y sqlite3 libsqlite3-dev libxml2 libxml2-dev \
                      libxslt1-dev postgresql postgresql-contrib  \
                      libdb-dev gcc-10 g++-10 flex bison doxygen python3-sphinx\
                      libpthread-stubs0-dev libltdl-dev git \
    && apt-get install -y curl unzip tar \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10  100


# create conda environment, install some python deps and pyomexmeta
RUN conda init bash \
    && . ~/.bashrc \
    && conda create --name pyomexmeta-test python=3.7 \
    && conda activate pyomexmeta-test \
    && pip install ipython sphinx breathe\
    && pip install --index-url https://test.pypi.org/simple/ pyomexmeta

# install cmake
ENV PATH="$PATH:/cmake-3.15.7-Linux-x86_64/bin"
RUN wget https://github.com/Kitware/CMake/releases/download/v3.15.7/cmake-3.15.7-Linux-x86_64.tar.gz \
    && tar -xvf cmake-3.15.7-Linux-x86_64.tar.gz


# get vcpkg and install some dependencies
ENV vcpkg /vcpkg/vcpkg
ENV install_dir /libOmexMeta/install-docker
RUN git clone https://github.com/microsoft/vcpkg.git \
    && cd vcpkg \
    && ./bootstrap-vcpkg.sh \
    && /vcpkg/vcpkg integrate install \
    && /vcpkg/vcpkg install libxml2 curl libiconv pcre openssl yajl libpq sqlite3


# get the libOmexMeta source and build
RUN git clone https://github.com/sys-bio/libOmexMeta.git \
    && cd libOmexMeta \
    && mkdir build && cd build \
    && cmake -DVCPKG_ROOT=/vcpkg -DCMAKE_INSTALL_PREFIX=$install_dir -DBUILD_TESTS=ON .. \
    && make -j 8 \
    && make install

