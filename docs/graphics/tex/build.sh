#!/usr/bin/env zsh

# exit on failure
set -e
# echo commands as they are run
set -o verbose

# cd to the directory of this script
cd "$( dirname "$0:A" )"
BASE_DIR=`pwd`
cd ..
mkdir -p html
cd $_

for f in $BASE_DIR/*.tex; do
  htlatex -interaction nonstopmode --halt-on-error $f
done
