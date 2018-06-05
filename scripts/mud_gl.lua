-- mud library
-- mud gl module

if _OPTIONS["context-glfw"] then
dofile(path.join(MUD_DIR, "scripts/mud_ctx_glfw.lua"))
elseif _OPTIONS["context-wasm"] then
dofile(path.join(MUD_DIR, "scripts/mud_ctx_wasm.lua"))
end

dofile(path.join(MUD_DIR, "scripts/mud_ui_gl.lua"))

project "mud_gl"
	kind "SharedLib"
    
    mud_module(false, "mud", "gl", MUD_SRC_DIR, "gl")
    
    mud_ctx_backend()
    mud_ui_backend()

    uses_mud()
    
function uses_mud_gl()
    links {
        "mud_gl",
    }
    
    uses_mud()
end
