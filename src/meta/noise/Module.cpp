#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.noise;
#else
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/noise/Module.h>
#include <meta/noise/Convert.h>
#endif

#include <noise/Api.h>

using namespace mud;

void mud_Noise_CellularDistanceFunction__to_string(void* val, string& str) { str = g_enu[type<mud::Noise::CellularDistanceFunction>().m_id]->name(uint32_t((*static_cast<mud::Noise::CellularDistanceFunction*>(val)))); }
void mud_Noise_CellularDistanceFunction__to_value(const string& str, void* val) { (*static_cast<mud::Noise::CellularDistanceFunction*>(val)) = mud::Noise::CellularDistanceFunction(g_enu[type<mud::Noise::CellularDistanceFunction>().m_id]->value(str.c_str())); }
void mud_Noise_CellularReturnType__to_string(void* val, string& str) { str = g_enu[type<mud::Noise::CellularReturnType>().m_id]->name(uint32_t((*static_cast<mud::Noise::CellularReturnType*>(val)))); }
void mud_Noise_CellularReturnType__to_value(const string& str, void* val) { (*static_cast<mud::Noise::CellularReturnType*>(val)) = mud::Noise::CellularReturnType(g_enu[type<mud::Noise::CellularReturnType>().m_id]->value(str.c_str())); }
void mud_Noise_FractalType__to_string(void* val, string& str) { str = g_enu[type<mud::Noise::FractalType>().m_id]->name(uint32_t((*static_cast<mud::Noise::FractalType*>(val)))); }
void mud_Noise_FractalType__to_value(const string& str, void* val) { (*static_cast<mud::Noise::FractalType*>(val)) = mud::Noise::FractalType(g_enu[type<mud::Noise::FractalType>().m_id]->value(str.c_str())); }
void mud_Noise_Interp__to_string(void* val, string& str) { str = g_enu[type<mud::Noise::Interp>().m_id]->name(uint32_t((*static_cast<mud::Noise::Interp*>(val)))); }
void mud_Noise_Interp__to_value(const string& str, void* val) { (*static_cast<mud::Noise::Interp*>(val)) = mud::Noise::Interp(g_enu[type<mud::Noise::Interp>().m_id]->value(str.c_str())); }
void mud_Noise_NoiseType__to_string(void* val, string& str) { str = g_enu[type<mud::Noise::NoiseType>().m_id]->name(uint32_t((*static_cast<mud::Noise::NoiseType*>(val)))); }
void mud_Noise_NoiseType__to_value(const string& str, void* val) { (*static_cast<mud::Noise::NoiseType*>(val)) = mud::Noise::NoiseType(g_enu[type<mud::Noise::NoiseType>().m_id]->value(str.c_str())); }
void mud_array3d_float___construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::array3d<float>*>(ref))) mud::array3d<float>(  ); }
void mud_array3d_float___copy_construct(void* ref, void* other) { new(&(*static_cast<mud::array3d<float>*>(ref))) mud::array3d<float>((*static_cast<mud::array3d<float>*>(other))); }
void mud_noise_2d_0(array<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::noise_2d(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Noise::NoiseType*>(args[2]), *static_cast<float*>(args[3]), *static_cast<mud::Noise::Interp*>(args[4])); }
void mud_noise_3d_1(array<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::noise_3d(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<mud::Noise::NoiseType*>(args[3]), *static_cast<float*>(args[4]), *static_cast<mud::Noise::Interp*>(args[5])); }
void mud_noise_fract_2d_2(array<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::noise_fract_2d(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Noise::NoiseType*>(args[2]), *static_cast<float*>(args[3]), *static_cast<mud::Noise::Interp*>(args[4]), *static_cast<mud::Noise::FractalType*>(args[5]), *static_cast<int*>(args[6]), *static_cast<float*>(args[7]), *static_cast<float*>(args[8])); }
void mud_noise_fract_3d_3(array<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::noise_fract_3d(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<mud::Noise::NoiseType*>(args[3]), *static_cast<float*>(args[4]), *static_cast<mud::Noise::Interp*>(args[5]), *static_cast<mud::Noise::FractalType*>(args[6]), *static_cast<int*>(args[7]), *static_cast<float*>(args[8]), *static_cast<float*>(args[9])); }
void mud_noise_field_2d_4(array<void*> args, void*& result) { UNUSED(result);  mud::noise_field_2d(*static_cast<mud::array3d<float>*>(args[0]), *static_cast<mud::Noise::NoiseType*>(args[1]), *static_cast<float*>(args[2]), *static_cast<mud::Noise::Interp*>(args[3])); }
void mud_noise_field_3d_5(array<void*> args, void*& result) { UNUSED(result);  mud::noise_field_3d(*static_cast<mud::array3d<float>*>(args[0]), *static_cast<mud::Noise::NoiseType*>(args[1]), *static_cast<float*>(args[2]), *static_cast<mud::Noise::Interp*>(args[3])); }

