#include <uio/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_uio)
{
    
    // Enums
    enum_<mud::EditNestMode>("mud::EditNestMode")
        .value("Inline", mud::EditNestMode::Inline)
        .value("Modal", mud::EditNestMode::Modal)
        .value("Embed", mud::EditNestMode::Embed)
        ;
    enum_<mud::EditorHint>("mud::EditorHint")
        .value("Table", mud::EditorHint::Table)
        .value("Rows", mud::EditorHint::Rows)
        .value("Inline", mud::EditorHint::Inline)
        ;
    
    // Sequences
    
    // Arrays
    
    // Structs
    
    // Classes
    class_<mud::ScriptEditor>("ScriptEditor")
        ;
    
    // Functions
    function("object_edit_inline", &mud::object_edit_inline);
    function("object_edit_rows", &mud::object_edit_rows);
    function("object_edit_columns", &mud::object_edit_columns);
    function("object_edit_table", &mud::object_edit_table);
    function("object_edit_expandbox", &mud::object_edit_expandbox);
    function("object_edit", &mud::object_edit);
    function("entity_edit", &mud::entity_edit);
    function("inspector", &mud::inspector);
    function("inspector", &mud::inspector);
    function("inspector", &mud::inspector);
    function("multi_inspector", &mud::multi_inspector);
    function("multi_object_edit", &mud::multi_object_edit);
    
}
