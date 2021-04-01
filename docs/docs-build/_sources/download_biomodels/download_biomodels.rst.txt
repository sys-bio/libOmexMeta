Downloading Biomodels
=======================

It is often useful to have access to the entire biomodels database locally, though it isn't necessarily obvious how best to
download them. Here, we provide a script that makes use to `bioservices.BioModels` for downloading sbml models
from the curated section.

.. note::

    This example does not use libOmexMeta and so arguably has no place in this documentation. However, this is a common
    task and can therefore be useful to our users.

.. note::

    This script downloads sbml files only. Biomodels hosts a number of other files associated with individual models.
    It is likely that these could also be downloaded using a similar strategy, but we do not do that here.

.. literalinclude:: download_biomodels.py
    :linenos:
    :language: python
    :caption: Download the curated section of biomodels




















