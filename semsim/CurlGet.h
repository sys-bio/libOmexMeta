//
// Created by Ciaran on 4/11/2020.
//

#ifndef LIBSEMGEN_CURLGET_H
#define LIBSEMGEN_CURLGET_H


#include <string>
#include "curl/curl.h"

namespace semsim {

    class CurlGet {

    private:
        bool verbose_download_ = false;

        static size_t curlWriteCallback(void *data, size_t size, size_t nmemb, void *userp);

    public:
        explicit CurlGet(bool verbose_download = false) : verbose_download_(verbose_download){};

        static int download(const std::string& url, const std::string& output_filename);
    };
}


#endif //LIBSEMGEN_CURLGET_H
