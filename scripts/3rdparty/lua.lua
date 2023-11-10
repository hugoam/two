-- two library
-- lua 3rdparty module

lua = dep(nil, "lua")
	kind "StaticLib"
    
	includedirs {
        path.join(TWO_3RDPARTY_DIR, "lua"),
	}

	files {
        path.join(TWO_3RDPARTY_DIR, "lua", "*.h"),
        path.join(TWO_3RDPARTY_DIR, "lua", "*.c"),
	}
              
    removefiles {
        path.join(TWO_3RDPARTY_DIR, "lua", "lua.c"),
        path.join(TWO_3RDPARTY_DIR, "lua", "luac.c"),
        path.join(TWO_3RDPARTY_DIR, "lua", "lbitlib.c"),
    }
    
    configuration { "vs*", "not wasm*" }
        buildoptions {
            "/wd4244", -- warning C4244: '=': conversion from 'int' to 'lu_byte', possible loss of data
			"/wd4389", -- warning C4389: '==': signed/unsigned mismatch
            "/wd4152", -- warning C4152: nonstandard extension, function/data pointer conversion in expression
            "/wd4701", -- warning C4701: potentially uninitialized local variable 'n1' used
            "/wd4310", -- warning C4310: cast truncates constant value
            "/wd4245", -- warning C4245: 'initializing': conversion from 'int' to 'const Instruction', signed/unsigned mismatch
            "/wd4702", -- warning C4702: unreachable code
        }
    
	configuration { "osx or *-clang* or wasm*" }
		buildoptions {
			"-Wno-expansion-to-defined",
		}

	configuration {}
