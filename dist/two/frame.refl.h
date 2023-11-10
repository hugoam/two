#pragma once

#include <two/frame.h>
#include <two/refl.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <frame/Types.h>

#ifndef TWO_FRAME_REFL_EXPORT
#define TWO_FRAME_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_FRAME_REFL_EXPORT two_frame : public two::Module
	{
	private:
		two_frame();
		
	public:
		static two_frame& m() { static two_frame instance; return instance; }
	};
}

#ifdef TWO_FRAME_MODULE
extern "C"
TWO_FRAME_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	
}
