
// Bindings utilities
function WrapperObject() {
}
// ScriptEditor
function ScriptEditor() { throw "cannot construct a ScriptEditor, no constructor in IDL" }
ScriptEditor.prototype = Object.create(WrapperObject.prototype);
ScriptEditor.prototype.constructor = ScriptEditor;
ScriptEditor.prototype.__class__ = ScriptEditor;
ScriptEditor.__cache__ = {};
Module['ScriptEditor'] = ScriptEditor;
ScriptEditor.prototype["__destroy__"] = ScriptEditor.prototype.__destroy__ = function() {
    var self = this.ptr;
    _ScriptEditor___destroy__(self);
};

(function() {
    function setupEnums() {
        // EditNestMode
        Module['EditNestMode']['Inline'] = _EditNestMode_Inline();
        Module['EditNestMode']['Modal'] = _EditNestMode_Modal();
        Module['EditNestMode']['Embed'] = _EditNestMode_Embed();
        // EditorHint
        Module['EditorHint']['Table'] = _EditorHint_Table();
        Module['EditorHint']['Rows'] = _EditorHint_Rows();
        Module['EditorHint']['Inline'] = _EditorHint_Inline();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
