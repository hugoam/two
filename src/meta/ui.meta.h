#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <ui/Forward.h>
//#include <ui/Types.h>

#ifndef TWO_UI_REFL_EXPORT
#define TWO_UI_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_UI_REFL_EXPORT two_ui : public two::Module
	{
	private:
		two_ui();
		
	public:
		static two_ui& m() { static two_ui instance; return instance; }
	};
}

#ifdef TWO_UI_MODULE
extern "C"
TWO_UI_REFL_EXPORT Module& getModule();
#endif
