-- mud library
-- mud db module

project "mud_db"
	kind "SharedLib"

	includedirs {
		path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "sqlite3"),
	}

	files {
        path.join(MUD_DB_DIR, "**.h"),
        path.join(MUD_DB_DIR, "**.cpp"),
        path.join(MUD_3RDPARTY_DIR, "sqlite3", "*.c"),
	}
                        
    defines { "MUD_DB_LIB" }
    
    links {
		"mud_obj",
		"mud_util",
	}
    
