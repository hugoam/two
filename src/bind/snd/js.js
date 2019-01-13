Module['glm'] = Module['glm'] || {};
Module['ui'] = Module['ui'] || {};

(function() {
    function setupEnums() {
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
