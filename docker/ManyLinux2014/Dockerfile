#FROM quay.io/pypa/manylinux2014_x86_64:latest
#FROM dockcross/manylinux2010-x64 # nooooope
#FROM pypywheels/manylinux2010-pypy_x86_64
FROM quay.io/pypa/manylinux2014_x86_64

RUN git clone https://github.com/microsoft/vcpkg.git
RUN cd vcpkg \
    && ./bootstrap-vcpkg.sh
RUN cd vcpkg ./vcpkg integrate install
RUN cd vcpkg && ./vcpkg install curl pcre openssl yajl sqlite3 liblzma

#RUN git clone https://github.com/microsoft/vcpkg.git $VCPKG_ROOT
#RUN cd $VCPKG_ROOT \
#    && ./bootstrap-vcpkg.sh
#RUN cd $VCPKG_ROOT ./vcpkg integrate install
#RUN $VCPKG_ROOT/vcpkg install curl pcre openssl yajl sqlite3 liblzma
#

RUN git clone https://github.com/sys-bio/libOmexMeta.git --recurse-submodules
RUN cd /libOmexMeta && mkdir build && cd build \
    && cmake -DCMAKE_INSTALL_PREFIX=../install-docker -DCMAKE_BUILD_TYPE=Release -DVCPKG_ROOT=/vcpkg -DBUILD_TESTS=ON .. \
    && cmake --build . --target install -j 12 --config Release

RUN yum install -y wget
RUN wget https://repo.anaconda.com/miniconda/Miniconda3-py39_4.9.2-Linux-x86_64.sh
RUN bash Miniconda3-py39_4.9.2-Linux-x86_64.sh -b -p /Miniconda3

RUN /Miniconda3/bin/conda create -y --name py37 python=3.7 pytest
RUN /Miniconda3/bin/conda create -y --name py38 python=3.8 pytest
RUN /Miniconda3/bin/conda create -y --name py39 python=3.9 pytest

RUN cd /libOmexMeta && mkdir build-py37 && cd build-py37 \
    && cmake -DCMAKE_INSTALL_PREFIX=../install-docker-py37 -DCMAKE_BUILD_TYPE=Release -DVCPKG_ROOT=/vcpkg -DBUILD_TESTS=ON -DBUILD_PYTHON=ON -DPython_ROOT_DIR=/Miniconda3/envs/py37 ..
RUN cd /libOmexMeta/build-py37 \
    && cmake --build . --target install -j 12 --config Release
RUN ctest --verbose --extra-verbose

RUN cd /libOmexMeta/install-docker-py37 \
    && /Miniconda3/envs/py37/bin/python ./setup.py bdist_wheel


RUN cd /libOmexMeta && mkdir build-py38 && cd build-py38 \
    && cmake -DCMAKE_INSTALL_PREFIX=../install-docker-py38 -DCMAKE_BUILD_TYPE=Release -DVCPKG_ROOT=/vcpkg -DBUILD_TESTS=ON -DBUILD_PYTHON=ON -DPython_ROOT_DIR=/Miniconda3/envs/py38 ..
RUN cd /libOmexMeta/build-py38 \
    && cmake --build . --target install -j 12 --config Release
RUN ctest --verbose --extra-verbose

RUN cd /libOmexMeta/install-docker-py38 \
    && /Miniconda3/envs/py38/bin/python ./setup.py bdist_wheel


RUN cd /libOmexMeta && mkdir build-py39 && cd build-py39 \
    && cmake -DCMAKE_INSTALL_PREFIX=../install-docker-py39 -DCMAKE_BUILD_TYPE=Release -DVCPKG_ROOT=/vcpkg -DBUILD_TESTS=ON -DBUILD_PYTHON=ON -DPython_ROOT_DIR=/Miniconda3/envs/py39 ..
RUN cd /libOmexMeta/build-py39 \
    && cmake --build . --target install -j 12 --config Release
RUN ctest --verbose --extra-verbose

RUN cd /libOmexMeta/install-docker-py39 \
    && /Miniconda3/envs/py39/bin/python ./setup.py bdist_wheel


#
#RUN cd /libOmexMeta && mkdir build-py38 && cd build-py38 \
#    && cmake -DCMAKE_INSTALL_PREFIX=../install-docker-py38 -DCMAKE_BUILD_TYPE=Release -DVCPKG_ROOT=/vcpkg -DBUILD_TESTS=ON -DBUILD_PYTHON=ON -DPython_ROOT_DIR=/Miniconda3/envs/py38 .. \
#    && cmake --build . --target install -j 12 --config Release \
#    && ctest --verbose --extra-verbose
#RUN cd /libOmexMeta/install-docker-py38 \
#    && /Miniconda3/envs/py38/bin/python ./setup.py bdist_wheel
#
#RUN cd /libOmexMeta && mkdir build-py39 && cd build-py39 \
#    && cmake -DCMAKE_INSTALL_PREFIX=../install-docker-py39 -DCMAKE_BUILD_TYPE=Release -DVCPKG_ROOT=/vcpkg -DBUILD_TESTS=ON -DBUILD_PYTHON=ON -DPython_ROOT_DIR=/Miniconda3/envs/py39 .. \
#    && cmake --build . --target install -j 12 --config Release \
#    && ctest --verbose --extra-verbose
#RUN cd /libOmexMeta/install-docker-py39 \
#    && /Miniconda3/envs/py39/bin/python ./setup.py bdist_wheel
