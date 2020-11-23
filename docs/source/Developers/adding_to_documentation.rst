Adding to the Documentation
============================

The documentation in libOmexMeta is example based and a lot of effort
has gone into streamlining the production of new examples for the documentation.
To build the documentation make sure you add the following cmake definitions
to your call to cmake. For example, this is what I have for my call to cmake.
Note the last three definitions. They are important for building the docs.
Also, ensure you have installed the dependencies in the Python distribution that
you are using to build the docs (i.e. argument to -DPYTHON_EXECUTABLE). They
are:

.. code-block:: bash

    pip install breathe sphinx sphinxcontrib-bibtex sphinx-tabs sphinx_rtd_theme

Then do:

.. code-block:: bash

    cmake -DVCPKG_ROOT=/home/ciaran/vcpkg -DCMAKE_INSTALL_PREFIX=/mnt/d/libOmexMeta/install-ubuntu -DBUILD_TESTS=ON -DBUILD_SHARED_LIBS=ON -DWITH_COVERAGE=OFF -DCMAKE_BUILD_TYPE=Debug  -DWITH_SANITIZER=OFF -DBUILD_DOCS_EXAMPLES=ON -DBUILD_DOCS=ON -DPYTHON_EXECUTABLE=/home/ciaran/miniconda3/envs/py37/bin/python ..


When you build the target called `libomexmeta-docs-sphinx` several things will happen:

    #. Cmake will build all C/C++ examples that we give it. See docs/CMakeList.txt. It is
       the job of the developer to add a new executable when new examples are added and to add the
       name of this executable to the cmake list called `EXAMPLE_EXECUTABLES_TARGETS`.
    #. Cmake will call out and run the Python script called build_doc_examples at the top level of the docs directory. This
       will run all programs it finds, including C++/C/Python
    #. Doxygen will generate documentation from c++ strings
    #. Sphinx and breathe will generate sphinx documentation from rst files, pulling in the source code and program output into sphinx.

