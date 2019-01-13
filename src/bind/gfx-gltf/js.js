Module['glm'] = Module['glm'] || {};
Module['gfx'] = Module['gfx'] || {};
Module['ui'] = Module['ui'] || {};

(function() {
    function setupEnums() {
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
