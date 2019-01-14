Module['glm'] = Module['glm'] || {};
Module['gfx'] = Module['gfx'] || {};
Module['ui'] = Module['ui'] || {};

(function() {
    function setup() {
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
