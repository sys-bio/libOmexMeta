# SemGen-cpp

[![Build Status](https://travis-ci.com/prakhar-agarwal/semgen-test.svg?branch=master)](https://travis-ci.com/prakhar-agarwal/semgen-test) 
<img src="https://travis-ci.com/images/logos/TravisCI-Mascot-1.png" width="50">
<img src="https://github.com/codecov/media/blob/master/logos/icon-50.png" width="50">

## Pre-requisites
    doxygen
    boost test-unit-framework
    lcov
    
## Usage 
    mkdir build
    cd build
    cmake ..
    make
    
## Features

### Documentation

Generates the doxygen documentation in doc/html. Hosted via ReadtheDocs

    cmake -DENABLE_DOC=1 ..
    make doc  

### Code Coverage

Generates code coverage test report

    cmake -DENABLE_COVERAGE=1 ..
    make test  
    
   