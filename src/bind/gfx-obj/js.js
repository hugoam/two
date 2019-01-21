Module['glm'] = Module['glm'] || {};
Module['ui'] = Module['ui'] || {};
Module['gfx'] = Module['gfx'] || {};

(function() {
    function setup() {
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
