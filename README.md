# SemGen-cpp

[![Build Status](https://travis-ci.com/prakhar-agarwal/semgen-test.svg?branch=master)](https://travis-ci.com/prakhar-agarwal/semgen-test) 


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
    
   

