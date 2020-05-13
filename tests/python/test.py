import os
import site
import unittest

test_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
proj_dir = os.path.dirname(test_dir)
src_dir = os.path.join(proj_dir, "src")
pysemsem_dir = os.path.join(src_dir, "pysemsim")

site.addsitedir(src_dir)

import pysemsim


class Test(unittest.TestCase):
    rdf_str = """<?xml version="1.0" encoding="utf-8"?>
    <rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
       xmlns:bqmodel="http://biomodels.net/model-qualifiers/"
       xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
       xmlns:semsim="http://www.bhi.washington.edu/semsim#"
       xml:base="file://./annotations.rdf">
      <rdf:Description rdf:about="force_0">
        <semsim:hasSinkParticipant rdf:resource="sink_0"/>
        <semsim:hasSourceParticipant rdf:resource="source_0"/>
      </rdf:Description>
      <rdf:Description rdf:about="parameter_metaid_0">
        <bqbiol:isPropertyOf rdf:resource="force_0"/>
        <bqbiol:isVersionOf rdf:resource="https://identifiers.org/opb/OPB_01058"/>
      </rdf:Description>
      <rdf:Description rdf:about="sink_0">
        <semsim:hasPhysicalEntityReference rdf:resource="species_metaid_1"/>
      </rdf:Description>
      <rdf:Description rdf:about="source_0">
        <semsim:hasPhysicalEntityReference rdf:resource="species_metaid_0"/>
      </rdf:Description>
    </rdf:RDF>"""

    def test_crete_new_rdf_obj(self):
        rdf = pysemsim.RDF()
        self.assertIsInstance(rdf._obj, int)

    def test_from_string(self):
        rdf = pysemsim.RDF.from_string(self.rdf_str, "rdfxml")
        self.assertEqual(6, len(rdf))

    def test_to_string(self):
        rdf = pysemsim.RDF.from_string(self.rdf_str, "rdfxml")
        rdf.to_string()

    def test_get_base_uri(self):
        rdf = pysemsim.RDF.from_string(self.rdf_str, "rdfxml")
        uri = rdf.get_base_uri()
        print("1", uri)
        rdf.set_base_uri("uri")
        uri = rdf.get_base_uri()
        print("2", uri)

    def test_query(self):
        rdf = pysemsim.RDF.from_string(self.rdf_str, "rdfxml")
        q = """SELECT ?x ?y ?z 
        WHERE {?x ?y ?z}
        """
        expected = """x,y,z
file://./force_0,http://www.bhi.washington.edu/semsim#hasSinkParticipant,file://./sink_0
file://./force_0,http://www.bhi.washington.edu/semsim#hasSourceParticipant,file://./source_0
file://./parameter_metaid_0,http://biomodels.net/biology-qualifiers/isPropertyOf,file://./force_0
file://./parameter_metaid_0,http://biomodels.net/biology-qualifiers/isVersionOf,https://identifiers.org/opb/OPB_01058
file://./sink_0,http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference,file://./species_metaid_1
file://./source_0,http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference,file://./species_metaid_0
"""
        self.maxDiff = None
        actual = rdf.query(q, "csv")
        self.assertEqual(expected, actual)


if __name__ == "__main__":
    unittest.main()
