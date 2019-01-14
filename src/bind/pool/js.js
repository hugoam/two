// HandlePool
function HandlePool() { throw "cannot construct a HandlePool, no constructor in IDL" }
HandlePool.prototype = Object.create(WrapperObject.prototype);
HandlePool.prototype.constructor = HandlePool;
HandlePool.prototype.__class__ = HandlePool;
HandlePool.__cache__ = {};
HandlePool.__type__ = _mud_HandlePool__type();
Module['HandlePool'] = HandlePool;
HandlePool.prototype["__destroy__"] = HandlePool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_HandlePool__destroy(self);
};
// Pool
function Pool() { throw "cannot construct a Pool, no constructor in IDL" }
Pool.prototype = Object.create(WrapperObject.prototype);
Pool.prototype.constructor = Pool;
Pool.prototype.__class__ = Pool;
Pool.__cache__ = {};
Pool.__type__ = _mud_Pool__type();
Module['Pool'] = Pool;
Pool.prototype["__destroy__"] = Pool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Pool__destroy(self);
};

(function() {
    function setupEnums() {
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
