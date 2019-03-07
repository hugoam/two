#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.bgfx;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/math.meta.h>
#include <meta/ctx.meta.h>
#include <meta/bgfx.meta.h>
#include <meta/bgfx.conv.h>
#endif

#include <bgfx/Api.h>

using namespace mud;


namespace mud
{
	void mud_bgfx_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// mud::BgfxSystem
	{
		Type& t = type<mud::BgfxSystem>();
		static Meta meta = { t, &namspc({ "mud" }), "BgfxSystem", sizeof(mud::BgfxSystem), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::RenderSystem>() };
		static size_t bases_offsets[] = { base_offset<mud::BgfxSystem, mud::RenderSystem>() };
		// defaults
		static uint32_t frame_default = 1;
		static float time_default = 0.f;
		static float frame_time_default = 0.f;
		static float delta_time_default = 0.f;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::BgfxSystem, m_frame), type<uint32_t>(), "frame", &frame_default, Member::Value, nullptr },
			{ t, offsetof(mud::BgfxSystem, m_time), type<float>(), "time", &time_default, Member::Value, nullptr },
			{ t, offsetof(mud::BgfxSystem, m_frame_time), type<float>(), "frame_time", &frame_time_default, Member::Value, nullptr },
			{ t, offsetof(mud::BgfxSystem, m_delta_time), type<float>(), "delta_time", &delta_time_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<mud::BgfxSystem>());
	}
}

namespace mud
{
	mud_bgfx::mud_bgfx()
		: Module("mud::bgfx", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_ctx::m() })
	{
		// setup reflection meta data
		mud_bgfx_meta(*this);
	}
}

#ifdef MUD_BGFX_MODULE
extern "C"
Module& getModule()
{
	return mud_bgfx::m();
}
#endif
