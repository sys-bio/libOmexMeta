import os
import matplotlib.pyplot as plt
from pyomexmeta import RDF

# get the link to teusink2000
teusink_biomod_link = r"https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000064.2?filename=BIOMD0000000064_url.xml"

# download model xml, scan for rdf, create rdf graph and store in sqlite database
rdf = RDF.from_uri(teusink_biomod_link, format="rdfxml",
                   storage_type="sqlite", storage_name="TeusinkAnnotations2000",
                   storage_options="new='yes'")

# do a search for all annotations with glucode as resource: CHEBI:17234
query_string = """
SELECT ?x ?y
WHERE {
    ?x ?y <http://identifiers.org/obo.chebi/CHEBI:17234>
}
"""

results_formats = [
    "xml",
    "json",
    "table",
    "csv",
    "mkr",
    "tsv",
    "html",
    "turtle",
    "rdfxml",
]

for i in results_formats:
    print("Sparql results format: {}".format(i))
    print(rdf.query(query_string, results_format=i))
    print("\n\n")

