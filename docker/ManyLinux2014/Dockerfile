FROM quay.io/pypa/manylinux2014_x86_64:latest


ENV VCPKG_ROOT /vcpkg
ENV MINICONDA_ROOT /miniconda3
ENV LIBOMEXMETA_ROOT /libOmexMeta
ENV LIBOMEXMETA_BUILD $LIBOMEXMETA_ROOT/build
ENV LIBOMEXMETA_INSTALL_PREFIX $LIBOMEXMETA_ROOT/install-docker
ENV PATH="/$(MINICONDA_ROOT)/bin:$PATH"


RUN git clone https://github.com/microsoft/vcpkg.git $VCPKG_ROOT
RUN cd $VCPKG_ROOT \
    && ./bootstrap-vcpkg.sh \
RUN cv $VCPKG_ROOT ./vcpkg integrate install
RUN $VCPKG_ROOT/vcpkg install curl pcre openssl yajl sqlite3 liblzma


RUN git clone https://github.com/sys-bio/libOmexMeta.git --recurse-submodules $LIBOMEXMETA_ROOT
RUN mkdir $LIBOMEXMETA_BUILD && cd $LIBOMEXMETA_BUILD \
    && cmake -DCMAKE_INSTALL_PREFIX=$LIBOMEXMETA_INSTALL_PREFIX -DCMAKE_BUILD_TYPE=Release -DVCPKG_ROOT=$VCPKG_ROOT .. \
    && cmake --build . --target install -j 12 --config Release
