from .pyomexmeta import PhysicalForce
from .pyomexmeta import PhysicalProcess
from .pyomexmeta import RDF, Editor, PhysicalEntity
from .pyomexmeta import SingularAnnotation
from .pyomexmeta import PersonalInformation
from .pyomexmeta_api import PyOmexMetaAPI, get_version
import os

__version__ = get_version()


def find_libomexmeta_c_api():
    CMAKE_SHARED_LIBRARY_PREFIX = ""
    CMAKE_SHARED_LIBRARY_SUFFIX = ""
    OMEXMETA_CAPI_FILENAME = f"{CMAKE_SHARED_LIBRARY_PREFIX}OmexMetaCAPI${CMAKE_SHARED_LIBRARY_SUFFIX}."
    # check current directory
    current_working_directory = os.getcwd()
