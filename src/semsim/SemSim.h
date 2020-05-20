//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMSIM_SEMSIM_H
#define LIBSEMSIM_SEMSIM_H

#define HERE()                              \
do {                                        \
  std::cout << __FILE__ << ":" << __LINE__ << std::endl; \
} while (0)

// these will be included in the finished product
#include "RDF.h"
#include "CurlGet.h"
#include "SemsimUtils.h"
#include "MetaID.h"
#include "XmlAssistant.h"
#include "Editor.h"

// these may be included in the finished product
#include "Subject.h"
#include "Resource.h"
#include "Predicate.h"
#include "Predicate.h"
#include "SemsimCombineArchive.h"

#endif //LIBSEMSIM_SEMSIM_H
