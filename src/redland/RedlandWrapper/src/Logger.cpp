//
// Created by Ciaran on 05/08/2021.
//

#include "redland/Logger.h"
#include "librdf.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <redland/LibrdfWorld.h>
#include <sstream>

namespace redland {


    Logger::Logger()
        : store(LoggerStore::getLoggerStore()) {
        consoleLogger();
    };



    void Logger::consoleLogger() {
        if (!spdlog::get("console")) {

            logger_ = spdlog::stdout_color_mt("console");

            // copy level of current logger
            logger_->set_level(level_);

            // copy backtrace statuc of current logger
            if (shouldBacktrace_) {
                logger_->enable_backtrace(backtraceNum);
            } else {
                logger_->disable_backtrace();
            }

            // and formatter
            logger_->set_pattern(formatterPattern);
        } else {
            logger_ = spdlog::get("console");
        }
        // assign this logger to the main logger
        spdlog::set_default_logger(logger_);
    }

    void Logger::fileLogger(const std::filesystem::path &filename) {
        if (!spdlog::get("file")) {
            filepath_ = filename;
            logger_ = spdlog::basic_logger_mt("file", filepath_.string());

            // copy level of current logger
            logger_->set_level(getLevel());

            // copy backtrace statuc of current logger
            if (shouldBacktrace_) {
                logger_->enable_backtrace(backtraceNum);
            } else {
                logger_->disable_backtrace();
            }

            // and formatter
            logger_->set_pattern(formatterPattern);
        } else {
            logger_ = spdlog::get("file");
        }
        spdlog::set_default_logger(logger_);
    }

    void Logger::setFormatter(const std::string &format) {
        formatterPattern = format;
        logger_->set_pattern(format);
    }

    void Logger::setLevel(LogLevel level) {
        Logger::level_ = level;
        logger_->set_level(Logger::level_);
    }

    LogLevel Logger::getLevel() {
        return logger_->level();
    }

    void Logger::enableBacktrace(int num) {
        shouldBacktrace_ = true;
        backtraceNum = num;
        logger_->enable_backtrace(backtraceNum);
    }

    void Logger::disableBacktrace() {
        shouldBacktrace_ = false;
        logger_->disable_backtrace();
    }
    void Logger::dumpBacktrace() {
        return logger_->dump_backtrace();
    }
    void Logger::info(const std::string &message) {
        store->addMessage(spdlog::level::level_enum::info, message);
        logger_->info(message);
    }

    void Logger::trace(const std::string &message) {
        store->addMessage(spdlog::level::level_enum::trace, message);
        logger_->trace(message);
    }

    void Logger::debug(const std::string &message) {
        store->addMessage(spdlog::level::level_enum::debug, message);
        logger_->debug(message);
    }

    void Logger::warn(const std::string &message) {
        store->addMessage(spdlog::level::level_enum::warn, message);
        logger_->warn(message);
    }

    void Logger::error(const std::string &message) {
        store->addMessage(spdlog::level::level_enum::err, message);
        logger_->error(message);
    }

    void Logger::critical(const std::string &message) {
        store->addMessage(spdlog::level::level_enum::critical, message);
        logger_->critical(message);
    }

    void Logger::clear() {
        store->clear();
    }

    Message &Logger::operator[](int idx) {
        return (*store)[idx];
    }

    unsigned long long Logger::size() {
        return store->size();
    }

    void Logger::addMessage(LogLevel level, const std::string &message) {
        store->addMessage(level, message);
    }

    std::vector<Message> Logger::getMessages() const {
        return store->getMessages();
    }

    void Logger::flush() {
        logger_->flush();
    }

    void Logger::flushOn(LogLevel level) {
        logger_->flush_on(level);
    }


}// namespace redland