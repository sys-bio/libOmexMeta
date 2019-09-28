from semsim import importSBMLFromFile
from sys import argv

model = importSBMLFromFile(argv[1])

print("**********************************************************")
print("RDF annotations")
print("**********************************************************")

# print(model.getRDF("./mymodel.xml", "turtle"))

print(model.getComponentForId(argv[2]).getRDF("./mymodel.xml", "turtle"))
