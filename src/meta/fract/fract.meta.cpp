#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.fract;
#else
#include <stddef.h>
#include <stl/new.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/infra.meta.h>
#include <meta/type/type.meta.h>
#include <meta/math/math.meta.h>
#include <meta/geom/geom.meta.h>
#include <meta/fract/fract.meta.h>
#include <meta/fract/Convert.h>
#endif

#include <fract/Api.h>

using namespace mud;

void mud_PatternSampling__to_string(void* val, string& str) { str = g_enu[type<mud::PatternSampling>().m_id]->name(uint32_t((*static_cast<mud::PatternSampling*>(val)))); }
void mud_PatternSampling__to_value(const string& str, void* val) { (*static_cast<mud::PatternSampling*>(val)) = mud::PatternSampling(g_enu[type<mud::PatternSampling>().m_id]->value(str.c_str())); }
size_t vector_mud_Image256___size(void* vec) { return (*static_cast<vector<mud::Image256>*>(vec)).size(); }
void* vector_mud_Image256___at(void* vec, size_t i) { return &(*static_cast<vector<mud::Image256>*>(vec))[i]; }
void vector_mud_Image256___add(void* vec, void* value) { (*static_cast<vector<mud::Image256>*>(vec)).push_back(*static_cast<mud::Image256*>(value)); }
void vector_mud_Image256___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::Image256>*>(vec)), *static_cast<mud::Image256*>(value)); }
void mud_Circlifier__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Circlifier*>(ref))) mud::Circlifier( *static_cast<mud::Image256*>(args[0]) ); }
void mud_Circlifier_compute(void* object, array<void*> args, void*& result) { (*static_cast<vector<mud::Circle>*>(result)) = (*static_cast<mud::Circlifier*>(object)).compute(*static_cast<mud::Colour*>(args[0]), *static_cast<float*>(args[1])); }
void mud_Fract__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Fract*>(ref))) mud::Fract( *static_cast<size_t*>(args[0]) ); }
void mud_Fract_generate(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Fract*>(object)).generate(*static_cast<size_t*>(args[0])); }
void mud_Fract_regen(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Fract*>(object)).regen(); }
void mud_Fract_render(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Fract*>(object)).render(*static_cast<mud::Rect*>(args[0]), *static_cast<mud::Pattern*>(args[1]), *static_cast<mud::uvec2*>(args[2]), *static_cast<mud::Image256*>(args[3])); }
void mud_Fract_render_whole(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Fract*>(object)).render_whole(*static_cast<mud::Pattern*>(args[0]), *static_cast<mud::uvec2*>(args[1]), *static_cast<mud::Image256*>(args[2])); }
void mud_Fract_render_grid(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Fract*>(object)).render_grid(*static_cast<mud::uvec2*>(args[0]), *static_cast<mud::Pattern*>(args[1]), *static_cast<mud::uvec2*>(args[2]), *static_cast<vector<mud::Image256>*>(args[3])); }
void mud_FractSample__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::FractSample*>(ref))) mud::FractSample( *static_cast<mud::Fract*>(args[0]), *static_cast<mud::Rect*>(args[1]), *static_cast<mud::uvec2*>(args[2]) ); }
void* mud_FractSample__get_fract(void* object) { return &(*static_cast<mud::FractSample*>(object)).m_fract; }
void mud_FractSample_render(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::FractSample*>(object)).render(*static_cast<mud::Pattern*>(args[0]), *static_cast<mud::Image256*>(args[1])); }
void mud_FractTab__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::FractTab*>(ref))) mud::FractTab(  ); }
void mud_FractTab__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::FractTab*>(ref))) mud::FractTab((*static_cast<mud::FractTab*>(other))); }
void mud_Pattern__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Pattern*>(ref))) mud::Pattern( *static_cast<mud::Palette*>(args[0]), *static_cast<mud::PatternSampling*>(args[1]), *static_cast<float*>(args[2]), *static_cast<size_t*>(args[3]) ); }
void mud_Pattern__construct_1(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Pattern*>(ref))) mud::Pattern(  ); }
void mud_Pattern__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Pattern*>(ref))) mud::Pattern((*static_cast<mud::Pattern*>(other))); }
void mud_generate_fract_0(array<void*> args, void*& result) { UNUSED(result);  mud::generate_fract(*static_cast<mud::uvec2*>(args[0]), *static_cast<mud::Pattern*>(args[1]), *static_cast<mud::Image256*>(args[2])); }

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
		static Convert convert = { mud_PatternSampling__to_string,
		                           mud_PatternSampling__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<vector<mud::Image256>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Image256>", sizeof(vector<mud::Image256>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Image256>(),
		                             vector_mud_Image256___size,
		                             vector_mud_Image256___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_Image256___add,
		                             vector_mud_Image256___remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// mud::Circlifier
	{
		Type& t = type<mud::Circlifier>();
		static Meta meta = { t, &namspc({ "mud" }), "Circlifier", sizeof(mud::Circlifier), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Circlifier__construct_0, { { "image", type<mud::Image256>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "compute", Address(), mud_Circlifier_compute, { { "colour", type<mud::Colour>(),  }, { "scale", type<float>(), Param::Default } }, { &type<vector<mud::Circle>>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, {}, methods, {}, };
	}
	// mud::Fract
	{
		Type& t = type<mud::Fract>();
		static Meta meta = { t, &namspc({ "mud" }), "Fract", sizeof(mud::Fract), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Fract__construct_0, { { "num_tabs", type<size_t>(), Param::Default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Fract, m_num_tabs), type<size_t>(), "nutabs", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "generate", Address(), mud_Fract_generate, { { "num_tabs", type<size_t>(), Param::Default } }, g_qvoid },
			{ t, "regen", Address(), mud_Fract_regen, {}, g_qvoid },
			{ t, "render", Address(), mud_Fract_render, { { "rect", type<mud::Rect>(),  }, { "pattern", type<mud::Pattern>(),  }, { "resolution", type<mud::uvec2>(),  }, { "output_image", type<mud::Image256>(), Param::Output } }, g_qvoid },
			{ t, "render_whole", Address(), mud_Fract_render_whole, { { "pattern", type<mud::Pattern>(),  }, { "resolution", type<mud::uvec2>(),  }, { "output_image", type<mud::Image256>(), Param::Output } }, g_qvoid },
			{ t, "render_grid", Address(), mud_Fract_render_grid, { { "size", type<mud::uvec2>(),  }, { "pattern", type<mud::Pattern>(),  }, { "resolution", type<mud::uvec2>(),  }, { "output_images", type<vector<mud::Image256>>(), Param::Output } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// mud::FractSample
	{
		Type& t = type<mud::FractSample>();
		static Meta meta = { t, &namspc({ "mud" }), "FractSample", sizeof(mud::FractSample), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_FractSample__construct_0, { { "fract", type<mud::Fract>(),  }, { "rect", type<mud::Rect>(),  }, { "resolution", type<mud::uvec2>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Fract>(), "fract", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_FractSample__get_fract },
			{ t, offsetof(mud::FractSample, m_rect), type<mud::Rect>(), "rect", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::FractSample, m_resolution), type<mud::uvec2>(), "resolution", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "render", Address(), mud_FractSample_render, { { "pattern", type<mud::Pattern>(),  }, { "outputImage", type<mud::Image256>(), Param::Output } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// mud::FractTab
	{
		Type& t = type<mud::FractTab>();
		static Meta meta = { t, &namspc({ "mud" }), "FractTab", sizeof(mud::FractTab), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_FractTab__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_FractTab__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Pattern
	{
		Type& t = type<mud::Pattern>();
		static Meta meta = { t, &namspc({ "mud" }), "Pattern", sizeof(mud::Pattern), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Pattern__construct_0, { { "palette", type<mud::Palette>(),  }, { "sampling", type<mud::PatternSampling>(),  }, { "precision", type<float>(), Param::Default }, { "step", type<size_t>(), Param::Default } } },
			{ t, mud_Pattern__construct_1, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Pattern__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
		m.m_types.push_back(&type<mud::Circlifier>());
		m.m_types.push_back(&type<mud::Fract>());
		m.m_types.push_back(&type<mud::FractSample>());
		m.m_types.push_back(&type<mud::FractTab>());
		m.m_types.push_back(&type<mud::Pattern>());
		m.m_types.push_back(&type<mud::PatternSampling>());
		m.m_types.push_back(&type<vector<mud::Image256>>());
		{
			static Function f = { &namspc({ "mud" }), "generate_fract", nullptr, mud_generate_fract_0, { { "resolution", type<mud::uvec2>(),  }, { "pattern", type<mud::Pattern>(),  }, { "output_image", type<mud::Image256>(), Param::Output } }, g_qvoid };
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
