-- toy engine
-- vorbisfile library

project "vorbisfile"
	kind "StaticLib"

	includedirs {
        path.join(TOY_3RDPARTY_DIR, "ogg", "include"),
        path.join(TOY_3RDPARTY_DIR, "vorbis", "include"),
        path.join(MUD_DIR, "scripts/3rdparty/ogg/"),
	}

	files {
        path.join(TOY_3RDPARTY_DIR, "vorbis", "lib/vorbisfile.c"),
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
