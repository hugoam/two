#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <noise/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Noise
	void DECL mud_Noise__destroy(mud::Noise* self) {
		delete self;
	}
	float DECL mud_noise_2d_3(float x, float y, mud::Noise::NoiseType noise_type) {
		return mud::noise_2d(x, y, noise_type);
	}
	float DECL mud_noise_2d_4(float x, float y, mud::Noise::NoiseType noise_type, float frequency) {
		return mud::noise_2d(x, y, noise_type, frequency);
	}
	float DECL mud_noise_2d_5(float x, float y, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp) {
		return mud::noise_2d(x, y, noise_type, frequency, interp);
	}
	float DECL mud_noise_3d_4(float x, float y, float z, mud::Noise::NoiseType noise_type) {
		return mud::noise_3d(x, y, z, noise_type);
	}
	float DECL mud_noise_3d_5(float x, float y, float z, mud::Noise::NoiseType noise_type, float frequency) {
		return mud::noise_3d(x, y, z, noise_type, frequency);
	}
	float DECL mud_noise_3d_6(float x, float y, float z, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp) {
		return mud::noise_3d(x, y, z, noise_type, frequency, interp);
	}
	float DECL mud_noise_fract_2d_4(float x, float y, mud::Noise::NoiseType noise_type, float frequency) {
		return mud::noise_fract_2d(x, y, noise_type, frequency);
	}
	float DECL mud_noise_fract_2d_5(float x, float y, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp) {
		return mud::noise_fract_2d(x, y, noise_type, frequency, interp);
	}
	float DECL mud_noise_fract_2d_6(float x, float y, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp, mud::Noise::FractalType fractal_type) {
		return mud::noise_fract_2d(x, y, noise_type, frequency, interp, fractal_type);
	}
	float DECL mud_noise_fract_2d_7(float x, float y, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp, mud::Noise::FractalType fractal_type, int octaves) {
		return mud::noise_fract_2d(x, y, noise_type, frequency, interp, fractal_type, octaves);
	}
	float DECL mud_noise_fract_2d_8(float x, float y, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp, mud::Noise::FractalType fractal_type, int octaves, float lacunarity) {
		return mud::noise_fract_2d(x, y, noise_type, frequency, interp, fractal_type, octaves, lacunarity);
	}
	float DECL mud_noise_fract_2d_9(float x, float y, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp, mud::Noise::FractalType fractal_type, int octaves, float lacunarity, float gain) {
		return mud::noise_fract_2d(x, y, noise_type, frequency, interp, fractal_type, octaves, lacunarity, gain);
	}
	float DECL mud_noise_fract_3d_5(float x, float y, float z, mud::Noise::NoiseType noise_type, float frequency) {
		return mud::noise_fract_3d(x, y, z, noise_type, frequency);
	}
	float DECL mud_noise_fract_3d_6(float x, float y, float z, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp) {
		return mud::noise_fract_3d(x, y, z, noise_type, frequency, interp);
	}
	float DECL mud_noise_fract_3d_7(float x, float y, float z, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp, mud::Noise::FractalType fractal_type) {
		return mud::noise_fract_3d(x, y, z, noise_type, frequency, interp, fractal_type);
	}
	float DECL mud_noise_fract_3d_8(float x, float y, float z, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp, mud::Noise::FractalType fractal_type, int octaves) {
		return mud::noise_fract_3d(x, y, z, noise_type, frequency, interp, fractal_type, octaves);
	}
	float DECL mud_noise_fract_3d_9(float x, float y, float z, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp, mud::Noise::FractalType fractal_type, int octaves, float lacunarity) {
		return mud::noise_fract_3d(x, y, z, noise_type, frequency, interp, fractal_type, octaves, lacunarity);
	}
	float DECL mud_noise_fract_3d_10(float x, float y, float z, mud::Noise::NoiseType noise_type, float frequency, mud::Noise::Interp interp, mud::Noise::FractalType fractal_type, int octaves, float lacunarity, float gain) {
		return mud::noise_fract_3d(x, y, z, noise_type, frequency, interp, fractal_type, octaves, lacunarity, gain);
	}
	// CellularDistanceFunction
	mud::Noise::CellularDistanceFunction DECL mud_Noise_CellularDistanceFunction_Euclidean() {
		return mud::Noise::Euclidean;
	}
	mud::Noise::CellularDistanceFunction DECL mud_Noise_CellularDistanceFunction_Manhattan() {
		return mud::Noise::Manhattan;
	}
	mud::Noise::CellularDistanceFunction DECL mud_Noise_CellularDistanceFunction_Natural() {
		return mud::Noise::Natural;
	}
	// CellularReturnType
	mud::Noise::CellularReturnType DECL mud_Noise_CellularReturnType_CellValue() {
		return mud::Noise::CellValue;
	}
	mud::Noise::CellularReturnType DECL mud_Noise_CellularReturnType_NoiseLookup() {
		return mud::Noise::NoiseLookup;
	}
	mud::Noise::CellularReturnType DECL mud_Noise_CellularReturnType_Distance() {
		return mud::Noise::Distance;
	}
	mud::Noise::CellularReturnType DECL mud_Noise_CellularReturnType_Distance2() {
		return mud::Noise::Distance2;
	}
	mud::Noise::CellularReturnType DECL mud_Noise_CellularReturnType_Distance2Add() {
		return mud::Noise::Distance2Add;
	}
	mud::Noise::CellularReturnType DECL mud_Noise_CellularReturnType_Distance2Sub() {
		return mud::Noise::Distance2Sub;
	}
	mud::Noise::CellularReturnType DECL mud_Noise_CellularReturnType_Distance2Mul() {
		return mud::Noise::Distance2Mul;
	}
	mud::Noise::CellularReturnType DECL mud_Noise_CellularReturnType_Distance2Div() {
		return mud::Noise::Distance2Div;
	}
	// FractalType
	mud::Noise::FractalType DECL mud_Noise_FractalType_FBM() {
		return mud::Noise::FBM;
	}
	mud::Noise::FractalType DECL mud_Noise_FractalType_Billow() {
		return mud::Noise::Billow;
	}
	mud::Noise::FractalType DECL mud_Noise_FractalType_RigidMulti() {
		return mud::Noise::RigidMulti;
	}
	// Interp
	mud::Noise::Interp DECL mud_Noise_Interp_Linear() {
		return mud::Noise::Linear;
	}
	mud::Noise::Interp DECL mud_Noise_Interp_Hermite() {
		return mud::Noise::Hermite;
	}
	mud::Noise::Interp DECL mud_Noise_Interp_Quintic() {
		return mud::Noise::Quintic;
	}
	// NoiseType
	mud::Noise::NoiseType DECL mud_Noise_NoiseType_Value() {
		return mud::Noise::Value;
	}
	mud::Noise::NoiseType DECL mud_Noise_NoiseType_ValueFractal() {
		return mud::Noise::ValueFractal;
	}
	mud::Noise::NoiseType DECL mud_Noise_NoiseType_Perlin() {
		return mud::Noise::Perlin;
	}
	mud::Noise::NoiseType DECL mud_Noise_NoiseType_PerlinFractal() {
		return mud::Noise::PerlinFractal;
	}
	mud::Noise::NoiseType DECL mud_Noise_NoiseType_Simplex() {
		return mud::Noise::Simplex;
	}
	mud::Noise::NoiseType DECL mud_Noise_NoiseType_SimplexFractal() {
		return mud::Noise::SimplexFractal;
	}
	mud::Noise::NoiseType DECL mud_Noise_NoiseType_Cellular() {
		return mud::Noise::Cellular;
	}
	mud::Noise::NoiseType DECL mud_Noise_NoiseType_WhiteNoise() {
		return mud::Noise::WhiteNoise;
	}
	mud::Noise::NoiseType DECL mud_Noise_NoiseType_Cubic() {
		return mud::Noise::Cubic;
	}
	mud::Noise::NoiseType DECL mud_Noise_NoiseType_CubicFractal() {
		return mud::Noise::CubicFractal;
	}
	
}


