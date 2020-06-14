//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFURI_H
#define LIBSEMSIM_LIBRDFURI_H


#include <memory>
#include <librdf.h>
#include "LibrdfException.h"


namespace redland {

    class LibrdfUri {

        librdf_uri *uri_ = nullptr;

        /*
         * Hidden to make creating with raw ptr more explicit.
         */
        explicit LibrdfUri(librdf_uri *uri);

    public:
        LibrdfUri() = default;

        /*
         * @brief create a LibrdfUri object from a raw librdf_uri* pointer
         * @param uri pointer to a librdf_uri object. Created with librdf_new_* methods from librdf
         *
         * @details caller is responsible for freeing the uri. See LibrdfUri::freeUri().
         */
        static LibrdfUri fromRawPtr(librdf_uri *uri);

        /*
         * @brief create a LibrdfUri object from a filename string
         * @param filename string representing path on system.
         *
         * @details caller is responsible for freeing the uri. See LibrdfUri::freeUri().
         * The string "file://" is prepended onto any string that doesn't already have it
         * at the begining of the string. This indicates to librdf that its a path on system
         *
         * For developers: Note this function should really replace SemsimUtils::addFilePrefixToString
         */
        static LibrdfUri fromFilename(const std::string &filename);

        /*
         * @brief Create a new uri from an old uri by concatonating to the end.
         * @param old_name A librdf_uri* instance
         * @param local_name A string to concatonate onto the end of @param old_name
         *
         * @code
         * LibrdfUri uri = LibrdfUri("./local_filename");
         * LibrdfUri uri2 = LibrdfUri::concatonate(uri.get(), "new_uri");
         * std::cout << uri2.str() std::endl;
         * @endcode
         * Will output `./local_filenamenew_uri` to console.
         */
        static LibrdfUri concatonate(librdf_uri *old_name, const std::string &local_name);

        /*
         * @brief Create a new uri from an this LibrdfUri by concatonating to the end.
         * @param local_name A string to concatonate onto the end of @param old_name
         *
         * @code
         * LibrdfUri uri = LibrdfUri("./local_filename");
         * LibrdfUri uri2 = uri.concatonate("new_uri");
         * std::cout << uri2.str() std::endl;
         * @endcode
         * Will output `./local_filenamenew_uri` to console.
         *
         * For developers: could overload the "+" operator here for syntatic
         * sugar.
         */
        [[nodiscard]] LibrdfUri concatonate(const std::string &local_name) const;

        [[nodiscard]] std::string str() const;

        explicit LibrdfUri(const std::string &uri);

        [[nodiscard]] librdf_uri *get() const;

        [[nodiscard]] bool isNull() const;

        [[nodiscard]] bool isEmpty() const;

        void freeUri();


        /*
         * @brief checks whether uri contained in LirdfUri is a filename uri
         * @returns true is uri is a file type uri
         */
        [[nodiscard]] bool isFileUri() const;

        bool operator==(const LibrdfUri &rhs) const;

        bool operator!=(const LibrdfUri &rhs) const;

        /*
         * @brief creates a filename type uri from existing uri
         * @returns std::string containing the filename type uri.
         */
        [[nodiscard]] std::string toFilenameString() const;

        int getUsage();
    };
}

#endif //LIBSEMSIM_LIBRDFURI_H
