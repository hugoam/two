// JobSystem
function JobSystem() { throw "cannot construct a JobSystem, no constructor in IDL" }
JobSystem.prototype = Object.create(WrapperObject.prototype);
JobSystem.prototype.constructor = JobSystem;
JobSystem.prototype.__class = JobSystem;
JobSystem.__cache = {};
Module['JobSystem'] = JobSystem;
JobSystem.prototype["__destroy"] = JobSystem.prototype.__destroy = function() {
    _mud_JobSystem__destroy(this.__ptr);
};

(function() {
    function setup() {
        JobSystem.__type = _mud_JobSystem__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
