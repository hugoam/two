-- mud library
-- lua dependency

project "lua"
	kind "StaticLib"
    
	includedirs {
        path.join(MUD_3RDPARTY_DIR, "lua"),
	}

	files {
        path.join(MUD_3RDPARTY_DIR, "lua", "*.h"),
        path.join(MUD_3RDPARTY_DIR, "lua", "*.c"),
	}
              
    removefiles {
        path.join(MUD_3RDPARTY_DIR, "lua", "lua.c"),
        path.join(MUD_3RDPARTY_DIR, "lua", "luac.c"),
        path.join(MUD_3RDPARTY_DIR, "lua", "lbitlib.c"),
    }
    
	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}

	configuration {}
