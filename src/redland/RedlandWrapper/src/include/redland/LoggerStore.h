//
// Created by Ciaran on 05/08/2021.
//

#ifndef LIBOMEXMETA_LOGGERSTORE_H
#define LIBOMEXMETA_LOGGERSTORE_H



#include "Message.h"
#include "librdf.h"
#include "raptor2.h"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <string>

namespace redland {

    using LogLevel = spdlog::level::level_enum;

    class Message;
    class Logger;

    /**
     * @brief Logging class for libOmexMeta. Implemented as a singleton
     */
    class LoggerStore {
    public:
        // This is how clients can access the single instance
        static LoggerStore *getLoggerStore();

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
        unsigned long long size();

        /**
         * @brief append a new message to the logger.
         */
        void addMessage(LogLevel level, const std::string &message);

        /**
         * @brief get the vector of messages logged so far.
         */
        [[nodiscard]] std::vector<Message> getMessages() const;
        
    private:

        static LoggerStore* inst_ ;

        /**
         * @brief constructor is private
         */
        LoggerStore() = default;

        /**
         * @brief a place to store the error messages
         */
        std::vector<Message> messages_;
    };



}// namespace redland

#endif  //LIBOMEXMETA_LOGGERSTORE_H
