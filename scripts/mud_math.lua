-- mud library
-- mud math module

project "mud_math"
	kind "SharedLib"
	--kind "StaticLib"
    
	includedirs {
		path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "mikkt"),
	}

	files {
        path.join(MUD_MATH_DIR, "**.h"),
		path.join(MUD_MATH_DIR, "**.cpp"),
        path.join(MUD_3RDPARTY_DIR, "mikkt", "mikktspace.c"),
	}

    defines { "MUD_MATH_LIB" }
    
    links {
		"mud_obj",
	}
    

