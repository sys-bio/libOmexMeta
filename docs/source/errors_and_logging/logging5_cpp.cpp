#include "omexmeta/OmexMeta.h"

using namespace omexmeta;

int main(){

    Logger::getLogger()->setLevel(Logger::LogLevel::trace); // switch to trace log level;
    // you can also use the logger yourself, if needed;
    Logger::getLogger()->trace("trace message");
    Logger::getLogger()->info("info message");
    Logger::getLogger()->debug("debug message");
    Logger::getLogger()->warn("warn message");
    Logger::getLogger()->error("error message");
    Logger::getLogger()->critical("critical message");

    return 0;
}
