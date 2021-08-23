//
// Created by Ciaran on 23/08/2021.
//

#include "redland/Message.h"

#include <utility>

namespace redland {

    Message::Message(LogLevel level, std::string message)
        : level_(level), message_(std::move(message)){};

    std::ostream &operator<<(std::ostream &os, Message &message) {
        os << message.level_ << ": " << message.message_;
        return os;
    }
    LogLevel Message::getLevel() const {
        return level_;
    }

    const std::string &Message::getMessage() const {
        return message_;
    }
    void Message::setLevel(LogLevel level) {
        level_ = level;
    }
    void Message::setMessage(const std::string &message) {
        message_ = message;
    }


}// namespace redland
