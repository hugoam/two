
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
Module['noise_2d'] = function(x, y, noise_type, frequency, interp) {
    var self = this.ptr;
    /* x <float> [] */
    /* y <float> [] */
    /* noise_type <NoiseType> [] */
    if (noise_type && typeof noise_type === "object") noise_type = noise_type.ptr;
    /* frequency <float> [] */
    /* interp <Interp> [] */
    if (interp && typeof interp === "object") interp = interp.ptr;
    if (frequency === undefined) { return _mud_noise_2d_3(x, y, noise_type); return; }
    if (interp === undefined) { return _mud_noise_2d_4(x, y, noise_type, frequency); return; }
    return _mud_noise_2d_5(x, y, noise_type, frequency, interp);
};
Module['noise_3d'] = function(x, y, z, noise_type, frequency, interp) {
    var self = this.ptr;
    /* x <float> [] */
    /* y <float> [] */
    /* z <float> [] */
    /* noise_type <NoiseType> [] */
    if (noise_type && typeof noise_type === "object") noise_type = noise_type.ptr;
    /* frequency <float> [] */
    /* interp <Interp> [] */
    if (interp && typeof interp === "object") interp = interp.ptr;
    if (frequency === undefined) { return _mud_noise_3d_4(x, y, z, noise_type); return; }
    if (interp === undefined) { return _mud_noise_3d_5(x, y, z, noise_type, frequency); return; }
    return _mud_noise_3d_6(x, y, z, noise_type, frequency, interp);
};
Module['noise_fract_2d'] = function(x, y, noise_type, frequency, interp, fractal_type, octaves, lacunarity, gain) {
    var self = this.ptr;
    /* x <float> [] */
    /* y <float> [] */
    /* noise_type <NoiseType> [] */
    if (noise_type && typeof noise_type === "object") noise_type = noise_type.ptr;
    /* frequency <float> [] */
    /* interp <Interp> [] */
    if (interp && typeof interp === "object") interp = interp.ptr;
    /* fractal_type <FractalType> [] */
    if (fractal_type && typeof fractal_type === "object") fractal_type = fractal_type.ptr;
    /* octaves <int> [] */
    /* lacunarity <float> [] */
    /* gain <float> [] */
    if (interp === undefined) { return _mud_noise_fract_2d_4(x, y, noise_type, frequency); return; }
    if (fractal_type === undefined) { return _mud_noise_fract_2d_5(x, y, noise_type, frequency, interp); return; }
    if (octaves === undefined) { return _mud_noise_fract_2d_6(x, y, noise_type, frequency, interp, fractal_type); return; }
    if (lacunarity === undefined) { return _mud_noise_fract_2d_7(x, y, noise_type, frequency, interp, fractal_type, octaves); return; }
    if (gain === undefined) { return _mud_noise_fract_2d_8(x, y, noise_type, frequency, interp, fractal_type, octaves, lacunarity); return; }
    return _mud_noise_fract_2d_9(x, y, noise_type, frequency, interp, fractal_type, octaves, lacunarity, gain);
};
Module['noise_fract_3d'] = function(x, y, z, noise_type, frequency, interp, fractal_type, octaves, lacunarity, gain) {
    var self = this.ptr;
    /* x <float> [] */
    /* y <float> [] */
    /* z <float> [] */
    /* noise_type <NoiseType> [] */
    if (noise_type && typeof noise_type === "object") noise_type = noise_type.ptr;
    /* frequency <float> [] */
    /* interp <Interp> [] */
    if (interp && typeof interp === "object") interp = interp.ptr;
    /* fractal_type <FractalType> [] */
    if (fractal_type && typeof fractal_type === "object") fractal_type = fractal_type.ptr;
    /* octaves <int> [] */
    /* lacunarity <float> [] */
    /* gain <float> [] */
    if (interp === undefined) { return _mud_noise_fract_3d_5(x, y, z, noise_type, frequency); return; }
    if (fractal_type === undefined) { return _mud_noise_fract_3d_6(x, y, z, noise_type, frequency, interp); return; }
    if (octaves === undefined) { return _mud_noise_fract_3d_7(x, y, z, noise_type, frequency, interp, fractal_type); return; }
    if (lacunarity === undefined) { return _mud_noise_fract_3d_8(x, y, z, noise_type, frequency, interp, fractal_type, octaves); return; }
    if (gain === undefined) { return _mud_noise_fract_3d_9(x, y, z, noise_type, frequency, interp, fractal_type, octaves, lacunarity); return; }
    return _mud_noise_fract_3d_10(x, y, z, noise_type, frequency, interp, fractal_type, octaves, lacunarity, gain);
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
