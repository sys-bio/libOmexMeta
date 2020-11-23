from pyomexmeta import RDF, eUriType

turtle_string = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:OmexMetaId0001
    bqbiol:isPropertyOf local:EntityProperty0000 ;
    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .

local:EntityProperty0000
    bqbiol:is <https://identifiers.org/uniprot/P84022> ;
    bqbiol:isPartOf <https://identifiers.org/fma/FMA:24178>, <https://identifiers.org/fma/FMA:63877>, <https://identifiers.org/fma/FMA:70737>, <https://identifiers.org/fma/FMA:7163> .

"""

# remember that the default parser is "guess".
# the parser will try to figure out which syntax is being used.
# but if it doesn't guess well, you can use the format argument for `from_string`
rdf = RDF.from_string(turtle_string)

formats = [
    "ntriples",
    "turtle",
    "rdfxml-abbrev",
    "rdfxml",
    "dot",
    "json-triples",
    "json",
    "nquads",
    "html"
]

for syntax in formats:
    print("Serializing to {}".format(syntax))
    print(rdf.to_string(syntax))
    print("\n\n")


# Note: printing the rdf object is the same as rdf.to_string("turtle")


