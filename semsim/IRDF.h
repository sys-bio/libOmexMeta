//
// Created by Ciaran on 4/5/2020.
//

#ifndef LIBSEMGEN_IRDF_H
#define LIBSEMGEN_IRDF_H

#include <string>

class IRDF {
public:

    virtual std::string serialize(std::string format) = 0;
};

#endif //LIBSEMGEN_IRDF_H
