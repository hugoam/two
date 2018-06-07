#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module ${ module.namespace }.${ module.name };
#else
#include <${ module.subdir }/Generated/Module.h>
#endif

#ifdef ${ module.preproc_name }_REFLECT
#ifndef MUD_MODULES
#include <${ module.subdir }/Generated/Convert.h>
#endif
#define ${ module.preproc_name }_REFLECTION_IMPL
#include <${ module.subdir }/Generated/Meta.h>
#endif

% if module.namespace != '' :
namespace ${ module.namespace }
{
% endif
	${ module.id }::${ module.id }()
		: Module("${ module.namespace + '::' if module.namespace != '' else '' }${ module.name }")
	{
        // ensure dependencies are instantiated
% for m in module.dependencies :
        ${ m.id }::m();
% endfor

#ifdef ${ module.preproc_name }_REFLECT
        // setup reflection meta data
		${ module.id }_meta(*this);
#endif
	}
% if module.namespace != '' :
}
% endif

#ifdef ${ module.preproc_name }_MODULE
extern "C"
${ module.export } Module& getModule()
{
	return ${ module.id }::m();
}
#endif
