#include <string>
#include <unordered_map>
#include <unordered_set>
#include <optional>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace semsim { namespace model { namespace computational { namespace units { class UnitFactor; } } } }
namespace semsim { class SemSimLibrary; }
namespace semsim { namespace model { namespace collection { class SemSimModel; } } }

namespace semsim
{
	namespace annotation
	{


		using SemSimLibrary = semsim::SemSimLibrary;
		using SemSimModel = semsim::model::collection::SemSimModel;
		using UnitFactor = semsim::model::computational::units::UnitFactor;

		class AutoAnnotate
		{

		public:
			static std::unordered_map<std::wstring, Set<UnitFactor*>*> fundamentalBaseUnits;

			// Automatically apply OPB annotations to the physical properties associated
			// with the model's data structures
			static SemSimModel *autoAnnotateWithOPB(SemSimModel *semsimmodel, SemSimLibrary *semsimlib, const std::wstring &cfgreadpath);
		};

	}
}