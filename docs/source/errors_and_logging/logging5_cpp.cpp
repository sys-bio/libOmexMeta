#include "omexmeta/OmexMeta.h"

using namespace omexmeta;

int main(){

    Logger().setLevel(LogLevel::trace); // switch to trace log level;
    // you can also use the logger yourself, if needed;
    Logger().trace("trace message");
    Logger().info("info message");
    Logger().debug("debug message");
    Logger().warn("warn message");
    Logger().error("error message");
    Logger().critical("critical message");

    return 0;
}
