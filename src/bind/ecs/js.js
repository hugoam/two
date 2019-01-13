
// Bindings utilities
function WrapperObject() {
}
// Complex
function Complex(id, type, parts) {
    /* id <mud::Id> [] */
    /* type <Type> [] */
    type = type.ptr;
    /* parts <std::vector<mud::Ref>> [] */
    parts = parts.ptr;
    if (parts === undefined) { this.ptr = _mud_Complex_Complex_2(id, type); getCache(Complex)[this.ptr] = this; return; }
    this.ptr = _mud_Complex_Complex_3(id, type, parts); getCache(Complex)[this.ptr] = this;
};
Complex.prototype = Object.create(WrapperObject.prototype);
Complex.prototype.constructor = Complex;
Complex.prototype.__class__ = Complex;
Complex.__cache__ = {};
Module['Complex'] = Complex;
Complex.prototype["has_part"] = Complex.prototype.has_part = function(self, type) {
    var self = this.ptr;
    /* type <Type> [] */
    type = type.ptr;
    return !!(_mud_Complex_has_part_1(self, type));
};
Object.defineProperty(Complex.prototype, "id", {
    get: function() {
        var self = this.ptr;
        return _mud_Complex__get_id(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Id> [] */
        _mud_Complex__set_id(self, value);
    }
});
Object.defineProperty(Complex.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Complex__get_type(self), Type);
    }});
Object.defineProperty(Complex.prototype, "prototype", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Complex__get_prototype(self), Prototype);
    }});
Complex.prototype["__destroy__"] = Complex.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Complex__destroy(self);
};
// Entity
function Entity() {
    this.ptr = _mud_Entity_Entity_0(); getCache(Entity)[this.ptr] = this;
};
Entity.prototype = Object.create(WrapperObject.prototype);
Entity.prototype.constructor = Entity;
Entity.prototype.__class__ = Entity;
Entity.__cache__ = {};
Module['Entity'] = Entity;
Entity.prototype["__destroy__"] = Entity.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Entity__destroy(self);
};
// Prototype
function Prototype() { throw "cannot construct a Prototype, no constructor in IDL" }
Prototype.prototype = Object.create(WrapperObject.prototype);
Prototype.prototype.constructor = Prototype;
Prototype.prototype.__class__ = Prototype;
Prototype.__cache__ = {};
Module['Prototype'] = Prototype;
Prototype.prototype["__destroy__"] = Prototype.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Prototype__destroy(self);
};

(function() {
    function setupEnums() {
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
