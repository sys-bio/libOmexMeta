# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
from os.path import dirname, join, isdir, isfile
import sys

docs_source = dirname(__file__)
docs_root = dirname(docs_source)
libomexmeta_root = dirname(docs_root)
libomexmeta_source = join(libomexmeta_root, "src")

sys.path += ["D:/libOmexMeta/cmake-build-release/site-packages"]


# -- Project information -----------------------------------------------------

project = 'libomexmeta'
copyright = '2020, Ciaran Welsh'
author = 'Ciaran Welsh'

# The full version, including alpha/beta/rc tags
release = '1.2.10'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "breathe", # links to doxygen generated docs.
    # "exhale",
    # 'sphinx.ext.pngmath',
    'sphinx.ext.todo',  #provides the todo box
    "sphinxcontrib.bibtex", # references
    "sphinx_tabs.tabs", # provides the tab construct
    "sphinx.ext.doctest", # not used.
    "sphinx.ext.autodoc",  # semi auto python docs
    "sphinx.ext.napoleon" # enable google/numpy style docs
]

bibtex_bibfiles = [os.path.join(os.path.dirname(__file__), 'refs.bib')]

breathe_default_project = "libomexmeta"
breathe_projects = {
    "libomexmeta": r"D:/libOmexMeta/docs/doxygen-output/xml"
}


# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']
