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
    loader = unittest.TestLoader()
    start_dir = os.path.abspath(os.path.dirname(__file__))
    suite = loader.discover(start_dir)
    runner = unittest.TextTestRunner()
    runner.run(suite)
