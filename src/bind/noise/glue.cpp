#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <noise/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// Noise
	void EMSCRIPTEN_KEEPALIVE mud_Noise___destroy__(mud::Noise* self) {
		delete self;
	}
	// CellularDistanceFunction
	mud::Noise::CellularDistanceFunction EMSCRIPTEN_KEEPALIVE mud_Noise_CellularDistanceFunction_Euclidean() {
		return mud::Noise::Euclidean;
	}
	mud::Noise::CellularDistanceFunction EMSCRIPTEN_KEEPALIVE mud_Noise_CellularDistanceFunction_Manhattan() {
		return mud::Noise::Manhattan;
	}
	mud::Noise::CellularDistanceFunction EMSCRIPTEN_KEEPALIVE mud_Noise_CellularDistanceFunction_Natural() {
		return mud::Noise::Natural;
	}
	// CellularReturnType
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE mud_Noise_CellularReturnType_CellValue() {
		return mud::Noise::CellValue;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE mud_Noise_CellularReturnType_NoiseLookup() {
		return mud::Noise::NoiseLookup;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE mud_Noise_CellularReturnType_Distance() {
		return mud::Noise::Distance;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE mud_Noise_CellularReturnType_Distance2() {
		return mud::Noise::Distance2;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE mud_Noise_CellularReturnType_Distance2Add() {
		return mud::Noise::Distance2Add;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE mud_Noise_CellularReturnType_Distance2Sub() {
		return mud::Noise::Distance2Sub;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE mud_Noise_CellularReturnType_Distance2Mul() {
		return mud::Noise::Distance2Mul;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE mud_Noise_CellularReturnType_Distance2Div() {
		return mud::Noise::Distance2Div;
	}
	// FractalType
	mud::Noise::FractalType EMSCRIPTEN_KEEPALIVE mud_Noise_FractalType_FBM() {
		return mud::Noise::FBM;
	}
	mud::Noise::FractalType EMSCRIPTEN_KEEPALIVE mud_Noise_FractalType_Billow() {
		return mud::Noise::Billow;
	}
	mud::Noise::FractalType EMSCRIPTEN_KEEPALIVE mud_Noise_FractalType_RigidMulti() {
		return mud::Noise::RigidMulti;
	}
	// Interp
	mud::Noise::Interp EMSCRIPTEN_KEEPALIVE mud_Noise_Interp_Linear() {
		return mud::Noise::Linear;
	}
	mud::Noise::Interp EMSCRIPTEN_KEEPALIVE mud_Noise_Interp_Hermite() {
		return mud::Noise::Hermite;
	}
	mud::Noise::Interp EMSCRIPTEN_KEEPALIVE mud_Noise_Interp_Quintic() {
		return mud::Noise::Quintic;
	}
	// NoiseType
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE mud_Noise_NoiseType_Value() {
		return mud::Noise::Value;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE mud_Noise_NoiseType_ValueFractal() {
		return mud::Noise::ValueFractal;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE mud_Noise_NoiseType_Perlin() {
		return mud::Noise::Perlin;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE mud_Noise_NoiseType_PerlinFractal() {
		return mud::Noise::PerlinFractal;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE mud_Noise_NoiseType_Simplex() {
		return mud::Noise::Simplex;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE mud_Noise_NoiseType_SimplexFractal() {
		return mud::Noise::SimplexFractal;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE mud_Noise_NoiseType_Cellular() {
		return mud::Noise::Cellular;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE mud_Noise_NoiseType_WhiteNoise() {
		return mud::Noise::WhiteNoise;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE mud_Noise_NoiseType_Cubic() {
		return mud::Noise::Cubic;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE mud_Noise_NoiseType_CubicFractal() {
		return mud::Noise::CubicFractal;
	}
	
}


