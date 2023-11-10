-- two library
-- FastNoise 3rdparty module

fastnoise = dep(nil, "FastNoise")
	kind "StaticLib"
    
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "FastNoise"),
    }
    
    files {
        path.join(TWO_3RDPARTY_DIR, "FastNoise", "**.h"),
        path.join(TWO_3RDPARTY_DIR, "FastNoise", "**.cpp"),
    }
        
    configuration { "mingw* or linux or osx or wasm*" }
        buildoptions {
            "-Wno-unused-function",
        }
        
    configuration { "vs*", "not wasm*" }
        buildoptions {
            "/wd4244", -- warning C4244: '=': conversion from 'int' to 'unsigned char', possible loss of data
            "/wd4505", -- warning C4505: 'FastAbs': unreferenced local function has been removed
            "/wd4701", -- warning C4701: potentially uninitialized local variable 'xs' used
        }

    configuration {}
