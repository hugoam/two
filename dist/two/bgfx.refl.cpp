#include <two/infra.refl.h>
#include <two/type.refl.h>
#include <two/bgfx.h>
#include <two/ctx.refl.h>
#include <two/refl.h>
#include <two/math.refl.h>
#include <two/infra.h>
#include <two/type.h>
#include <two/bgfx.refl.h>


#ifdef TWO_MODULES
module two.bgfx;
#else
#include <cstddef>
#include <stl/new.h>
#endif


using namespace two;


namespace two
{
	void two_bgfx_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// two::BgfxSystem
	{
		Type& t = type<two::BgfxSystem>();
		static Meta meta = { t, &namspc({ "two" }), "BgfxSystem", sizeof(two::BgfxSystem), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::RenderSystem>() };
		static size_t bases_offsets[] = { base_offset<two::BgfxSystem, two::RenderSystem>() };
		// defaults
		static uint32_t frame_default = 1;
		static float time_default = 0.f;
		static float frame_time_default = 0.f;
		static float delta_time_default = 0.f;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::BgfxSystem, m_frame), type<uint32_t>(), "frame", &frame_default, Member::Value, nullptr },
			{ t, offsetof(two::BgfxSystem, m_time), type<float>(), "time", &time_default, Member::Value, nullptr },
			{ t, offsetof(two::BgfxSystem, m_frame_time), type<float>(), "frame_time", &frame_time_default, Member::Value, nullptr },
			{ t, offsetof(two::BgfxSystem, m_delta_time), type<float>(), "delta_time", &delta_time_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<two::BgfxSystem>());
	}
}

namespace two
{
	two_bgfx::two_bgfx()
		: Module("two::bgfx", { &two_infra::m(), &two_type::m(), &two_math::m(), &two_ctx::m() })
	{
		// setup reflection meta data
		two_bgfx_meta(*this);
	}
}

#ifdef TWO_BGFX_MODULE
extern "C"
Module& getModule()
{
	return two_bgfx::m();
}
#endif
