#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <noise/Api.h>
#include <emscripten.h>


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// Noise
	void EMSCRIPTEN_KEEPALIVE Noise___destroy__(mud::Noise* self) {
		delete self;
	}
	// CellularDistanceFunction
	mud::Noise::CellularDistanceFunction EMSCRIPTEN_KEEPALIVE CellularDistanceFunction_Euclidean() {
		return mud::Noise::Euclidean;
	}
	mud::Noise::CellularDistanceFunction EMSCRIPTEN_KEEPALIVE CellularDistanceFunction_Manhattan() {
		return mud::Noise::Manhattan;
	}
	mud::Noise::CellularDistanceFunction EMSCRIPTEN_KEEPALIVE CellularDistanceFunction_Natural() {
		return mud::Noise::Natural;
	}
	// CellularReturnType
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE CellularReturnType_CellValue() {
		return mud::Noise::CellValue;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE CellularReturnType_NoiseLookup() {
		return mud::Noise::NoiseLookup;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE CellularReturnType_Distance() {
		return mud::Noise::Distance;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE CellularReturnType_Distance2() {
		return mud::Noise::Distance2;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE CellularReturnType_Distance2Add() {
		return mud::Noise::Distance2Add;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE CellularReturnType_Distance2Sub() {
		return mud::Noise::Distance2Sub;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE CellularReturnType_Distance2Mul() {
		return mud::Noise::Distance2Mul;
	}
	mud::Noise::CellularReturnType EMSCRIPTEN_KEEPALIVE CellularReturnType_Distance2Div() {
		return mud::Noise::Distance2Div;
	}
	// FractalType
	mud::Noise::FractalType EMSCRIPTEN_KEEPALIVE FractalType_FBM() {
		return mud::Noise::FBM;
	}
	mud::Noise::FractalType EMSCRIPTEN_KEEPALIVE FractalType_Billow() {
		return mud::Noise::Billow;
	}
	mud::Noise::FractalType EMSCRIPTEN_KEEPALIVE FractalType_RigidMulti() {
		return mud::Noise::RigidMulti;
	}
	// Interp
	mud::Noise::Interp EMSCRIPTEN_KEEPALIVE Interp_Linear() {
		return mud::Noise::Linear;
	}
	mud::Noise::Interp EMSCRIPTEN_KEEPALIVE Interp_Hermite() {
		return mud::Noise::Hermite;
	}
	mud::Noise::Interp EMSCRIPTEN_KEEPALIVE Interp_Quintic() {
		return mud::Noise::Quintic;
	}
	// NoiseType
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE NoiseType_Value() {
		return mud::Noise::Value;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE NoiseType_ValueFractal() {
		return mud::Noise::ValueFractal;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE NoiseType_Perlin() {
		return mud::Noise::Perlin;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE NoiseType_PerlinFractal() {
		return mud::Noise::PerlinFractal;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE NoiseType_Simplex() {
		return mud::Noise::Simplex;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE NoiseType_SimplexFractal() {
		return mud::Noise::SimplexFractal;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE NoiseType_Cellular() {
		return mud::Noise::Cellular;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE NoiseType_WhiteNoise() {
		return mud::Noise::WhiteNoise;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE NoiseType_Cubic() {
		return mud::Noise::Cubic;
	}
	mud::Noise::NoiseType EMSCRIPTEN_KEEPALIVE NoiseType_CubicFractal() {
		return mud::Noise::CubicFractal;
	}
	
}


