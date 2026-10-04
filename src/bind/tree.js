// NodeKey
function NodeKey() {
    this.__ptr = _two_NodeKey__construct_0(); getCache(NodeKey)[this.__ptr] = this;
};
NodeKey.prototype = Object.create(WrapperObject.prototype);
NodeKey.prototype.constructor = NodeKey;
NodeKey.prototype.__class = NodeKey;
NodeKey.__cache = {};
Module['NodeKey'] = NodeKey;
Object.defineProperty(NodeKey.prototype, "value", {
    get: function() {
        return _two_NodeKey__get_value(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('NodeKey.value: expected integer');
        _two_NodeKey__set_value(this.__ptr, value);
    }
});
NodeKey.prototype["__destroy"] = NodeKey.prototype.__destroy = function() {
    _two_NodeKey__destroy(this.__ptr);
};

(function() {
    function setup() {
        NodeKey.prototype.__type = _two_NodeKey__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
