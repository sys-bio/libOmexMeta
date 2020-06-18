FROM conda/miniconda3
RUN apt update && apt install -y wget libxslt1-dev libltdl-dev yajl-tools
RUN pip install ipython
RUN pip install --index-url https://test.pypi.org/simple pysemsim









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


# create an environment and install pysemsim version 0.0.5
#RUN conda init bash
#RUN conda create --name py38 -y python=3.8 \
#    && conda activate py38 \
#    && pip install ipython \
#    && pip install --index-url https://test.pypi.org/simple pysemsim

