-- two library
-- two gl module

if _OPTIONS["context-glfw"] then
dofile(path.join(TWO_DIR, "scripts/two_ctx_glfw.lua"))
elseif _OPTIONS["context-wasm"] then
dofile(path.join(TWO_DIR, "scripts/two_ctx_wasm.lua"))
end

dofile(path.join(TWO_DIR, "scripts/two_ui_gl.lua"))

two.gl = module("two", "gl", TWO_SRC_DIR, "gl")
	kind "SharedLib"
    
    two_ctx_backend()
    two_ui_backend()

    uses_two()
    
function uses_two_gl()
    links {
        "two_gl",
    }
    
    uses_two()
end
