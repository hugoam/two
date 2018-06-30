-- mud library
-- vorbisfile library

vorbisfile = mud_dep(nil, "vorbisfile")
	kind "StaticLib"

	includedirs {
        path.join(MUD_3RDPARTY_DIR, "ogg", "include"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "include"),
        path.join(MUD_DIR, "scripts/3rdparty/ogg/"),
	}

	files {
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/vorbisfile.c"),
	}
                        
    defines { }
    
    links {
		"ogg"
	}
    
	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}

	configuration {}
