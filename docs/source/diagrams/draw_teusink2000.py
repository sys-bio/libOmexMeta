import os
from pyomexmeta import RDF, eUriType

# get the link to teusink2000
rdf_str = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>
  bqbiol:is <https://identifiers.org/uniprot/PD12345> ."""

# download model xml, scan for rdf, create rdf graph and store in sqlite database
rdf = RDF.from_string(rdf_str, format="turtle")

# draw a diagram
docs_dir = os.path.join(os.path.dirname(__file__), "source")
diagrams_dir = os.path.join(docs_dir, "diagrams")
fname = os.path.join(diagrams_dir, "TeusinkDiagram.png")
rdf.draw(fname)
print(f"file saved to {fname}")
