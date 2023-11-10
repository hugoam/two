// Noise
function Noise() { throw "cannot construct a Noise, no constructor in IDL" }
Noise.prototype = Object.create(WrapperObject.prototype);
Noise.prototype.constructor = Noise;
Noise.prototype.__class = Noise;
Noise.__cache = {};
Module['Noise'] = Noise;
Noise.prototype["__destroy"] = Noise.prototype.__destroy = function() {
    _two_Noise__destroy(this.__ptr);
};
Module['noise_2d'] = function(a0, a1, a2, a3, a4) {
    if (a3 === undefined) { if (typeof a0 !== 'number') throw Error('noise_2d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_2d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_2d(2:noise_type): expected integer'); }
    else if (a4 === undefined) { if (typeof a0 !== 'number') throw Error('noise_2d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_2d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_2d(2:noise_type): expected integer'); if (typeof a3 !== 'number') throw Error('noise_2d(3:frequency): expected number'); }
    else { if (typeof a0 !== 'number') throw Error('noise_2d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_2d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_2d(2:noise_type): expected integer'); if (typeof a3 !== 'number') throw Error('noise_2d(3:frequency): expected number'); if (typeof a4 !== 'number') throw Error('noise_2d(4:interp): expected integer'); }
    if (a3 === undefined) { return _two_noise_2d_3(/*x*/a0, /*y*/a1, /*noise_type*/a2); }
    else if (a4 === undefined) { return _two_noise_2d_4(/*x*/a0, /*y*/a1, /*noise_type*/a2, /*frequency*/a3); }
    else { return _two_noise_2d_5(/*x*/a0, /*y*/a1, /*noise_type*/a2, /*frequency*/a3, /*interp*/a4); }
};
Module['noise_3d'] = function(a0, a1, a2, a3, a4, a5) {
    if (a4 === undefined) { if (typeof a0 !== 'number') throw Error('noise_3d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_3d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_3d(2:z): expected number'); if (typeof a3 !== 'number') throw Error('noise_3d(3:noise_type): expected integer'); }
    else if (a5 === undefined) { if (typeof a0 !== 'number') throw Error('noise_3d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_3d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_3d(2:z): expected number'); if (typeof a3 !== 'number') throw Error('noise_3d(3:noise_type): expected integer'); if (typeof a4 !== 'number') throw Error('noise_3d(4:frequency): expected number'); }
    else { if (typeof a0 !== 'number') throw Error('noise_3d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_3d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_3d(2:z): expected number'); if (typeof a3 !== 'number') throw Error('noise_3d(3:noise_type): expected integer'); if (typeof a4 !== 'number') throw Error('noise_3d(4:frequency): expected number'); if (typeof a5 !== 'number') throw Error('noise_3d(5:interp): expected integer'); }
    if (a4 === undefined) { return _two_noise_3d_4(/*x*/a0, /*y*/a1, /*z*/a2, /*noise_type*/a3); }
    else if (a5 === undefined) { return _two_noise_3d_5(/*x*/a0, /*y*/a1, /*z*/a2, /*noise_type*/a3, /*frequency*/a4); }
    else { return _two_noise_3d_6(/*x*/a0, /*y*/a1, /*z*/a2, /*noise_type*/a3, /*frequency*/a4, /*interp*/a5); }
};
Module['noise_fract_2d'] = function(a0, a1, a2, a3, a4, a5, a6, a7, a8) {
    if (a4 === undefined) { if (typeof a0 !== 'number') throw Error('noise_fract_2d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_2d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_2d(2:noise_type): expected integer'); if (typeof a3 !== 'number') throw Error('noise_fract_2d(3:frequency): expected number'); }
    else if (a5 === undefined) { if (typeof a0 !== 'number') throw Error('noise_fract_2d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_2d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_2d(2:noise_type): expected integer'); if (typeof a3 !== 'number') throw Error('noise_fract_2d(3:frequency): expected number'); if (typeof a4 !== 'number') throw Error('noise_fract_2d(4:interp): expected integer'); }
    else if (a6 === undefined) { if (typeof a0 !== 'number') throw Error('noise_fract_2d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_2d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_2d(2:noise_type): expected integer'); if (typeof a3 !== 'number') throw Error('noise_fract_2d(3:frequency): expected number'); if (typeof a4 !== 'number') throw Error('noise_fract_2d(4:interp): expected integer'); if (typeof a5 !== 'number') throw Error('noise_fract_2d(5:fractal_type): expected integer'); }
    else if (a7 === undefined) { if (typeof a0 !== 'number') throw Error('noise_fract_2d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_2d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_2d(2:noise_type): expected integer'); if (typeof a3 !== 'number') throw Error('noise_fract_2d(3:frequency): expected number'); if (typeof a4 !== 'number') throw Error('noise_fract_2d(4:interp): expected integer'); if (typeof a5 !== 'number') throw Error('noise_fract_2d(5:fractal_type): expected integer'); if (typeof a6 !== 'number') throw Error('noise_fract_2d(6:octaves): expected integer'); }
    else if (a8 === undefined) { if (typeof a0 !== 'number') throw Error('noise_fract_2d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_2d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_2d(2:noise_type): expected integer'); if (typeof a3 !== 'number') throw Error('noise_fract_2d(3:frequency): expected number'); if (typeof a4 !== 'number') throw Error('noise_fract_2d(4:interp): expected integer'); if (typeof a5 !== 'number') throw Error('noise_fract_2d(5:fractal_type): expected integer'); if (typeof a6 !== 'number') throw Error('noise_fract_2d(6:octaves): expected integer'); if (typeof a7 !== 'number') throw Error('noise_fract_2d(7:lacunarity): expected number'); }
    else { if (typeof a0 !== 'number') throw Error('noise_fract_2d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_2d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_2d(2:noise_type): expected integer'); if (typeof a3 !== 'number') throw Error('noise_fract_2d(3:frequency): expected number'); if (typeof a4 !== 'number') throw Error('noise_fract_2d(4:interp): expected integer'); if (typeof a5 !== 'number') throw Error('noise_fract_2d(5:fractal_type): expected integer'); if (typeof a6 !== 'number') throw Error('noise_fract_2d(6:octaves): expected integer'); if (typeof a7 !== 'number') throw Error('noise_fract_2d(7:lacunarity): expected number'); if (typeof a8 !== 'number') throw Error('noise_fract_2d(8:gain): expected number'); }
    if (a4 === undefined) { return _two_noise_fract_2d_4(/*x*/a0, /*y*/a1, /*noise_type*/a2, /*frequency*/a3); }
    else if (a5 === undefined) { return _two_noise_fract_2d_5(/*x*/a0, /*y*/a1, /*noise_type*/a2, /*frequency*/a3, /*interp*/a4); }
    else if (a6 === undefined) { return _two_noise_fract_2d_6(/*x*/a0, /*y*/a1, /*noise_type*/a2, /*frequency*/a3, /*interp*/a4, /*fractal_type*/a5); }
    else if (a7 === undefined) { return _two_noise_fract_2d_7(/*x*/a0, /*y*/a1, /*noise_type*/a2, /*frequency*/a3, /*interp*/a4, /*fractal_type*/a5, /*octaves*/a6); }
    else if (a8 === undefined) { return _two_noise_fract_2d_8(/*x*/a0, /*y*/a1, /*noise_type*/a2, /*frequency*/a3, /*interp*/a4, /*fractal_type*/a5, /*octaves*/a6, /*lacunarity*/a7); }
    else { return _two_noise_fract_2d_9(/*x*/a0, /*y*/a1, /*noise_type*/a2, /*frequency*/a3, /*interp*/a4, /*fractal_type*/a5, /*octaves*/a6, /*lacunarity*/a7, /*gain*/a8); }
};
Module['noise_fract_3d'] = function(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) {
    if (a5 === undefined) { if (typeof a0 !== 'number') throw Error('noise_fract_3d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_3d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_3d(2:z): expected number'); if (typeof a3 !== 'number') throw Error('noise_fract_3d(3:noise_type): expected integer'); if (typeof a4 !== 'number') throw Error('noise_fract_3d(4:frequency): expected number'); }
    else if (a6 === undefined) { if (typeof a0 !== 'number') throw Error('noise_fract_3d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_3d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_3d(2:z): expected number'); if (typeof a3 !== 'number') throw Error('noise_fract_3d(3:noise_type): expected integer'); if (typeof a4 !== 'number') throw Error('noise_fract_3d(4:frequency): expected number'); if (typeof a5 !== 'number') throw Error('noise_fract_3d(5:interp): expected integer'); }
    else if (a7 === undefined) { if (typeof a0 !== 'number') throw Error('noise_fract_3d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_3d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_3d(2:z): expected number'); if (typeof a3 !== 'number') throw Error('noise_fract_3d(3:noise_type): expected integer'); if (typeof a4 !== 'number') throw Error('noise_fract_3d(4:frequency): expected number'); if (typeof a5 !== 'number') throw Error('noise_fract_3d(5:interp): expected integer'); if (typeof a6 !== 'number') throw Error('noise_fract_3d(6:fractal_type): expected integer'); }
    else if (a8 === undefined) { if (typeof a0 !== 'number') throw Error('noise_fract_3d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_3d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_3d(2:z): expected number'); if (typeof a3 !== 'number') throw Error('noise_fract_3d(3:noise_type): expected integer'); if (typeof a4 !== 'number') throw Error('noise_fract_3d(4:frequency): expected number'); if (typeof a5 !== 'number') throw Error('noise_fract_3d(5:interp): expected integer'); if (typeof a6 !== 'number') throw Error('noise_fract_3d(6:fractal_type): expected integer'); if (typeof a7 !== 'number') throw Error('noise_fract_3d(7:octaves): expected integer'); }
    else if (a9 === undefined) { if (typeof a0 !== 'number') throw Error('noise_fract_3d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_3d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_3d(2:z): expected number'); if (typeof a3 !== 'number') throw Error('noise_fract_3d(3:noise_type): expected integer'); if (typeof a4 !== 'number') throw Error('noise_fract_3d(4:frequency): expected number'); if (typeof a5 !== 'number') throw Error('noise_fract_3d(5:interp): expected integer'); if (typeof a6 !== 'number') throw Error('noise_fract_3d(6:fractal_type): expected integer'); if (typeof a7 !== 'number') throw Error('noise_fract_3d(7:octaves): expected integer'); if (typeof a8 !== 'number') throw Error('noise_fract_3d(8:lacunarity): expected number'); }
    else { if (typeof a0 !== 'number') throw Error('noise_fract_3d(0:x): expected number'); if (typeof a1 !== 'number') throw Error('noise_fract_3d(1:y): expected number'); if (typeof a2 !== 'number') throw Error('noise_fract_3d(2:z): expected number'); if (typeof a3 !== 'number') throw Error('noise_fract_3d(3:noise_type): expected integer'); if (typeof a4 !== 'number') throw Error('noise_fract_3d(4:frequency): expected number'); if (typeof a5 !== 'number') throw Error('noise_fract_3d(5:interp): expected integer'); if (typeof a6 !== 'number') throw Error('noise_fract_3d(6:fractal_type): expected integer'); if (typeof a7 !== 'number') throw Error('noise_fract_3d(7:octaves): expected integer'); if (typeof a8 !== 'number') throw Error('noise_fract_3d(8:lacunarity): expected number'); if (typeof a9 !== 'number') throw Error('noise_fract_3d(9:gain): expected number'); }
    if (a5 === undefined) { return _two_noise_fract_3d_5(/*x*/a0, /*y*/a1, /*z*/a2, /*noise_type*/a3, /*frequency*/a4); }
    else if (a6 === undefined) { return _two_noise_fract_3d_6(/*x*/a0, /*y*/a1, /*z*/a2, /*noise_type*/a3, /*frequency*/a4, /*interp*/a5); }
    else if (a7 === undefined) { return _two_noise_fract_3d_7(/*x*/a0, /*y*/a1, /*z*/a2, /*noise_type*/a3, /*frequency*/a4, /*interp*/a5, /*fractal_type*/a6); }
    else if (a8 === undefined) { return _two_noise_fract_3d_8(/*x*/a0, /*y*/a1, /*z*/a2, /*noise_type*/a3, /*frequency*/a4, /*interp*/a5, /*fractal_type*/a6, /*octaves*/a7); }
    else if (a9 === undefined) { return _two_noise_fract_3d_9(/*x*/a0, /*y*/a1, /*z*/a2, /*noise_type*/a3, /*frequency*/a4, /*interp*/a5, /*fractal_type*/a6, /*octaves*/a7, /*lacunarity*/a8); }
    else { return _two_noise_fract_3d_10(/*x*/a0, /*y*/a1, /*z*/a2, /*noise_type*/a3, /*frequency*/a4, /*interp*/a5, /*fractal_type*/a6, /*octaves*/a7, /*lacunarity*/a8, /*gain*/a9); }
};

