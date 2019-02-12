// ScriptEditor
function ScriptEditor() { throw "cannot construct a ScriptEditor, no constructor in IDL" }
ScriptEditor.prototype = Object.create(WrapperObject.prototype);
ScriptEditor.prototype.constructor = ScriptEditor;
ScriptEditor.prototype.__class__ = ScriptEditor;
ScriptEditor.__cache__ = {};
Module['ScriptEditor'] = ScriptEditor;
ScriptEditor.prototype["__destroy__"] = ScriptEditor.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ScriptEditor__destroy(self);
};
Module['object_edit_inline'] = function(a0, a1) {
    return !!(_mud_object_edit_inline_2(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)));
};
Module['object_edit_rows'] = function(a0, a1) {
    return !!(_mud_object_edit_rows_2(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)));
};
Module['object_edit_columns'] = function(a0, a1) {
    return !!(_mud_object_edit_columns_2(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)));
};
Module['object_edit_table'] = function(a0, a1) {
    return !!(_mud_object_edit_table_2(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)));
};
Module['object_edit_expandbox'] = function(a0, a1) {
    return !!(_mud_object_edit_expandbox_2(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)));
};
Module['object_edit'] = function(a0, a1, a2) {
    if (a2 === undefined) { return !!(_mud_object_edit_2(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1))); }
    return !!(_mud_object_edit_3(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1), /*hint*/a2));
};
Module['entity_edit'] = function(a0, a1, a2) {
    if (a2 === undefined) { return !!(_mud_entity_edit_2(/*parent*/a0.ptr, /*entity*/a1.ptr)); }
    return !!(_mud_entity_edit_3(/*parent*/a0.ptr, /*entity*/a1.ptr, /*hint*/a2));
};
Module['inspector'] = function(a0, a1) {
    if (a1 === undefined) { return !!(_mud_inspector_1(/*parent*/a0.ptr)); }
    return !!(_mud_inspector_2(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)));
};

(function() {
    function setup() {
        ScriptEditor.__type__ = _mud_ScriptEditor__type();
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
