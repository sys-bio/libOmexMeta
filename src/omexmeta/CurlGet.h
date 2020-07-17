//
// Created by Ciaran on 4/11/2020.
//

#ifndef LIBOMEXMETA_CURLGET_H
#define LIBOMEXMETA_CURLGET_H


#include <string>
#include "curl/curl.h"
#include <stdexcept>

namespace omexmeta {

    /*
     * @brief Use libcurl to download from url
     */
    class CurlGet {

    private:
        /*
         * @brief callback used to write bytes to file
         */
        static size_t curlWriteCallback(void *data, size_t size, size_t nmemb, void *userp);

    public:
        CurlGet() = default;

        /*
         * @brief download a file from the internet
         * @param url The url to download.
         * @param output_filename. Where to put the downloaded content.
         * @return success code. Non-0 fails.
         */
        static int download(const std::string &url, const std::string &output_filename);
    };
}


#endif //LIBOMEXMETA_CURLGET_H
