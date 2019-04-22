%module semgen

// Add necessary symbols to generated header
%{
#include "libsemgen.h"
%}

// Process symbols in header
%include "libsemgen.h"
