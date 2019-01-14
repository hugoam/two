// Entity
function Entity() {
    this.ptr = _mud_Entity_Entity_0(); getCache(Entity)[this.ptr] = this;
    this.type = Entity;
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
    function setup() {
        Entity.__type__ = _mud_Entity__type();
        Prototype.__type__ = _mud_Prototype__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
