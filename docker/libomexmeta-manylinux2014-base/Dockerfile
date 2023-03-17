# docker build --tag sysbiouw/libomexmeta-manylinux2014-base:latest .
# docker push  sysbiouw/libomexmeta-manylinux2014-base:latest
FROM quay.io/pypa/manylinux2014_x86_64

RUN yum -y install curl zip unzip tar
RUN yum -y install perl-IPC-Cmd
RUN git clone https://github.com/microsoft/vcpkg.git
RUN cd vcpkg \
    && git pull  \
#    && ./vcpkg update \
    && ./bootstrap-vcpkg.sh
RUN cd vcpkg ./vcpkg integrate install
RUN cd vcpkg && ./vcpkg install curl
RUN cd vcpkg && ./vcpkg install pcre
RUN cd vcpkg && ./vcpkg install yajl
RUN cd vcpkg && ./vcpkg install sqlite3
RUN cd vcpkg && ./vcpkg install liblzma
RUN cd vcpkg && ./vcpkg install openssl

RUN yum install -y wget doxygen
RUN wget https://repo.anaconda.com/miniconda/Miniconda3-py39_4.9.2-Linux-x86_64.sh
RUN bash Miniconda3-py39_4.9.2-Linux-x86_64.sh -b -p /Miniconda3

RUN /Miniconda3/bin/conda create -y --name py37 python=3.7 pytest
RUN /Miniconda3/bin/conda create -y --name py38 python=3.8 pytest
RUN /Miniconda3/bin/conda create -y --name py39 python=3.9 pytest



