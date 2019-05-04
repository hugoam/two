-- two library
-- ogg library

ogg = dep(nil, "ogg")
	kind "StaticLib"
    
	includedirs {
        path.join(TWO_3RDPARTY_DIR, "ogg", "include"),
        path.join(TWO_DIR, "scripts/3rdparty/ogg/"),
	}

	files {
        path.join(TWO_3RDPARTY_DIR, "ogg", "include/ogg/config_types.h"),
        path.join(TWO_3RDPARTY_DIR, "ogg", "include/ogg/ogg.h"),
        path.join(TWO_3RDPARTY_DIR, "ogg", "include/ogg/os_types.h"),
        path.join(TWO_3RDPARTY_DIR, "ogg", "src/bitwise.c"),
        path.join(TWO_3RDPARTY_DIR, "ogg", "src/framing.c"),
	}
                        
    defines { }
    
    links {
		
	}
    
	configuration {}
