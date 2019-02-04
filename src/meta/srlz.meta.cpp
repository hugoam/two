#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.srlz;
#else
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/refl.meta.h>
#include <meta/srlz.meta.h>
#include <meta/srlz.conv.h>
#endif

#include <srlz/Api.h>

using namespace mud;


namespace mud
{
	void mud_srlz_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	}
}

namespace mud
{
	mud_srlz::mud_srlz()
		: Module("mud::srlz", { &mud_infra::m(), &mud_type::m(), &mud_refl::m() })
	{
		// setup reflection meta data
		mud_srlz_meta(*this);
	}
}

#ifdef MUD_SRLZ_MODULE
extern "C"
Module& getModule()
{
		return mud_srlz::m();
}
#endif
