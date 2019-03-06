#pragma once

#ifndef MUD_MODULES
#include <math/Grid.h>
#endif
#include <noise/Forward.h>

#ifndef MUD_META_GENERATOR
export_ class MUD_NOISE_EXPORT FastNoise;
#include <FastNoise.h>
#endif

namespace mud
{
	//using fnScalar = FN_DECIMAL;

#ifdef MUD_META_GENERATOR
	export_ class refl_ MUD_NOISE_EXPORT Noise
	{
	public:
		export_ enum refl_ NoiseType { Value, ValueFractal, Perlin, PerlinFractal, Simplex, SimplexFractal, Cellular, WhiteNoise, Cubic, CubicFractal };
		export_ enum refl_ Interp { Linear, Hermite, Quintic };
		export_ enum refl_ FractalType { FBM, Billow, RigidMulti };
		export_ enum refl_ CellularDistanceFunction { Euclidean, Manhattan, Natural };
		export_ enum refl_ CellularReturnType { CellValue, NoiseLookup, Distance, Distance2, Distance2Add, Distance2Sub, Distance2Mul, Distance2Div };
#else
	export_ class refl_ MUD_NOISE_EXPORT Noise : public FastNoise
	{
#endif
	public:
		Noise(int seed = 1337);

#if 0 //def MUD_META_GENERATOR
		meth_ float GetNoise(float x, float y) const;
		meth_ float GetNoise(float x, float y, float z) const;

		attr_ NoiseType m_noiseType;

		attr_ int m_seed;
		attr_ float m_frequency;
		attr_ Interp m_interp;

		// fractal
		attr_ FractalType m_fractalType;
		attr_ int m_octaves;
		attr_ float m_lacunarity;
		attr_ float m_gain;

		// cellular
		attr_ CellularDistanceFunction m_cellularDistanceFunction;
		attr_ CellularReturnType m_cellularReturnType;
		attr_ FastNoise* m_cellularNoiseLookup;
		attr_ float m_cellularJitter;

		attr_ int m_cellularDistanceIndex0;
		attr_ int m_cellularDistanceIndex1;

		// warp
		attr_ float m_gradientPerturbAmp;
#endif
	};

	MUD_NOISE_EXPORT func_ float noise_2d(float x, float y, Noise::NoiseType noise_type, float frequency = 0.01f, Noise::Interp interp = Noise::Quintic);
	MUD_NOISE_EXPORT func_ float noise_3d(float x, float y, float z, Noise::NoiseType noise_type, float frequency = 0.01f, Noise::Interp interp = Noise::Quintic);

	MUD_NOISE_EXPORT func_ float noise_fract_2d(float x, float y, Noise::NoiseType noise_type, float frequency, Noise::Interp interp = Noise::Quintic,
											    Noise::FractalType fractal_type = Noise::FBM, int octaves = 3, float lacunarity = 2.f, float gain = 0.5f);

	MUD_NOISE_EXPORT func_ float noise_fract_3d(float x, float y, float z, Noise::NoiseType noise_type, float frequency, Noise::Interp interp = Noise::Quintic,
											    Noise::FractalType fractal_type = Noise::FBM, int octaves = 3, float lacunarity = 2.f, float gain = 0.5f);


	export_ extern template struct refl_ struct_ seque_ vector3d<float>;

	MUD_NOISE_EXPORT func_ void noise_field_2d(vector3d<float>& output_values, Noise::NoiseType noise_type, float frequency = 0.01f, Noise::Interp interp = Noise::Quintic);
	MUD_NOISE_EXPORT func_ void noise_field_3d(vector3d<float>& output_values, Noise::NoiseType noise_type, float frequency = 0.01f, Noise::Interp interp = Noise::Quintic);
}
