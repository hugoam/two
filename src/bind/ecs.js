// Entity
function Entity() {
    this.ptr = _mud_Entity__construct_0(); getCache(Entity)[this.ptr] = this;
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

(function() {
    function setup() {
        Entity.__type__ = _mud_Entity__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
