from pyomexmeta import RDF

rdf_str1 = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
              @prefix OMEXlib: <http://omex-library.org/> .
              @prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
              @prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .
 
              <http://omex-library.org/NewOmex.omex/NewModel.xml#>
                  <http://purl.org/dc/terms/creator> <https://orchid.org/1234-1234-1234-1234> ."""


rdf_str2 = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
              @prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
              @prefix OMEXlib: <http://omex-library.org/> .
              @prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
              @prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .
              
              local:OmexMetaId0000
                  bqbiol:is <https://identifiers.org/uniprot/PD12345> ."""

# read the first string into our RDF graph
rdf = RDF.from_string(rdf_str1, format="turtle")
# Add to our RDF graph by reading the second string
rdf.add_from_string(rdf_str2)
print(f"Number of annotations in graph: {len(rdf)}")
