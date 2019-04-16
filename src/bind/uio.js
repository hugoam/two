// ScriptEditor
function ScriptEditor() { throw "cannot construct a ScriptEditor, no constructor in IDL" }
ScriptEditor.prototype = Object.create(WrapperObject.prototype);
ScriptEditor.prototype.constructor = ScriptEditor;
ScriptEditor.prototype.__class = ScriptEditor;
ScriptEditor.__cache = {};
Module['ScriptEditor'] = ScriptEditor;
ScriptEditor.prototype["__destroy"] = ScriptEditor.prototype.__destroy = function() {
    _mud_ScriptEditor__destroy(this.__ptr);
};
Module['object_edit_inline'] = function(a0, a1) {
    if (!checkClass(a0, Widget) throw Error('object_edit_inline(0:parent): expected Widget'); if (!checkClass(a1, Ref) throw Error('object_edit_inline(1:object): expected Ref');
    return !!(_mud_object_edit_inline_2(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)));
};
Module['object_edit_rows'] = function(a0, a1) {
    if (!checkClass(a0, Widget) throw Error('object_edit_rows(0:parent): expected Widget'); if (!checkClass(a1, Ref) throw Error('object_edit_rows(1:object): expected Ref');
    return !!(_mud_object_edit_rows_2(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)));
};
Module['object_edit_columns'] = function(a0, a1) {
    if (!checkClass(a0, Widget) throw Error('object_edit_columns(0:parent): expected Widget'); if (!checkClass(a1, Ref) throw Error('object_edit_columns(1:object): expected Ref');
    return !!(_mud_object_edit_columns_2(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)));
};
Module['object_edit_table'] = function(a0, a1) {
    if (!checkClass(a0, Widget) throw Error('object_edit_table(0:parent): expected Widget'); if (!checkClass(a1, Ref) throw Error('object_edit_table(1:object): expected Ref');
    return !!(_mud_object_edit_table_2(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)));
};
Module['object_edit_expandbox'] = function(a0, a1) {
    if (!checkClass(a0, Widget) throw Error('object_edit_expandbox(0:parent): expected Widget'); if (!checkClass(a1, Ref) throw Error('object_edit_expandbox(1:object): expected Ref');
    return !!(_mud_object_edit_expandbox_2(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)));
};
Module['object_edit'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget) throw Error('object_edit(0:parent): expected Widget'); if (!checkClass(a1, Ref) throw Error('object_edit(1:object): expected Ref'); }
    else { if (!checkClass(a0, Widget) throw Error('object_edit(0:parent): expected Widget'); if (!checkClass(a1, Ref) throw Error('object_edit(1:object): expected Ref'); if (typeof a2 !== 'number') throw Error('object_edit(2:hint): expected integer'); }
    if (a2 === undefined) { return !!(_mud_object_edit_2(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1))); }
    else { return !!(_mud_object_edit_3(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1), /*hint*/a2)); }
};
Module['entity_edit'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget) throw Error('entity_edit(0:parent): expected Widget'); if (!checkClass(a1, Entity) throw Error('entity_edit(1:entity): expected Entity'); }
    else { if (!checkClass(a0, Widget) throw Error('entity_edit(0:parent): expected Widget'); if (!checkClass(a1, Entity) throw Error('entity_edit(1:entity): expected Entity'); if (typeof a2 !== 'number') throw Error('entity_edit(2:hint): expected integer'); }
    if (a2 === undefined) { return !!(_mud_entity_edit_2(/*parent*/a0.__ptr, /*entity*/a1.__ptr)); }
    else { return !!(_mud_entity_edit_3(/*parent*/a0.__ptr, /*entity*/a1.__ptr, /*hint*/a2)); }
};
Module['inspector'] = function(a0, a1) {
    if (a1 === undefined) { if (!checkClass(a0, Widget) throw Error('inspector(0:parent): expected Widget'); }
    else { if (!checkClass(a0, Widget) throw Error('inspector(0:parent): expected Widget'); if (!checkClass(a1, Ref) throw Error('inspector(1:object): expected Ref'); }
    if (a1 === undefined) { return !!(_mud_inspector_1(/*parent*/a0.__ptr)); }
    else { return !!(_mud_inspector_2(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1))); }
};

(function() {
    function setup() {
        ScriptEditor.prototype.__type = _mud_ScriptEditor__type();
        // EditNestMode
        Module['EditNestMode'] = Module['EditNestMode'] || {};
        Module['EditNestMode']['Inline'] = _mud_EditNestMode_Inline();
        Module['EditNestMode']['Modal'] = _mud_EditNestMode_Modal();
        Module['EditNestMode']['Embed'] = _mud_EditNestMode_Embed();
        // EditorHint
        Module['EditorHint'] = Module['EditorHint'] || {};
        Module['EditorHint']['Table'] = _mud_EditorHint_Table();
        Module['EditorHint']['Rows'] = _mud_EditorHint_Rows();
        Module['EditorHint']['Inline'] = _mud_EditorHint_Inline();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
