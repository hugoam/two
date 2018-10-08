-- mud library
-- vorbis library

vorbis = mud_dep(nil, "vorbis")
	kind "StaticLib"

	includedirs {
        path.join(MUD_3RDPARTY_DIR, "ogg", "include"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "include"),
        path.join(MUD_DIR, "scripts/3rdparty/ogg/"),
	}

	files {        
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/envelope.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/lpc.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/lsp.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/codebook.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/misc.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/psy.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/masking.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/os.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/mdct.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/smallft.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/highlevel.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/registry.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/scales.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/window.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/lookup.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/lookup_data.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/codec_internal.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/backends.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/bitrate.h"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/mdct.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/smallft.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/block.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/envelope.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/window.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/lsp.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/lpc.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/analysis.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/synthesis.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/psy.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/info.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/floor1.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/floor0.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/res0.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/mapping0.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/registry.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/codebook.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/sharedbook.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/lookup.c"),
        path.join(MUD_3RDPARTY_DIR, "vorbis", "lib/bitrate.c"),
	}
                      
    defines { }
    
    links {
		"ogg"
	}
    
    configuration { "vs*", "not asmjs" }
        buildoptions {
            "/wd4244", -- warning C4244: '=': conversion from 'double' to 'int', possible loss of data
            "/wd4456", -- warning C4456: declaration of 'i' hides previous local declaration
        }
        
	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}

	configuration {}
