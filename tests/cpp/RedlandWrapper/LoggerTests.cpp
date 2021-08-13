//
// Created by Ciaran on 05/08/2021.
//
#include "cpp/omexmeta/SBMLFactory.h"
#include "redland/Logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "gtest/gtest.h"
#include <redland/LibrdfParser.h>

using namespace redland;


class LoggerTests : public ::testing::Test {
public:
    std::filesystem::path p = std::filesystem::current_path() / "log.log";
    LoggerTests() = default;

    ~LoggerTests() override{
        if (std::filesystem::exists(p)){
            try {
                std::filesystem::remove(p);
            } catch (std::exception& e){
                REDLAND_INFO(e.what());
            }
        }
    }
};

TEST_F(LoggerTests, DefaultLevel){
    auto actual = Logger::getLogger()->getLevel();
    auto expected = Logger::LogLevel::warn;
    ASSERT_EQ(expected, actual);
}

TEST_F(LoggerTests, UseConsoleLoggerOutOfTheBox){
    // needs to be called at least once, otherwise we'll
    // not have init the omexmeta logger, and we'll just
    // be using the spdlog defaults.
    Logger::getLogger();
    // should not output to console
    REDLAND_INFO("Not displayed to console");
    // should output to console
    REDLAND_WARN("Displayed to console");
}

TEST_F(LoggerTests, SwitchToFileLogger){
    std::filesystem::path fname = std::filesystem::current_path() / "log.log";
    Logger::getLogger()->fileLogger(fname);
    // should not output to console
    REDLAND_INFO("Not displayed to console");
    // should output to console
    REDLAND_WARN("Displayed to console");
    ASSERT_TRUE(std::filesystem::exists(fname));
}

TEST_F(LoggerTests, UseFileLogger) {
    LibrdfStorage storage;
    LibrdfModel model(storage);
    Logger::getLogger()->setLevel(Logger::LogLevel::info);
    std::cout<< p << std::endl;
    Logger::getLogger()->fileLogger(p);
    std::string sbml = SBMLFactory::getSBML(SBML_INVALID_METAIDS);
    redland::LibrdfParser parser("turtle");
    parser.parseString(sbml, model, "Nothing");
    ASSERT_TRUE(std::filesystem::exists(p));
}























