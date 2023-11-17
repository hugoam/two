#include <two/infra.h>

module;
module two.noise.meta;

using namespace two;

void two_Noise_NoiseType__to_string(void* val, string& str) { str = g_enu[type<two::Noise::NoiseType>().m_id]->name(uint32_t((*static_cast<two::Noise::NoiseType*>(val)))); }
void two_Noise_NoiseType__to_value(const string& str, void* val) { (*static_cast<two::Noise::NoiseType*>(val)) = two::Noise::NoiseType(g_enu[type<two::Noise::NoiseType>().m_id]->value(str.c_str())); }
void two_Noise_Interp__to_string(void* val, string& str) { str = g_enu[type<two::Noise::Interp>().m_id]->name(uint32_t((*static_cast<two::Noise::Interp*>(val)))); }
void two_Noise_Interp__to_value(const string& str, void* val) { (*static_cast<two::Noise::Interp*>(val)) = two::Noise::Interp(g_enu[type<two::Noise::Interp>().m_id]->value(str.c_str())); }
void two_Noise_FractalType__to_string(void* val, string& str) { str = g_enu[type<two::Noise::FractalType>().m_id]->name(uint32_t((*static_cast<two::Noise::FractalType*>(val)))); }
void two_Noise_FractalType__to_value(const string& str, void* val) { (*static_cast<two::Noise::FractalType*>(val)) = two::Noise::FractalType(g_enu[type<two::Noise::FractalType>().m_id]->value(str.c_str())); }
void two_Noise_CellularDistanceFunction__to_string(void* val, string& str) { str = g_enu[type<two::Noise::CellularDistanceFunction>().m_id]->name(uint32_t((*static_cast<two::Noise::CellularDistanceFunction*>(val)))); }
void two_Noise_CellularDistanceFunction__to_value(const string& str, void* val) { (*static_cast<two::Noise::CellularDistanceFunction*>(val)) = two::Noise::CellularDistanceFunction(g_enu[type<two::Noise::CellularDistanceFunction>().m_id]->value(str.c_str())); }
void two_Noise_CellularReturnType__to_string(void* val, string& str) { str = g_enu[type<two::Noise::CellularReturnType>().m_id]->name(uint32_t((*static_cast<two::Noise::CellularReturnType*>(val)))); }
void two_Noise_CellularReturnType__to_value(const string& str, void* val) { (*static_cast<two::Noise::CellularReturnType*>(val)) = two::Noise::CellularReturnType(g_enu[type<two::Noise::CellularReturnType>().m_id]->value(str.c_str())); }
size_t two_vector3d_float__size(void* vec) { return (*static_cast<two::vector3d<float>*>(vec)).size(); }
void* two_vector3d_float__at(void* vec, size_t i) { return &(*static_cast<two::vector3d<float>*>(vec))[i]; }
void two_vector3d_float__push(void* vec) { (*static_cast<two::vector3d<float>*>(vec)).emplace_back(); }
void two_vector3d_float__add(void* vec, void* value) { (*static_cast<two::vector3d<float>*>(vec)).push_back(*static_cast<float*>(value)); }
void two_vector3d_float__remove(void* vec, void* value) { vector_remove_any((*static_cast<two::vector3d<float>*>(vec)), *static_cast<float*>(value)); }
void two_noise_2d_0(span<void*> args, void*& result) { (*static_cast<float*>(result)) = two::noise_2d(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<two::Noise::NoiseType*>(args[2]), *static_cast<float*>(args[3]), *static_cast<two::Noise::Interp*>(args[4])); }
void two_noise_3d_1(span<void*> args, void*& result) { (*static_cast<float*>(result)) = two::noise_3d(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<two::Noise::NoiseType*>(args[3]), *static_cast<float*>(args[4]), *static_cast<two::Noise::Interp*>(args[5])); }
void two_noise_fract_2d_2(span<void*> args, void*& result) { (*static_cast<float*>(result)) = two::noise_fract_2d(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<two::Noise::NoiseType*>(args[2]), *static_cast<float*>(args[3]), *static_cast<two::Noise::Interp*>(args[4]), *static_cast<two::Noise::FractalType*>(args[5]), *static_cast<int*>(args[6]), *static_cast<float*>(args[7]), *static_cast<float*>(args[8])); }
void two_noise_fract_3d_3(span<void*> args, void*& result) { (*static_cast<float*>(result)) = two::noise_fract_3d(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<two::Noise::NoiseType*>(args[3]), *static_cast<float*>(args[4]), *static_cast<two::Noise::Interp*>(args[5]), *static_cast<two::Noise::FractalType*>(args[6]), *static_cast<int*>(args[7]), *static_cast<float*>(args[8]), *static_cast<float*>(args[9])); }
void two_noise_field_2d_4(span<void*> args, void*& result) { UNUSED(result);  two::noise_field_2d(*static_cast<two::vector3d<float>*>(args[0]), *static_cast<two::Noise::NoiseType*>(args[1]), *static_cast<float*>(args[2]), *static_cast<two::Noise::Interp*>(args[3])); }
void two_noise_field_3d_5(span<void*> args, void*& result) { UNUSED(result);  two::noise_field_3d(*static_cast<two::vector3d<float>*>(args[0]), *static_cast<two::Noise::NoiseType*>(args[1]), *static_cast<float*>(args[2]), *static_cast<two::Noise::Interp*>(args[3])); }

