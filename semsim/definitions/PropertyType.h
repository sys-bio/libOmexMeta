# ifndef SEMSIM_PROPERTY_TYPE_H_
# define SEMSIM_PROPERTY_TYPE_H_

# include <string>
# include <vector>

namespace semsim {
    /**
     * Enumeration of the main types of physical properties
     * represented in biosimulation models. These correspond to the main
     * classes of physical properties in the Ontology of Physics for Biology.
     *
     * - Properties of physical entities ("State properties"). Examples: The chemical
     * concentration of a molecular species, the fluid volume of a portion of blood.
     *
     * - Properties of physical processes ("Rate properties"). Examples: The rate of
     * the phosphofructokinase reaction, the rate of blood flow through an artery.
     *
     * * - Properties of physical forces ("Force properties"). Examples: Electrical
     * potential across a cell membrane, fluid pressure in an artery.
     *
     * - Properties of physical dependencies ("Constitutive properties"). Examples:
     * A first order reaction rate constant used to determine a reaction rate,
     *  the fluid resistance term in an instance of Ohm's Law for fluids.
     */
    class PropertyType {
      public:
        static PropertyType PropertyOfPhysicalEntity;
        static PropertyType PropertyOfPhysicalProcess;
        static PropertyType PropertyOfPhysicalForce;
        static PropertyType Unknown;

      private:
        // static std::vector<PropertyType> valueList;

        // class StaticConstructor {
        //   public:
        //     StaticConstructor();
        // };
        //
        // static StaticConstructor staticConstructor;

      public:
        // enum InnerEnum {
        //     PropertyOfPhysicalEntity,
        //     PropertyOfPhysicalProcess,
        //     PropertyOfPhysicalForce,
        //     Unknown
        // };

        // const InnerEnum innerEnumValue;
      private:
        const std::string nameValue;
        // const int ordinalValue;
        // static int nextOrdinal;

      protected:
        // String representation of enum
        const std::string desc_;

        // PropertyType(const std::string& name, InnerEnum innerEnum, const std::string& name);

      public:
        /**
         * Returns the name of the property type as a string.
         */
        // const std::string& ToString();

      public:
        // bool operator == (const PropertyType& other);

        // bool operator != (const PropertyType& other);

        // static std::vector<PropertyType> values();

        // int ordinal();

        // static PropertyType valueOf(const std::string& name);
    };
}

# endif
