#include <string>
#include <optional>

namespace semsim
{
	namespace utilities
	{

		/**
		 * An entry in a SemSim {@link ErrorLog}
		 * @author mneal
		 *
		 */
		class ErrorEntry : public Comparable<ErrorEntry*>
		{
		public:
			std::wstring errmsg;
			std::optional<bool> isfatal;

			ErrorEntry(const std::wstring &message, std::optional<bool> &fatal);

			int compareTo(ErrorEntry *arg0) override;
		};

	}
}