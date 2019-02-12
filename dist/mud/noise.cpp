#include <mud/noise.h>
#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>


#include <climits>

#ifdef MUD_MODULES
module mud.noise;
#else
#endif

namespace mud
{
	Noise::Noise(int seed)
		: FastNoise(seed)
	{}
	
	float noise_2d(float x, float y, Noise::NoiseType noise_type, float frequency, Noise::Interp interp)
	{
		static Noise n = { random_integer(INT_MIN, INT_MAX) };
		n.SetNoiseType(noise_type);
		n.SetFrequency(frequency);
		n.SetInterp(interp);
		return n.GetNoise(x, y);
	}

	float noise_3d(float x, float y, float z, Noise::NoiseType noise_type, float frequency, Noise::Interp interp)
	{
		static Noise n = { random_integer(INT_MIN, INT_MAX) };
		n.SetNoiseType(noise_type);
		n.SetFrequency(frequency);
		n.SetInterp(interp);
		return n.GetNoise(x, y, z);
	}

	float noise_fract_2d(float x, float y, Noise::NoiseType noise_type, float frequency, Noise::Interp interp, 
									  Noise::FractalType fractal_type, int octaves, float lacunarity, float gain)
	{
		static Noise n = { random_integer(INT_MIN, INT_MAX) };
		n.SetNoiseType(noise_type);
		n.SetFrequency(frequency);
		n.SetInterp(interp);
		n.SetFractalType(fractal_type);
		n.SetFractalOctaves(octaves);
		n.SetFractalLacunarity(lacunarity);
		n.SetFractalGain(gain);
		return n.GetNoise(x, y);
	}

	float noise_fract_3d(float x, float y, float z, Noise::NoiseType noise_type, float frequency, Noise::Interp interp,
									  Noise::FractalType fractal_type, int octaves, float lacunarity, float gain)
	{
		static Noise n = { random_integer(INT_MIN, INT_MAX) };
		n.SetNoiseType(noise_type);
		n.SetFrequency(frequency);
		n.SetInterp(interp);
		n.SetFractalType(fractal_type);
		n.SetFractalOctaves(octaves);
		n.SetFractalLacunarity(lacunarity);
		n.SetFractalGain(gain);
		return n.GetNoise(x, y, z);
	}

	void noise_field_2d(vector3d<float>& output_values, Noise::NoiseType noise_type, float frequency, Noise::Interp interp)
	{
		for(size_t x = 0; x < output_values.m_x; ++x)
			for(size_t y = 0; y < output_values.m_y; ++y)
				{
					output_values.at(x, y) = noise_2d(float(x) / 1.f, float(y) / 1.f, noise_type, frequency, interp);
				}
	}

	void noise_field_3d(vector3d<float>& output_values, Noise::NoiseType noise_type, float frequency, Noise::Interp interp)
	{
		for(size_t x = 0; x < output_values.m_x; ++x)
			for(size_t y = 0; y < output_values.m_y; ++y)
				for(size_t z = 0; z < output_values.m_z; ++z)
				{
					output_values.at(x, y, z) = noise_3d(float(x) / 1.f, float(y) / 1.f, float(z) / 1.f, noise_type, frequency, interp);
				}
	}
}
#ifndef USE_STL
#ifdef MUD_MODULES
module mud.jobs;
#else
#include <stl/vector.hpp>
#endif

namespace mud
{
	template struct MUD_NOISE_EXPORT vector3d<float>;
}
#endif

#ifdef MUD_MODULES
module mud.noise;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::CellularDistanceFunction>() { static Type ty("CellularDistanceFunction", sizeof(mud::Noise::CellularDistanceFunction)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::CellularReturnType>() { static Type ty("CellularReturnType", sizeof(mud::Noise::CellularReturnType)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::FractalType>() { static Type ty("FractalType", sizeof(mud::Noise::FractalType)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::Interp>() { static Type ty("Interp", sizeof(mud::Noise::Interp)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise::NoiseType>() { static Type ty("NoiseType", sizeof(mud::Noise::NoiseType)); return ty; }
    
    
    template <> MUD_NOISE_EXPORT Type& type<mud::Noise>() { static Type ty("Noise", sizeof(mud::Noise)); return ty; }
    template <> MUD_NOISE_EXPORT Type& type<mud::vector3d<float>>() { static Type ty("vector3d<float>", sizeof(mud::vector3d<float>)); return ty; }
}
