from pyomexmeta import RDF

fname = "/path/to/annotation_file.rdf"

# Add to our RDF graph by reading the second string
rdf = RDF.from_file(fname, "rdfxml")
