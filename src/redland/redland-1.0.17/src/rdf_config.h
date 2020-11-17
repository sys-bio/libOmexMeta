#if defined(WIN32)
#include "win32_rdf_config.h"
#elif defined(__linux__)
#include "rdf_config_linux.h"
#elif defined(__APPLE__)
#include "rdf_config_mac.h"
#endif