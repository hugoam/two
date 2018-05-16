-- mud library
-- mud util module

project "mud_util"
	kind "SharedLib"
    
	includedirs {
		path.join(MUD_SRC_DIR),
	}

	files {
        path.join(MUD_UTIL_DIR, "**.h"),
		path.join(MUD_UTIL_DIR, "**.cpp"),
	}
                        
    defines { "MUD_UTIL_LIB" }
    
    links {
		"mud_obj",
	}


