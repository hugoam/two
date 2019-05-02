-- two library
-- wren 3rdparty module

wren = two_dep(nil, "wren")
	kind "StaticLib"
    language "C"
    
	includedirs {
        path.join(TWO_3RDPARTY_DIR, "wren", "src", "include"),
        path.join(TWO_3RDPARTY_DIR, "wren", "src", "vm"),
        path.join(TWO_3RDPARTY_DIR, "wren", "src", "optional"),
	}

	files {
        path.join(TWO_3RDPARTY_DIR, "wren", "src", "vm", "*.h"),
        path.join(TWO_3RDPARTY_DIR, "wren", "src", "vm", "*.c"),
        path.join(TWO_3RDPARTY_DIR, "wren", "src", "optional", "*.h"),
        path.join(TWO_3RDPARTY_DIR, "wren", "src", "optional", "*.c"),
        path.join(TWO_SRC_DIR, "3rdparty", "wren_vm.c"),
	}

    removefiles {
        path.join(TWO_3RDPARTY_DIR, "wren", "src", "vm", "wren_vm.c"),
    }
    
    configuration { "Debug" }
        defines {
            "DEBUG",
        }
        
    configuration { "asmjs" }
        defines {
            "WREN_NAN_TAGGING=0",
        }
        
    configuration { "mingw* or linux or osx or asmjs" }
        buildoptions {
            "-Wno-unused-parameter",
        }
        
    configuration { "osx or *-clang* or asmjs" }
        buildoptions {
            "-Wno-macro-redefined", -- for __STDC_LIMIT_MACROS, we can't touch the source and don't want to touch the toolchain
        }
        
    configuration { "vs*", "not asmjs" }
        buildoptions {
            "/wd4100", -- warning C4100: 'vm': unreferenced formal parameter
            "/wd4200", -- warning C4200: nonstandard extension used: zero-sized array in struct/union
            "/wd4709", -- warning C4200: comma operator within array index expression
        }
    
	configuration {}
