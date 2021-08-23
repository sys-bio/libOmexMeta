//
// Created by Ciaran on 23/08/2021.
//

#ifndef LIBOMEXMETA_REDLANDERROR_H
#define LIBOMEXMETA_REDLANDERROR_H

#include "Logger.h"
#include "spdlog/common.h"

namespace redland {

    class Logger;

    using LogLevel = spdlog::level::level_enum;

    /**
     * @brief container for Redland logging messages.
     */
    class Message {
    public:
        Message() = default;
        /**
         * @brief Constructor for Message takes a @param level
         * and a @param message.
         */
        Message(LogLevel level, std::string  message);

        friend std::ostream& operator<<(std::ostream& os, Message & message);

        /**
         * @brief getter for the level of this logger message
         */
        LogLevel getLevel() const;

        /**
         * @brief getter for the content string for this logger message
         */
        const std::string &getMessage() const;
        void setLevel(LogLevel level);
        void setMessage(const std::string &message);

    private:
        LogLevel level_;
        std::string message_;

    };

}// namespace redland

#endif//LIBOMEXMETA_REDLANDERROR_H
