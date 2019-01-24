#pragma once

#include <mud/srlz.refl.h>
#include <mud/srlz.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.srlz;
#else
#endif


namespace mud
{
	void mud_srlz_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	}
}

namespace mud
{
	mud_srlz::mud_srlz()
		: Module("mud::srlz", { &mud_infra::m(), &mud_type::m(), &mud_refl::m() })
	{
		// setup reflection meta data
		mud_srlz_meta(*this);
	}
}

#ifdef MUD_SRLZ_MODULE
extern "C"
Module& getModule()
{
		return mud_srlz::m();
}
#endif
