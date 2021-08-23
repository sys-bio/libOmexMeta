# Information, warnings and errors are logged to console by default
from pyomexmeta import RDF, Logger, Message

cellml = '''<?xml version=\"1.1\" encoding=\"UTF-8\"?>
            <model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">
              <component name=\"main\">
                <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />
                <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />
                <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />
              </component>
            </model>'''

# oops - did a whoops. Parsing rdfxml as turtle
rdf = RDF.from_string(cellml, syntax="turtle")  # See Python console for logging message

assert len(Logger()) == 1

# get the message as a object
message = Logger()[0]

# print as string
print(message)

# or collect the message content / level as objects
message_string  = message.get_message()
message_level = message.get_level()

print("message_string: ", message_string)
print("message_level: ", message_level)

# now clear the logger
Logger.clear()

assert len(Logger()) == 0

