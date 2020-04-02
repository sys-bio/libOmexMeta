# ifndef SEMSIM_OBJECT_H_
# define SEMSIM_OBJECT_H_

# include "definitions/SemSimTypes.h"
# include <string>

namespace semsim {
    /**
     * Class representing elements within a SemSim model
     *
     *
     */
    class SemSimObject {
    protected:
        std::string name;
        std::string description;
        std::string metadataID;
        SemSimTypes semsimtype;

    public:
        SemSimObject(SemSimTypes type);

        /**
         * Copy constructor
         * @param objtocopy The object to copy
         */
        // SemSimObject( SemSimObject& other);

        /** @return The object's free-text description */
         std::string &getDescription() ;

        /** @return The object's name */
         std::string &getName() ;

        /** @return Whether the object has an associated name*/
        bool hasName() ;

        /** @return Whether the object has an associated textual description */
        bool hasDescription() ;

        /** @return Whether the object has an associated metadata ID */
        bool hasMetadataID() ;

        /**
         * Set the object's name
         * @param name The name to apply
         */
        void setName( std::string &name);

        /**
         * Set the component's free-text description
         * @param description The free-text description
         */
        void setDescription( std::string &description);

        /**
         * Copy this object's description from another SemSimObject
         * @param other The object with the description we want to copy
         */
        void copyDescription( SemSimObject &other);

        /**
         * Set the component's metadata ID. These ID's are often used
         * by XML-based modeling languages such as SBML and CellML
         * to link XML elements to RDF statements that describe
         * the elements.
         *
         * @param metadataID The ID to apply
         */
        void setMetadataID( std::string &metadataID);

        /**
         * @return The component's metadata ID. These ID's are used
         * by XML-based modeling languages such as SBML and CellML
         * to link XML elements to RDF statements that describe
         * the elements.
         */
         std::string &getMetadataID() ;


        /** @return This object's SemSimType */
        // virtual SemSimTypes getSemSimType();

        /** @return This object's SemSim class URI */
        // virtual URI getSemSimClassURI();

        /**
         * @param type A specified SemSimType
         * @return Whether this object is a specified SemSimType
         */
        // virtual bool isType(SemSimTypes type);

    };


}

# endif
