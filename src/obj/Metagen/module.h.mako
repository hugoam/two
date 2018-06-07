
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
% for m in module.dependencies :
#include <${ m.subdir }/Generated/Module.h>
% endfor
#endif
        
#include <${ module.subdir }/Generated/Forward.h>
#include <${ module.subdir }/Generated/Types.h>
#include <${ module.subdir }/Api.h>

#include <${ module.subdir }/Generated/Convert.h>

% if module.namespace != '' :
namespace ${ module.namespace }
{
% endif
	export_ class ${ module.export } ${ module.id } : public Module
	{
	private:
		${ module.id }();

	public:
		static ${ module.id }& m() { static ${ module.id } instance; return instance; }
	};
% if module.namespace != '' :
}
% endif

#ifdef ${ module.preproc_name }_MODULE
extern "C"
${ module.export } Module& getModule();
#endif
