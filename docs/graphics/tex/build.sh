#!/usr/bin/env zsh

# exit on failure
set -e
# echo commands as they are run
set -o verbose

# cd to the directory of this script
cd "$( dirname "$0:A" )"
BASE_DIR=`pwd`
cd ..
rm -rf html
mkdir -p html
cd $_

for f in $BASE_DIR/*.tex; do
  htlatex $f </dev/null
done

# fix links in svgs
for f in $BASE_DIR/../html/*.svg; do
  sed -Ei 's:href="([^"]+)" >([^<>]+)</a>:href="\1" target="_parent">\2</a>:g' $f
done
