from .pyomexmeta import (
    PersonalInformation,
    EnergyDiff,
    PhysicalProcess,
    _PropertyBearer,
    PhysicalProperty,
    RDF,
    Editor,
    PhysicalEntity,
    SingularAnnotation,
    OmexMetaException,
    Logger,
    Message
)
from .pyomexmeta_api import PyOmexMetaAPI, get_version, eUriType, eXmlType, eLogLevel

__version__ = get_version()


def run_tests():
    import os
    import unittest
    loader = unittest.TestLoader()
    start_dir = os.path.abspath(os.path.dirname(__file__))
    suite = loader.discover(start_dir)
    runner = unittest.TextTestRunner()
    runner.run(suite)
