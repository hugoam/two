#include <two/geom.refl.h>
#include <two/infra.refl.h>
#include <two/type.refl.h>
#include <two/fract.h>
#include <two/refl.h>
#include <two/math.refl.h>
#include <two/fract.refl.h>
#include <two/infra.h>
#include <two/type.h>


#ifdef TWO_MODULES
module two.fract;
#else
#include <cstddef>
#include <stl/new.h>
#endif


using namespace two;

void two_PatternSampling__to_string(void* val, string& str) { str = g_enu[type<two::PatternSampling>().m_id]->name(uint32_t((*static_cast<two::PatternSampling*>(val)))); }
void two_PatternSampling__to_value(const string& str, void* val) { (*static_cast<two::PatternSampling*>(val)) = two::PatternSampling(g_enu[type<two::PatternSampling>().m_id]->value(str.c_str())); }
size_t stl_vector_two_Image256__size(void* vec) { return (*static_cast<stl::vector<two::Image256>*>(vec)).size(); }
void* stl_vector_two_Image256__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Image256>*>(vec))[i]; }
void stl_vector_two_Image256__push(void* vec) { (*static_cast<stl::vector<two::Image256>*>(vec)).emplace_back(); }
void stl_vector_two_Image256__add(void* vec, void* value) { (*static_cast<stl::vector<two::Image256>*>(vec)).push_back(*static_cast<two::Image256*>(value)); }
void stl_vector_two_Image256__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Image256>*>(vec)), *static_cast<two::Image256*>(value)); }
void two_Circlifier__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Circlifier( *static_cast<two::Image256*>(args[0]) ); }
void two_Circlifier_compute(void* object, span<void*> args, void*& result) { (*static_cast<stl::vector<two::Circle>*>(result)) = (*static_cast<two::Circlifier*>(object)).compute(*static_cast<two::Colour*>(args[0]), *static_cast<float*>(args[1])); }
void two_Pattern__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Pattern( *static_cast<two::Palette*>(args[0]), *static_cast<two::PatternSampling*>(args[1]), *static_cast<float*>(args[2]), *static_cast<size_t*>(args[3]) ); }
void two_Pattern__construct_1(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Pattern(  ); }
void two_Pattern__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Pattern((*static_cast<two::Pattern*>(other))); }
void two_FractTab__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::FractTab(  ); }
void two_FractTab__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::FractTab((*static_cast<two::FractTab*>(other))); }
void two_Fract__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Fract( *static_cast<size_t*>(args[0]) ); }
void two_Fract_generate(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Fract*>(object)).generate(*static_cast<size_t*>(args[0])); }
void two_Fract_regen(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Fract*>(object)).regen(); }
void two_Fract_render(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Fract*>(object)).render(*static_cast<two::Rect*>(args[0]), *static_cast<two::Pattern*>(args[1]), *static_cast<two::uvec2*>(args[2]), *static_cast<two::Image256*>(args[3])); }
void two_Fract_render_whole(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Fract*>(object)).render_whole(*static_cast<two::Pattern*>(args[0]), *static_cast<two::uvec2*>(args[1]), *static_cast<two::Image256*>(args[2])); }
void two_Fract_render_grid(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Fract*>(object)).render_grid(*static_cast<two::uvec2*>(args[0]), *static_cast<two::Pattern*>(args[1]), *static_cast<two::uvec2*>(args[2]), *static_cast<stl::vector<two::Image256>*>(args[3])); }
void two_FractSample__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::FractSample( *static_cast<two::Fract*>(args[0]), *static_cast<two::Rect*>(args[1]), *static_cast<two::uvec2*>(args[2]) ); }
void* two_FractSample__get_fract(void* object) { return &(*static_cast<two::FractSample*>(object)).m_fract; }
void two_FractSample_render(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::FractSample*>(object)).render(*static_cast<two::Pattern*>(args[0]), *static_cast<two::Image256*>(args[1])); }
void two_generate_fract_0(span<void*> args, void*& result) { UNUSED(result);  two::generate_fract(*static_cast<two::uvec2*>(args[0]), *static_cast<two::Pattern*>(args[1]), *static_cast<two::Image256*>(args[2])); }

