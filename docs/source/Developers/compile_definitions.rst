Compile Definitions
===================

libOmexMeta uses standard CMake generated export headers so though
familiar with CMake should find this straight forward. The default
visibility settings for visual studio are hidden while the default for
GCC is not to hide symbols. In libOmexMeta, this is rectified
by setting the default symbol visibility to hidden on all platforms. Then,
we have a set of CMake definitions that need some attention. For
full details of these definitions please see `the cmake documentation <https://cmake.org/cmake/help/v3.0/module/GenerateExportHeader.html>`_.

To compile any of the static targets in libomexmeta
you should have *_STATIC_DEFINE compile definition defined. For instance
when compiling the redland-combined-static target you need to have something
like this in your cmake script:

.. code-block:: cmake

    add_target(${target} STATIC ${target_sources})
    # assuming we have OmexMeta-static as an imported target
    target_link_libraries(${target} PRIVATE OmexMeta-static)
    target_compile_definitions(${target} PRIVATE REDLAND_STATIC_DEFINE)


OMEXMETA_STATIC_DEFINE is analogous for when linking OmexMeta-static.

When linking the SHARED library, no additional CMake definitions are needed.

When building SHARED libraries developers need to have
`*_EXPORT`. For instance, building libOmexMeta shared library
requires OmexMeta_EXPORTS defined.



















