-- toy engine
-- ogg library

project "ogg"
	kind "StaticLib"
    
	includedirs {
        path.join(TOY_3RDPARTY_DIR, "ogg", "include"),
        path.join(MUD_DIR, "scripts/3rdparty/ogg/"),
	}

	files {
        path.join(TOY_3RDPARTY_DIR, "ogg", "include/ogg/config_types.h"),
        path.join(TOY_3RDPARTY_DIR, "ogg", "include/ogg/ogg.h"),
        path.join(TOY_3RDPARTY_DIR, "ogg", "include/ogg/os_types.h"),
        path.join(TOY_3RDPARTY_DIR, "ogg", "src/bitwise.c"),
        path.join(TOY_3RDPARTY_DIR, "ogg", "src/framing.c"),
	}
                        
    defines { }
    
    links {
		
	}
    
	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}

	configuration {}
