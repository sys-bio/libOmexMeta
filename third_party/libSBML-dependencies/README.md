# libSBML Dependencies<img width="14%" align="right" src=".graphics/sbml-badge.svg">

This repository gathers together a number of open-source libraries to make building [libSBML](sbml.org/Software/libSBML "libSBML") with [CMAKE](http://www.cmake.org/) easier.

[![License](https://img.shields.io/badge/License-BSD-blue.svg?style=flat-square)](https://choosealicense.com/licenses/bsd-2-clause/)


Table of contents
-----------------

* [Introduction](#introduction)
* [Installation](#installation)
* [Usage](#usage)
* [Getting help](#getting-help)
* [License](#license)
* [Authors and history](#authors-and-history)
* [Acknowledgments](#authors-and-acknowledgments)


Introduction
------------

This project contains a number of open source libraries, that make the building of [libSBML](sbml.org/Software/libSBML "libSBML") with [CMAKE](http://www.cmake.org/) as easy as to configure with: 

	cmake -DLIBSBML_DEPENDENCY_DIR=<dir> <libSBML source dir>  
	make  
	make install

This project is primarily meant to aid Windows users, as all of these libraries are readily available on other systems. As such, the project consists of `cmake` scripts and batch files to make it easy to build the correct set of dependencies. 


Installation
------------

Clone this repository to your computer or use the download link on the GitHub repository front page.


Usage
-----

This project contains one primary [CMAKE](http://www.cmake.org/) script, that will build all libraries. So all that will be required would be the normal step, of creating a build dir, and then calling `cmake` for building. To make this process even easier there are a number of batch files, to aid in the process:

	createNinja32_vs10.bat
	createNinja32_vs11.bat
	createNinja32_vs12.bat
	createNinja32_vs9.bat
	createNinja64_vs10.bat
	createNinja64_vs11.bat
	createNinja64_vs12.bat
	createNinja64_vs9.bat
	createNMake.bat
	createNMakeVS11.bat
	createWin64.bat
	createWin64Debug.bat
	createWin64vs11.bat


### _Libraries_

The following open source libraries are included in this project: 

- [bzip2 v1.0.5](http://http://www.bzip.org/)
- [check v0.9.8](http://check.sourceforge.net/)
- [expat 2.1.0](http://expat.sourceforge.net/)
- [iconv v1.12](http://www.gnu.org/software/libiconv/)
- [libxml2 v2.7.3](http://www.xmlsoft.org/)
- [xerces-c v3.1.1](https://xerces.apache.org/xerces-c/)
- [zlib v1.2.3](http://www.zlib.net/)


Getting help
------------

If you find an issue, please submit it in [the GitHub issue tracker](https://github.com/sbmlteam/libSBML-dependencies/issues) for this repository.  Alternatively, you are welcome to contact the author or the SBML Team [via email](mailto:sbml-team@googlegroups.com) with questions.


License
-------

Each of the libraries in each of the sub folders are released under their own respective licenses. Otherwise this project (i.e.: the build scripts) are released under the BSD License: 

```
Copyright (c) 2013-2015, Frank T. Bergmann  
All rights reserved. 

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are 
met: 

Redistributions of source code must retain the above copyright notice, 
this list of conditions and the following disclaimer. Redistributions in 
binary form must reproduce the above copyright notice, this list of 
conditions and the following disclaimer in the documentation and/or 
other materials provided with the distribution. THIS SOFTWARE IS 
PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
```

Author and history
------------------

Frank Bergmann created this project around 2015; he and Sarah Keating have been maintaining it since.


Acknowledgments
---------------

Funding for this and other SBML work has come from the [National Institute of General Medical Sciences](https://www.nigms.nih.gov) via grant NIH R01&nbsp;GM070923 (Principal Investigator: Michael Hucka).

<br>
<div align="center">
  <a href="https://www.nigms.nih.gov">
    <img valign="middle"  height="100" src=".graphics/US-NIH-NIGMS-Logo.svg">
  </a>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <a href="https://www.caltech.edu">
    <img valign="middle" height="130" src=".graphics/caltech-round.png">
  </a>
</div>
