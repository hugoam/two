// Entity
function Entity() {
    
    this.__ptr = _two_Entity__construct_0(); getCache(Entity)[this.__ptr] = this;
};
Entity.prototype = Object.create(WrapperObject.prototype);
Entity.prototype.constructor = Entity;
Entity.prototype.__class = Entity;
Entity.__cache = {};
Module['Entity'] = Entity;
Entity.prototype["__destroy"] = Entity.prototype.__destroy = function() {
    _two_Entity__destroy(this.__ptr);
};
// Entt
function Entt() {
    
    this.__ptr = _two_Entt__construct_0(); getCache(Entt)[this.__ptr] = this;
};
Entt.prototype = Object.create(WrapperObject.prototype);
Entt.prototype.constructor = Entt;
Entt.prototype.__class = Entt;
Entt.__cache = {};
Module['Entt'] = Entt;
Entt.prototype["__destroy"] = Entt.prototype.__destroy = function() {
    _two_Entt__destroy(this.__ptr);
};
// OEntt
function OEntt() { throw "cannot construct a OEntt, no constructor in IDL" }
OEntt.prototype = Object.create(Entt.prototype);
OEntt.prototype.constructor = OEntt;
OEntt.prototype.__class = OEntt;
OEntt.__base = Entt;
OEntt.__cache = {};
Module['OEntt'] = OEntt;
OEntt.prototype["__destroy"] = OEntt.prototype.__destroy = function() {
    _two_OEntt__destroy(this.__ptr);
};

(function() {
    function setup() {
        Entity.prototype.__type = _two_Entity__type();
        Entt.prototype.__type = _two_Entt__type();
        OEntt.prototype.__type = _two_OEntt__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
