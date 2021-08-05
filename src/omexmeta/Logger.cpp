//
// Created by Ciaran on 05/08/2021.
//

#include "omexmeta/Logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace omexmeta {

    Logger::Logger() {
        consoleLogger();
        setFormatter(formatterPattern);
        setLevel(level_);
        enableBacktrace(backtraceNum);
    };

    // Define the static Logger pointer
    Logger *Logger::inst_ = nullptr;

    Logger *Logger::getLogger() {
        if (inst_ == nullptr) {
            inst_ = new Logger();
        }
        return (inst_);
    }

    void Logger::consoleLogger() {
        isConsoleLogger = true;
        isFileLogger = false;
        LoggerPtr console = spdlog::stdout_color_mt("console");

        // copy level of current logger
        console->set_level(level_);

        // copy backtrace statuc of current logger
        if (shouldBacktrace_) {
            console->enable_backtrace(backtraceNum);
        } else {
            console->disable_backtrace();
        }

        // and formatter
        console->set_pattern(formatterPattern);

        // assign this logger to the main logger
        logger = spdlog::get("console");
        spdlog::set_default_logger(logger);
    }

    void Logger::fileLogger(const std::filesystem::path &filename) {
        isConsoleLogger = false;
        isFileLogger = true;

        filepath_ = filename;
        LoggerPtr fileLogger = spdlog::basic_logger_mt("fileLogger", filepath_.string());

        // copy level of current logger
        fileLogger->set_level(getLevel());

        // copy backtrace statuc of current logger
        if (shouldBacktrace_) {
            fileLogger->enable_backtrace(backtraceNum);
        } else {
            fileLogger->disable_backtrace();
        }

        // and formatter
        fileLogger->set_pattern(formatterPattern);

        logger = spdlog::get("fileLogger");
        spdlog::set_default_logger(logger);
    }

    void Logger::setFormatter(const std::string &format) {
        logger->set_pattern(format);
    }

    void Logger::setLevel(Logger::LogLevel level) {
        Logger::level_ = level;
        logger->set_level(Logger::level_);
    }

    Logger::LogLevel Logger::getLevel() {
        return logger->level();
    }

    void Logger::enableBacktrace(int num) {
        shouldBacktrace_ = true;
        backtraceNum = num;
        logger->enable_backtrace(backtraceNum);
    }

    void Logger::disableBacktrace() {
        shouldBacktrace_ = false;
        logger->disable_backtrace();
    }

    void Logger::info(const std::string &message) {
        logger->info(message);
    }

    void Logger::trace(const std::string &message) {
        logger->trace(message);
    }

    void Logger::debug(const std::string &message) {
        logger->debug(message);
    }

    void Logger::warn(const std::string &message) {
        logger->warn(message);
    }

    void Logger::error(const std::string &message) {
        logger->error(message);
    }

    void Logger::critical(const std::string &message) {
        logger->critical(message);
    }

}// namespace omexmeta