from pyomexmeta import RDF

rdf_str = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
              @prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
              @prefix myOMEXlib: <http://omex-library.org/> .
              @prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
              @prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .
              
              local:OmexMetaId0000
                  bqbiol:is <https://identifiers.org/uniprot/PD12345> ."""

# read the string into our RDF graph
rdf = RDF.from_string(rdf_str, format="turtle")

fname = "/path/to/annotation_file.rdf"

# Add to our RDF graph by reading the second string
rdf.add_from_file(fname, "rdfxml")
