#include "SemSimComponentComparator.h"

namespace semsim
{
	namespace utilities
	{
		using SemSimObject = semsim::SemSimObject;

		int SemSimComponentComparator::compare(SemSimObject *A, SemSimObject *B)
		{
//JAVA TO C++ CONVERTER TODO TASK: The following Java case-insensitive String method call is not converted:
			return A->getName().compareToIgnoreCase(B->getName());
		}
	}
}