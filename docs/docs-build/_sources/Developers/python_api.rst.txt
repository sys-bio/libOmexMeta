Developing the Python API
=========================

When you build then install OmexMeta, copies of OmexMeta and its dependencies
are put into the pyomexmeta folder so the tests can be run locally. These binaries
are included in the setup.py script and everything is already configured to build
a pip wheel and upload to pypi. The only thing you need to remember is to ensure you
update the omexmeta version in the main CMakeLists.txt, which will be propagated into the python
setup.py script.
