
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
    _mud_Noise__destroy(self);
};

(function() {
    function setupEnums() {
        // CellularDistanceFunction
        Module['Euclidean'] = _mud_Noise_CellularDistanceFunction_Euclidean();
        Module['Manhattan'] = _mud_Noise_CellularDistanceFunction_Manhattan();
        Module['Natural'] = _mud_Noise_CellularDistanceFunction_Natural();
        // CellularReturnType
        Module['CellValue'] = _mud_Noise_CellularReturnType_CellValue();
        Module['NoiseLookup'] = _mud_Noise_CellularReturnType_NoiseLookup();
        Module['Distance'] = _mud_Noise_CellularReturnType_Distance();
        Module['Distance2'] = _mud_Noise_CellularReturnType_Distance2();
        Module['Distance2Add'] = _mud_Noise_CellularReturnType_Distance2Add();
        Module['Distance2Sub'] = _mud_Noise_CellularReturnType_Distance2Sub();
        Module['Distance2Mul'] = _mud_Noise_CellularReturnType_Distance2Mul();
        Module['Distance2Div'] = _mud_Noise_CellularReturnType_Distance2Div();
        // FractalType
        Module['FBM'] = _mud_Noise_FractalType_FBM();
        Module['Billow'] = _mud_Noise_FractalType_Billow();
        Module['RigidMulti'] = _mud_Noise_FractalType_RigidMulti();
        // Interp
        Module['Linear'] = _mud_Noise_Interp_Linear();
        Module['Hermite'] = _mud_Noise_Interp_Hermite();
        Module['Quintic'] = _mud_Noise_Interp_Quintic();
        // NoiseType
        Module['Value'] = _mud_Noise_NoiseType_Value();
        Module['ValueFractal'] = _mud_Noise_NoiseType_ValueFractal();
        Module['Perlin'] = _mud_Noise_NoiseType_Perlin();
        Module['PerlinFractal'] = _mud_Noise_NoiseType_PerlinFractal();
        Module['Simplex'] = _mud_Noise_NoiseType_Simplex();
        Module['SimplexFractal'] = _mud_Noise_NoiseType_SimplexFractal();
        Module['Cellular'] = _mud_Noise_NoiseType_Cellular();
        Module['WhiteNoise'] = _mud_Noise_NoiseType_WhiteNoise();
        Module['Cubic'] = _mud_Noise_NoiseType_Cubic();
        Module['CubicFractal'] = _mud_Noise_NoiseType_CubicFractal();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
