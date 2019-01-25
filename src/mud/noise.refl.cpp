#include <mud/noise.h>
#include <mud/geom.refl.h>
#include <mud/noise.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.noise;
#else
#endif


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
		meta_enum<mud::Noise::CellularDistanceFunction>();
	}
	{
		Type& t = type<mud::Noise::CellularReturnType>();
		static Meta meta = { t, &namspc({ "mud", "Noise" }), "CellularReturnType", sizeof(mud::Noise::CellularReturnType), TypeClass::Enum };
		static cstring ids[] = { "CellValue", "NoiseLookup", "Distance", "Distance2", "Distance2Add", "Distance2Sub", "Distance2Mul", "Distance2Div" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		static mud::Noise::CellularReturnType vars[] = { mud::Noise::CellValue, mud::Noise::NoiseLookup, mud::Noise::Distance, mud::Noise::Distance2, mud::Noise::Distance2Add, mud::Noise::Distance2Sub, mud::Noise::Distance2Mul, mud::Noise::Distance2Div};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Noise::CellularReturnType>();
	}
	{
		Type& t = type<mud::Noise::FractalType>();
		static Meta meta = { t, &namspc({ "mud", "Noise" }), "FractalType", sizeof(mud::Noise::FractalType), TypeClass::Enum };
		static cstring ids[] = { "FBM", "Billow", "RigidMulti" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Noise::FractalType vars[] = { mud::Noise::FBM, mud::Noise::Billow, mud::Noise::RigidMulti};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Noise::FractalType>();
	}
	{
		Type& t = type<mud::Noise::Interp>();
		static Meta meta = { t, &namspc({ "mud", "Noise" }), "Interp", sizeof(mud::Noise::Interp), TypeClass::Enum };
		static cstring ids[] = { "Linear", "Hermite", "Quintic" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Noise::Interp vars[] = { mud::Noise::Linear, mud::Noise::Hermite, mud::Noise::Quintic};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Noise::Interp>();
	}
	{
		Type& t = type<mud::Noise::NoiseType>();
		static Meta meta = { t, &namspc({ "mud", "Noise" }), "NoiseType", sizeof(mud::Noise::NoiseType), TypeClass::Enum };
		static cstring ids[] = { "Value", "ValueFractal", "Perlin", "PerlinFractal", "Simplex", "SimplexFractal", "Cellular", "WhiteNoise", "Cubic", "CubicFractal" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		static mud::Noise::NoiseType vars[] = { mud::Noise::Value, mud::Noise::ValueFractal, mud::Noise::Perlin, mud::Noise::PerlinFractal, mud::Noise::Simplex, mud::Noise::SimplexFractal, mud::Noise::Cellular, mud::Noise::WhiteNoise, mud::Noise::Cubic, mud::Noise::CubicFractal};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Noise::NoiseType>();
	}
	
	// Sequences
	
	// mud::Noise
	{
		Type& t = type<mud::Noise>();
		static Meta meta = { t, &namspc({ "mud" }), "Noise", sizeof(mud::Noise), TypeClass::Object };
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
		meta_class<mud::Noise>();
	}
	// mud::array3d<float>
	{
		Type& t = type<mud::array3d<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "array3d<float>", sizeof(mud::array3d<float>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<vector<float>>() },
			{ base_offset<mud::array3d<float>, vector<float>>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::array3d<float>>(ref)) mud::array3d<float>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::array3d<float>>(ref)) mud::array3d<float>(val<mud::array3d<float>>(other)); } }
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
		meta_class<mud::array3d<float>>();
	}
		m.m_types.push_back(&type<mud::Noise::CellularDistanceFunction>());
		m.m_types.push_back(&type<mud::Noise::CellularReturnType>());
		m.m_types.push_back(&type<mud::Noise::FractalType>());
		m.m_types.push_back(&type<mud::Noise::Interp>());
		m.m_types.push_back(&type<mud::Noise>());
		m.m_types.push_back(&type<mud::Noise::NoiseType>());
		m.m_types.push_back(&type<mud::array3d<float>>());
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::noise_2d(val<float>(args[0]), val<float>(args[1]), val<mud::Noise::NoiseType>(args[2]), val<float>(args[3]), val<mud::Noise::Interp>(args[4])); };
			vector<Param> params = { { "x", var(float()) }, { "y", var(float()) }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float(0.01f)), Param::Default }, { "interp", var(mud::Noise::Interp(Noise::Quintic)), Param::Default } };
			static Function f = { &namspc({ "mud" }), "noise_2d", funcptr<float(*)(float, float, mud::Noise::NoiseType, float, mud::Noise::Interp)>(&mud::noise_2d), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::noise_3d(val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<mud::Noise::NoiseType>(args[3]), val<float>(args[4]), val<mud::Noise::Interp>(args[5])); };
			vector<Param> params = { { "x", var(float()) }, { "y", var(float()) }, { "z", var(float()) }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float(0.01f)), Param::Default }, { "interp", var(mud::Noise::Interp(Noise::Quintic)), Param::Default } };
			static Function f = { &namspc({ "mud" }), "noise_3d", funcptr<float(*)(float, float, float, mud::Noise::NoiseType, float, mud::Noise::Interp)>(&mud::noise_3d), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::noise_fract_2d(val<float>(args[0]), val<float>(args[1]), val<mud::Noise::NoiseType>(args[2]), val<float>(args[3]), val<mud::Noise::Interp>(args[4]), val<mud::Noise::FractalType>(args[5]), val<int>(args[6]), val<float>(args[7]), val<float>(args[8])); };
			vector<Param> params = { { "x", var(float()) }, { "y", var(float()) }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float()) }, { "interp", var(mud::Noise::Interp(Noise::Quintic)), Param::Default }, { "fractal_type", var(mud::Noise::FractalType(Noise::FBM)), Param::Default }, { "octaves", var(int(3)), Param::Default }, { "lacunarity", var(float(2.f)), Param::Default }, { "gain", var(float(0.5f)), Param::Default } };
			static Function f = { &namspc({ "mud" }), "noise_fract_2d", funcptr<float(*)(float, float, mud::Noise::NoiseType, float, mud::Noise::Interp, mud::Noise::FractalType, int, float, float)>(&mud::noise_fract_2d), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::noise_fract_3d(val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<mud::Noise::NoiseType>(args[3]), val<float>(args[4]), val<mud::Noise::Interp>(args[5]), val<mud::Noise::FractalType>(args[6]), val<int>(args[7]), val<float>(args[8]), val<float>(args[9])); };
			vector<Param> params = { { "x", var(float()) }, { "y", var(float()) }, { "z", var(float()) }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float()) }, { "interp", var(mud::Noise::Interp(Noise::Quintic)), Param::Default }, { "fractal_type", var(mud::Noise::FractalType(Noise::FBM)), Param::Default }, { "octaves", var(int(3)), Param::Default }, { "lacunarity", var(float(2.f)), Param::Default }, { "gain", var(float(0.5f)), Param::Default } };
			static Function f = { &namspc({ "mud" }), "noise_fract_3d", funcptr<float(*)(float, float, float, mud::Noise::NoiseType, float, mud::Noise::Interp, mud::Noise::FractalType, int, float, float)>(&mud::noise_fract_3d), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::noise_field_2d(val<mud::array3d<float>>(args[0]), val<mud::Noise::NoiseType>(args[1]), val<float>(args[2]), val<mud::Noise::Interp>(args[3])); };
			vector<Param> params = { { "output_values", var(mud::array3d<float>()), Param::Output }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float(0.01f)), Param::Default }, { "interp", var(mud::Noise::Interp(Noise::Quintic)), Param::Default } };
			static Function f = { &namspc({ "mud" }), "noise_field_2d", funcptr<void(*)(mud::array3d<float>&, mud::Noise::NoiseType, float, mud::Noise::Interp)>(&mud::noise_field_2d), func, params, Var() };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::noise_field_3d(val<mud::array3d<float>>(args[0]), val<mud::Noise::NoiseType>(args[1]), val<float>(args[2]), val<mud::Noise::Interp>(args[3])); };
			vector<Param> params = { { "output_values", var(mud::array3d<float>()), Param::Output }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float(0.01f)), Param::Default }, { "interp", var(mud::Noise::Interp(Noise::Quintic)), Param::Default } };
			static Function f = { &namspc({ "mud" }), "noise_field_3d", funcptr<void(*)(mud::array3d<float>&, mud::Noise::NoiseType, float, mud::Noise::Interp)>(&mud::noise_field_3d), func, params, Var() };
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
