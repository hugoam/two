
(function() {
    function setup() {
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
