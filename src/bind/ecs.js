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

(function() {
    function setup() {
        Entity.__type = _mud_Entity__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
