#if defined(WIN32)
#include "win32_rasqal_config.h"
#elif defined(__linux__)
#include "rasqal_config_linux.h"
#elif defined(__APPLE__)
#include "rasqal_config_mac.h"
#endif