namespace two
{
	void two_fract_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::PatternSampling>();
		static Meta meta = { t, &namspc({ "two" }), "PatternSampling", sizeof(two::PatternSampling), TypeClass::Enum };
		static cstring ids[] = { "X", "XY", "Depth" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::PatternSampling vars[] = { two::PatternSampling::X, two::PatternSampling::XY, two::PatternSampling::Depth};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_PatternSampling__to_string,
		                           two_PatternSampling__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<stl::vector<two::Image256>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Image256>", sizeof(stl::vector<two::Image256>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Image256>(),
		                             stl_vector_two_Image256__size,
		                             stl_vector_two_Image256__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Image256__push,
		                             stl_vector_two_Image256__add,
		                             stl_vector_two_Image256__remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// two::Circlifier
	{
		Type& t = type<two::Circlifier>();
		static Meta meta = { t, &namspc({ "two" }), "Circlifier", sizeof(two::Circlifier), TypeClass::Object };
		// bases
		// defaults
		static float compute_0_scale_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Circlifier__construct_0, { { "image", type<two::Image256>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "compute", Address(), two_Circlifier_compute, { { "colour", type<two::Colour>(),  }, { "scale", type<float>(), Param::Default, &compute_0_scale_default } }, { &type<stl::vector<two::Circle>>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, {}, methods, {}, };
	}
	// two::Pattern
	{
		Type& t = type<two::Pattern>();
		static Meta meta = { t, &namspc({ "two" }), "Pattern", sizeof(two::Pattern), TypeClass::Struct };
		// bases
		// defaults
		static float construct_0_precision_default = 1.f;
		static size_t construct_0_step_default = 1;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Pattern__construct_0, { { "palette", type<two::Palette>(),  }, { "sampling", type<two::PatternSampling>(),  }, { "precision", type<float>(), Param::Default, &construct_0_precision_default }, { "step", type<size_t>(), Param::Default, &construct_0_step_default } } },
			{ t, two_Pattern__construct_1, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Pattern__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::FractTab
	{
		Type& t = type<two::FractTab>();
		static Meta meta = { t, &namspc({ "two" }), "FractTab", sizeof(two::FractTab), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_FractTab__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_FractTab__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Fract
	{
		Type& t = type<two::Fract>();
		static Meta meta = { t, &namspc({ "two" }), "Fract", sizeof(two::Fract), TypeClass::Object };
		// bases
		// defaults
		static size_t construct_0_num_tabs_default = 75;
		static size_t generate_0_num_tabs_default = 75;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Fract__construct_0, { { "num_tabs", type<size_t>(), Param::Default, &construct_0_num_tabs_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Fract, m_num_tabs), type<size_t>(), "nutabs", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "generate", Address(), two_Fract_generate, { { "num_tabs", type<size_t>(), Param::Default, &generate_0_num_tabs_default } }, g_qvoid },
			{ t, "regen", Address(), two_Fract_regen, {}, g_qvoid },
			{ t, "render", Address(), two_Fract_render, { { "rect", type<two::Rect>(),  }, { "pattern", type<two::Pattern>(),  }, { "resolution", type<two::uvec2>(),  }, { "output_image", type<two::Image256>(), Param::Output } }, g_qvoid },
			{ t, "render_whole", Address(), two_Fract_render_whole, { { "pattern", type<two::Pattern>(),  }, { "resolution", type<two::uvec2>(),  }, { "output_image", type<two::Image256>(), Param::Output } }, g_qvoid },
			{ t, "render_grid", Address(), two_Fract_render_grid, { { "size", type<two::uvec2>(),  }, { "pattern", type<two::Pattern>(),  }, { "resolution", type<two::uvec2>(),  }, { "output_images", type<stl::vector<two::Image256>>(), Param::Output } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// two::FractSample
	{
		Type& t = type<two::FractSample>();
		static Meta meta = { t, &namspc({ "two" }), "FractSample", sizeof(two::FractSample), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_FractSample__construct_0, { { "fract", type<two::Fract>(),  }, { "rect", type<two::Rect>(),  }, { "resolution", type<two::uvec2>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Fract>(), "fract", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_FractSample__get_fract },
			{ t, offsetof(two::FractSample, m_rect), type<two::Rect>(), "rect", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::FractSample, m_resolution), type<two::uvec2>(), "resolution", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "render", Address(), two_FractSample_render, { { "pattern", type<two::Pattern>(),  }, { "outputImage", type<two::Image256>(), Param::Output } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	
	
		m.m_types.push_back(&type<stl::vector<two::Image256>>());
		m.m_types.push_back(&type<two::Circlifier>());
		m.m_types.push_back(&type<two::PatternSampling>());
		m.m_types.push_back(&type<two::Pattern>());
		m.m_types.push_back(&type<two::FractTab>());
		m.m_types.push_back(&type<two::Fract>());
		m.m_types.push_back(&type<two::FractSample>());
		{
			static Function f = { &namspc({ "two" }), "generate_fract", funcptr<void(*)(two::uvec2, const two::Pattern&, two::Image256&)>(two::generate_fract), two_generate_fract_0, { { "resolution", type<two::uvec2>(),  }, { "pattern", type<two::Pattern>(),  }, { "output_image", type<two::Image256>(), Param::Output } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_fract::two_fract()
		: Module("two::fract", { &two_infra::m(), &two_type::m(), &two_math::m(), &two_geom::m() })
	{
		// setup reflection meta data
		two_fract_meta(*this);
	}
}

#ifdef TWO_FRACT_MODULE
extern "C"
Module& getModule()
{
	return two_fract::m();
}
#endif
