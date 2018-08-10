-- mud library
-- wren 3rdparty module

wren = mud_dep(nil, "wren")
	kind "StaticLib"
    language "C"
    
	includedirs {
        path.join(MUD_3RDPARTY_DIR, "wren", "src", "include"),
        path.join(MUD_3RDPARTY_DIR, "wren", "src", "vm"),
        path.join(MUD_3RDPARTY_DIR, "wren", "src", "optional"),
	}

	files {
        path.join(MUD_3RDPARTY_DIR, "wren", "src", "vm", "*.h"),
        path.join(MUD_3RDPARTY_DIR, "wren", "src", "vm", "*.c"),
        path.join(MUD_3RDPARTY_DIR, "wren", "src", "optional", "*.h"),
        path.join(MUD_3RDPARTY_DIR, "wren", "src", "optional", "*.c"),
        path.join(MUD_SRC_DIR, "3rdparty", "wren_vm.c"),
	}

    removefiles {
        path.join(MUD_3RDPARTY_DIR, "wren", "src", "vm", "wren_vm.c"),
    }
    
    configuration { "Debug" }
        defines {
            "DEBUG",
        }
        
    configuration { "asmjs" }
        defines {
            "WREN_NAN_TAGGING=0",
        }
        
    configuration { "vs*", "not asmjs" }
        buildoptions {
            "/wd4100", -- warning C4100: 'vm': unreferenced formal parameter
        }
    
	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}

	configuration {}
