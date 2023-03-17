//
// Created by Ciaran on 05/08/2021.
//

#include "redland/LoggerStore.h"
#include "librdf.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <redland/LibrdfWorld.h>
#include <sstream>

namespace redland {

    // Define the static LoggerStore pointer
    LoggerStore *LoggerStore::inst_ = nullptr;

    LoggerStore *LoggerStore::getLoggerStore() {
        if (inst_ == nullptr) {
            inst_ = new LoggerStore();
        }
        return inst_;
    }

    void LoggerStore::clear() {
        messages_.clear();
    }

    Message &LoggerStore::operator[](int idx) {
        return messages_[idx];
    }

    unsigned long long LoggerStore::size() {
        return messages_.size();
    }

    void LoggerStore::addMessage(LogLevel level, const std::string &message) {
        messages_.emplace_back(level, message);
    }

    std::vector<Message> LoggerStore::getMessages() const {
        return messages_;
    }


}// namespace redland