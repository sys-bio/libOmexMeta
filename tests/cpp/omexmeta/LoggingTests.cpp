//
// Created by Ciaran on 05/08/2021.
//

#include "SBMLFactory.h"
#include "omexmeta/OmexMeta.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include "gtest/gtest.h"

using namespace omexmeta;


class LoggingTests : public ::testing::Test {
public:
    LoggingTests() = default;
};

TEST_F(LoggingTests, DefaultLevel){
    auto actual = Logger::getLogger()->getLevel();
    auto expected = Logger::LogLevel::warn;
    ASSERT_EQ(expected, actual);
}

TEST_F(LoggingTests, UseConsoleLoggerOutOfTheBox){
    // needs to be called at least once, otherwise we'll
    // not have init the omexmeta logger, and we'll just
    // be using the spdlog defaults.
    Logger::getLogger();
    // should not output to console
    OMEX_INFO("Not displayed to console");
    // should output to console
    OMEX_WARN("Displayed to console");
}

TEST_F(LoggingTests, SwitchToFileLogger){
    std::filesystem::path fname = std::filesystem::current_path() / "log.log";
    Logger::getLogger()->fileLogger(fname);
    // should not output to console
    OMEX_INFO("Not displayed to console");
    // should output to console
    OMEX_WARN("Displayed to console");
    ASSERT_TRUE(std::filesystem::exists(fname));
}

TEST_F(LoggingTests, L) {

    // create color multi threaded logger
    auto console = spdlog::stdout_color_mt("console");
    auto err_logger = spdlog::stderr_color_mt("stderr");
    spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");


    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    spdlog::set_level(spdlog::level::debug);// Set global log level to debug
    spdlog::debug("This message should be displayed..");

    // change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    // Compile time log levels
    // define SPDLOG_ACTIVE_LEVEL to desired level
    SPDLOG_TRACE("Some trace message with param {}", 42);
    SPDLOG_DEBUG("Some debug message");


    std::string sbml = SBMLFactory::getSBML(SBML_INVALID_METAIDS);

    RDF rdf = RDF::fromString(sbml);

    //    std::cout << rdf.toString("turtle") << std::endl;
}




TEST_F(LoggingTests, T) {

    /**
     * Firstly I want a logger that works from
     * inside libOmexMeta and or redland wrapper.
     *
     * Need a console and a file logger, and a way to switch between them
     *
     */

    auto logger = Logger::getLogger();
    logger->setLevel(spdlog::level::info);

    Logger::getLogger()->critical("Warn me up scotty");

//    spdlog::info("Logging some info");
//
//    std::filesystem::path log = std::filesystem::current_path() / "logger.log";
//    std::cout << "log: " << log << std::endl;
//    auto logger = spdlog::basic_logger_mt("basic_logger", log.string());
//
//    spdlog::info("Logging some info to file");
//
//    logger->info("logging some infor to file: 24234");

//    spdlog::log(spdlog::level::info, "logger ksadnf;kajsdnf");
//    .info("logging to file 2");

//    Logger::setLogger("console", LEVEL);
//    Logger::setLogger("file", "filename", LEVEL);
//
//    Logger::useConsoleLogger(true);
//    Logger::useFileLogger(true)

//    std::string sbml = SBMLFactory::getSBML(SBML_INVALID_METAIDS);
//
//    RDF rdf = RDF::fromString(sbml);
}




























