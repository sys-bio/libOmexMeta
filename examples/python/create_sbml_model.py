# in this file, we show a minimal example of constructing
# an SBML model containing composite annotations
# we want to describe "cytosolic glucose in a pancreatic beta cell"

import antimony

# load a simple SBML model with MIRIAM-style annotations
# for 'glucose' and the 'cytosol'
sb='''
// Created by libAntimony v2.11.0
model *beta_cell_model()

  // Compartments and Species:
  compartment cytosol;
  species glucose in cytosol;

  // Reactions:
  glucose_import:  => glucose; glucose_import_glucose_import_rate;

  // Species initializations:
  glucose = 0;
  glucose has molar_per_volume;

  // Compartment initializations:
  cytosol = 1;

  // Variable initializations:
  glucose_import_glucose_import_rate = 1;

  // Other declarations:
  const cytosol;

  // Unit definitions:
  unit molar = 1e1 mole / 1e1 litre;
  unit molar_per_volume = 1e1 mole / (1e1 litre * litre);

  // CV terms:
  cytosol identity "https://identifiers.org/GO:0005829"
  glucose identity "http://identifiers.org/CHEBI:17234"
end
'''

antimony.loadAntimonyString(sb)

sbml = antimony.getSBMLString('beta_cell_model')
# print the raw SBML content
print('**********************************************************')
print('SBML output:')
print('**********************************************************')
print(sbml)

# import the model into libSemSim
import semsim
from semsim import OPB, CL, PhysicalProperty, bqb

# importing the model into libSemSim will automatically
# add metaids for any annotatable SBML elements that lack them
importer = semsim.SBMLImporter(sbml)

model = importer.getSBMLModel()

# print the extracted annotations as RDF
print('**********************************************************')
print('RDF serialization of annotations:')
print('**********************************************************')

# the RDF always needs the location of the original SBML file
# (which is actually a URI)
# for COMBINE archives, this will be a relative path inside the archive
print(model.getRDF('./my-sbml-file.xml', 'turtle'))

# this isn't bad - the RDF already contains a composite annotation
# telling is that the species "glucose" is inside the "cytosol"
# we currently have "cytosolic glucose"
# however - what we want is "cytosolic glucose in a pancreatic beta cell"
# to describe this, we need to annotate the compartment (not the species!)
# and describe the cell type it is part of

# the compartment currently has a *singular annotation*, which can't
# represent membership in a "pancreatic beta cell", so we change this to
# a composite annotation
c = model.getComponentForId('cytosol')
c.setAnnotation(c.getAnnotation().makeComposite(PhysicalProperty(OPB.get(523))))

# now add a descriptor term specifying that the cytoplasm
#is part of a pancreatic beta cell (CL:0000169)
c.getCompositeAnnotation().addTerm(
    bqb.isPartOf.fget(), # the relation (the cytoplasm *is part of* ...)
    CL.get(169)   # the resource (pancreatic beta cell)
)

print('**********************************************************')
print('RDF serialization with cell type annotation:')
print('**********************************************************')

# the RDF always needs the location of the original SBML file
# (which is actually a URI)
# for COMBINE archives, this will be a relative path inside the archive
print(model.getRDF('./my-sbml-file.xml', 'turtle'))
