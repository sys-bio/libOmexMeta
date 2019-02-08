#include "definitions/SemSimTypes.h"
#include <string>

namespace semsim
{


	using SemSimTypes = semsim::definitions::SemSimTypes;

	/**
	 * Class representing elements within a SemSim model
	 *
	 *
	 */
	class SemSimObject
	{
	private:
		std::wstring name = std::wstring(L"");
		std::wstring description = std::wstring(L"");
		std::wstring metadataID = std::wstring(L"");
		SemSimTypes semsimtype = static_cast<SemSimTypes>(0);

	public:
		SemSimObject(SemSimTypes type);

		/**
		 * Copy constructor
		 * @param objtocopy The object to copy
		 */
		SemSimObject(const SemSimObject &objtocopy);

		/** @return The object's free-text description */
		virtual std::wstring getDescription();

		/** @return The object's name */
		virtual std::wstring getName();

		/** @return Whether the object has an associated name*/
		virtual bool hasName();

		/** @return Whether the object has an associated textual description */
		virtual bool hasDescription();

		/** @return Whether the object has an associated metadata ID */
		virtual bool hasMetadataID();

		/**
		 * Set the object's name
		 * @param name The name to apply
		 */
		virtual void setName(const std::wstring &name);

		/**
		 * Set the component's free-text description
		 * @param description The free-text description
		 */
		virtual void setDescription(const std::wstring &description);

		/**
		 * Copy this object's description to another SemSimObject
		 * @param srcds The object with the description we want to copy
		 */
		virtual void copyDescription(SemSimObject *srcds);

		/**
		 * Set the component's metadata ID. These ID's are often used
		 * by XML-based modeling languages such as SBML and CellML
		 * to link XML elements to RDF statements that describe
		 * the elements.
		 * 
		 * @param metadataID The ID to apply
		 */
		virtual void setMetadataID(const std::wstring &metadataID);

		/**
		 * @return The component's metadata ID. These ID's are used
		 * by XML-based modeling languages such as SBML and CellML
		 * to link XML elements to RDF statements that describe
		 * the elements.
		 */
		virtual std::wstring getMetadataID();


		/** @return This object's SemSimType */
		virtual SemSimTypes getSemSimType();

		/** @return This object's SemSim class URI */
		virtual URI *getSemSimClassURI();

		/**
		 * @param type A specified SemSimType
		 * @return Whether this object is a specified SemSimType
		 */
		virtual bool isType(SemSimTypes type);

	};


}