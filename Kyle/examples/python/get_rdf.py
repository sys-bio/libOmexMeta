from sys import argv

from semsim import importSBMLFromFile

model = importSBMLFromFile(argv[1])

print("**********************************************************")
print("RDF annotations")
print("**********************************************************")

# print(model.getRDF("./mymodel.xml", "turtle"))

print(model.getComponentForId(argv[2]).getRDF("./mymodel.xml", "turtle"))
