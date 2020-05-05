#!/usr/bin/env bash
############################################################
# Test python scripts
############################################################
# To test the python examples setup a virtual environment
#
#   cd ./examples/python
#   mkvirtualenv libcombine
#   (libcombine) pip install -r requirements.txt
#
# and run the tests via
#
#   (libcombine) ./test.sh
############################################################

python printExample.py testdata/case_01.omex
python createArchiveExample.py testdata/case_01.xml
python printExample.py testdata/out.omex
rm testdata/out.omex
python printExample.py testdata/CombineArchiveShowCase.omex

python printExample.py testdata/zhao2013_fig3a-user.sedx
