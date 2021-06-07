//
// Created by Ciaran Welsh on 04/06/2021.
//

#ifndef LIBOMEXMETA_OPTIONS_H
#define LIBOMEXMETA_OPTIONS_H

/**
 * @brief global options for libOmexMeta
 */
class Options {
public:
    Options() = default;

    /**
     * @brief when true, parsing rdf will remove rdf:Bag constructs
     */
    static bool removeRDFBag_;

    /**
     * @brief when true, VCARD constructs wil be replaced with FOAF counterparts
     */
    static bool translateVCard_;
};


#endif//LIBOMEXMETA_OPTIONS_H
