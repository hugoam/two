#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
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
	
}


// 'CellularDistanceFunction'
CellularDistanceFunction EMSCRIPTEN_KEEPALIVE emscripten_enum_CellularDistanceFunction_Euclidean() {
	return mud::Noise::Euclidean;
}
CellularDistanceFunction EMSCRIPTEN_KEEPALIVE emscripten_enum_CellularDistanceFunction_Manhattan() {
	return mud::Noise::Manhattan;
}
CellularDistanceFunction EMSCRIPTEN_KEEPALIVE emscripten_enum_CellularDistanceFunction_Natural() {
	return mud::Noise::Natural;
}
// 'CellularReturnType'
CellularReturnType EMSCRIPTEN_KEEPALIVE emscripten_enum_CellularReturnType_CellValue() {
	return mud::Noise::CellValue;
}
CellularReturnType EMSCRIPTEN_KEEPALIVE emscripten_enum_CellularReturnType_NoiseLookup() {
	return mud::Noise::NoiseLookup;
}
CellularReturnType EMSCRIPTEN_KEEPALIVE emscripten_enum_CellularReturnType_Distance() {
	return mud::Noise::Distance;
}
CellularReturnType EMSCRIPTEN_KEEPALIVE emscripten_enum_CellularReturnType_Distance2() {
	return mud::Noise::Distance2;
}
CellularReturnType EMSCRIPTEN_KEEPALIVE emscripten_enum_CellularReturnType_Distance2Add() {
	return mud::Noise::Distance2Add;
}
CellularReturnType EMSCRIPTEN_KEEPALIVE emscripten_enum_CellularReturnType_Distance2Sub() {
	return mud::Noise::Distance2Sub;
}
CellularReturnType EMSCRIPTEN_KEEPALIVE emscripten_enum_CellularReturnType_Distance2Mul() {
	return mud::Noise::Distance2Mul;
}
CellularReturnType EMSCRIPTEN_KEEPALIVE emscripten_enum_CellularReturnType_Distance2Div() {
	return mud::Noise::Distance2Div;
}
// 'FractalType'
FractalType EMSCRIPTEN_KEEPALIVE emscripten_enum_FractalType_FBM() {
	return mud::Noise::FBM;
}
FractalType EMSCRIPTEN_KEEPALIVE emscripten_enum_FractalType_Billow() {
	return mud::Noise::Billow;
}
FractalType EMSCRIPTEN_KEEPALIVE emscripten_enum_FractalType_RigidMulti() {
	return mud::Noise::RigidMulti;
}
// 'Interp'
Interp EMSCRIPTEN_KEEPALIVE emscripten_enum_Interp_Linear() {
	return mud::Noise::Linear;
}
Interp EMSCRIPTEN_KEEPALIVE emscripten_enum_Interp_Hermite() {
	return mud::Noise::Hermite;
}
Interp EMSCRIPTEN_KEEPALIVE emscripten_enum_Interp_Quintic() {
	return mud::Noise::Quintic;
}
// 'NoiseType'
NoiseType EMSCRIPTEN_KEEPALIVE emscripten_enum_NoiseType_Value() {
	return mud::Noise::Value;
}
NoiseType EMSCRIPTEN_KEEPALIVE emscripten_enum_NoiseType_ValueFractal() {
	return mud::Noise::ValueFractal;
}
NoiseType EMSCRIPTEN_KEEPALIVE emscripten_enum_NoiseType_Perlin() {
	return mud::Noise::Perlin;
}
NoiseType EMSCRIPTEN_KEEPALIVE emscripten_enum_NoiseType_PerlinFractal() {
	return mud::Noise::PerlinFractal;
}
NoiseType EMSCRIPTEN_KEEPALIVE emscripten_enum_NoiseType_Simplex() {
	return mud::Noise::Simplex;
}
NoiseType EMSCRIPTEN_KEEPALIVE emscripten_enum_NoiseType_SimplexFractal() {
	return mud::Noise::SimplexFractal;
}
NoiseType EMSCRIPTEN_KEEPALIVE emscripten_enum_NoiseType_Cellular() {
	return mud::Noise::Cellular;
}
NoiseType EMSCRIPTEN_KEEPALIVE emscripten_enum_NoiseType_WhiteNoise() {
	return mud::Noise::WhiteNoise;
}
NoiseType EMSCRIPTEN_KEEPALIVE emscripten_enum_NoiseType_Cubic() {
	return mud::Noise::Cubic;
}
NoiseType EMSCRIPTEN_KEEPALIVE emscripten_enum_NoiseType_CubicFractal() {
	return mud::Noise::CubicFractal;
}
