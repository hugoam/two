#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <noise/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Noise
	two::Type* DECL two_Noise__type() {
		return &two::type<two::Noise>();
	}
	void DECL two_Noise__destroy(two::Noise* self) {
		delete self;
	}
	float DECL two_noise_2d_3(float x, float y, two::Noise::NoiseType noise_type) {
		return two::noise_2d(x, y, noise_type);
	}
	float DECL two_noise_2d_4(float x, float y, two::Noise::NoiseType noise_type, float frequency) {
		return two::noise_2d(x, y, noise_type, frequency);
	}
	float DECL two_noise_2d_5(float x, float y, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp) {
		return two::noise_2d(x, y, noise_type, frequency, interp);
	}
	float DECL two_noise_3d_4(float x, float y, float z, two::Noise::NoiseType noise_type) {
		return two::noise_3d(x, y, z, noise_type);
	}
	float DECL two_noise_3d_5(float x, float y, float z, two::Noise::NoiseType noise_type, float frequency) {
		return two::noise_3d(x, y, z, noise_type, frequency);
	}
	float DECL two_noise_3d_6(float x, float y, float z, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp) {
		return two::noise_3d(x, y, z, noise_type, frequency, interp);
	}
	float DECL two_noise_fract_2d_4(float x, float y, two::Noise::NoiseType noise_type, float frequency) {
		return two::noise_fract_2d(x, y, noise_type, frequency);
	}
	float DECL two_noise_fract_2d_5(float x, float y, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp) {
		return two::noise_fract_2d(x, y, noise_type, frequency, interp);
	}
	float DECL two_noise_fract_2d_6(float x, float y, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp, two::Noise::FractalType fractal_type) {
		return two::noise_fract_2d(x, y, noise_type, frequency, interp, fractal_type);
	}
	float DECL two_noise_fract_2d_7(float x, float y, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp, two::Noise::FractalType fractal_type, int octaves) {
		return two::noise_fract_2d(x, y, noise_type, frequency, interp, fractal_type, octaves);
	}
	float DECL two_noise_fract_2d_8(float x, float y, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp, two::Noise::FractalType fractal_type, int octaves, float lacunarity) {
		return two::noise_fract_2d(x, y, noise_type, frequency, interp, fractal_type, octaves, lacunarity);
	}
	float DECL two_noise_fract_2d_9(float x, float y, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp, two::Noise::FractalType fractal_type, int octaves, float lacunarity, float gain) {
		return two::noise_fract_2d(x, y, noise_type, frequency, interp, fractal_type, octaves, lacunarity, gain);
	}
	float DECL two_noise_fract_3d_5(float x, float y, float z, two::Noise::NoiseType noise_type, float frequency) {
		return two::noise_fract_3d(x, y, z, noise_type, frequency);
	}
	float DECL two_noise_fract_3d_6(float x, float y, float z, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp) {
		return two::noise_fract_3d(x, y, z, noise_type, frequency, interp);
	}
	float DECL two_noise_fract_3d_7(float x, float y, float z, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp, two::Noise::FractalType fractal_type) {
		return two::noise_fract_3d(x, y, z, noise_type, frequency, interp, fractal_type);
	}
	float DECL two_noise_fract_3d_8(float x, float y, float z, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp, two::Noise::FractalType fractal_type, int octaves) {
		return two::noise_fract_3d(x, y, z, noise_type, frequency, interp, fractal_type, octaves);
	}
	float DECL two_noise_fract_3d_9(float x, float y, float z, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp, two::Noise::FractalType fractal_type, int octaves, float lacunarity) {
		return two::noise_fract_3d(x, y, z, noise_type, frequency, interp, fractal_type, octaves, lacunarity);
	}
	float DECL two_noise_fract_3d_10(float x, float y, float z, two::Noise::NoiseType noise_type, float frequency, two::Noise::Interp interp, two::Noise::FractalType fractal_type, int octaves, float lacunarity, float gain) {
		return two::noise_fract_3d(x, y, z, noise_type, frequency, interp, fractal_type, octaves, lacunarity, gain);
	}
	// NoiseType
	two::Noise::NoiseType DECL two_Noise_NoiseType_Value() {
		return two::Noise::Value;
	}
	two::Noise::NoiseType DECL two_Noise_NoiseType_ValueFractal() {
		return two::Noise::ValueFractal;
	}
	two::Noise::NoiseType DECL two_Noise_NoiseType_Perlin() {
		return two::Noise::Perlin;
	}
	two::Noise::NoiseType DECL two_Noise_NoiseType_PerlinFractal() {
		return two::Noise::PerlinFractal;
	}
	two::Noise::NoiseType DECL two_Noise_NoiseType_Simplex() {
		return two::Noise::Simplex;
	}
	two::Noise::NoiseType DECL two_Noise_NoiseType_SimplexFractal() {
		return two::Noise::SimplexFractal;
	}
	two::Noise::NoiseType DECL two_Noise_NoiseType_Cellular() {
		return two::Noise::Cellular;
	}
	two::Noise::NoiseType DECL two_Noise_NoiseType_WhiteNoise() {
		return two::Noise::WhiteNoise;
	}
	two::Noise::NoiseType DECL two_Noise_NoiseType_Cubic() {
		return two::Noise::Cubic;
	}
	two::Noise::NoiseType DECL two_Noise_NoiseType_CubicFractal() {
		return two::Noise::CubicFractal;
	}
	// Interp
	two::Noise::Interp DECL two_Noise_Interp_Linear() {
		return two::Noise::Linear;
	}
	two::Noise::Interp DECL two_Noise_Interp_Hermite() {
		return two::Noise::Hermite;
	}
	two::Noise::Interp DECL two_Noise_Interp_Quintic() {
		return two::Noise::Quintic;
	}
	// FractalType
	two::Noise::FractalType DECL two_Noise_FractalType_FBM() {
		return two::Noise::FBM;
	}
	two::Noise::FractalType DECL two_Noise_FractalType_Billow() {
		return two::Noise::Billow;
	}
	two::Noise::FractalType DECL two_Noise_FractalType_RigidMulti() {
		return two::Noise::RigidMulti;
	}
	// CellularDistanceFunction
	two::Noise::CellularDistanceFunction DECL two_Noise_CellularDistanceFunction_Euclidean() {
		return two::Noise::Euclidean;
	}
	two::Noise::CellularDistanceFunction DECL two_Noise_CellularDistanceFunction_Manhattan() {
		return two::Noise::Manhattan;
	}
	two::Noise::CellularDistanceFunction DECL two_Noise_CellularDistanceFunction_Natural() {
		return two::Noise::Natural;
	}
	// CellularReturnType
	two::Noise::CellularReturnType DECL two_Noise_CellularReturnType_CellValue() {
		return two::Noise::CellValue;
	}
	two::Noise::CellularReturnType DECL two_Noise_CellularReturnType_NoiseLookup() {
		return two::Noise::NoiseLookup;
	}
	two::Noise::CellularReturnType DECL two_Noise_CellularReturnType_Distance() {
		return two::Noise::Distance;
	}
	two::Noise::CellularReturnType DECL two_Noise_CellularReturnType_Distance2() {
		return two::Noise::Distance2;
	}
	two::Noise::CellularReturnType DECL two_Noise_CellularReturnType_Distance2Add() {
		return two::Noise::Distance2Add;
	}
	two::Noise::CellularReturnType DECL two_Noise_CellularReturnType_Distance2Sub() {
		return two::Noise::Distance2Sub;
	}
	two::Noise::CellularReturnType DECL two_Noise_CellularReturnType_Distance2Mul() {
		return two::Noise::Distance2Mul;
	}
	two::Noise::CellularReturnType DECL two_Noise_CellularReturnType_Distance2Div() {
		return two::Noise::Distance2Div;
	}
	
}


