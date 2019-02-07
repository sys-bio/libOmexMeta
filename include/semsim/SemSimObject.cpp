#include "SemSimObject.h"

namespace semsim
{
	using SemSimTypes = semsim::definitions::SemSimTypes;

	SemSimObject::SemSimObject(SemSimTypes type)
	{
		semsimtype = type;
	}

	SemSimObject::SemSimObject(const SemSimObject &objtocopy)
	{
		semsimtype = objtocopy->semsimtype;
		name = std::wstring(objtocopy->name);

		if (objtocopy->description != "")
		{
			description = std::wstring(objtocopy->description);
		}

		if (objtocopy->metadataID != "")
		{
			metadataID = std::wstring(objtocopy->metadataID);
		}
	}

	std::wstring SemSimObject::getDescription()
	{
		return description;
	}

	std::wstring SemSimObject::getName()
	{
		return name;
	}

	bool SemSimObject::hasName()
	{
		return (name != "" && name != "");
	}

	bool SemSimObject::hasDescription()
	{
		if (description != "" && description != "")
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool SemSimObject::hasMetadataID()
	{
		return (metadataID != "" && metadataID != "");
	}

	void SemSimObject::setName(const std::wstring &name)
	{
		this->name = name;
	}

	void SemSimObject::setDescription(const std::wstring &description)
	{
		this->description = description;
	}

	void SemSimObject::copyDescription(SemSimObject *srcds)
	{
		// Copy free-text description
		setDescription(std::wstring(srcds->getDescription()));
	}

	void SemSimObject::setMetadataID(const std::wstring &metadataID)
	{
		if (metadataID != "")
		{
			this->metadataID = metadataID;
		}
	}

	std::wstring SemSimObject::getMetadataID()
	{
		return metadataID;
	}

	SemSimTypes SemSimObject::getSemSimType()
	{
		return semsimtype;
	}

	URI *SemSimObject::getSemSimClassURI()
	{
		return semsimtype.getURI();
	}

	bool SemSimObject::isType(SemSimTypes type)
	{
		return type == semsimtype;
	}
}