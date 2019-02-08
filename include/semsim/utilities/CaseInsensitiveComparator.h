#include <string>

namespace semsim
{
	namespace utilities
	{


		/**
		 * Convenience class for performing case-insensitive comparisons between Strings
		 *
		 *
		 */
		class CaseInsensitiveComparator : public Comparator<std::wstring>
		{
		public:
			virtual int compare(const std::wstring &strA, const std::wstring &strB);
		};

	}
}