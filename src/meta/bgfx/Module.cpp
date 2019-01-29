#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.bgfx;
#else
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/ctx/Module.h>
#include <meta/bgfx/Module.h>
#include <meta/bgfx/Convert.h>
#endif

#include <bgfx/Api.h>

using namespace mud;


namespace mud
{
	void mud_bgfx_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	}
}

namespace mud
{
	mud_bgfx::mud_bgfx()
		: Module("mud::bgfx", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_ctx::m() })
	{
		// setup reflection meta data
		mud_bgfx_meta(*this);
	}
}

#ifdef MUD_BGFX_MODULE
extern "C"
Module& getModule()
{
		return mud_bgfx::m();
}
#endif
