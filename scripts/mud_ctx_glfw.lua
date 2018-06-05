-- mud library
-- mud ctx glfw module

function mud_ctx_backend()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glfw", "include"),
    }

    mud_module(false, "mud", "ctx-glfw", MUD_SRC_DIR, "ctx-glfw")

    configuration { "not asmjs" }
        links {
            "glfw",
        }
        
    configuration {}
end
