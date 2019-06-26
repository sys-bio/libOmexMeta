%module semgen

// Add necessary symbols to generated header
%{
#define SWIG_FILE_WITH_INIT
#include "semsim/semsim.h"
%}

// Process symbols in header
%include "semsim/semsim.h"
