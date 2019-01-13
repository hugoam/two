
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
        Module['Euclidean'] = _CellularDistanceFunction_Euclidean();
        Module['Manhattan'] = _CellularDistanceFunction_Manhattan();
        Module['Natural'] = _CellularDistanceFunction_Natural();
        // CellularReturnType
        Module['CellValue'] = _CellularReturnType_CellValue();
        Module['NoiseLookup'] = _CellularReturnType_NoiseLookup();
        Module['Distance'] = _CellularReturnType_Distance();
        Module['Distance2'] = _CellularReturnType_Distance2();
        Module['Distance2Add'] = _CellularReturnType_Distance2Add();
        Module['Distance2Sub'] = _CellularReturnType_Distance2Sub();
        Module['Distance2Mul'] = _CellularReturnType_Distance2Mul();
        Module['Distance2Div'] = _CellularReturnType_Distance2Div();
        // FractalType
        Module['FBM'] = _FractalType_FBM();
        Module['Billow'] = _FractalType_Billow();
        Module['RigidMulti'] = _FractalType_RigidMulti();
        // Interp
        Module['Linear'] = _Interp_Linear();
        Module['Hermite'] = _Interp_Hermite();
        Module['Quintic'] = _Interp_Quintic();
        // NoiseType
        Module['Value'] = _NoiseType_Value();
        Module['ValueFractal'] = _NoiseType_ValueFractal();
        Module['Perlin'] = _NoiseType_Perlin();
        Module['PerlinFractal'] = _NoiseType_PerlinFractal();
        Module['Simplex'] = _NoiseType_Simplex();
        Module['SimplexFractal'] = _NoiseType_SimplexFractal();
        Module['Cellular'] = _NoiseType_Cellular();
        Module['WhiteNoise'] = _NoiseType_WhiteNoise();
        Module['Cubic'] = _NoiseType_Cubic();
        Module['CubicFractal'] = _NoiseType_CubicFractal();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
