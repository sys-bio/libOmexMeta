from setuptools import setup
import os

version_file = os.path.join(os.path.dirname(__file__), "VERSION.txt")
if not os.path.isfile(version_file):
    raise FileNotFoundError(f"The version file \"{version_file}\" should exist in"
                            f" the top level "
                            "directory of the libsemsim pacakge but does not. "
                            "Please ensure you have configured with cmake, "
                            "which will convert \"VERSION.in\" into \"VERSION.txt\"")

with open(version_file) as f:
    version = f.read().strip()

"""
Install with 
    pip install --index-url https://test.pypi.org/simple pysemsim
for now. 
"""

setup(
    name='pysemsim',
    version=version,
    license='MIT',
    long_description=open('README.md').read(),
    long_description_content_type="text/markdown",
    author='Ciaran Welsh',
    author_email='cwelsh2@uw.edu',
    url='https://github.com/sys-bio/libsemsim',
    keywords=['annotation', 'rdf'],
    install_requires=[],
    packages=['pysemsim'],
    package_dir={'pysemsim': 'src/pysemsim'},
    package_data={'pysemsim': [
        'LICENCE.txt',
        'libsemsim.so']
    },
    include_package_data=True,
)
