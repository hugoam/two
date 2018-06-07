-- mud library
-- mud ctx glfw module

function mud_ctx_backend(parent)
    mud.ctxbackend = mud_module(false, "mud", "ctx-glfw", MUD_SRC_DIR, "ctx-glfw", { mud.math, mud.ctx })
    table.insert(parent.deps, mud.ctxbackend)

    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glfw", "include"),
    }

    configuration { "not asmjs" }
        links {
            "glfw",
        }
        
    configuration {}
end
