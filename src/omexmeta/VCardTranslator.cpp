//
// Created by Ciaran on 20/04/2021.
//

#include <omexmeta/VCardTranslator.h>
#include "redland/LibrdfModel.h"

using namespace redland;

namespace omexmeta {

    omexmeta::VCardTranslator::VCardTranslator(LibrdfModel &model)
        : model_(model){}

}