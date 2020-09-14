# ciaranwelsh/ubuntu-base:latest suppies a lot for the build enviornment

FROM ciaranwelsh/libomexmeta-build-env

# checkout libomexmeta
# this is the build environment only
ENV install_prefix "/libOmexMeta/install-docker"
RUN pip install pytest
RUN git clone https://github.com/sys-bio/libOmexMeta.git \
    && cd libOmexMeta \
    && mkdir build \
    && cd build \
    && cmake -DCMAKE_INSTALL_PREFIX="$install_prefix" -DVCPKG_ROOT="/vcpkg" -DBUILD_TESTS=ON -DBUILD_DOCS=ON -DBUILD_DOCS_EXAMPLES=ON .. \
    && make -j 8 \
    && make install


