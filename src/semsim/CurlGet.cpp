//
// Created by Ciaran on 4/11/2020.
//

#include <stdexcept>
#include <iostream>
#include <utility>
#include "CurlGet.h"
#include "semsim/SemSim.h"



size_t semsim::CurlGet::curlWriteCallback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t bytes_written = fwrite(data, size, nmemb, (FILE *) userp);
    return bytes_written;
}

int semsim::CurlGet::download(const std::string& url, const std::string& output_filename) {
    CURL *curl_handle;

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();
    if (!curl_handle) {
        throw std::logic_error("You no curl");
    }

    /* set URL to get here */
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());

    /* Switch on full protocol/debug output while testing */
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

    /* disable progress meter, set to 0L to enable it */
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 0L);

    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, CurlGet::curlWriteCallback);

    // Tell curl to automatically deal with encodings
    curl_easy_setopt(curl_handle, CURLOPT_ACCEPT_ENCODING, "");

    // follow redirects
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);

    /* open the file */
    FILE *f = fopen(output_filename.c_str(), "wb");
    if (!f) {
        throw std::invalid_argument("You no got file");
    }

    /* write the page body to this file handle */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, f);

    /* get it! */
    curl_easy_perform(curl_handle);

    /* close the header file */
    fclose(f);

    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);

    curl_global_cleanup();
    return 0;
}




