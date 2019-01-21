#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/ui/Convert.h>
#endif

#include <ui/Api.h>
#define MUD_UI_REFLECTION_IMPL
#include <meta/ui/Meta.h>

namespace mud
{
	mud_ui::mud_ui()
		: Module("mud::ui", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_ctx::m() })
	{
		// setup reflection meta data
		mud_ui_meta(*this);
	}
}

#ifdef MUD_UI_MODULE
extern "C"
Module& getModule()
{
		return mud_ui::m();
}
#endif
