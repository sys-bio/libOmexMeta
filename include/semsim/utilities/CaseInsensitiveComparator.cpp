#include "CaseInsensitiveComparator.h"

namespace semsim
{
	namespace utilities
	{

		int CaseInsensitiveComparator::compare(const std::wstring &strA, const std::wstring &strB)
		{
			return strA.compareToIgnoreCase(strB);
		}
	}
}