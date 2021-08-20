# custom logging formatter
from pyomexmeta import RDF, Logger, eLogLevel

cellml = '''<?xml version=\"1.1\" encoding=\"UTF-8\"?>
            <model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">
              <component name=\"main\">
                <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />
                <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />
                <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />
              </component>
            </model>'''


# users can customize the formatting of the logger
# See https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
# for more information on the supported symbols and their meanings
Logger.set_formatter("%^ [%H-%M-%S] - %t - %P - %n - %l : %v %$")
rdf = RDF.from_string(cellml, syntax="rdfxml")
