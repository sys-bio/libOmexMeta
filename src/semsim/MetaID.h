//
// Created by Ciaran on 4/14/2020.
//

#ifndef LIBSEMSIM_METAID_H
#define LIBSEMSIM_METAID_H

#include <string>
#include "redland/RedlandAPIWrapper/RedlandAPIWrapper.h"
#include <sstream>
#include <utility>
#include <iostream>

namespace semsim {
    class MetaID {
    private:
        std::string base_;
        long number_;
        int num_digits_;

    public:
        MetaID(std::string base, long number, int num_digits = 4);

        bool operator==(const MetaID &rhs) const;

        bool operator!=(const MetaID &rhs) const;

        std::string generate() const;

        std::string generate(long n) const;

        int maxNumber() const;

        static int countDigits(long n);
    };
}

#endif //LIBSEMSIM_METAID_H
