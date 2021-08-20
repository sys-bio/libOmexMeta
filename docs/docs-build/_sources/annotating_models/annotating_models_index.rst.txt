==================
Annotating Models
==================

Annotating a biological complex
================================

A biological complex is a functional unit composed of multiple parts. To annotate that you are modelling
a complex you can neglect the `identity` and instead use an arbitrary number of `hasPart` predicates. In this example
we model the binding of `Sos`, `Grb2` and `Shc`.

.. note::

    You can create this model using the following `tellurium` code:

.. code-block:: python

    import tellurium as te

    r = te.loada("""
        model ComplexBinding
           compartment cytoplasm = 1;

           Shc in cytoplasm;
           Sos in cytoplasm;
           Grb2 in cytoplasm;
           Shc = 1;
           Sos = 1;
           Grb2 = 1;
           Shc_Sos_Grb2 = 0;
           k_bind = 0.1;
           k_unbind = 0.1;
           Binding: Shc + Sos + Grb2 => Shc_Sos_Grb2; cytoplasm*k_bind*Shc*Sos*Grb2;
           Unbinding: Shc_Sos_Grb2 => Shc + Sos + Grb2; cytoplasm*k_unbind*Shc_Sos_Grb2;
        end
        """
    )
    sbml = r.getSBML()
    print(sbml)


.. tabs::

    .. tab:: python

        .. literalinclude:: annotating_a_biological_complex_python.py
            :language: python
            :caption: Annotating a biological complex in Python

        .. literalinclude:: ../../ExampleOutputFiles/annotating_a_biological_complex_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: annotating_a_biological_complex_cpp.cpp
            :language: C++
            :caption: Annotating a biological complex in C++

        .. literalinclude:: ../../ExampleOutputFiles/AnnotatingABiologicalComplexCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: annotating_a_biological_complex_c.cpp
            :language: C
            :caption: Annotating a biological complex in C

        Output:

        .. literalinclude:: ../../ExampleOutputFiles/AnnotatingABiologicalComplexC.txt
            :caption: Output















