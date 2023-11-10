-- two library
-- vorbisfile library

vorbisfile = dep(nil, "vorbisfile")
	kind "StaticLib"

	includedirs {
        path.join(TWO_3RDPARTY_DIR, "ogg", "include"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "include"),
        path.join(TWO_DIR, "scripts/3rdparty/ogg/"),
	}

	files {
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/vorbisfile.c"),
	}
                        
    defines { }
    
    links {
		"ogg"
	}
    
	configuration {}
