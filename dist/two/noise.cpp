#include <two/infra.h>


#include <climits>

module two.noise;

namespace two
{
	Noise::Noise(int seed)
		: FastNoise(seed)
	{}
	
	float noise_2d(float x, float y, Noise::NoiseType noise_type, float frequency, Noise::Interp interp)
	{
		static Noise n = { randi(INT_MIN, INT_MAX) };
		n.SetNoiseType(noise_type);
		n.SetFrequency(frequency);
		n.SetInterp(interp);
		return n.GetNoise(x, y);
	}

	float noise_3d(float x, float y, float z, Noise::NoiseType noise_type, float frequency, Noise::Interp interp)
	{
		static Noise n = { randi(INT_MIN, INT_MAX) };
		n.SetNoiseType(noise_type);
		n.SetFrequency(frequency);
		n.SetInterp(interp);
		return n.GetNoise(x, y, z);
	}

	float noise_fract_2d(float x, float y, Noise::NoiseType noise_type, float frequency, Noise::Interp interp, 
									  Noise::FractalType fractal_type, int octaves, float lacunarity, float gain)
	{
		static Noise n = { randi(INT_MIN, INT_MAX) };
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
		static Noise n = { randi(INT_MIN, INT_MAX) };
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
module two.jobs;

namespace two
{
	template struct TWO_NOISE_EXPORT vector3d<float>;
}
#endif
module;
module two.noise;

namespace two
{
    // Exported types
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::NoiseType>() { static Type ty("NoiseType", sizeof(two::Noise::NoiseType)); return ty; }
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::Interp>() { static Type ty("Interp", sizeof(two::Noise::Interp)); return ty; }
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::FractalType>() { static Type ty("FractalType", sizeof(two::Noise::FractalType)); return ty; }
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::CellularDistanceFunction>() { static Type ty("CellularDistanceFunction", sizeof(two::Noise::CellularDistanceFunction)); return ty; }
    template <> TWO_NOISE_EXPORT Type& type<two::Noise::CellularReturnType>() { static Type ty("CellularReturnType", sizeof(two::Noise::CellularReturnType)); return ty; }
    
    template <> TWO_NOISE_EXPORT Type& type<two::vector3d<float>>() { static Type ty("vector3d<float>", sizeof(two::vector3d<float>)); return ty; }
    
    template <> TWO_NOISE_EXPORT Type& type<two::Noise>() { static Type ty("Noise", sizeof(two::Noise)); return ty; }
}
