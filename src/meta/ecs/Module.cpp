#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ecs;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/refl/Module.h>
#include <meta/ecs/Module.h>
#include <meta/ecs/Convert.h>
#endif

#include <ecs/Api.h>
#define MUD_ECS_REFLECTION_IMPL
#include <meta/ecs/Meta.h>

namespace mud
{
	mud_ecs::mud_ecs()
		: Module("mud::ecs", { &mud_infra::m(), &mud_type::m(), &mud_refl::m() })
	{
		// setup reflection meta data
		mud_ecs_meta(*this);
	}
}

#ifdef MUD_ECS_MODULE
extern "C"
Module& getModule()
{
		return mud_ecs::m();
}
#endif
