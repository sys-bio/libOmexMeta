%module semgen

%include "semsim/Preproc.h"

%{
#define SWIG_FILE_WITH_INIT
#include "semsim/SemSim.h"
%}

// Process symbols in header
%include "semsim/SemSim.h"
