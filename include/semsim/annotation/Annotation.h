#include <string>
#include <any>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace semsim { namespace annotation { class Relation; } }

namespace semsim
{
	namespace annotation
	{

		using namespace org::apache::commons::lang3::builder;


		/**
		 * A SemSim annotation provides additional information about
		 * a SemSim model or one of its elements. Annotations can be used
		 * to define the physical meaning of a SemSim model or model element, 
		 * identify model authors, link a model to its PubMed ID, etc.
		 */
		class Annotation
		{

		protected:
			std::wstring valueDescription;
			Relation *relation;
			std::any value;


			/**
			 * Constructor without a free-text description of the annotation.
			 * @param relation Indicates the relationship between the object being annotated
			 * and the annotation value
			 * @param value The annotation value
			 */
		public:
			virtual ~Annotation()
			{
				delete relation;
			}

			Annotation(Relation *relation, std::any value);

			/**
			 * Constructor that includes a free-text description of the annotation.
			 * @param relation Indicates the relationship between the object being annotated
			 * and the annotation value
			 * @param value The annotation value
			 * @param valueDescription A free-text description of the annotation value
			 */
			Annotation(Relation *relation, std::any value, const std::wstring &valueDescription);
			/**
			 * Constructor for copying an Annotation
			 * @param tocopy The Annotation to copy
			 */
			Annotation(const Annotation &tocopy);

			/**
			 * Set the free-text description for the annotation value
			 * @param valueDescription The free-text description
			 */
			virtual void setValueDescription(const std::wstring &valueDescription);

			/**
			 * @return The free-text description of the annotation value
			 */
			virtual std::wstring getValueDescription();

			/**
			 * Set the relationship between the object being annotated and the annotation value
			 * @param relation The relation (AKA predicate, qualifier) between the object being annotated and the annotation value
			 */
			virtual void setRelation(Relation *relation);

			/** @return The relationship between the object being annotated and the annotation value */
			virtual Relation *getRelation();

			/**
			 * Set the annotation value
			 * @param value The annotation value
			 */
			virtual void setValue(std::any value);

			/**
			 * @return The annotation value
			 */
			virtual std::any getValue();

			/**
			 * Create a copy of the annotation
			 */
			virtual Annotation *clone() throw(CloneNotSupportedException);

			int hashCode() override;

			bool equals(std::any obj) override;
		};

	}
}