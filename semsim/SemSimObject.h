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
        // SemSimObject(const SemSimObject& other);

        /** @return The object's free-text description */
        const std::string& getDescription() const;

        /** @return The object's name */
        const std::string& getName() const;

        /** @return Whether the object has an associated name*/
        bool hasName() const;

        /** @return Whether the object has an associated textual description */
        bool hasDescription() const;

        /** @return Whether the object has an associated metadata ID */
        bool hasMetadataID() const;

        /**
         * Set the object's name
         * @param name The name to apply
         */
        void setName(const std::string& name);

        /**
         * Set the component's free-text description
         * @param description The free-text description
         */
        void setDescription(const std::string& description);

        /**
         * Copy this object's description from another SemSimObject
         * @param other The object with the description we want to copy
         */
        void copyDescription(const SemSimObject& other);

        /**
         * Set the component's metadata ID. These ID's are often used
         * by XML-based modeling languages such as SBML and CellML
         * to link XML elements to RDF statements that describe
         * the elements.
         *
         * @param metadataID The ID to apply
         */
        void setMetadataID(const std::string& metadataID);

        /**
         * @return The component's metadata ID. These ID's are used
         * by XML-based modeling languages such as SBML and CellML
         * to link XML elements to RDF statements that describe
         * the elements.
         */
        const std::string& getMetadataID() const;


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
