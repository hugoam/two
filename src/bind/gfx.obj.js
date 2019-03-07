// ImporterOBJ
function ImporterOBJ(a0) {
    this.__ptr = _mud_ImporterOBJ__construct_1(/*gfx*/a0.__ptr); this.__type = ImporterOBJ.__type; getCache(ImporterOBJ)[this.__ptr] = this;
};
ImporterOBJ.prototype = Object.create(WrapperObject.prototype);
ImporterOBJ.prototype.constructor = ImporterOBJ;
ImporterOBJ.prototype.__class = ImporterOBJ;
ImporterOBJ.__cache = {};
Module['ImporterOBJ'] = ImporterOBJ;
ImporterOBJ.prototype["import"] = ImporterOBJ.prototype.import = function(a0, a1, a2) {
    ensureCache.prepare();
    _mud_ImporterOBJ_import_3(this.__ptr, /*import*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterOBJ.prototype["import_model"] = ImporterOBJ.prototype.import_model = function(a0, a1, a2) {
    ensureCache.prepare();
    _mud_ImporterOBJ_import_model_3(this.__ptr, /*model*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterOBJ.prototype["import_prefab"] = ImporterOBJ.prototype.import_prefab = function(a0, a1, a2) {
    ensureCache.prepare();
    _mud_ImporterOBJ_import_prefab_3(this.__ptr, /*prefab*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterOBJ.prototype["repack"] = ImporterOBJ.prototype.repack = function(a0, a1) {
    ensureCache.prepare();
    _mud_ImporterOBJ_repack_2(this.__ptr, ensureString(/*filepath*/a0), /*config*/a1.__ptr);
};
ImporterOBJ.prototype["__destroy"] = ImporterOBJ.prototype.__destroy = function() {
    _mud_ImporterOBJ__destroy(this.__ptr);
};

(function() {
    function setup() {
        ImporterOBJ.__type = _mud_ImporterOBJ__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