namespace mud
{
	void mud_noise_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::Noise::CellularDistanceFunction>();
		static Meta meta = { t, &namspc({ "mud", "Noise" }), "CellularDistanceFunction", sizeof(mud::Noise::CellularDistanceFunction), TypeClass::Enum };
		static cstring ids[] = { "Euclidean", "Manhattan", "Natural" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Noise::CellularDistanceFunction vars[] = { mud::Noise::Euclidean, mud::Noise::Manhattan, mud::Noise::Natural};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Noise_CellularDistanceFunction__to_string,
		                           mud_Noise_CellularDistanceFunction__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Noise::CellularReturnType>();
		static Meta meta = { t, &namspc({ "mud", "Noise" }), "CellularReturnType", sizeof(mud::Noise::CellularReturnType), TypeClass::Enum };
		static cstring ids[] = { "CellValue", "NoiseLookup", "Distance", "Distance2", "Distance2Add", "Distance2Sub", "Distance2Mul", "Distance2Div" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		static mud::Noise::CellularReturnType vars[] = { mud::Noise::CellValue, mud::Noise::NoiseLookup, mud::Noise::Distance, mud::Noise::Distance2, mud::Noise::Distance2Add, mud::Noise::Distance2Sub, mud::Noise::Distance2Mul, mud::Noise::Distance2Div};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Noise_CellularReturnType__to_string,
		                           mud_Noise_CellularReturnType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Noise::FractalType>();
		static Meta meta = { t, &namspc({ "mud", "Noise" }), "FractalType", sizeof(mud::Noise::FractalType), TypeClass::Enum };
		static cstring ids[] = { "FBM", "Billow", "RigidMulti" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Noise::FractalType vars[] = { mud::Noise::FBM, mud::Noise::Billow, mud::Noise::RigidMulti};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Noise_FractalType__to_string,
		                           mud_Noise_FractalType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Noise::Interp>();
		static Meta meta = { t, &namspc({ "mud", "Noise" }), "Interp", sizeof(mud::Noise::Interp), TypeClass::Enum };
		static cstring ids[] = { "Linear", "Hermite", "Quintic" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Noise::Interp vars[] = { mud::Noise::Linear, mud::Noise::Hermite, mud::Noise::Quintic};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Noise_Interp__to_string,
		                           mud_Noise_Interp__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Noise::NoiseType>();
		static Meta meta = { t, &namspc({ "mud", "Noise" }), "NoiseType", sizeof(mud::Noise::NoiseType), TypeClass::Enum };
		static cstring ids[] = { "Value", "ValueFractal", "Perlin", "PerlinFractal", "Simplex", "SimplexFractal", "Cellular", "WhiteNoise", "Cubic", "CubicFractal" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		static mud::Noise::NoiseType vars[] = { mud::Noise::Value, mud::Noise::ValueFractal, mud::Noise::Perlin, mud::Noise::PerlinFractal, mud::Noise::Simplex, mud::Noise::SimplexFractal, mud::Noise::Cellular, mud::Noise::WhiteNoise, mud::Noise::Cubic, mud::Noise::CubicFractal};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Noise_NoiseType__to_string,
		                           mud_Noise_NoiseType__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// mud::Noise
	{
		Type& t = type<mud::Noise>();
		static Meta meta = { t, &namspc({ "mud" }), "Noise", sizeof(mud::Noise), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::array3d<float>
	{
		Type& t = type<mud::array3d<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "array3d<float>", sizeof(mud::array3d<float>), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<vector<float>>() };
		static size_t bases_offsets[] = { base_offset<mud::array3d<float>, vector<float>>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_array3d_float___construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_array3d_float___copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
		m.m_types.push_back(&type<mud::Noise::CellularDistanceFunction>());
		m.m_types.push_back(&type<mud::Noise::CellularReturnType>());
		m.m_types.push_back(&type<mud::Noise::FractalType>());
		m.m_types.push_back(&type<mud::Noise::Interp>());
		m.m_types.push_back(&type<mud::Noise>());
		m.m_types.push_back(&type<mud::Noise::NoiseType>());
		m.m_types.push_back(&type<mud::array3d<float>>());
		{
			static Function f = { &namspc({ "mud" }), "noise_2d", nullptr, mud_noise_2d_0, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "noise_type", type<mud::Noise::NoiseType>(),  }, { "frequency", type<float>(), Param::Default }, { "interp", type<mud::Noise::Interp>(), Param::Default } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "noise_3d", nullptr, mud_noise_3d_1, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  }, { "noise_type", type<mud::Noise::NoiseType>(),  }, { "frequency", type<float>(), Param::Default }, { "interp", type<mud::Noise::Interp>(), Param::Default } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "noise_fract_2d", nullptr, mud_noise_fract_2d_2, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "noise_type", type<mud::Noise::NoiseType>(),  }, { "frequency", type<float>(),  }, { "interp", type<mud::Noise::Interp>(), Param::Default }, { "fractal_type", type<mud::Noise::FractalType>(), Param::Default }, { "octaves", type<int>(), Param::Default }, { "lacunarity", type<float>(), Param::Default }, { "gain", type<float>(), Param::Default } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "noise_fract_3d", nullptr, mud_noise_fract_3d_3, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  }, { "noise_type", type<mud::Noise::NoiseType>(),  }, { "frequency", type<float>(),  }, { "interp", type<mud::Noise::Interp>(), Param::Default }, { "fractal_type", type<mud::Noise::FractalType>(), Param::Default }, { "octaves", type<int>(), Param::Default }, { "lacunarity", type<float>(), Param::Default }, { "gain", type<float>(), Param::Default } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "noise_field_2d", nullptr, mud_noise_field_2d_4, { { "output_values", type<mud::array3d<float>>(), Param::Output }, { "noise_type", type<mud::Noise::NoiseType>(),  }, { "frequency", type<float>(), Param::Default }, { "interp", type<mud::Noise::Interp>(), Param::Default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "noise_field_3d", nullptr, mud_noise_field_3d_5, { { "output_values", type<mud::array3d<float>>(), Param::Output }, { "noise_type", type<mud::Noise::NoiseType>(),  }, { "frequency", type<float>(), Param::Default }, { "interp", type<mud::Noise::Interp>(), Param::Default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_noise::mud_noise()
		: Module("mud::noise", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_geom::m() })
	{
		// setup reflection meta data
		mud_noise_meta(*this);
	}
}

#ifdef MUD_NOISE_MODULE
extern "C"
Module& getModule()
{
		return mud_noise::m();
}
#endif
