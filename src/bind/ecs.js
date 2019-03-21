// Entity
function Entity() {
    this.__ptr = _mud_Entity__construct_0(); this.__type = Entity.__type; getCache(Entity)[this.__ptr] = this;
};
Entity.prototype = Object.create(WrapperObject.prototype);
Entity.prototype.constructor = Entity;
Entity.prototype.__class = Entity;
Entity.__cache = {};
Module['Entity'] = Entity;
Entity.prototype["__destroy"] = Entity.prototype.__destroy = function() {
    _mud_Entity__destroy(this.__ptr);
};
// Entt
function Entt() {
    this.__ptr = _mud_Entt__construct_0(); this.__type = Entt.__type; getCache(Entt)[this.__ptr] = this;
};
Entt.prototype = Object.create(WrapperObject.prototype);
Entt.prototype.constructor = Entt;
Entt.prototype.__class = Entt;
Entt.__cache = {};
Module['Entt'] = Entt;
Entt.prototype["__destroy"] = Entt.prototype.__destroy = function() {
    _mud_Entt__destroy(this.__ptr);
};
// OEntt
function OEntt() { throw "cannot construct a OEntt, no constructor in IDL" }
OEntt.prototype = Object.create(Entt.prototype);
OEntt.prototype.constructor = OEntt;
OEntt.prototype.__class = OEntt;
OEntt.__cache = {};
Module['OEntt'] = OEntt;
OEntt.prototype["__destroy"] = OEntt.prototype.__destroy = function() {
    _mud_OEntt__destroy(this.__ptr);
};

(function() {
    function setup() {
        Entity.__type = _mud_Entity__type();
        Entt.__type = _mud_Entt__type();
        OEntt.__type = _mud_OEntt__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
