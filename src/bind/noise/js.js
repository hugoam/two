Module['glm'] = Module['glm'] || {};
// Noise
function Noise() { throw "cannot construct a Noise, no constructor in IDL" }
Noise.prototype = Object.create(WrapperObject.prototype);
Noise.prototype.constructor = Noise;
Noise.prototype.__class__ = Noise;
Noise.__cache__ = {};
Noise.__type__ = _mud_Noise__type();
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
    if (frequency === undefined) { return _mud_noise_2d_3(x, y, noise_type); }
    if (interp === undefined) { return _mud_noise_2d_4(x, y, noise_type, frequency); }
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
    if (frequency === undefined) { return _mud_noise_3d_4(x, y, z, noise_type); }
    if (interp === undefined) { return _mud_noise_3d_5(x, y, z, noise_type, frequency); }
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
    if (interp === undefined) { return _mud_noise_fract_2d_4(x, y, noise_type, frequency); }
    if (fractal_type === undefined) { return _mud_noise_fract_2d_5(x, y, noise_type, frequency, interp); }
    if (octaves === undefined) { return _mud_noise_fract_2d_6(x, y, noise_type, frequency, interp, fractal_type); }
    if (lacunarity === undefined) { return _mud_noise_fract_2d_7(x, y, noise_type, frequency, interp, fractal_type, octaves); }
    if (gain === undefined) { return _mud_noise_fract_2d_8(x, y, noise_type, frequency, interp, fractal_type, octaves, lacunarity); }
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
    if (interp === undefined) { return _mud_noise_fract_3d_5(x, y, z, noise_type, frequency); }
    if (fractal_type === undefined) { return _mud_noise_fract_3d_6(x, y, z, noise_type, frequency, interp); }
    if (octaves === undefined) { return _mud_noise_fract_3d_7(x, y, z, noise_type, frequency, interp, fractal_type); }
    if (lacunarity === undefined) { return _mud_noise_fract_3d_8(x, y, z, noise_type, frequency, interp, fractal_type, octaves); }
    if (gain === undefined) { return _mud_noise_fract_3d_9(x, y, z, noise_type, frequency, interp, fractal_type, octaves, lacunarity); }
    return _mud_noise_fract_3d_10(x, y, z, noise_type, frequency, interp, fractal_type, octaves, lacunarity, gain);
};

(function() {
    function setupEnums() {
        // CellularDistanceFunction
        Module['Noise']['Euclidean'] = _mud_Noise_CellularDistanceFunction_Euclidean();
        Module['Noise']['Manhattan'] = _mud_Noise_CellularDistanceFunction_Manhattan();
        Module['Noise']['Natural'] = _mud_Noise_CellularDistanceFunction_Natural();
        // CellularReturnType
        Module['Noise']['CellValue'] = _mud_Noise_CellularReturnType_CellValue();
        Module['Noise']['NoiseLookup'] = _mud_Noise_CellularReturnType_NoiseLookup();
        Module['Noise']['Distance'] = _mud_Noise_CellularReturnType_Distance();
        Module['Noise']['Distance2'] = _mud_Noise_CellularReturnType_Distance2();
        Module['Noise']['Distance2Add'] = _mud_Noise_CellularReturnType_Distance2Add();
        Module['Noise']['Distance2Sub'] = _mud_Noise_CellularReturnType_Distance2Sub();
        Module['Noise']['Distance2Mul'] = _mud_Noise_CellularReturnType_Distance2Mul();
        Module['Noise']['Distance2Div'] = _mud_Noise_CellularReturnType_Distance2Div();
        // FractalType
        Module['Noise']['FBM'] = _mud_Noise_FractalType_FBM();
        Module['Noise']['Billow'] = _mud_Noise_FractalType_Billow();
        Module['Noise']['RigidMulti'] = _mud_Noise_FractalType_RigidMulti();
        // Interp
        Module['Noise']['Linear'] = _mud_Noise_Interp_Linear();
        Module['Noise']['Hermite'] = _mud_Noise_Interp_Hermite();
        Module['Noise']['Quintic'] = _mud_Noise_Interp_Quintic();
        // NoiseType
        Module['Noise']['Value'] = _mud_Noise_NoiseType_Value();
        Module['Noise']['ValueFractal'] = _mud_Noise_NoiseType_ValueFractal();
        Module['Noise']['Perlin'] = _mud_Noise_NoiseType_Perlin();
        Module['Noise']['PerlinFractal'] = _mud_Noise_NoiseType_PerlinFractal();
        Module['Noise']['Simplex'] = _mud_Noise_NoiseType_Simplex();
        Module['Noise']['SimplexFractal'] = _mud_Noise_NoiseType_SimplexFractal();
        Module['Noise']['Cellular'] = _mud_Noise_NoiseType_Cellular();
        Module['Noise']['WhiteNoise'] = _mud_Noise_NoiseType_WhiteNoise();
        Module['Noise']['Cubic'] = _mud_Noise_NoiseType_Cubic();
        Module['Noise']['CubicFractal'] = _mud_Noise_NoiseType_CubicFractal();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
