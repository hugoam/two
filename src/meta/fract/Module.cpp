#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.fract;
#else
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/fract/Module.h>
#include <meta/fract/Convert.h>
#endif

#include <fract/Api.h>

namespace mud
{
	void mud_fract_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::PatternSampling>();
		static Meta meta = { t, &namspc({ "mud" }), "PatternSampling", sizeof(mud::PatternSampling), TypeClass::Enum };
		static cstring ids[] = { "X", "XY", "Depth" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::PatternSampling vars[] = { mud::PatternSampling::X, mud::PatternSampling::XY, mud::PatternSampling::Depth};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::PatternSampling>();
	}
	
	// Sequences
	{
		Type& t = type<vector<mud::Image256>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Image256>", sizeof(vector<mud::Image256>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::Image256>();
		meta_vector<vector<mud::Image256>, mud::Image256>();
	}
	
	// mud::Circlifier
	{
		Type& t = type<mud::Circlifier>();
		static Meta meta = { t, &namspc({ "mud" }), "Circlifier", sizeof(mud::Circlifier), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Circlifier>(ref)) mud::Circlifier( val<mud::Image256>(args[0]) ); }, { { "image", var(mud::Image256()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
				{ t, "compute", member_address<vector<mud::Circle>(mud::Circlifier::*)(const mud::Colour&, float)>(&mud::Circlifier::compute), [](Ref object, array<Var> args, Var& result) { val<vector<mud::Circle>>(result) = val<mud::Circlifier>(object).compute(val<mud::Colour>(args[0]), val<float>(args[1])); }, { { "colour", var(mud::Colour()) }, { "scale", var(float(1.f)), Param::Default } }, var(vector<mud::Circle>()) }
			},
			// static members
			{
			}
		};
		init_pool<mud::Circlifier>();
		meta_class<mud::Circlifier>();
	}
	// mud::Fract
	{
		Type& t = type<mud::Fract>();
		static Meta meta = { t, &namspc({ "mud" }), "Fract", sizeof(mud::Fract), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Fract>(ref)) mud::Fract( val<size_t>(args[0]) ); }, { { "num_tabs", var(size_t(75)), Param::Default } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Fract::m_num_tabs), type<size_t>(), "nutabs", Ref(), Member::Value, nullptr }
			},
			// methods
			{
				{ t, "generate", member_address<void(mud::Fract::*)(size_t)>(&mud::Fract::generate), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).generate(val<size_t>(args[0])); }, { { "num_tabs", var(size_t(75)), Param::Default } }, Var() },
				{ t, "regen", member_address<void(mud::Fract::*)()>(&mud::Fract::regen), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::Fract>(object).regen(); }, {}, Var() },
				{ t, "render", member_address<void(mud::Fract::*)(const mud::Rect&, const mud::Pattern&, mud::uvec2, mud::Image256&)>(&mud::Fract::render), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).render(val<mud::Rect>(args[0]), val<mud::Pattern>(args[1]), val<mud::uvec2>(args[2]), val<mud::Image256>(args[3])); }, { { "rect", var(mud::Rect()) }, { "pattern", var(mud::Pattern()) }, { "resolution", var(mud::uvec2()) }, { "output_image", var(mud::Image256()), Param::Output } }, Var() },
				{ t, "render_whole", member_address<void(mud::Fract::*)(const mud::Pattern&, mud::uvec2, mud::Image256&)>(&mud::Fract::render_whole), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).render_whole(val<mud::Pattern>(args[0]), val<mud::uvec2>(args[1]), val<mud::Image256>(args[2])); }, { { "pattern", var(mud::Pattern()) }, { "resolution", var(mud::uvec2()) }, { "output_image", var(mud::Image256()), Param::Output } }, Var() },
				{ t, "render_grid", member_address<void(mud::Fract::*)(mud::uvec2, const mud::Pattern&, mud::uvec2, vector<mud::Image256>&)>(&mud::Fract::render_grid), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).render_grid(val<mud::uvec2>(args[0]), val<mud::Pattern>(args[1]), val<mud::uvec2>(args[2]), val<vector<mud::Image256>>(args[3])); }, { { "size", var(mud::uvec2()) }, { "pattern", var(mud::Pattern()) }, { "resolution", var(mud::uvec2()) }, { "output_images", var(vector<mud::Image256>()), Param::Output } }, Var() }
			},
			// static members
			{
			}
		};
		init_pool<mud::Fract>();
		meta_class<mud::Fract>();
	}
	// mud::FractSample
	{
		Type& t = type<mud::FractSample>();
		static Meta meta = { t, &namspc({ "mud" }), "FractSample", sizeof(mud::FractSample), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::FractSample>(ref)) mud::FractSample( val<mud::Fract>(args[0]), val<mud::Rect>(args[1]), val<mud::uvec2>(args[2]) ); }, { { "fract", Ref(type<mud::Fract>()) }, { "rect", var(mud::Rect()) }, { "resolution", var(mud::uvec2()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, Address(), type<mud::Fract>(), "fract", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::FractSample>(object).m_fract); } },
				{ t, member_address(&mud::FractSample::m_rect), type<mud::Rect>(), "rect", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::FractSample::m_resolution), type<mud::uvec2>(), "resolution", Ref(), Member::Value, nullptr }
			},
			// methods
			{
				{ t, "render", member_address<void(mud::FractSample::*)(const mud::Pattern&, mud::Image256&)>(&mud::FractSample::render), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::FractSample>(object).render(val<mud::Pattern>(args[0]), val<mud::Image256>(args[1])); }, { { "pattern", var(mud::Pattern()) }, { "outputImage", var(mud::Image256()), Param::Output } }, Var() }
			},
			// static members
			{
			}
		};
		init_pool<mud::FractSample>();
		meta_class<mud::FractSample>();
	}
	// mud::FractTab
	{
		Type& t = type<mud::FractTab>();
		static Meta meta = { t, &namspc({ "mud" }), "FractTab", sizeof(mud::FractTab), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::FractTab>(ref)) mud::FractTab(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::FractTab>(ref)) mud::FractTab(val<mud::FractTab>(other)); } }
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
		meta_class<mud::FractTab>();
	}
	// mud::Pattern
	{
		Type& t = type<mud::Pattern>();
		static Meta meta = { t, &namspc({ "mud" }), "Pattern", sizeof(mud::Pattern), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Pattern>(ref)) mud::Pattern( val<mud::Palette>(args[0]), val<mud::PatternSampling>(args[1]), val<float>(args[2]), val<size_t>(args[3]) ); }, { { "palette", var(mud::Palette()) }, { "sampling", var(mud::PatternSampling()) }, { "precision", var(float(1.f)), Param::Default }, { "step", var(size_t(1)), Param::Default } } },
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Pattern>(ref)) mud::Pattern(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Pattern>(ref)) mud::Pattern(val<mud::Pattern>(other)); } }
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
		meta_class<mud::Pattern>();
	}
		m.m_types.push_back(&type<mud::Circlifier>());
		m.m_types.push_back(&type<mud::Fract>());
		m.m_types.push_back(&type<mud::FractSample>());
		m.m_types.push_back(&type<mud::FractTab>());
		m.m_types.push_back(&type<mud::Pattern>());
		m.m_types.push_back(&type<mud::PatternSampling>());
		m.m_types.push_back(&type<vector<mud::Image256>>());
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::generate_fract(val<mud::uvec2>(args[0]), val<mud::Pattern>(args[1]), val<mud::Image256>(args[2])); };
			vector<Param> params = { { "resolution", var(mud::uvec2()) }, { "pattern", var(mud::Pattern()) }, { "output_image", var(mud::Image256()), Param::Output } };
			static Function f = { &namspc({ "mud" }), "generate_fract", funcptr<void(*)(mud::uvec2, const mud::Pattern&, mud::Image256&)>(&mud::generate_fract), func, params, Var() };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_fract::mud_fract()
		: Module("mud::fract", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_geom::m() })
	{
		// setup reflection meta data
		mud_fract_meta(*this);
	}
}

#ifdef MUD_FRACT_MODULE
extern "C"
Module& getModule()
{
		return mud_fract::m();
}
#endif
