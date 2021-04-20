//
// Created by Ciaran on 20/04/2021.
//

#ifndef LIBOMEXMETA_VCARDTRANSLATOR_H
#define LIBOMEXMETA_VCARDTRANSLATOR_H

namespace omexmeta {

    class VCardTranslator {

    public:

        VCardTranslator(LibrdfModel& model);

    private:
        LibrdfModel& model_;
    };





}// namespace omexmeta


#endif//LIBOMEXMETA_VCARDTRANSLATOR_H
