-- mud library
-- ogg library

project "ogg"
	kind "StaticLib"
    
	includedirs {
        path.join(MUD_3RDPARTY_DIR, "ogg", "include"),
        path.join(MUD_DIR, "scripts/3rdparty/ogg/"),
	}

	files {
        path.join(MUD_3RDPARTY_DIR, "ogg", "include/ogg/config_types.h"),
        path.join(MUD_3RDPARTY_DIR, "ogg", "include/ogg/ogg.h"),
        path.join(MUD_3RDPARTY_DIR, "ogg", "include/ogg/os_types.h"),
        path.join(MUD_3RDPARTY_DIR, "ogg", "src/bitwise.c"),
        path.join(MUD_3RDPARTY_DIR, "ogg", "src/framing.c"),
	}
                        
    defines { }
    
    links {
		
	}
    
	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}

	configuration {}
