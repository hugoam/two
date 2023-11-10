-- two library
-- vg-renderer 3rdparty module

vg = dep(nil, "vg")
    kind "StaticLib"
    
    includedirs {
        path.join(BX_DIR,    "include"),
        path.join(BGFX_DIR,    "include"),
        path.join(TWO_SRC_DIR),
        path.join(TWO_3RDPARTY_DIR, "vg-renderer", "include"),
        path.join(TWO_3RDPARTY_DIR, "vg-renderer", "src"),
    }
    
    files {
        path.join(TWO_3RDPARTY_DIR, "vg-renderer",  "src/**.h"),
        path.join(TWO_3RDPARTY_DIR, "vg-renderer",  "src/**.c"),
        path.join(TWO_3RDPARTY_DIR, "vg-renderer",  "src/**.cpp"),
        path.join(TWO_SRC_DIR, "3rdparty", "vg.cpp"),
    }
    
    removefiles {
        path.join(TWO_3RDPARTY_DIR, "vg-renderer", "src/vg.cpp"),
    }
    
    configuration { "*-gcc*" }
        buildoptions {
            "-Wno-empty-body",
        }
        
	configuration { "osx or *-clang* or wasm*" }
		buildoptions {
            "-Wno-shadow",
		}
        
    configuration { "Debug" }
        defines {
            "VG_CONFIG_DEBUG=1"
        }
        
    configuration {}
    
--nanovg = dep(nil, "nanovg")
--    cxxmodule("vg")
--    kind "StaticLib"
--    
--    files {
--        path.join(TWO_NANOVG_DIR, "src/nanovg.c"),
--        path.join(TWO_NANOVG_DIR, "src/nanovg_bgfx.cpp"),
--    }
