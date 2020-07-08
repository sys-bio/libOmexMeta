//
// Created by Ciaran on 4/14/2020.
//

#ifndef LIBOMEXMETA_METAID_H
#define LIBOMEXMETA_METAID_H

#include <string>
#include "RedlandAPIWrapper.h"
#include <sstream>
#include <utility>
#include <iostream>

namespace omexmeta {
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

        /*
         * @brief generate the string for a metaid
         * @return a metaid defined by the parameters in instantiation
         */
        [[nodiscard]] std::string generate() const;

        /*
         * @brief generate the string for a metaid
         * @param number of digits
         * @return a metaid defined by the parameters in instantiation
         */
        [[nodiscard]] std::string generate(long n) const;

        /*
         * @brief figure out the max number possible with user parameters
         * @return the maximum possible number with user parameters
         */
        [[nodiscard]] int maxNumber() const;

        /*
         * @brief count the digits in a number
         * @param n the number to count digits in
         * @return the number of digits in n
         */
        static int countDigits(long long int n);
    };
}

#endif //LIBOMEXMETA_METAID_H
