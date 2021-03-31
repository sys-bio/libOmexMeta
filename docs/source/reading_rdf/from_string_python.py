from pyomexmeta import RDF, eUriType

rdf_str = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
             @prefix OMEXlib: <http://omex-library.org/> .
             @prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
             @prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

             <http://omex-library.org/NewOmex.omex/NewModel.xml#>
                 <https://dublincore.org/specifications/dublin-core/dcmi-terms/creator> <https://orcid.org/1234-1234-1234-1234> ."""

# read the annotations into RDF graph
rdf = RDF.from_string(rdf_str, format="turtle")

# serialize the string to rdfxml-abbrev
xml_string = rdf.to_string("rdfxml-abbrev")
print(f"RDF graph serialized to rdfxml abbreviated is:\n\n{xml_string}")
