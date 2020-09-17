from pyomexmeta import RDF
import os

turtle_string = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:OmexMetaId0001
    bqbiol:isPropertyOf local:PhysicalEntity0000 ;
    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .

local:PhysicalEntity0000
    bqbiol:is <https://identifiers.org/uniprot/P84022> ;
    bqbiol:isPartOf <https://identifiers.org/fma/FMA:24178>, <https://identifiers.org/fma/FMA:63877>, <https://identifiers.org/fma/FMA:70737>, <https://identifiers.org/fma/FMA:7163> .

"""

# remember that the default parser is "guess".
# the parser will try to figure out which syntax is being used.
# but if it doesn't guess well, you can use the format argument for `from_string`
rdf = RDF.from_string(turtle_string)

syntax = "ntriples"
filename = os.path.join(os.path.dirname(__file__), "write_to_file.rdf")
print("Serializing to {}:".format(syntax))
print(rdf.to_file(syntax, filename))
print(f"RDF graph serialized to \"{filename}\"")
print(f"Counted \"{len(rdf)}\" triples")

# clear up file
if os.path.isfile(filename):
    os.remove(filename)


# Note: printing the rdf object is the same as rdf.to_string("turtle")
