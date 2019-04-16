// ImporterGltf
function ImporterGltf(a0) {
    if (!checkClass(a0, GfxSystem)) throw Error('ImporterGltf(0:gfx): expected GfxSystem');
    this.__ptr = _mud_ImporterGltf__construct_1(/*gfx*/a0.__ptr); getCache(ImporterGltf)[this.__ptr] = this;
};
ImporterGltf.prototype = Object.create(WrapperObject.prototype);
ImporterGltf.prototype.constructor = ImporterGltf;
ImporterGltf.prototype.__class = ImporterGltf;
ImporterGltf.__cache = {};
Module['ImporterGltf'] = ImporterGltf;
ImporterGltf.prototype["import"] = ImporterGltf.prototype.import = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Import)) throw Error('import(0:import): expected Import'); if (typeof a1 !== 'string') throw Error('import(1:filepath): expected string'); if (!checkClass(a2, ImportConfig)) throw Error('import(2:config): expected ImportConfig');
    _mud_ImporterGltf_import_3(this.__ptr, /*import*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterGltf.prototype["import_model"] = ImporterGltf.prototype.import_model = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Model)) throw Error('import_model(0:model): expected Model'); if (typeof a1 !== 'string') throw Error('import_model(1:filepath): expected string'); if (!checkClass(a2, ImportConfig)) throw Error('import_model(2:config): expected ImportConfig');
    _mud_ImporterGltf_import_model_3(this.__ptr, /*model*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterGltf.prototype["import_prefab"] = ImporterGltf.prototype.import_prefab = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Prefab)) throw Error('import_prefab(0:prefab): expected Prefab'); if (typeof a1 !== 'string') throw Error('import_prefab(1:filepath): expected string'); if (!checkClass(a2, ImportConfig)) throw Error('import_prefab(2:config): expected ImportConfig');
    _mud_ImporterGltf_import_prefab_3(this.__ptr, /*prefab*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterGltf.prototype["repack"] = ImporterGltf.prototype.repack = function(a0, a1) {
    ensureCache.prepare();
    if (typeof a0 !== 'string') throw Error('repack(0:filepath): expected string'); if (!checkClass(a1, ImportConfig)) throw Error('repack(1:config): expected ImportConfig');
    _mud_ImporterGltf_repack_2(this.__ptr, ensureString(/*filepath*/a0), /*config*/a1.__ptr);
};
ImporterGltf.prototype["__destroy"] = ImporterGltf.prototype.__destroy = function() {
    _mud_ImporterGltf__destroy(this.__ptr);
};

(function() {
    function setup() {
        ImporterGltf.prototype.__type = _mud_ImporterGltf__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
