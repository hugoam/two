
#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
% for m in module.dependencies :
#include <meta/${ m.subdir }/Module.h>
% endfor
#endif
        
#include <${ module.subdir }/Forward.h>
#include <${ module.subdir }/Types.h>
#include <${ module.subdir }/Api.h>

#include <meta/${ module.subdir }/Convert.h>

#ifndef ${ module.refl_export }
#define ${ module.refl_export } MUD_IMPORT
#endif

% if module.namespace != '' :
namespace ${ module.namespace }
{
% endif
	export_ class ${ module.refl_export } ${ module.id } : public Module
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
${ module.refl_export } Module& getModule();
#endif
