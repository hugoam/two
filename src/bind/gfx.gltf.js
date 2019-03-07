// ImporterGltf
function ImporterGltf(a0) {
    this.__ptr = _mud_ImporterGltf__construct_1(/*gfx*/a0.__ptr); this.__type = ImporterGltf.__type; getCache(ImporterGltf)[this.__ptr] = this;
};
ImporterGltf.prototype = Object.create(WrapperObject.prototype);
ImporterGltf.prototype.constructor = ImporterGltf;
ImporterGltf.prototype.__class = ImporterGltf;
ImporterGltf.__cache = {};
Module['ImporterGltf'] = ImporterGltf;
ImporterGltf.prototype["import"] = ImporterGltf.prototype.import = function(a0, a1, a2) {
    ensureCache.prepare();
    _mud_ImporterGltf_import_3(this.__ptr, /*import*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterGltf.prototype["import_model"] = ImporterGltf.prototype.import_model = function(a0, a1, a2) {
    ensureCache.prepare();
    _mud_ImporterGltf_import_model_3(this.__ptr, /*model*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterGltf.prototype["import_prefab"] = ImporterGltf.prototype.import_prefab = function(a0, a1, a2) {
    ensureCache.prepare();
    _mud_ImporterGltf_import_prefab_3(this.__ptr, /*prefab*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterGltf.prototype["repack"] = ImporterGltf.prototype.repack = function(a0, a1) {
    ensureCache.prepare();
    _mud_ImporterGltf_repack_2(this.__ptr, ensureString(/*filepath*/a0), /*config*/a1.__ptr);
};
ImporterGltf.prototype["__destroy"] = ImporterGltf.prototype.__destroy = function() {
    _mud_ImporterGltf__destroy(this.__ptr);
};

(function() {
    function setup() {
        ImporterGltf.__type = _mud_ImporterGltf__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
