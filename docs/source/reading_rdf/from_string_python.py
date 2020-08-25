from pyomexmeta import RDF

rdf_str = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
             @prefix OMEXlib: <http://omex-library.org/> .
             @prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
             @prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

             <http://omex-library.org/NewOmex.omex/NewModel.xml#>
                 <http://purl.org/dc/terms/creator> <https://orchid.org/1234-1234-1234-1234> ."""
rdf = RDF.from_string(rdf_str, format="turtle")
print(f"Number of annotations in graph: {len(rdf)}")
