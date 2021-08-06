from os.path import (join, exists, dirname,
                     abspath, isdir, isfile)
from os import remove
from pyomexmeta import RDF, Logger, eLogLevel

cellml = '''<?xml version=\"1.1\" encoding=\"UTF-8\"?>
            <model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">
              <component name=\"main\">
                <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />
                <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />
                <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />
              </component>
            </model>'''

# oops. Parsing this as turtle is an error since it is
# a rdfxml string. Librdf will complain by emiting errors
# to console.
print("first")
rdf = RDF.from_string(cellml, syntax="turtle") # See Python console
print("end first\n")

# changing the logging level to critical is one way to hide such messages
print("second")
Logger.set_level(eLogLevel.critical)
rdf = RDF.from_string(cellml, syntax="turtle") # See Python console - nothing is emitted
print("end second\n")

# changing the logging level to critical is one way to hide such messages
print("third")
Logger.set_level(eLogLevel.trace)
rdf = RDF.from_string(cellml, syntax="rdfxml") # See Python console - nothing is emitted
print(rdf)
print("end third\n")

# users can customize the formatting of the logger
# See https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
# for more information on the supported symbols and their meanings
print("fourth")
Logger.set_formatter("%^ [%H-%M-%S] - %t - %P - %n - %l : %v %$")
rdf = RDF.from_string(cellml, syntax="rdfxml")
print(rdf)
print("end fourth\n")

# Users can opt to switch to a file logger instead
# Formatters are remembered from the previous logger
print("fifth")
logger_file = join(abspath(dirname(__file__)), "log.log")
print("check logger_file: " , logger_file)
if exists(logger_file):
    remove(logger_file)
Logger.file_logger(logger_file)
rdf = RDF.from_string(cellml, syntax="turtle")
# now check logger_file
print("end fifth")

print("sixth")
Logger.set_level(eLogLevel.trace) # switch to trace log level
Logger.console_logger() # switch back to console logger
# you can also use the logger yourself, if needed
Logger.trace("trace message")
Logger.info("info message")
Logger.debug("debug message")
Logger.warn("warn message")
Logger.error("error message")
Logger.critical("critical message")
print("end sixth")







