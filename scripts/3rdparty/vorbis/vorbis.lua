-- two library
-- vorbis library

vorbis = two_dep(nil, "vorbis")
	kind "StaticLib"

	includedirs {
        path.join(TWO_3RDPARTY_DIR, "ogg", "include"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "include"),
        path.join(TWO_DIR, "scripts/3rdparty/ogg/"),
	}

	files {        
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/envelope.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/lpc.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/lsp.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/codebook.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/misc.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/psy.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/masking.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/os.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/mdct.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/smallft.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/highlevel.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/registry.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/scales.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/window.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/lookup.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/lookup_data.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/codec_internal.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/backends.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/bitrate.h"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/mdct.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/smallft.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/block.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/envelope.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/window.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/lsp.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/lpc.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/analysis.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/synthesis.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/psy.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/info.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/floor1.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/floor0.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/res0.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/mapping0.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/registry.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/codebook.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/sharedbook.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/lookup.c"),
        path.join(TWO_3RDPARTY_DIR, "vorbis", "lib/bitrate.c"),
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
        
	configuration {}
