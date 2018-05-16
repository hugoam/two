-- mud library
-- mud ui module

project "mud_ui"
	kind "SharedLib"

	includedirs {
		path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "glm"),
		path.join(MUD_3RDPARTY_DIR, "stb"),
		path.join(MUD_3RDPARTY_DIR, "rectpacking"),
        path.join(MUD_3RDPARTY_DIR, "json", "src"),
	}

	files {
        path.join(MUD_UI_DIR, "**.h"),
        path.join(MUD_UI_DIR, "**.cpp"),
		path.join(MUD_3RDPARTY_DIR, "rectpacking", "**.cpp"),
	}
    
    removefiles {
        path.join(MUD_UI_DIR, "Backend/**.h"),
        path.join(MUD_UI_DIR, "Backend/**.cpp"),
    }
    
    defines { "MUD_UI_LIB" }
    
    links {
		"mud_obj",
		"mud_math",
		"mud_ctx",
	}
    