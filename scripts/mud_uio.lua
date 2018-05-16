-- mud library
-- mud uio module

project "mud_uio"
	kind "SharedLib"

	includedirs {
		path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "glm"),
	}

	files {
        path.join(MUD_UIO_DIR, "**.h"),
        path.join(MUD_UIO_DIR, "**.cpp"),
	}
        
    defines { "MUD_UIO_LIB" }
    
    links {
		"mud_obj",
		"mud_math",
		"mud_ctx",
		"mud_ui",
	}
    
