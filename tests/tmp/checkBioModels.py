# will be deleted soon.

import pyomexmeta as pyo
import os
biomodels_tmpdir = r"D:\temp-biomodels\final"

failing_biomodels = [
    "BIOMD0000000094/BIOMD0000000094_url.xml",
    "BIOMD0000000192/BIOMD0000000192_url.xml",
    "BIOMD0000000220/BIOMD0000000220_url.xml",
    "BIOMD0000000226/BIOMD0000000226_url.xml",
    "BIOMD0000000227/BIOMD0000000227_url.xml",
    "BIOMD0000000394/BIOMD0000000394_url.xml",
    "BIOMD0000000395/BIOMD0000000395_url.xml",
    "BIOMD0000000396/BIOMD0000000396_url.xml",
    "BIOMD0000000397/BIOMD0000000397_url.xml",
    "BIOMD0000000398/BIOMD0000000398_url.xml",
    "BIOMD0000000436/BIOMD0000000436_url.xml"]


failing_biomodels = [os.path.join(biomodels_tmpdir, i) for i in failing_biomodels]

current = failing_biomodels[0]

assert os.path.isfile(current), current

#
# rdf = pyo.RDF.from_file(current, "rdfxml")
#
#
# print(rdf)
#




















