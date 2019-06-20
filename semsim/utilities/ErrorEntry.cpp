#include "ErrorEntry.h"

namespace semsim
{
	namespace utilities
	{

		ErrorEntry::ErrorEntry(const std::wstring &message, std::optional<bool> &fatal)
		{
			errmsg = message;
			isfatal = fatal;
		}

		int ErrorEntry::compareTo(ErrorEntry *arg0)
		{
			// TODO Auto-generated method stub
			return 0;
		}
	}
}