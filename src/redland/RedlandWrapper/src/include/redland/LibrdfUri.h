//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBOMEXMETA_LIBRDFURI_H
#define LIBOMEXMETA_LIBRDFURI_H


#include "LibrdfException.h"
#include "librdf.h"
#include "redland/RefCountedRedlandType.h"


namespace redland {

    /**
     * @brief std::function signature of  librdf_free_uri
     */
    using uri_free_func = std::function<void(librdf_uri *)>;

    /**
     * Instantiation of templated superclass
     */
    using RefCounted_librdf_uri = RefCountedRedlandType<librdf_uri, uri_free_func>;

    /**
     * @brief C++ wrapper around librdf_uri using RAII
     */
    class LibrdfUri : public RefCounted_librdf_uri {

    public:
        /**
         * @brief use constructors from superclass
         */
        using RefCounted_librdf_uri::RefCounted_librdf_uri;

        LibrdfUri() = default;

        /**
         * @brief instantiate a LibrdfUri from a librdf_uri pointer. The
         * pointer is stolen from librdf_uri and thereafter managed correctly
         * by LibrdfUri via RAII.
         */
        explicit LibrdfUri(librdf_uri* uri);
        /*
         * @brief create a LibrdfUri object from a filename string
         * @param filename string representing path on system.
         *
         * @details caller is responsible for freeing the uri. See LibrdfUri::freeUri().
         * The string "file://" is prepended onto any string that doesn't already have it
         * at the begining of the string. This indicates to librdf that its a path on system
         *
         * For developers: Note this function should really replace OmexMetaUtils::prepareBaseUri
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

        /**
         * @brief returns a librdf_uri pointer and increments the
         * usage count. The caller is responsible for calling
         * @see freeUri to decrement the librdf_uri* again.
         * @note when @see getUsage() is 1 the destructor
         * will take care of freeing memory associated with
         * librdf_uri object.
         */
//        [[nodiscard]] librdf_uri *get() const;

        /**
         * @brief get the underlying librdf_uri*
         * @details do not increment the shared pointer reference
         * counter.
         * @warning this method assumes you know what you are doing
         * with regards to the librdf reference counting system
         * @see LibrdfUri::get()
         */
//        [[nodiscard]] librdf_uri *getWithoutIncrement() const;

        [[nodiscard]] bool isEmpty() const;

//        void freeUri();


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

//        int getUsage() const  override;
//
//        /**
//         * @brief adds 1 to the usage count
//         * for underlying reference counter
//         * in librdf_uri*
//         */
//        void incrementUsage() const override;

//    private:
////        librdf_uri *uri_ = nullptr;
//
//        /*
//         * Hidden to make creating with raw ptr more explicit.
//         */
//        explicit LibrdfUri(librdf_uri *uri);
    };
}// namespace redland

#endif//LIBOMEXMETA_LIBRDFURI_H
