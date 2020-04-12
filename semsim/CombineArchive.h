//
// Created by Ciaran on 4/11/2020.
//

#ifndef LIBSEMGEN_COMBINEARCHIVE_H
#define LIBSEMGEN_COMBINEARCHIVE_H


#include <string>

class CombineArchive {
private:
    std::string file_or_uri_;

    bool isfile();

    bool isurl();

    void fromUrl();

    void fromFile();

public:

    CombineArchive(std::string file_or_uri);


};


#endif //LIBSEMGEN_COMBINEARCHIVE_H
