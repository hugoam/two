
// Bindings utilities
function WrapperObject() {
}
// Noise
function Noise() { throw "cannot construct a Noise, no constructor in IDL" }
Noise.prototype = Object.create(WrapperObject.prototype);
Noise.prototype.constructor = Noise;
Noise.prototype.__class__ = Noise;
Noise.__cache__ = {};
Module['Noise'] = Noise;
Noise.prototype["__destroy__"] = Noise.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Noise___destroy__(self);
};

(function() {
    function setupEnums() {
        // CellularDistanceFunction
        Module['Euclidean'] = _emscripten_enum_CellularDistanceFunction_Euclidean();
        Module['Manhattan'] = _emscripten_enum_CellularDistanceFunction_Manhattan();
        Module['Natural'] = _emscripten_enum_CellularDistanceFunction_Natural();
        // CellularReturnType
        Module['CellValue'] = _emscripten_enum_CellularReturnType_CellValue();
        Module['NoiseLookup'] = _emscripten_enum_CellularReturnType_NoiseLookup();
        Module['Distance'] = _emscripten_enum_CellularReturnType_Distance();
        Module['Distance2'] = _emscripten_enum_CellularReturnType_Distance2();
        Module['Distance2Add'] = _emscripten_enum_CellularReturnType_Distance2Add();
        Module['Distance2Sub'] = _emscripten_enum_CellularReturnType_Distance2Sub();
        Module['Distance2Mul'] = _emscripten_enum_CellularReturnType_Distance2Mul();
        Module['Distance2Div'] = _emscripten_enum_CellularReturnType_Distance2Div();
        // FractalType
        Module['FBM'] = _emscripten_enum_FractalType_FBM();
        Module['Billow'] = _emscripten_enum_FractalType_Billow();
        Module['RigidMulti'] = _emscripten_enum_FractalType_RigidMulti();
        // Interp
        Module['Linear'] = _emscripten_enum_Interp_Linear();
        Module['Hermite'] = _emscripten_enum_Interp_Hermite();
        Module['Quintic'] = _emscripten_enum_Interp_Quintic();
        // NoiseType
        Module['Value'] = _emscripten_enum_NoiseType_Value();
        Module['ValueFractal'] = _emscripten_enum_NoiseType_ValueFractal();
        Module['Perlin'] = _emscripten_enum_NoiseType_Perlin();
        Module['PerlinFractal'] = _emscripten_enum_NoiseType_PerlinFractal();
        Module['Simplex'] = _emscripten_enum_NoiseType_Simplex();
        Module['SimplexFractal'] = _emscripten_enum_NoiseType_SimplexFractal();
        Module['Cellular'] = _emscripten_enum_NoiseType_Cellular();
        Module['WhiteNoise'] = _emscripten_enum_NoiseType_WhiteNoise();
        Module['Cubic'] = _emscripten_enum_NoiseType_Cubic();
        Module['CubicFractal'] = _emscripten_enum_NoiseType_CubicFractal();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
