
// Bindings utilities
function WrapperObject() {
}
// Circlifier
function Circlifier(image) {
    var self = this.ptr;
    /* image <Image256> [] */
    image = image.ptr;
    this.ptr = _mud_Circlifier_Circlifier_1(self, image); getCache(Circlifier)[this.ptr] = this;
};
Circlifier.prototype = Object.create(WrapperObject.prototype);
Circlifier.prototype.constructor = Circlifier;
Circlifier.prototype.__class__ = Circlifier;
Circlifier.__cache__ = {};
Module['Circlifier'] = Circlifier;
Circlifier.prototype["__destroy__"] = Circlifier.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Circlifier___destroy__(self);
};
// Fract
function Fract(num_tabs) {
    var self = this.ptr;
    /* num_tabs <size_t> [] */
    if (num_tabs === undefined) { this.ptr = _mud_Fract_Fract_0(self); getCache(Fract)[this.ptr] = this; return; }
    this.ptr = _mud_Fract_Fract_1(self, num_tabs); getCache(Fract)[this.ptr] = this;
};
Fract.prototype = Object.create(WrapperObject.prototype);
Fract.prototype.constructor = Fract;
Fract.prototype.__class__ = Fract;
Fract.__cache__ = {};
Module['Fract'] = Fract;
Fract.prototype["generate"] = Fract.prototype.generate = function(num_tabs) {
    /* num_tabs <size_t> [] */
    if (num_tabs === undefined) { _mud_Fract_generate_0(); return; }
    _mud_Fract_generate_1(num_tabs);
};
Fract.prototype["regen"] = Fract.prototype.regen = function() {
    _mud_Fract_regen_0();
};
Fract.prototype["render"] = Fract.prototype.render = function(rect, pattern, resolution, output_image) {
    /* rect <Rect> [] */
    rect = rect.ptr;
    /* pattern <Pattern> [] */
    pattern = pattern.ptr;
    /* resolution <uvec2> [] */
    resolution = resolution.ptr;
    /* output_image <Image256> [] */
    output_image = output_image.ptr;
    _mud_Fract_render_4(rect, pattern, resolution, output_image);
};
Fract.prototype["render_whole"] = Fract.prototype.render_whole = function(pattern, resolution, output_image) {
    /* pattern <Pattern> [] */
    pattern = pattern.ptr;
    /* resolution <uvec2> [] */
    resolution = resolution.ptr;
    /* output_image <Image256> [] */
    output_image = output_image.ptr;
    _mud_Fract_render_whole_3(pattern, resolution, output_image);
};
Object.defineProperty(Fract.prototype, "nutabs", {
    get: function() {
        var self = this.ptr;
        return _mud_Fract_get_nutabs(self);
    },
    set: function(nutabs) {
        var self = this.ptr;
        /* nutabs <size_t> [] */
        _mud_Fract_set_nutabs(self, nutabs);
    }
});
Fract.prototype["__destroy__"] = Fract.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Fract___destroy__(self);
};
// FractSample
function FractSample(fract, rect, resolution) {
    var self = this.ptr;
    /* fract <Fract> [] */
    fract = fract.ptr;
    /* rect <Rect> [] */
    rect = rect.ptr;
    /* resolution <uvec2> [] */
    resolution = resolution.ptr;
    this.ptr = _mud_FractSample_FractSample_3(self, fract, rect, resolution); getCache(FractSample)[this.ptr] = this;
};
FractSample.prototype = Object.create(WrapperObject.prototype);
FractSample.prototype.constructor = FractSample;
FractSample.prototype.__class__ = FractSample;
FractSample.__cache__ = {};
Module['FractSample'] = FractSample;
FractSample.prototype["render"] = FractSample.prototype.render = function(pattern, outputImage) {
    /* pattern <Pattern> [] */
    pattern = pattern.ptr;
    /* outputImage <Image256> [] */
    outputImage = outputImage.ptr;
    _mud_FractSample_render_2(pattern, outputImage);
};
Object.defineProperty(FractSample.prototype, "fract", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_FractSample_get_fract(self), mud::Fract);
    }});
Object.defineProperty(FractSample.prototype, "rect", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_FractSample_get_rect(self), mud::Rect);
    },
    set: function(rect) {
        var self = this.ptr;
        /* rect <Rect> [] */
        rect = rect.ptr;
        _mud_FractSample_set_rect(self, rect);
    }
});
Object.defineProperty(FractSample.prototype, "resolution", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_FractSample_get_resolution(self), mud::uvec2);
    },
    set: function(resolution) {
        var self = this.ptr;
        /* resolution <uvec2> [] */
        resolution = resolution.ptr;
        _mud_FractSample_set_resolution(self, resolution);
    }
});
FractSample.prototype["__destroy__"] = FractSample.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FractSample___destroy__(self);
};
// FractTab
function FractTab() {
    var self = this.ptr;
    this.ptr = _mud_FractTab_FractTab_0(self); getCache(FractTab)[this.ptr] = this;
};
FractTab.prototype = Object.create(WrapperObject.prototype);
FractTab.prototype.constructor = FractTab;
FractTab.prototype.__class__ = FractTab;
FractTab.__cache__ = {};
Module['FractTab'] = FractTab;
FractTab.prototype["__destroy__"] = FractTab.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FractTab___destroy__(self);
};
// Pattern
function Pattern(palette, sampling, precision, step) {
    var self = this.ptr;
    /* palette <Palette> [] */
    palette = palette.ptr;
    /* sampling <PatternSampling> [] */
    if (sampling && typeof sampling === "object") sampling = sampling.ptr;
    /* precision <float> [] */
    /* step <size_t> [] */
    if (precision === undefined) { this.ptr = _mud_Pattern_Pattern_2(self, palette, sampling); getCache(Pattern)[this.ptr] = this; return; }
    if (step === undefined) { this.ptr = _mud_Pattern_Pattern_3(self, palette, sampling, precision); getCache(Pattern)[this.ptr] = this; return; }
    this.ptr = _mud_Pattern_Pattern_4(self, palette, sampling, precision, step); getCache(Pattern)[this.ptr] = this;
};
Pattern.prototype = Object.create(WrapperObject.prototype);
Pattern.prototype.constructor = Pattern;
Pattern.prototype.__class__ = Pattern;
Pattern.__cache__ = {};
Module['Pattern'] = Pattern;
Pattern.prototype["__destroy__"] = Pattern.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Pattern___destroy__(self);
};

(function() {
    function setupEnums() {
        // PatternSampling
        Module['PatternSampling']['X'] = _mud_PatternSampling_X();
        Module['PatternSampling']['XY'] = _mud_PatternSampling_XY();
        Module['PatternSampling']['Depth'] = _mud_PatternSampling_Depth();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
