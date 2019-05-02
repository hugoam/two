#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <uio/Forward.h>
//#include <uio/Types.h>

#ifndef TWO_UIO_REFL_EXPORT
#define TWO_UIO_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_UIO_REFL_EXPORT two_uio : public two::Module
	{
	private:
		two_uio();
		
	public:
		static two_uio& m() { static two_uio instance; return instance; }
	};
}

#ifdef TWO_UIO_MODULE
extern "C"
TWO_UIO_REFL_EXPORT Module& getModule();
#endif
