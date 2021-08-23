//
// Created by Ciaran on 05/08/2021.
//

#ifndef LIBOMEXMETA_LOGGER2_H
#define LIBOMEXMETA_LOGGER2_H

/**
 * @brief Enable logging macros to use trace and higher.
 * @details We must still use spdlog::set_level to switch
 * logging levels. Must be included before spdlog.
 * @see https://github.com/gabime/spdlog/issues/1318
 *
 */
#ifndef SPDLOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include "Message.h"
#include "librdf.h"
#include "raptor2.h"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <string>

namespace redland {
    /**
 * wrapper macros around spdlog
 */
    class Message;

    using LogLevel = spdlog::level::level_enum;

#define REDLAND_INFO(msg)                                         \
    if (LogLevel::info >= Logger::getLogger()->getLevel() ) {       \
            Logger::getLogger()->addMessage(LogLevel::info, msg); \
        }                                                         \
    SPDLOG_INFO(msg);

#define REDLAND_TRACE(msg)                                 \
    if (LogLevel::trace >= Logger::getLogger()->getLevel() ) {       \
            Logger::getLogger()->addMessage(LogLevel::trace, msg); \
        }                                                         \
    SPDLOG_TRACE(msg);

#define REDLAND_DEBUG(msg)                                 \
    if (LogLevel::debug >= Logger::getLogger()->getLevel() ) {       \
            Logger::getLogger()->addMessage(LogLevel::debug, msg); \
        }                                                         \
    SPDLOG_DEBUG(msg);

#define REDLAND_WARN(msg)                                 \
    if (LogLevel::warn >= Logger::getLogger()->getLevel() ) {       \
            Logger::getLogger()->addMessage(LogLevel::warn, msg); \
        }                                                         \
    SPDLOG_WARN(msg);

#define REDLAND_ERROR(msg)                               \
    if (LogLevel::err >= Logger::getLogger()->getLevel() ) {       \
            Logger::getLogger()->addMessage(LogLevel::err, msg); \
        }                                                         \
    SPDLOG_ERROR(msg);

#define REDLAND_CRITICAL(msg)                                 \
    if (LogLevel::critical >= Logger::getLogger()->getLevel() ) {       \
            Logger::getLogger()->addMessage(LogLevel::critical, msg); \
        }                                                         \
    SPDLOG_CRITICAL(msg);

    /**
     * @brief Logging class for libOmexMeta. Implemented as a singleton
     */
    class Logger {
    public:
        using LoggerPtr = std::shared_ptr<spdlog::logger>;
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

        /**
         * @brief remove the cache of stored logging messages.
         */
        void clear();

        /**
         * @brief get a specific logging message based on the numerical index.
         * @details The index is determined by when the message occured in the program
         * - i.e. the first message that appears is index 0, etc.
         * @note if the Logger is Logger::clear 'ed then indexing starts again at 0.
         */
        Message &operator[](int idx);

        /**
          * @brief returns the number of logging messages currently stored in the Logger.
          * @details this is reset to 0 when Logger::clear is called
          */
        int size();

        /**
         * @brief append a new message to the logger.
         */
        void addMessage(LogLevel level, const std::string &message);

        /**
         * @brief get the vector of messages logged so far.
         */
        std::vector<Message> getMessages() const;


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

        /**
         * @brief a place to store the error messages
         */
        std::vector<Message> messages_;
    };


// quickly set logging levels
#define LOGGER_SET_INFO() Logger::getLogger()->setLevel(LogLevel::info);
#define LOGGER_SET_TRACE() Logger::getLogger()->setLevel(LogLevel::trace);
#define LOGGER_SET_DEBUG() Logger::getLogger()->setLevel(LogLevel::debug);
#define LOGGER_SET_WARN() Logger::getLogger()->setLevel(LogLevel::warn);
#define LOGGER_SET_ERROR() Logger::getLogger()->setLevel(LogLevel::err);
#define LOGGER_SET_CRITICAL() Logger::getLogger()->setLevel(LogLevel::critical);

}// namespace redland

#endif//LIBOMEXMETA_LOGGER2_H
