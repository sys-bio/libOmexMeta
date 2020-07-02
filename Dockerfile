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
RUN apt-get install -y sqlite3 libsqlite3-dev libxml2 libxml2-dev \
                      libxslt1-dev postgresql postgresql-contrib  \
                      libdb-dev gcc-10 g++-10 flex bison doxygen python3-sphinx\
    && apt-get install -y apt-get install -y curl unzip tar \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10  100


# create conda environment
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
    &&

# get vcpkg and install deps
ENV vcpkg /vcpkg/vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git \
    && cd vcpkg \
    && ./boostrap-vcpkg.sh \
    && vcpkg integrate install \
    && vcpkg install libxml2 curl libiconv pcre openssl yajl libpq sqlite3 \
    && mkdir build && cd build \
    && cmake -DVCPKG_ROOT=/vcpkg .. \
    && make -j 8 \
    && make install

# get the libOmexMeta source
RUN apt-get install -y git \
    && git clone https://github.com/sys-bio/libOmexMeta.git
    && cd libOmexMeta
#RUN

#RUN . ~/.bashrc
#	&& pip install -y ipython

## install pyomexmeta
#	&& site_packages="/usr/local/envs/pyomexmeta-test/lib/python3.7/site-packages"



#RUN apt update && apt install -y wget libxslt1-dev libltdl-dev yajl-tools
#RUN pip install ipython
#RUN pip install --index-url https://test.pypi.org/simple pyomexmeta









#RUN wget https://github.com/Kitware/CMake/releases/download/v3.15.7/cmake-3.15.7-Linux-x86_64.tar.gz \
#    && tar -xf cmake-3.15.7-Linux-x86_64.tar.gz \
#    && export PATH="$PATH:$(pwd)/cmake-3.15.7-Linux-x86_64/bin" \
#    && apt install -y make build-essential \
#    && build-essential checkinstall zlib1g-dev \
#    && sudo wget https://www.openssl.org/source/openssl-1.1.1g.tar.gz
#    && tar -xf openssl-1.1.1g.tar.gz \
#    && ./config --prefix=/usr/local/ssl --openssldir=/usr/local/ssl shared zlib \
#    && make




## install miniconda
#RUN wget \
#    https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh \
#    && mkdir /root/.conda \
#    && bash Miniconda3-latest-Linux-x86_64.sh -b \
#    && rm -f Miniconda3-latest-Linux-x86_64.sh \
#    && conda --version \
#    && conda create -y --name py38 python=3.8


# create an environment and install pyomexmeta version 0.0.5
#RUN conda init bash
#RUN conda create --name py38 -y python=3.8 \
#    && conda activate py38 \
#    && pip install ipython \
#    && pip install --index-url https://test.pypi.org/simple pyomexmeta