namespace two
{
	void two_noise_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::Noise::NoiseType>();
		static Meta meta = { t, &namspc({ "two", "Noise" }), "NoiseType", sizeof(two::Noise::NoiseType), TypeClass::Enum };
		static cstring ids[] = { "Value", "ValueFractal", "Perlin", "PerlinFractal", "Simplex", "SimplexFractal", "Cellular", "WhiteNoise", "Cubic", "CubicFractal" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		static two::Noise::NoiseType vars[] = { two::Noise::Value, two::Noise::ValueFractal, two::Noise::Perlin, two::Noise::PerlinFractal, two::Noise::Simplex, two::Noise::SimplexFractal, two::Noise::Cellular, two::Noise::WhiteNoise, two::Noise::Cubic, two::Noise::CubicFractal};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_Noise_NoiseType__to_string,
		                           two_Noise_NoiseType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Noise::Interp>();
		static Meta meta = { t, &namspc({ "two", "Noise" }), "Interp", sizeof(two::Noise::Interp), TypeClass::Enum };
		static cstring ids[] = { "Linear", "Hermite", "Quintic" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::Noise::Interp vars[] = { two::Noise::Linear, two::Noise::Hermite, two::Noise::Quintic};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_Noise_Interp__to_string,
		                           two_Noise_Interp__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Noise::FractalType>();
		static Meta meta = { t, &namspc({ "two", "Noise" }), "FractalType", sizeof(two::Noise::FractalType), TypeClass::Enum };
		static cstring ids[] = { "FBM", "Billow", "RigidMulti" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::Noise::FractalType vars[] = { two::Noise::FBM, two::Noise::Billow, two::Noise::RigidMulti};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_Noise_FractalType__to_string,
		                           two_Noise_FractalType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Noise::CellularDistanceFunction>();
		static Meta meta = { t, &namspc({ "two", "Noise" }), "CellularDistanceFunction", sizeof(two::Noise::CellularDistanceFunction), TypeClass::Enum };
		static cstring ids[] = { "Euclidean", "Manhattan", "Natural" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::Noise::CellularDistanceFunction vars[] = { two::Noise::Euclidean, two::Noise::Manhattan, two::Noise::Natural};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_Noise_CellularDistanceFunction__to_string,
		                           two_Noise_CellularDistanceFunction__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Noise::CellularReturnType>();
		static Meta meta = { t, &namspc({ "two", "Noise" }), "CellularReturnType", sizeof(two::Noise::CellularReturnType), TypeClass::Enum };
		static cstring ids[] = { "CellValue", "NoiseLookup", "Distance", "Distance2", "Distance2Add", "Distance2Sub", "Distance2Mul", "Distance2Div" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		static two::Noise::CellularReturnType vars[] = { two::Noise::CellValue, two::Noise::NoiseLookup, two::Noise::Distance, two::Noise::Distance2, two::Noise::Distance2Add, two::Noise::Distance2Sub, two::Noise::Distance2Mul, two::Noise::Distance2Div};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_Noise_CellularReturnType__to_string,
		                           two_Noise_CellularReturnType__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<two::vector3d<float>>();
		static Meta meta = { t, &namspc({ "two" }), "vector3d<float>", sizeof(two::vector3d<float>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<float>(),
		                             two_vector3d_float__size,
		                             two_vector3d_float__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { two_vector3d_float__push,
		                             two_vector3d_float__add,
		                             two_vector3d_float__remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// two::Noise
	{
		Type& t = type<two::Noise>();
		static Meta meta = { t, &namspc({ "two" }), "Noise", sizeof(two::Noise), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<two::Noise>());
		m.m_types.push_back(&type<two::Noise::NoiseType>());
		m.m_types.push_back(&type<two::Noise::Interp>());
		m.m_types.push_back(&type<two::Noise::FractalType>());
		m.m_types.push_back(&type<two::Noise::CellularDistanceFunction>());
		m.m_types.push_back(&type<two::Noise::CellularReturnType>());
		m.m_types.push_back(&type<two::vector3d<float>>());
		{
			static float frequency_default = 0.01f;
			static two::Noise::Interp interp_default = Noise::Quintic;
			static Function f = { &namspc({ "two" }), "noise_2d", funcptr<float(*)(float, float, two::Noise::NoiseType, float, two::Noise::Interp)>(two::noise_2d), two_noise_2d_0, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "noise_type", type<two::Noise::NoiseType>(),  }, { "frequency", type<float>(), Param::Default, &frequency_default }, { "interp", type<two::Noise::Interp>(), Param::Default, &interp_default } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float frequency_default = 0.01f;
			static two::Noise::Interp interp_default = Noise::Quintic;
			static Function f = { &namspc({ "two" }), "noise_3d", funcptr<float(*)(float, float, float, two::Noise::NoiseType, float, two::Noise::Interp)>(two::noise_3d), two_noise_3d_1, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  }, { "noise_type", type<two::Noise::NoiseType>(),  }, { "frequency", type<float>(), Param::Default, &frequency_default }, { "interp", type<two::Noise::Interp>(), Param::Default, &interp_default } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Noise::Interp interp_default = Noise::Quintic;
			static two::Noise::FractalType fractal_type_default = Noise::FBM;
			static int octaves_default = 3;
			static float lacunarity_default = 2.f;
			static float gain_default = 0.5f;
			static Function f = { &namspc({ "two" }), "noise_fract_2d", funcptr<float(*)(float, float, two::Noise::NoiseType, float, two::Noise::Interp, two::Noise::FractalType, int, float, float)>(two::noise_fract_2d), two_noise_fract_2d_2, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "noise_type", type<two::Noise::NoiseType>(),  }, { "frequency", type<float>(),  }, { "interp", type<two::Noise::Interp>(), Param::Default, &interp_default }, { "fractal_type", type<two::Noise::FractalType>(), Param::Default, &fractal_type_default }, { "octaves", type<int>(), Param::Default, &octaves_default }, { "lacunarity", type<float>(), Param::Default, &lacunarity_default }, { "gain", type<float>(), Param::Default, &gain_default } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Noise::Interp interp_default = Noise::Quintic;
			static two::Noise::FractalType fractal_type_default = Noise::FBM;
			static int octaves_default = 3;
			static float lacunarity_default = 2.f;
			static float gain_default = 0.5f;
			static Function f = { &namspc({ "two" }), "noise_fract_3d", funcptr<float(*)(float, float, float, two::Noise::NoiseType, float, two::Noise::Interp, two::Noise::FractalType, int, float, float)>(two::noise_fract_3d), two_noise_fract_3d_3, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  }, { "noise_type", type<two::Noise::NoiseType>(),  }, { "frequency", type<float>(),  }, { "interp", type<two::Noise::Interp>(), Param::Default, &interp_default }, { "fractal_type", type<two::Noise::FractalType>(), Param::Default, &fractal_type_default }, { "octaves", type<int>(), Param::Default, &octaves_default }, { "lacunarity", type<float>(), Param::Default, &lacunarity_default }, { "gain", type<float>(), Param::Default, &gain_default } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float frequency_default = 0.01f;
			static two::Noise::Interp interp_default = Noise::Quintic;
			static Function f = { &namspc({ "two" }), "noise_field_2d", funcptr<void(*)(two::vector3d<float>&, two::Noise::NoiseType, float, two::Noise::Interp)>(two::noise_field_2d), two_noise_field_2d_4, { { "output_values", type<two::vector3d<float>>(), Param::Output }, { "noise_type", type<two::Noise::NoiseType>(),  }, { "frequency", type<float>(), Param::Default, &frequency_default }, { "interp", type<two::Noise::Interp>(), Param::Default, &interp_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static float frequency_default = 0.01f;
			static two::Noise::Interp interp_default = Noise::Quintic;
			static Function f = { &namspc({ "two" }), "noise_field_3d", funcptr<void(*)(two::vector3d<float>&, two::Noise::NoiseType, float, two::Noise::Interp)>(two::noise_field_3d), two_noise_field_3d_5, { { "output_values", type<two::vector3d<float>>(), Param::Output }, { "noise_type", type<two::Noise::NoiseType>(),  }, { "frequency", type<float>(), Param::Default, &frequency_default }, { "interp", type<two::Noise::Interp>(), Param::Default, &interp_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_noise::two_noise()
		: Module("two::noise", { &two_infra::m(), &two_type::m(), &two_math::m(), &two_geom::m() })
	{
		// setup reflection meta data
		two_noise_meta(*this);
	}
}

#ifdef TWO_NOISE_MODULE
extern "C"
Module& getModule()
{
	return two_noise::m();
}
#endif
