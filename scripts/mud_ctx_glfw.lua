-- mud library
-- mud ctx glfw module

project "mud_ctx_glfw"
	kind "StaticLib"
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glfw", "include"),
    }

    mud_module("ctx-glfw", MUD_SRC_DIR, "ctx-glfw", "MUD_CTX_GLFW")
    uses_mud()
    
--usage "mud_ctx_glfw"
    links {
        "glfw",
    }
