
#include <15_script/Generated/Module.h>

#ifdef _15_SCRIPT_REFLECT
#include <15_script/Generated/Convert.h>

#define _15_SCRIPT_REFLECTION_IMPL
#include <15_script/Generated/Meta.h>
#endif

	ex_15_script::ex_15_script()
		: Module("ex_15_script")
	{
        // ensure dependencies are instantiated
        mudobj::module();
        mudmath::module();
        mudui::module();
        muduio::module();
        mudgfx::module();
        mudedit::module();
        mudgen::module();

#ifdef _15_SCRIPT_REFLECT
        // setup reflection meta data
		ex_15_script_meta(*this);
#endif
	}

#ifdef _EX_15_SCRIPT_MODULE
extern "C"
_15_SCRIPT_EXPORT Module& getModule()
{
	return ex_15_script::module();
}
#endif
