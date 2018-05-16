
#include <00_tutorial/Generated/Module.h>

#ifdef _00_TUTORIAL_REFLECT
#include <00_tutorial/Generated/Convert.h>

#define _00_TUTORIAL_REFLECTION_IMPL
#include <00_tutorial/Generated/Meta.h>
#endif

	ex_00_tutorial::ex_00_tutorial()
		: Module("ex_00_tutorial")
	{
        // ensure dependencies are instantiated
        mudobj::module();
        mudmath::module();
        mudui::module();
        muduio::module();
        mudgfx::module();
        mudedit::module();
        mudgen::module();

#ifdef _00_TUTORIAL_REFLECT
        // setup reflection meta data
		ex_00_tutorial_meta(*this);
#endif
	}

#ifdef _EX_00_TUTORIAL_MODULE
extern "C"
_00_TUTORIAL_EXPORT Module& getModule()
{
	return ex_00_tutorial::module();
}
#endif
