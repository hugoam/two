#include <mud/gfx.pbr.refl.h>
#include <mud/geom.refl.h>
#include <mud/gfx.pbr.h>
#include <mud/gfx.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.gfx-pbr;
#else
#endif


namespace mud
{
	void mud_gfx_pbr_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::TonemapMode>();
		static Meta meta = { t, &namspc({ "mud" }), "TonemapMode", sizeof(mud::TonemapMode), TypeClass::Enum };
		static cstring ids[] = { "Linear", "Reinhardt", "Filmic", "ACES" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::TonemapMode vars[] = { mud::TonemapMode::Linear, mud::TonemapMode::Reinhardt, mud::TonemapMode::Filmic, mud::TonemapMode::ACES};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::TonemapMode>();
	}
	
	// Sequences
	
	// mud::BCS
	{
		Type& t = type<mud::BCS>();
		static Meta meta = { t, &namspc({ "mud" }), "BCS", sizeof(mud::BCS), TypeClass::Struct };
		// defaults
		static bool enabled_default = false;
		static float brightness_default = 1.0f;
		static float contrast_default = 1.0f;
		static float saturation_default = 1.0f;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::BCS>(ref)) mud::BCS(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::BCS>(ref)) mud::BCS(val<mud::BCS>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::BCS::m_enabled), type<bool>(), "enabled", Ref(&enabled_default), Member::Value, nullptr },
				{ t, member_address(&mud::BCS::m_brightness), type<float>(), "brightness", Ref(&brightness_default), Member::Value, nullptr },
				{ t, member_address(&mud::BCS::m_contrast), type<float>(), "contrast", Ref(&contrast_default), Member::Value, nullptr },
				{ t, member_address(&mud::BCS::m_saturation), type<float>(), "saturation", Ref(&saturation_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BCS>();
	}
	// mud::DofBlur
	{
		Type& t = type<mud::DofBlur>();
		static Meta meta = { t, &namspc({ "mud" }), "DofBlur", sizeof(mud::DofBlur), TypeClass::Struct };
		// defaults
		static bool enabled_default = false;
		static float far_distance_default = 10.f;
		static float far_transition_default = 5.f;
		static float far_radius_default = 5.f;
		static float near_distance_default = 2.f;
		static float near_transition_default = 1.f;
		static float near_radius_default = 5.f;
		static float max_coc_radius_default = 8.f;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::DofBlur>(ref)) mud::DofBlur(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::DofBlur>(ref)) mud::DofBlur(val<mud::DofBlur>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::DofBlur::m_enabled), type<bool>(), "enabled", Ref(&enabled_default), Member::Value, nullptr },
				{ t, member_address(&mud::DofBlur::m_far_distance), type<float>(), "far_distance", Ref(&far_distance_default), Member::Value, nullptr },
				{ t, member_address(&mud::DofBlur::m_far_transition), type<float>(), "far_transition", Ref(&far_transition_default), Member::Value, nullptr },
				{ t, member_address(&mud::DofBlur::m_far_radius), type<float>(), "far_radius", Ref(&far_radius_default), Member::Value, nullptr },
				{ t, member_address(&mud::DofBlur::m_near_distance), type<float>(), "near_distance", Ref(&near_distance_default), Member::Value, nullptr },
				{ t, member_address(&mud::DofBlur::m_near_transition), type<float>(), "near_transition", Ref(&near_transition_default), Member::Value, nullptr },
				{ t, member_address(&mud::DofBlur::m_near_radius), type<float>(), "near_radius", Ref(&near_radius_default), Member::Value, nullptr },
				{ t, member_address(&mud::DofBlur::m_max_coc_radius), type<float>(), "max_coc_radius", Ref(&max_coc_radius_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::DofBlur>();
	}
	// mud::GIProbe
	{
		Type& t = type<mud::GIProbe>();
		static Meta meta = { t, &namspc({ "mud" }), "GIProbe", sizeof(mud::GIProbe), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::GIProbe>();
	}
	// mud::Glow
	{
		Type& t = type<mud::Glow>();
		static Meta meta = { t, &namspc({ "mud" }), "Glow", sizeof(mud::Glow), TypeClass::Struct };
		// defaults
		static bool enabled_default = false;
		static mud::vec4 levels_1_4_default = {1.f,0.f,0.f,0.f};
		static mud::vec4 levels_5_8_default = Zero4;
		static float intensity_default = 0.4f;
		static float bloom_default = 0.0f;
		static float bleed_threshold_default = 1.0f;
		static float bleed_scale_default = 2.0f;
		static bool bicubic_filter_default = false;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Glow>(ref)) mud::Glow(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Glow>(ref)) mud::Glow(val<mud::Glow>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Glow::m_enabled), type<bool>(), "enabled", Ref(&enabled_default), Member::Value, nullptr },
				{ t, member_address(&mud::Glow::m_levels_1_4), type<mud::vec4>(), "levels_1_4", Ref(&levels_1_4_default), Member::Value, nullptr },
				{ t, member_address(&mud::Glow::m_levels_5_8), type<mud::vec4>(), "levels_5_8", Ref(&levels_5_8_default), Member::Value, nullptr },
				{ t, member_address(&mud::Glow::m_intensity), type<float>(), "intensity", Ref(&intensity_default), Member::Value, nullptr },
				{ t, member_address(&mud::Glow::m_bloom), type<float>(), "bloom", Ref(&bloom_default), Member::Value, nullptr },
				{ t, member_address(&mud::Glow::m_bleed_threshold), type<float>(), "bleed_threshold", Ref(&bleed_threshold_default), Member::Value, nullptr },
				{ t, member_address(&mud::Glow::m_bleed_scale), type<float>(), "bleed_scale", Ref(&bleed_scale_default), Member::Value, nullptr },
				{ t, member_address(&mud::Glow::m_bicubic_filter), type<bool>(), "bicubic_filter", Ref(&bicubic_filter_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Glow>();
	}
	// mud::LightShadow
	{
		Type& t = type<mud::LightShadow>();
		static Meta meta = { t, &namspc({ "mud" }), "LightShadow", sizeof(mud::LightShadow), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::LightShadow>(ref)) mud::LightShadow(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::LightShadow>(ref)) mud::LightShadow(val<mud::LightShadow>(other)); } }
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::LightShadow>();
	}
	// mud::Lightmap
	{
		Type& t = type<mud::Lightmap>();
		static Meta meta = { t, &namspc({ "mud" }), "Lightmap", sizeof(mud::Lightmap), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Lightmap>();
	}
	// mud::LightmapAtlas
	{
		Type& t = type<mud::LightmapAtlas>();
		static Meta meta = { t, &namspc({ "mud" }), "LightmapAtlas", sizeof(mud::LightmapAtlas), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::LightmapAtlas>();
	}
	// mud::LightmapItem
	{
		Type& t = type<mud::LightmapItem>();
		static Meta meta = { t, &namspc({ "mud" }), "LightmapItem", sizeof(mud::LightmapItem), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::LightmapItem>();
	}
	// mud::ReflectionProbe
	{
		Type& t = type<mud::ReflectionProbe>();
		static Meta meta = { t, &namspc({ "mud" }), "ReflectionProbe", sizeof(mud::ReflectionProbe), TypeClass::Object };
		// defaults
		static bool visible_default = true;
		static float intensity_default = 1.f;
		static mud::vec3 extents_default = Zero3;
		static bool shadows_default = false;
		static bool dirty_default = true;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, Address(), type<mud::Node3>(), "node", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::ReflectionProbe>(object).m_node); } },
				{ t, member_address(&mud::ReflectionProbe::m_visible), type<bool>(), "visible", Ref(&visible_default), Member::Value, nullptr },
				{ t, member_address(&mud::ReflectionProbe::m_intensity), type<float>(), "intensity", Ref(&intensity_default), Member::Value, nullptr },
				{ t, member_address(&mud::ReflectionProbe::m_extents), type<mud::vec3>(), "extents", Ref(&extents_default), Member::Value, nullptr },
				{ t, member_address(&mud::ReflectionProbe::m_shadows), type<bool>(), "shadows", Ref(&shadows_default), Member::Value, nullptr },
				{ t, member_address(&mud::ReflectionProbe::m_dirty), type<bool>(), "dirty", Ref(&dirty_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ReflectionProbe>();
	}
	// mud::Tonemap
	{
		Type& t = type<mud::Tonemap>();
		static Meta meta = { t, &namspc({ "mud" }), "Tonemap", sizeof(mud::Tonemap), TypeClass::Struct };
		// defaults
		static mud::TonemapMode mode_default = mud::TonemapMode::Linear;
		static bool enabled_default = false;
		static float exposure_default = 1.0f;
		static float white_point_default = 1.0f;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Tonemap>(ref)) mud::Tonemap(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Tonemap>(ref)) mud::Tonemap(val<mud::Tonemap>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Tonemap::m_mode), type<mud::TonemapMode>(), "mode", Ref(&mode_default), Member::Value, nullptr },
				{ t, member_address(&mud::Tonemap::m_enabled), type<bool>(), "enabled", Ref(&enabled_default), Member::Value, nullptr },
				{ t, member_address(&mud::Tonemap::m_exposure), type<float>(), "exposure", Ref(&exposure_default), Member::Value, nullptr },
				{ t, member_address(&mud::Tonemap::m_white_point), type<float>(), "white_point", Ref(&white_point_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Tonemap>();
	}
	// mud::BlockBlur
	{
		Type& t = type<mud::BlockBlur>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockBlur", sizeof(mud::BlockBlur), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::GfxBlock>() },
			{ base_offset<mud::BlockBlur, mud::GfxBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockBlur>();
	}
	// mud::BlockDofBlur
	{
		Type& t = type<mud::BlockDofBlur>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockDofBlur", sizeof(mud::BlockDofBlur), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::GfxBlock>() },
			{ base_offset<mud::BlockDofBlur, mud::GfxBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockDofBlur>();
	}
	// mud::BlockGIBake
	{
		Type& t = type<mud::BlockGIBake>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockGIBake", sizeof(mud::BlockGIBake), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::DrawBlock>() },
			{ base_offset<mud::BlockGIBake, mud::DrawBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockGIBake>();
	}
	// mud::BlockGITrace
	{
		Type& t = type<mud::BlockGITrace>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockGITrace", sizeof(mud::BlockGITrace), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::DrawBlock>() },
			{ base_offset<mud::BlockGITrace, mud::DrawBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockGITrace>();
	}
	// mud::BlockGeometry
	{
		Type& t = type<mud::BlockGeometry>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockGeometry", sizeof(mud::BlockGeometry), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::DrawBlock>() },
			{ base_offset<mud::BlockGeometry, mud::DrawBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockGeometry>();
	}
	// mud::BlockGlow
	{
		Type& t = type<mud::BlockGlow>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockGlow", sizeof(mud::BlockGlow), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::GfxBlock>() },
			{ base_offset<mud::BlockGlow, mud::GfxBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockGlow>();
	}
	// mud::BlockLight
	{
		Type& t = type<mud::BlockLight>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockLight", sizeof(mud::BlockLight), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::DrawBlock>() },
			{ base_offset<mud::BlockLight, mud::DrawBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockLight>();
	}
	// mud::BlockLightmap
	{
		Type& t = type<mud::BlockLightmap>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockLightmap", sizeof(mud::BlockLightmap), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::DrawBlock>() },
			{ base_offset<mud::BlockLightmap, mud::DrawBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockLightmap>();
	}
	// mud::BlockRadiance
	{
		Type& t = type<mud::BlockRadiance>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockRadiance", sizeof(mud::BlockRadiance), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::DrawBlock>() },
			{ base_offset<mud::BlockRadiance, mud::DrawBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockRadiance>();
	}
	// mud::BlockReflection
	{
		Type& t = type<mud::BlockReflection>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockReflection", sizeof(mud::BlockReflection), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::DrawBlock>() },
			{ base_offset<mud::BlockReflection, mud::DrawBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockReflection>();
	}
	// mud::BlockShadow
	{
		Type& t = type<mud::BlockShadow>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockShadow", sizeof(mud::BlockShadow), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::DrawBlock>() },
			{ base_offset<mud::BlockShadow, mud::DrawBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockShadow>();
	}
	// mud::BlockTonemap
	{
		Type& t = type<mud::BlockTonemap>();
		static Meta meta = { t, &namspc({ "mud" }), "BlockTonemap", sizeof(mud::BlockTonemap), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::GfxBlock>() },
			{ base_offset<mud::BlockTonemap, mud::GfxBlock>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::BlockTonemap>();
	}
		m.m_types.push_back(&type<mud::BCS>());
		m.m_types.push_back(&type<mud::DofBlur>());
		m.m_types.push_back(&type<mud::GIProbe>());
		m.m_types.push_back(&type<mud::Glow>());
		m.m_types.push_back(&type<mud::LightShadow>());
		m.m_types.push_back(&type<mud::Lightmap>());
		m.m_types.push_back(&type<mud::LightmapAtlas>());
		m.m_types.push_back(&type<mud::LightmapItem>());
		m.m_types.push_back(&type<mud::ReflectionProbe>());
		m.m_types.push_back(&type<mud::Tonemap>());
		m.m_types.push_back(&type<mud::TonemapMode>());
		m.m_types.push_back(&type<mud::BlockBlur>());
		m.m_types.push_back(&type<mud::BlockDofBlur>());
		m.m_types.push_back(&type<mud::BlockGIBake>());
		m.m_types.push_back(&type<mud::BlockGITrace>());
		m.m_types.push_back(&type<mud::BlockGeometry>());
		m.m_types.push_back(&type<mud::BlockGlow>());
		m.m_types.push_back(&type<mud::BlockLight>());
		m.m_types.push_back(&type<mud::BlockLightmap>());
		m.m_types.push_back(&type<mud::BlockRadiance>());
		m.m_types.push_back(&type<mud::BlockReflection>());
		m.m_types.push_back(&type<mud::BlockShadow>());
		m.m_types.push_back(&type<mud::BlockTonemap>());
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::gi_probe(val<mud::Gnode>(args[0]), val<uint16_t>(args[1]), val<mud::vec3>(args[2]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "subdiv", var(uint16_t()) }, { "extents", var(mud::vec3()) } };
			static Function f = { &namspc({ "mud", "gfx" }), "gi_probe", funcptr<mud::GIProbe&(*)(mud::Gnode&, uint16_t, const mud::vec3&)>(&mud::gfx::gi_probe), func, params, Ref(type<mud::GIProbe>()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  result = Ref(&mud::gfx::lightmap(val<mud::Gnode>(args[0]), val<uint32_t>(args[1]), val<float>(args[2]), val<string>(args[3]))); };
			vector<Param> params = { { "parent", Ref(type<mud::Gnode>()) }, { "resolution", var(uint32_t()) }, { "density", var(float(8.f)), Param::Default }, { "save_path", var(string("")), Param::Default } };
			static Function f = { &namspc({ "mud", "gfx" }), "lightmap", funcptr<mud::LightmapAtlas&(*)(mud::Gnode&, uint32_t, float, const string&)>(&mud::gfx::lightmap), func, params, Ref(type<mud::LightmapAtlas>()) };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_gfx_pbr::mud_gfx_pbr()
		: Module("mud::gfx-pbr", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_geom::m(), &mud_gfx::m() })
	{
		// setup reflection meta data
		mud_gfx_pbr_meta(*this);
	}
}

#ifdef MUD_GFX_PBR_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx_pbr::m();
}
#endif
