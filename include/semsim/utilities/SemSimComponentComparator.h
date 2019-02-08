namespace semsim { class SemSimObject; }

namespace semsim
{
	namespace utilities
	{


		using SemSimObject = semsim::SemSimObject;

		/**
		 * Comparator for comparing the names of SemSimObjects, ignoring case
		 *
		 *
		 */
		class SemSimComponentComparator : public Comparator<SemSimObject*>
		{
		public:
			virtual int compare(SemSimObject *A, SemSimObject *B);
		};

	}
}