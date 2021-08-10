//
// Created by Ciaran on 05/08/2021.
//

#ifndef LIBOMEXMETA_LOGGER_H
#define LIBOMEXMETA_LOGGER_H

#include "spdlog/spdlog.h"
#include <filesystem>
#include <string>
#include "raptor2.h"


namespace redland {
/**
 * wrapper macros around spdlog
 */
#define REDLAND_INFO(msg) SPDLOG_INFO(msg)
#define REDLAND_TRACE(msg) SPDLOG_TRACE(msg)
#define REDLAND_DEBUG(msg) SPDLOG_DEBUG(msg)
#define REDLAND_WARN(msg) SPDLOG_WARN(msg)
#define REDLAND_ERROR(msg) SPDLOG_ERROR(msg)
#define REDLAND_CRITICAL(msg) SPDLOG_CRITICAL(msg)


    /**
     * @brief Logging class for libOmexMeta. Implemented as a singleton
     */
    class Logger {
    public:
        using LoggerPtr = std::shared_ptr<spdlog::logger>;
        using LogLevel = spdlog::level::level_enum;
        // This is how clients can access the single instance
        static Logger *getLogger();

        /**
         * @brief formatter strings use the {fmt} library.
         * See documentation here: https://fmt.dev/latest/index.html
         */
        void setFormatter(const std::string &format);

        /**
         * @brief set the current logging level
         * @details possible values of level:
         *  - spdlog::level::critical;
         *  - spdlog::level::err;
         *  - spdlog::level::warn;
         *  - spdlog::level::debug;
         *  - spdlog::level::info;
         *  - spdlog::level::trace;
         *  - spdlog::level::off;
         */
        void setLevel(LogLevel level);

        /**
         * @brief returns the current logging level
         */
        LogLevel getLevel();

        /**
         * @brief enable the backtrace logging feature - display the last
         * @param num messages when spdlog::dump_backtrace is called.
         */
        void enableBacktrace(int num);

        /**
         * @brief disable the backtrace feature
         */
        void disableBacktrace();

        /**
         * @brief create and switch to a console logger
         */
        void consoleLogger();

        /**
         * @brief create and switch to a file logger
         */
        void fileLogger(const std::filesystem::path &filename);

        /**
         * @brief dump backtrace messages when called
         */
        void dumpBacktrace();

        /**
         * @brief log a info message to the currently
         * active logger
         */
        void info(const std::string &message);

        /**
         * @brief log a trace message to the currently
         * active logger
         */
        void trace(const std::string &message);

        /**
         * @brief log a debug message to the currently
         * active logger
         */
        void debug(const std::string &message);

        /**
         * @brief log a warning message to the currently
         * active logger
         */
        void warn(const std::string &message);

        /**
         * @brief log a error message to the currently
         * active logger
         */
        void error(const std::string &message);

        /**
         * @brief log a critical message to the currently
         * active logger
         */
        void critical(const std::string &message);


        /**
         * @brief reference to the currently active logger
         */
        LoggerPtr logger;

        /**
         * @brief indicator, true when the file logger is active
         */
        bool isFileLogger = false;

        /**
         * @brief indicator, true when the console logger is active
         */
        bool isConsoleLogger = false;


    private:
        /**
         * @brief constructor is private
         */
        Logger();

        /**
         * The one single instance of Logger
         */
        static Logger *inst_;// The one, single instance

        /**
         * @brief the filepath to be used for when
         * fileLogger is active
         */
        std::filesystem::path filepath_;

        /**
         * @brief store how many message to store during backtrace feature
         */
        int backtraceNum = 32;

        /**
         * @brief store the current formatter pattern
         */
        std::string formatterPattern = "[%H:%M:%S %z] %^ %l %g:%# %v %$";

        /**
          * @brief default logging level
          */
        LogLevel level_ = LogLevel::warn;

        /**
          * @brief indicator variable for backtracing
          */
        bool shouldBacktrace_ = false;


    };


}// namespace omexmeta

#endif//LIBOMEXMETA_LOGGER_H
