#!/usr/bin/env python
"""
Create example archive.
"""
from __future__ import print_function
import sys

from libcombine import *


def createArchiveExample(fileName):
    """ Creates Combine Archive containing the given file.

    :param fileName: file to include in the archive
    :return: None
    """
    print('*' * 80)
    print('Create archive')
    print('*' * 80)

    archive = CombineArchive()
    archive.addFile(
        fileName,  # filename
        "./models/model.xml",  # target file name
        KnownFormats.lookupFormat("sbml"),  # look up identifier for SBML models
        True  # mark file as master
    )

    # add metadata to the archive itself
    description = OmexDescription()
    description.setAbout(".")
    description.setDescription("Simple test archive including one SBML model")
    description.setCreated(OmexDescription.getCurrentDateAndTime())

    creator = VCard()
    creator.setFamilyName("Bergmann")
    creator.setGivenName("Frank")
    creator.setEmail("fbergman@caltech.edu")
    creator.setOrganization("Caltech")

    description.addCreator(creator)

    archive.addMetadata(".", description)

    # add metadata to the added file
    location = "./models/model.xml"
    description = OmexDescription()
    description.setAbout(location)
    description.setDescription("SBML model")
    description.setCreated(OmexDescription.getCurrentDateAndTime())
    archive.addMetadata(location, description)

    # write the archive
    out_file = "out.omex"
    archive.writeToFile(out_file)

    print('Archive created:', out_file)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("usage: python createArchiveExample.py sbml-file")
        sys.exit(1)
    createArchiveExample(sys.argv[1])
