#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_JOBS_META_EXPORT
#define TWO_JOBS_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_JOBS_META_EXPORT two_jobs : public two::Module
	{
	private:
		two_jobs();
		
	public:
		static two_jobs& m() { static two_jobs instance; return instance; }
	};
}

#ifdef TWO_JOBS_MODULE
extern "C"
TWO_JOBS_META_EXPORT Module& getModule();
#endif
