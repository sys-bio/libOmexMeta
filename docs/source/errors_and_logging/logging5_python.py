# using the logger
from pyomexmeta import RDF, Logger, eLogLevel

Logger.set_level(eLogLevel.trace)  # switch to trace log level
Logger.trace("trace message")
Logger.info("info message")
Logger.debug("debug message")
Logger.warn("warn message")
Logger.error("error message")
Logger.critical("critical message")
