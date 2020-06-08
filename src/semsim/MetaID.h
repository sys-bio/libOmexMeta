//
// Created by Ciaran on 4/14/2020.
//

#ifndef LIBSEMSIM_METAID_H
#define LIBSEMSIM_METAID_H

#include <string>
#include "RedlandAPIWrapper.h"
#include <sstream>
#include <utility>
#include <iostream>

namespace semsim {
    /*
     * @brief an ID generator
     */
    class MetaID {
    private:
        std::string base_;
        long number_;
        int num_digits_;

    public:
        /*
         * @brief an ID generator used when creating IDs in the Editor.
         * @param base_ the constant portion of the id. Like semsim in semsim00001
         * @param number_ the number portion of the id, like 1 in semsim00001
         * @param num_digits specifies the number of digits to use in the id. So semsim00001 has 5 digits.
         *
         * Example
         * -------
         * MetaID metaid("ANewMetaID", 15, 3);
         * std::string id = metaid.generate();
         */
        MetaID(std::string base, long number, int num_digits = 4);

        bool operator==(const MetaID &rhs) const;

        bool operator!=(const MetaID &rhs) const;

        [[nodiscard]] std::string generate() const;

        [[nodiscard]] std::string generate(long n) const;

        [[nodiscard]] int maxNumber() const;

        static int countDigits(long n);
    };
}

#endif //LIBSEMSIM_METAID_H
