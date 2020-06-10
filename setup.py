from setuptools import setup

MAJOR = 0
MINOR = 0
MICRO = 1

version = f'{MAJOR}.{MINOR}.{MICRO}'

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
