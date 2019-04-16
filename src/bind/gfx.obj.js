// ImporterOBJ
function ImporterOBJ(a0) {
    if (!checkClass(a0, GfxSystem) throw Error('ImporterOBJ(0:gfx): expected GfxSystem');
    this.__ptr = _mud_ImporterOBJ__construct_1(/*gfx*/a0.__ptr); getCache(ImporterOBJ)[this.__ptr] = this;
};
ImporterOBJ.prototype = Object.create(WrapperObject.prototype);
ImporterOBJ.prototype.constructor = ImporterOBJ;
ImporterOBJ.prototype.__class = ImporterOBJ;
ImporterOBJ.__cache = {};
Module['ImporterOBJ'] = ImporterOBJ;
ImporterOBJ.prototype["import"] = ImporterOBJ.prototype.import = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Import) throw Error('import(0:import): expected Import'); if (typeof a1 !== 'string') throw Error('import(1:filepath): expected string'); if (!checkClass(a2, ImportConfig) throw Error('import(2:config): expected ImportConfig');
    _mud_ImporterOBJ_import_3(this.__ptr, /*import*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterOBJ.prototype["import_model"] = ImporterOBJ.prototype.import_model = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Model) throw Error('import_model(0:model): expected Model'); if (typeof a1 !== 'string') throw Error('import_model(1:filepath): expected string'); if (!checkClass(a2, ImportConfig) throw Error('import_model(2:config): expected ImportConfig');
    _mud_ImporterOBJ_import_model_3(this.__ptr, /*model*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterOBJ.prototype["import_prefab"] = ImporterOBJ.prototype.import_prefab = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Prefab) throw Error('import_prefab(0:prefab): expected Prefab'); if (typeof a1 !== 'string') throw Error('import_prefab(1:filepath): expected string'); if (!checkClass(a2, ImportConfig) throw Error('import_prefab(2:config): expected ImportConfig');
    _mud_ImporterOBJ_import_prefab_3(this.__ptr, /*prefab*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterOBJ.prototype["repack"] = ImporterOBJ.prototype.repack = function(a0, a1) {
    ensureCache.prepare();
    if (typeof a0 !== 'string') throw Error('repack(0:filepath): expected string'); if (!checkClass(a1, ImportConfig) throw Error('repack(1:config): expected ImportConfig');
    _mud_ImporterOBJ_repack_2(this.__ptr, ensureString(/*filepath*/a0), /*config*/a1.__ptr);
};
ImporterOBJ.prototype["__destroy"] = ImporterOBJ.prototype.__destroy = function() {
    _mud_ImporterOBJ__destroy(this.__ptr);
};
// ImporterPLY
function ImporterPLY(a0) {
    if (!checkClass(a0, GfxSystem) throw Error('ImporterPLY(0:gfx): expected GfxSystem');
    this.__ptr = _mud_ImporterPLY__construct_1(/*gfx*/a0.__ptr); getCache(ImporterPLY)[this.__ptr] = this;
};
ImporterPLY.prototype = Object.create(WrapperObject.prototype);
ImporterPLY.prototype.constructor = ImporterPLY;
ImporterPLY.prototype.__class = ImporterPLY;
ImporterPLY.__cache = {};
Module['ImporterPLY'] = ImporterPLY;
ImporterPLY.prototype["import"] = ImporterPLY.prototype.import = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Import) throw Error('import(0:import): expected Import'); if (typeof a1 !== 'string') throw Error('import(1:filepath): expected string'); if (!checkClass(a2, ImportConfig) throw Error('import(2:config): expected ImportConfig');
    _mud_ImporterPLY_import_3(this.__ptr, /*import*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterPLY.prototype["import_model"] = ImporterPLY.prototype.import_model = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Model) throw Error('import_model(0:model): expected Model'); if (typeof a1 !== 'string') throw Error('import_model(1:filepath): expected string'); if (!checkClass(a2, ImportConfig) throw Error('import_model(2:config): expected ImportConfig');
    _mud_ImporterPLY_import_model_3(this.__ptr, /*model*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterPLY.prototype["import_prefab"] = ImporterPLY.prototype.import_prefab = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Prefab) throw Error('import_prefab(0:prefab): expected Prefab'); if (typeof a1 !== 'string') throw Error('import_prefab(1:filepath): expected string'); if (!checkClass(a2, ImportConfig) throw Error('import_prefab(2:config): expected ImportConfig');
    _mud_ImporterPLY_import_prefab_3(this.__ptr, /*prefab*/a0.__ptr, ensureString(/*filepath*/a1), /*config*/a2.__ptr);
};
ImporterPLY.prototype["repack"] = ImporterPLY.prototype.repack = function(a0, a1) {
    ensureCache.prepare();
    if (typeof a0 !== 'string') throw Error('repack(0:filepath): expected string'); if (!checkClass(a1, ImportConfig) throw Error('repack(1:config): expected ImportConfig');
    _mud_ImporterPLY_repack_2(this.__ptr, ensureString(/*filepath*/a0), /*config*/a1.__ptr);
};
ImporterPLY.prototype["__destroy"] = ImporterPLY.prototype.__destroy = function() {
    _mud_ImporterPLY__destroy(this.__ptr);
};

(function() {
    function setup() {
        ImporterOBJ.prototype.__type = _mud_ImporterOBJ__type();
        ImporterPLY.prototype.__type = _mud_ImporterPLY__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
