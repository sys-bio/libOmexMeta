import os
from pyomexmeta import RDF, eUriType

# get the link to teusink2000
teusink_biomod_link = r"https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000064.2?filename=BIOMD0000000064_url.xml"

# download model xml, scan for rdf, create rdf graph and store in sqlite database
rdf = RDF.from_uri(teusink_biomod_link, syntax="rdfxml",
                   storage_type="sqlite", storage_name="TeusinkAnnotations2000",
                   storage_options="new='yes'")

# do a search for all annotations with glucode as resource: CHEBI:17234
query_string = """
SELECT ?x ?y
WHERE {
    ?x ?y <http://identifiers.org/obo.chebi/CHEBI:17234>
}
"""

query_results = rdf.query_results_as_dict(query_string)
print(type(query_results))
for k, v in query_results.items():
    print(k, v)


