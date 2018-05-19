-- mud library
-- mud ctx glfw module

function mud_ctx_backend()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glfw", "include"),
    }

    mud_module("ctx-glfw", MUD_SRC_DIR, "ctx-glfw", "MUD_CTX_GLFW")

    configuration { "not asmjs" }
        links {
            "glfw",
        }
end
