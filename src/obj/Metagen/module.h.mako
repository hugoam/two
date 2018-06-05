
#pragma once

#ifndef MUD_MODULES
#include <obj/System/System.h>

% for m in module.dependencies :
#include <${ m.subdir }/Generated/Module.h>
% endfor
#endif
        
#include <${ module.subdir }/Generated/Forward.h>
#include <${ module.subdir }/Generated/Types.h>
#include <${ module.subdir }/Generated/Convert.h>

% for header in module.headers :
#include <${ module.subdir }/${ header }>
% endfor

% if module.namespace != '' :
namespace ${ module.namespace }
{
% endif
	export_ class ${ module.export } ${ module.namespace }${ module.name } : public Module
	{
	private:
		${ module.namespace }${ module.name }();

	public:
		static ${ module.namespace }${ module.name }& m() { static ${ module.namespace }${ module.name } instance; return instance; }
	};
% if module.namespace != '' :
}
% endif

#ifdef ${ module.namespace.upper() }_${ module.name.upper() }_MODULE
extern "C"
${ module.export } Module& getModule();
#endif
