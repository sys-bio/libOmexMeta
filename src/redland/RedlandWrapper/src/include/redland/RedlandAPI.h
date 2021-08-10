//
// Created by Ciaran on 5/19/2020.
//

#ifndef LIBOMEXMETA_REDLANDWRAPPER_H
#define LIBOMEXMETA_REDLANDWRAPPER_H


#include "RedlandType.h"
#include "RefCountedRedlandType.h"
#include "LibrdfModel.h"
#include "LibrdfNode.h"
#include "LibrdfParser.h"
#include "LibrdfQuery.h"
#include "LibrdfQueryResults.h"
#include "LibrdfSerializer.h"
#include "LibrdfStorage.h"
#include "LibrdfStream.h"
#include "LibrdfUri.h"
#include "LibrdfWorld.h"
#include "RaptorIOStream.h"
#include "Logger.h"

/**
 * @brief Call to getLogger is mainly to initialize the logging system, which
 * doesn't actually hook into the redland libraries until its called for the first time.
 * The logger is a singleton, and therefore persists throughout the lifetime of the
 * program.
 */
redland::Logger* logger = redland::Logger::getLogger();


#endif//LIBOMEXMETA_REDLANDAPI_H
