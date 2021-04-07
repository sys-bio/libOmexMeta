from .pyomexmeta import PersonalInformation
from .pyomexmeta import EnergyDiff
from .pyomexmeta import PhysicalProcess
from .pyomexmeta import RDF, Editor, PhysicalEntity
from .pyomexmeta import SingularAnnotation
from .pyomexmeta import OmexMetaException
from .pyomexmeta_api import PyOmexMetaAPI, get_version, eUriType, eXmlType

__version__ = get_version()


def run_tests():
    import os
    import unittest
    test_modules = [
        "api_tests",
        "pyomexmeta_tests",
    ]

    for t in other_test_modules:
        unittest.main(module=t)


