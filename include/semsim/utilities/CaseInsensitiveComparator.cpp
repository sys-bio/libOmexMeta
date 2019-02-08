#include "CaseInsensitiveComparator.h"

namespace semsim
{
	namespace utilities
	{

		int CaseInsensitiveComparator::compare(const std::wstring &strA, const std::wstring &strB)
		{
//JAVA TO C++ CONVERTER TODO TASK: The following Java case-insensitive String method call is not converted:
			return strA.compareToIgnoreCase(strB);
		}
	}
}