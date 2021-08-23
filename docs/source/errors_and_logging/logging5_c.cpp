// using the logger
#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

int main(){

    Logger_setLevel(LogLevel::trace); // switch to trace log level;
    // you can also use the logger yourself, if needed;
    Logger_trace("trace message");
    Logger_info("info message");
    Logger_debug("debug message");
    Logger_warn("warn message");
    Logger_error("error message");
    Logger_critical("critical message");

    return 0;
}
