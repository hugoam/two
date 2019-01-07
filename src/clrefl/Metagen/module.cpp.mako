#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module ${ module.namespace }.${ module.name };
#else
#include <meta/${ module.subdir }/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/${ module.subdir }/Convert.h>
#endif
#define ${ module.preproc_name }_REFLECTION_IMPL
#include <meta/${ module.subdir }/Meta.h>

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

        // setup reflection meta data
		${ module.id }_meta(*this);
	}
% if module.namespace != '' :
}
% endif

#ifdef ${ module.preproc_name }_MODULE
extern "C"
Module& getModule()
{
	return ${ module.id }::m();
}
#endif
