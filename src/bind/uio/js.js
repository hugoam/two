Module['glm'] = Module['glm'] || {};
Module['ui'] = Module['ui'] || {};
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
Module['entity_edit'] = function(parent, entity, hint) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* entity <Entity> [] */
    entity = entity.ptr;
    /* hint <EditorHint> [] */
    if (hint && typeof hint === "object") hint = hint.ptr;
    if (hint === undefined) { return !!(_mud_entity_edit_2(parent, entity)); }
    return !!(_mud_entity_edit_3(parent, entity, hint));
};
Module['inspector'] = function(parent, object) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* object <Ref> [] */
    var object_type;
    if(typeof object !== "undefined" && object !== null) { object = object.ptr; object_type = object.type.__type__; }
    else { object = 0; object_type = 0; }
    return !!(_mud_inspector_2(parent, object, object_type));
};
Module['object_edit'] = function(parent, object, hint) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* object <Ref> [] */
    var object_type;
    if(typeof object !== "undefined" && object !== null) { object = object.ptr; object_type = object.type.__type__; }
    else { object = 0; object_type = 0; }
    /* hint <EditorHint> [] */
    if (hint && typeof hint === "object") hint = hint.ptr;
    if (hint === undefined) { return !!(_mud_object_edit_2(parent, object, object_type)); }
    return !!(_mud_object_edit_3(parent, object, object_type, hint));
};
Module['object_edit_columns'] = function(parent, object) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* object <Ref> [] */
    var object_type;
    if(typeof object !== "undefined" && object !== null) { object = object.ptr; object_type = object.type.__type__; }
    else { object = 0; object_type = 0; }
    return !!(_mud_object_edit_columns_2(parent, object, object_type));
};
Module['object_edit_expandbox'] = function(parent, object) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* object <Ref> [] */
    var object_type;
    if(typeof object !== "undefined" && object !== null) { object = object.ptr; object_type = object.type.__type__; }
    else { object = 0; object_type = 0; }
    return !!(_mud_object_edit_expandbox_2(parent, object, object_type));
};
Module['object_edit_inline'] = function(parent, object) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* object <Ref> [] */
    var object_type;
    if(typeof object !== "undefined" && object !== null) { object = object.ptr; object_type = object.type.__type__; }
    else { object = 0; object_type = 0; }
    return !!(_mud_object_edit_inline_2(parent, object, object_type));
};
Module['object_edit_rows'] = function(parent, object) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* object <Ref> [] */
    var object_type;
    if(typeof object !== "undefined" && object !== null) { object = object.ptr; object_type = object.type.__type__; }
    else { object = 0; object_type = 0; }
    return !!(_mud_object_edit_rows_2(parent, object, object_type));
};
Module['object_edit_table'] = function(parent, object) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* object <Ref> [] */
    var object_type;
    if(typeof object !== "undefined" && object !== null) { object = object.ptr; object_type = object.type.__type__; }
    else { object = 0; object_type = 0; }
    return !!(_mud_object_edit_table_2(parent, object, object_type));
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
