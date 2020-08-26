from setuptools import setup
import os
import glob
import sys

version_file = os.path.join(os.path.dirname(__file__), "VERSION.txt")
if not os.path.isfile(version_file):
    raise FileNotFoundError(f"The version file \"{version_file}\" should exist in"
                            f" the top level "
                            f"directory of the libomexmeta pacakge but does not. "
                            f"Please ensure you have configured with cmake, "
                            f"which will convert \"VERSION.in\" into \"VERSION.txt\"")

with open(version_file) as f:
    version = f.read().strip()

# get source directory
THIS_DIR = os.path.abspath(os.path.dirname(__file__))
SRC_DIR = os.path.join(THIS_DIR, "src")
PYOMEXMETA_DIR = os.path.join(SRC_DIR, "pyomexmeta")

"""
Install with 
    pip install --index-url https://test.pypi.org/simple pyomexmeta
for now. 
"""

CLASSIFIERS = """\
Development Status :: 3 - Alpha
Intended Audience :: Science/Research
Intended Audience :: Developers
License :: OSI Approved :: Apache Software License
Programming Language :: C
Programming Language :: C++
Programming Language :: Python
Programming Language :: Python :: 3
Programming Language :: Python :: 3.6
Programming Language :: Python :: 3.7
Programming Language :: Python :: 3.8
Programming Language :: Python :: 3 :: Only
Programming Language :: Python :: Implementation :: CPython
Topic :: Software Development
Topic :: Scientific/Engineering
Operating System :: Microsoft :: Windows
Operating System :: POSIX
Operating System :: Unix
"""
# Operating System :: MacOS // macos not yet supported


binaries = [
    os.path.join(PYOMEXMETA_DIR, "concrt140.dll"),
    os.path.join(PYOMEXMETA_DIR, "api-ms-win-core-wow64-l1-1-0.dll"),
    os.path.join(PYOMEXMETA_DIR, "libcharset.dll"),
    os.path.join(PYOMEXMETA_DIR, "libcrypto-1_1-x64.dll"),
    os.path.join(PYOMEXMETA_DIR, "libcurl.dll"),
    os.path.join(PYOMEXMETA_DIR, "libdb48.dll"),
    os.path.join(PYOMEXMETA_DIR, "libdb-5.3.so"),
    os.path.join(PYOMEXMETA_DIR, "libiconv.dll"),
    os.path.join(PYOMEXMETA_DIR, "libpq.dll"),
    os.path.join(PYOMEXMETA_DIR, "libssl-1_1-x64.dll"),
    os.path.join(PYOMEXMETA_DIR, "libxml2.dll"),
    os.path.join(PYOMEXMETA_DIR, "libxslt.dll"),
    os.path.join(PYOMEXMETA_DIR, "lzma.dll"),
    os.path.join(PYOMEXMETA_DIR, "msvcp140.dll"),
    os.path.join(PYOMEXMETA_DIR, "msvcp140_1.dll"),
    os.path.join(PYOMEXMETA_DIR, "msvcp140_2.dll"),
    os.path.join(PYOMEXMETA_DIR, "msvcp140_codecvt_ids.dll"),
    os.path.join(PYOMEXMETA_DIR, "OmexMeta.dll"),
    os.path.join(PYOMEXMETA_DIR, "pcre.dll"),
    os.path.join(PYOMEXMETA_DIR, "redland-combined.dll"),
    os.path.join(PYOMEXMETA_DIR, "sqlite3.dll"),
    os.path.join(PYOMEXMETA_DIR, "vcruntime140.dll"),
    os.path.join(PYOMEXMETA_DIR, "yajl.dll"),
    os.path.join(PYOMEXMETA_DIR, "zlib1.dll"),
    os.path.join(PYOMEXMETA_DIR, "vcruntime140.dll"),
    os.path.join(PYOMEXMETA_DIR, "vcruntime140_1.dll"),
    # linux dependencies
    os.path.join(PYOMEXMETA_DIR, "libOmexMeta.so"),
    os.path.join(PYOMEXMETA_DIR, "libOmexMetaCAPI.so"),
    # os.path.join(PYOMEXMETA_DIR, "libsqlite3.so"),
    # os.path.join(PYOMEXMETA_DIR, "libxml2.so"),
    # Problem with distributing linux dependencies:
    #   The .so files are actually symlinks. They have a size of 0 and do not
    #   get packaged into a pip wheel. On linux, its therefore easier to
    #   get users to install dependencies manually.  One solution is
    #   to copy over the actual so files (i.e. with version number) in cmake
    #   instead of the symlink.
]


for i in binaries:
    print(i)
    if not os.path.isfile(i):
        raise FileNotFoundError(f"Dependency \"{i}\" not found.")

setup(
    name='pyomexmeta',
    version=version,
    license='MIT',
    long_description=open('README.md').read(),
    long_description_content_type="text/markdown",
    author='Ciaran Welsh',
    author_email='cwelsh2@uw.edu',
    url='https://github.com/sys-bio/libomexmeta',
    keywords=['annotation', 'rdf'],
    # install_requires=open('requirements.txt').read().split('\n'),
    install_requires=["graphviz", "pydot"],#["pypiwin32"] if sys.platform.startswith("win") else [],
    packages=['pyomexmeta'],
    package_dir={'pyomexmeta': 'src/pyomexmeta'},
    package_data={'pyomexmeta': [
        'LICENCE.txt',
    ] + binaries},
    include_package_data=True,
    classifiers=[_f for _f in CLASSIFIERS.split('\n') if _f],
    platforms=["Windows", "Linux", "Unix"],  # "Mac OS-X", - not yet supported.
)
