import os
import matplotlib.pyplot as plt
from pyomexmeta import RDF

# get the link to teusink2000
teusink_biomod_link = r"https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000064.2?filename=BIOMD0000000064_url.xml"

# download model xml, scan for rdf, create rdf graph and store in sqlite database
rdf = RDF.from_uri(teusink_biomod_link, format="rdfxml",
                   storage_type="sqlite", storage_name="TeusinkAnnotations2000",
                   storage_options="new='yes'")

# serialize to turtle
print(rdf)

# draw a diagram
fname = os.path.join(os.path.getcwd(), "TeusinkDiagram.png")
rdf.draw(fname)
plt.show()







