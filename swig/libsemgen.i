%module semgen

// Add necessary symbols to generated header
%{
#include "semgen.h"
%}

// Process symbols in header
%include "semgen.h"
