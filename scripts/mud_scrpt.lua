-- mud library
-- mud lang module

project "mud_lang"
	kind "SharedLib"

	includedirs {
		path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "lua"),
	}

	files {
		path.join(MUD_SCRPT_DIR, "**.h"),
		path.join(MUD_SCRPT_DIR, "**.cpp"),
	}

    defines { "MUD_SCRPT_LIB" }
    
    links {
		"mud_obj",
        "lua",
	}

