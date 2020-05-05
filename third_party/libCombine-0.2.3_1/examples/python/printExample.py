#!/usr/bin/env python
"""
Example prints contents of combine archive.
"""
from __future__ import print_function
import sys

from libcombine import *


def printMetaDataFor(archive, location):
    """ Prints metadata for given location.

    :param archive: CombineArchive instance
    :param location:
    :return:
    """
    desc = archive.getMetadataForLocation(location)
    if desc.isEmpty():
        print("  no metadata for '{0}'".format(location))
        return None

    print("  metadata for '{0}':".format(location))
    print("     Created : {0}".format(desc.getCreated().getDateAsString()))
    for i in range(desc.getNumModified()):
        print("     Modified : {0}".format(desc.getModified(i).getDateAsString()))

    print("     # Creators: {0}".format(desc.getNumCreators()))
    for i in range(desc.getNumCreators()):
        creator = desc.getCreator(i)
        print("       {0} {1}".format(creator.getGivenName(), creator.getFamilyName()))


def printArchive(fileName):
    """ Prints content of combine archive

    :param fileName: path of archive
    :return: None
    """
    archive = CombineArchive()
    if archive.initializeFromArchive(fileName) is None:
        print("Invalid Combine Archive")
        return None

    print('*'*80)
    print('Print archive:', fileName)
    print('*' * 80)
    printMetaDataFor(archive, ".")
    print("Num Entries: {0}".format(archive.getNumEntries()))

    for i in range(archive.getNumEntries()):
        entry = archive.getEntry(i)
        print(" {0}: location: {1} format: {2}".format(i, entry.getLocation(), entry.getFormat()))
        printMetaDataFor(archive, entry.getLocation())

        for j in range(entry.getNumCrossRefs()):
            print("  {0}: crossRef location {1}".format(j, entry.getCrossRef(j).getLocation()))

        # the entry could now be extracted via
        # archive.extractEntry(entry.getLocation(), <filename or folder>)

        # or used as string
        # content = archive.extractEntryToString(entry.getLocation());

    archive.cleanUp()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("usage: python printExample.py archive-file")
        sys.exit(1)
    printArchive(sys.argv[1])
