#!/usr/bin/env zsh
astyle --style=google --indent-classes --indent-switches --indent-namespaces --indent-labels --indent-preproc-block --indent-preproc-define --indent-preproc-cond --indent-col1-comments --max-continuation-indent=80 --pad-header --delete-empty-lines --lineend=linux --align-pointer=type semsim/**/*(.cpp|.h)