(function() {
    function setup() {
        Noise.prototype.__type = _two_Noise__type();
        // NoiseType
        Module['Noise']['Value'] = _two_Noise_NoiseType_Value();
        Module['Noise']['ValueFractal'] = _two_Noise_NoiseType_ValueFractal();
        Module['Noise']['Perlin'] = _two_Noise_NoiseType_Perlin();
        Module['Noise']['PerlinFractal'] = _two_Noise_NoiseType_PerlinFractal();
        Module['Noise']['Simplex'] = _two_Noise_NoiseType_Simplex();
        Module['Noise']['SimplexFractal'] = _two_Noise_NoiseType_SimplexFractal();
        Module['Noise']['Cellular'] = _two_Noise_NoiseType_Cellular();
        Module['Noise']['WhiteNoise'] = _two_Noise_NoiseType_WhiteNoise();
        Module['Noise']['Cubic'] = _two_Noise_NoiseType_Cubic();
        Module['Noise']['CubicFractal'] = _two_Noise_NoiseType_CubicFractal();
        // Interp
        Module['Noise']['Linear'] = _two_Noise_Interp_Linear();
        Module['Noise']['Hermite'] = _two_Noise_Interp_Hermite();
        Module['Noise']['Quintic'] = _two_Noise_Interp_Quintic();
        // FractalType
        Module['Noise']['FBM'] = _two_Noise_FractalType_FBM();
        Module['Noise']['Billow'] = _two_Noise_FractalType_Billow();
        Module['Noise']['RigidMulti'] = _two_Noise_FractalType_RigidMulti();
        // CellularDistanceFunction
        Module['Noise']['Euclidean'] = _two_Noise_CellularDistanceFunction_Euclidean();
        Module['Noise']['Manhattan'] = _two_Noise_CellularDistanceFunction_Manhattan();
        Module['Noise']['Natural'] = _two_Noise_CellularDistanceFunction_Natural();
        // CellularReturnType
        Module['Noise']['CellValue'] = _two_Noise_CellularReturnType_CellValue();
        Module['Noise']['NoiseLookup'] = _two_Noise_CellularReturnType_NoiseLookup();
        Module['Noise']['Distance'] = _two_Noise_CellularReturnType_Distance();
        Module['Noise']['Distance2'] = _two_Noise_CellularReturnType_Distance2();
        Module['Noise']['Distance2Add'] = _two_Noise_CellularReturnType_Distance2Add();
        Module['Noise']['Distance2Sub'] = _two_Noise_CellularReturnType_Distance2Sub();
        Module['Noise']['Distance2Mul'] = _two_Noise_CellularReturnType_Distance2Mul();
        Module['Noise']['Distance2Div'] = _two_Noise_CellularReturnType_Distance2Div();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
