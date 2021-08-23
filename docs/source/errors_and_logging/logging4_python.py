# switching to the file logger
from os.path import join, exists, dirname, abspath
from os import remove, getcwd
from pyomexmeta import RDF, Logger

cellml = '''<?xml version=\"1.1\" encoding=\"UTF-8\"?>
            <model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">
              <component name=\"main\">
                <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />
                <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />
                <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />
              </component>
            </model>'''

logger_file = join(getcwd(), "log.log")
print(f"Logger file is: \"{logger_file}\"")

# if already exists, remove
if exists(logger_file):
    remove(logger_file)
assert not exists(logger_file)

# activate the file logger
Logger.file_logger(logger_file)
rdf = RDF.from_string(cellml, syntax="turtle")  # nothing is emitted to console

# ensure logging content has been written to disk
Logger.flush()

# now check logger_file
print(f"Reading logging data from \"{logger_file}\":")
with open(logger_file) as f:
    print(f.read())


# now activate the console logger again
Logger.console_logger()
print("Switching back to the console logger:")
rdf = RDF.from_string(cellml, syntax="turtle")  # and our log message is back
