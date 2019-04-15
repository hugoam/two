// HandlePool
function HandlePool() { throw "cannot construct a HandlePool, no constructor in IDL" }
HandlePool.prototype = Object.create(WrapperObject.prototype);
HandlePool.prototype.constructor = HandlePool;
HandlePool.prototype.__class = HandlePool;
HandlePool.__cache = {};
Module['HandlePool'] = HandlePool;
HandlePool.prototype["__destroy"] = HandlePool.prototype.__destroy = function() {
    _mud_HandlePool__destroy(this.__ptr);
};
// Pool
function Pool() { throw "cannot construct a Pool, no constructor in IDL" }
Pool.prototype = Object.create(WrapperObject.prototype);
Pool.prototype.constructor = Pool;
Pool.prototype.__class = Pool;
Pool.__cache = {};
Module['Pool'] = Pool;
Pool.prototype["__destroy"] = Pool.prototype.__destroy = function() {
    _mud_Pool__destroy(this.__ptr);
};

(function() {
    function setup() {
        HandlePool.prototype.__type = _mud_HandlePool__type();
        Pool.prototype.__type = _mud_Pool__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
