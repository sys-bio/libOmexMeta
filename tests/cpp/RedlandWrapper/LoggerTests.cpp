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

    ~LoggerTests() override {
        if (std::filesystem::exists(p)) {
            try {
                std::filesystem::remove(p);
            } catch (std::exception &e) {
                REDLAND_INFO(e.what());
            }
        }
        Logger().clear();
    }
};

TEST_F(LoggerTests, DefaultLevel) {
    auto actual = Logger().getLevel();
    auto expected = LogLevel::warn;
    ASSERT_EQ(expected, actual);
    Logger().clear();
}

TEST_F(LoggerTests, UseConsoleLoggerOutOfTheBox) {
    // should not output to console
    REDLAND_INFO("Not displayed to console");
    // should output to console
    REDLAND_WARN("Displayed to console");
    Logger().clear();
}

TEST_F(LoggerTests, SwitchToFileLogger) {
    std::filesystem::path fname = std::filesystem::current_path() / "log.log";
    Logger().fileLogger(fname);
    // should not output to console
    REDLAND_INFO("Not displayed to console");
    // should output to console
    REDLAND_WARN("Displayed to console");
    ASSERT_TRUE(std::filesystem::exists(fname));
    Logger().clear();
}

TEST_F(LoggerTests, UseFileLogger) {
    LibrdfStorage storage;
    LibrdfModel model(storage);
    Logger().setLevel(LogLevel::info);
    std::cout << p << std::endl;
    Logger().fileLogger(p);
    std::string sbml = SBMLFactory::getSBML(SBML_INVALID_METAIDS);
    redland::LibrdfParser parser("turtle");
    parser.parseString(sbml, model, "Nothing");
    ASSERT_TRUE(std::filesystem::exists(p));
    Logger().clear();
}


TEST_F(LoggerTests, UseFileLoggerReproduceIssue128) {
    // if file already exists remove
    if (std::filesystem::exists(p)) {
        std::filesystem::remove(p);
    }
    std::cout << p << std::endl;
    Logger().fileLogger(p);

    Logger().setLevel(LogLevel::info);
    ASSERT_TRUE(std::filesystem::exists(p));

    REDLAND_INFO("INFO");
    REDLAND_TRACE("TRACE");
    REDLAND_DEBUG("DEBUG");
    REDLAND_WARN("WARN");
    REDLAND_ERROR("ERROR");
    REDLAND_CRITICAL("CRITICAL");
    Logger().clear();
}


TEST_F(LoggerTests, CollectLogMessageSize) {
    LOGGER_SET_WARN();
    REDLAND_INFO("INFO");
    REDLAND_TRACE("TRACE");
    REDLAND_DEBUG("DEBUG");
    REDLAND_WARN("WARN");
    REDLAND_ERROR("ERROR");
    REDLAND_CRITICAL("CRITICAL");
    std::cout << "logger get level: " << Logger().getLevel() << std::endl;
    for (auto i : Logger().getMessages()) {
        std::cout << i << std::endl;
    }
    ASSERT_EQ(3, Logger().size());
    Logger().clear();
}

TEST_F(LoggerTests, GetLogMessage) {
    LOGGER_SET_INFO();
    REDLAND_INFO("INFO");
    std::string msg = Logger()[0].getMessage();
    ASSERT_STREQ("INFO", msg.c_str());
    Logger().clear();
}
