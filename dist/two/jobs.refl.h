#pragma once

#include <two/jobs.h>
#include <two/refl.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <jobs/Types.h>

#ifndef TWO_JOBS_REFL_EXPORT
#define TWO_JOBS_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_JOBS_REFL_EXPORT two_jobs : public two::Module
	{
	private:
		two_jobs();
		
	public:
		static two_jobs& m() { static two_jobs instance; return instance; }
	};
}

#ifdef TWO_JOBS_MODULE
extern "C"
TWO_JOBS_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	
}
