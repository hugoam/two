#pragma once

#include <gen/Generated/Forward.h>
#include <math/Random.h>
#include <math/Grid.h>

#ifndef MUD_META_GENERATOR
class MUD_GEN_EXPORT FastNoise;
#include <FastNoise.h>
#endif

namespace mud
{
	//using fnScalar = FN_DECIMAL;

#ifdef MUD_META_GENERATOR
	class _refl_ MUD_GEN_EXPORT Noise
	{
	public:
		enum _refl_ NoiseType { Value, ValueFractal, Perlin, PerlinFractal, Simplex, SimplexFractal, Cellular, WhiteNoise, Cubic, CubicFractal };
		enum _refl_ Interp { Linear, Hermite, Quintic };
		enum _refl_ FractalType { FBM, Billow, RigidMulti };
		enum _refl_ CellularDistanceFunction { Euclidean, Manhattan, Natural };
		enum _refl_ CellularReturnType { CellValue, NoiseLookup, Distance, Distance2, Distance2Add, Distance2Sub, Distance2Mul, Distance2Div };
#else
	class _refl_ MUD_GEN_EXPORT Noise : public FastNoise
	{
#endif
	public:
		Noise(int seed = 1337);

#if 0 //def MUD_META_GENERATOR
		_meth_ float GetNoise(float x, float y) const;
		_meth_ float GetNoise(float x, float y, float z) const;

		_attr_ NoiseType m_noiseType;

		_attr_ int m_seed;
		_attr_ float m_frequency;
		_attr_ Interp m_interp;

		// fractal
		_attr_ FractalType m_fractalType;
		_attr_ int m_octaves;
		_attr_ float m_lacunarity;
		_attr_ float m_gain;

		// cellular
		_attr_ CellularDistanceFunction m_cellularDistanceFunction;
		_attr_ CellularReturnType m_cellularReturnType;
		_attr_ FastNoise* m_cellularNoiseLookup;
		_attr_ float m_cellularJitter;

		_attr_ int m_cellularDistanceIndex0;
		_attr_ int m_cellularDistanceIndex1;

		// warp
		_attr_ float m_gradientPerturbAmp;
#endif
	};

	MUD_GEN_EXPORT _func_ float noise_2d(float x, float y, Noise::NoiseType noise_type, float frequency = 0.01f, Noise::Interp interp = Noise::Quintic);
	MUD_GEN_EXPORT _func_ float noise_3d(float x, float y, float z, Noise::NoiseType noise_type, float frequency = 0.01f, Noise::Interp interp = Noise::Quintic);

	MUD_GEN_EXPORT _func_ float noise_fract_2d(float x, float y, Noise::NoiseType noise_type, float frequency, Noise::Interp interp = Noise::Quintic,
											   Noise::FractalType fractal_type = Noise::FBM, int octaves = 3, float lacunarity = 2.f, float gain = 0.5f);

	MUD_GEN_EXPORT _func_ float noise_fract_3d(float x, float y, float z, Noise::NoiseType noise_type, float frequency, Noise::Interp interp = Noise::Quintic,
											   Noise::FractalType fractal_type = Noise::FBM, int octaves = 3, float lacunarity = 2.f, float gain = 0.5f);


	template struct _refl_ _struct_ MUD_GEN_EXPORT array_3d<float>;

	MUD_GEN_EXPORT _func_ void noise_field_2d(array_3d<float>& output_values, Noise::NoiseType noise_type, float frequency = 0.01f, Noise::Interp interp = Noise::Quintic);
	MUD_GEN_EXPORT _func_ void noise_field_3d(array_3d<float>& output_values, Noise::NoiseType noise_type, float frequency = 0.01f, Noise::Interp interp = Noise::Quintic);
}
