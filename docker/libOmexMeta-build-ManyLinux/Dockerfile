FROM ciaranwelsh/manylinux2014

RUN git clone https://github.com/sys-bio/libOmexMeta.git --recurse-submodules
RUN cd /libOmexMeta && mkdir build && cd build \
    && cmake -DCMAKE_INSTALL_PREFIX=../install-docker -DCMAKE_BUILD_TYPE=Release -DVCPKG_ROOT=/vcpkg -DBUILD_TESTS=ON .. \
    && cmake --build . --target install -j 12 --config Release


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
