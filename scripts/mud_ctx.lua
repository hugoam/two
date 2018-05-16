-- mud library
-- mud ctx module

project "mud_ctx"
	kind "SharedLib"
    
    includedirs {
		path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }

    files {
        path.join(MUD_CTX_DIR, "**.h"),
        path.join(MUD_CTX_DIR, "**.cpp"),
    }

    defines { "MUD_CTX_LIB" }
    
    links {
		"mud_obj",
	}