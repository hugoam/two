//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.noise;
#else
#include <noise/Noise.h>
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

	void noise_field_2d(array_3d<float>& output_values, Noise::NoiseType noise_type, float frequency, Noise::Interp interp)
	{
		for(size_t x = 0; x < output_values.m_x; ++x)
			for(size_t y = 0; y < output_values.m_y; ++y)
				{
					output_values.at(x, y) = noise_2d(float(x) / 1.f, float(y) / 1.f, noise_type, frequency, interp);
				}
	}

	void noise_field_3d(array_3d<float>& output_values, Noise::NoiseType noise_type, float frequency, Noise::Interp interp)
	{
		for(size_t x = 0; x < output_values.m_x; ++x)
			for(size_t y = 0; y < output_values.m_y; ++y)
				for(size_t z = 0; z < output_values.m_z; ++z)
				{
					output_values.at(x, y, z) = noise_3d(float(x) / 1.f, float(y) / 1.f, float(z) / 1.f, noise_type, frequency, interp);
				}
	}
}
