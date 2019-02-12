Module['stl'] = Module['stl'] || {};
// Circlifier
function Circlifier(a0) {
    this.ptr = _mud_Circlifier__construct_1(/*image*/a0.ptr); this.type = Circlifier; getCache(Circlifier)[this.ptr] = this;
};
Circlifier.prototype = Object.create(WrapperObject.prototype);
Circlifier.prototype.constructor = Circlifier;
Circlifier.prototype.__class__ = Circlifier;
Circlifier.__cache__ = {};
Module['Circlifier'] = Circlifier;
Circlifier.prototype["__destroy__"] = Circlifier.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Circlifier__destroy(self);
};
// Fract
function Fract(a0) {
    if (a0 === undefined) { this.ptr = _mud_Fract__construct_0(); this.type = Fract; getCache(Fract)[this.ptr] = this; return; }
    this.ptr = _mud_Fract__construct_1(/*num_tabs*/a0); this.type = Fract; getCache(Fract)[this.ptr] = this;
};
Fract.prototype = Object.create(WrapperObject.prototype);
Fract.prototype.constructor = Fract;
Fract.prototype.__class__ = Fract;
Fract.__cache__ = {};
Module['Fract'] = Fract;
Fract.prototype["generate"] = Fract.prototype.generate = function(self, a0) {
    var self = this.ptr;
    if (a0 === undefined) { _mud_Fract_generate_0(self); return; }
    _mud_Fract_generate_1(self, /*num_tabs*/a0);
};
Fract.prototype["regen"] = Fract.prototype.regen = function(self) {
    var self = this.ptr;
    _mud_Fract_regen_0(self);
};
Fract.prototype["render"] = Fract.prototype.render = function(self, a0, a1, a2, a3) {
    var self = this.ptr;
    _mud_Fract_render_4(self, /*rect*/a0.ptr, /*pattern*/a1.ptr, /*resolution*/a2.ptr, /*output_image*/a3.ptr);
};
Fract.prototype["render_whole"] = Fract.prototype.render_whole = function(self, a0, a1, a2) {
    var self = this.ptr;
    _mud_Fract_render_whole_3(self, /*pattern*/a0.ptr, /*resolution*/a1.ptr, /*output_image*/a2.ptr);
};
Object.defineProperty(Fract.prototype, "nutabs", {
    get: function() {
        var self = this.ptr;
        return _mud_Fract__get_nutabs(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fract__set_nutabs(self, value);
    }
});
Fract.prototype["__destroy__"] = Fract.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Fract__destroy(self);
};
// FractSample
function FractSample(a0, a1, a2) {
    this.ptr = _mud_FractSample__construct_3(/*fract*/a0.ptr, /*rect*/a1.ptr, /*resolution*/a2.ptr); this.type = FractSample; getCache(FractSample)[this.ptr] = this;
};
FractSample.prototype = Object.create(WrapperObject.prototype);
FractSample.prototype.constructor = FractSample;
FractSample.prototype.__class__ = FractSample;
FractSample.__cache__ = {};
Module['FractSample'] = FractSample;
FractSample.prototype["render"] = FractSample.prototype.render = function(self, a0, a1) {
    var self = this.ptr;
    _mud_FractSample_render_2(self, /*pattern*/a0.ptr, /*outputImage*/a1.ptr);
};
Object.defineProperty(FractSample.prototype, "fract", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_FractSample__get_fract(self), Fract);
    }});
Object.defineProperty(FractSample.prototype, "rect", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_FractSample__get_rect(self), Rect);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_FractSample__set_rect(self, value.ptr);
    }
});
Object.defineProperty(FractSample.prototype, "resolution", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_FractSample__get_resolution(self), v2_uint);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_FractSample__set_resolution(self, value.ptr);
    }
});
FractSample.prototype["__destroy__"] = FractSample.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FractSample__destroy(self);
};
// FractTab
function FractTab() {
    this.ptr = _mud_FractTab__construct_0(); this.type = FractTab; getCache(FractTab)[this.ptr] = this;
};
FractTab.prototype = Object.create(WrapperObject.prototype);
FractTab.prototype.constructor = FractTab;
FractTab.prototype.__class__ = FractTab;
FractTab.__cache__ = {};
Module['FractTab'] = FractTab;
FractTab.prototype["__destroy__"] = FractTab.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FractTab__destroy(self);
};
// Pattern
function Pattern(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_Pattern__construct_0(); this.type = Pattern; getCache(Pattern)[this.ptr] = this; return; }
    if (a2 === undefined) { this.ptr = _mud_Pattern__construct_2(/*palette*/a0.ptr, /*sampling*/a1); this.type = Pattern; getCache(Pattern)[this.ptr] = this; return; }
    if (a3 === undefined) { this.ptr = _mud_Pattern__construct_3(/*palette*/a0.ptr, /*sampling*/a1, /*precision*/a2); this.type = Pattern; getCache(Pattern)[this.ptr] = this; return; }
    this.ptr = _mud_Pattern__construct_4(/*palette*/a0.ptr, /*sampling*/a1, /*precision*/a2, /*step*/a3); this.type = Pattern; getCache(Pattern)[this.ptr] = this;
};
Pattern.prototype = Object.create(WrapperObject.prototype);
Pattern.prototype.constructor = Pattern;
Pattern.prototype.__class__ = Pattern;
Pattern.__cache__ = {};
Module['Pattern'] = Pattern;
Pattern.prototype["__destroy__"] = Pattern.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Pattern__destroy(self);
};
Module['generate_fract'] = function(a0, a1, a2) {
    _mud_generate_fract_3(/*resolution*/a0.ptr, /*pattern*/a1.ptr, /*output_image*/a2.ptr);
};

(function() {
    function setup() {
        Circlifier.__type__ = _mud_Circlifier__type();
        Fract.__type__ = _mud_Fract__type();
        FractSample.__type__ = _mud_FractSample__type();
        FractTab.__type__ = _mud_FractTab__type();
        Pattern.__type__ = _mud_Pattern__type();
        // PatternSampling
        Module['PatternSampling'] = Module['PatternSampling'] || {};
        Module['PatternSampling']['X'] = _mud_PatternSampling_X();
        Module['PatternSampling']['XY'] = _mud_PatternSampling_XY();
        Module['PatternSampling']['Depth'] = _mud_PatternSampling_Depth();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
