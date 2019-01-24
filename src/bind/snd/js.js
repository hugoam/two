Module['ui'] = Module['ui'] || {};

(function() {
    function setup() {
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
