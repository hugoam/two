-- mud library
-- vg-renderer 3rdparty module

vg = mud_dep(nil, "vg")
    kind "StaticLib"
    
    includedirs {
        path.join(BX_DIR,    "include"),
        path.join(BGFX_DIR,    "include"),
        path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "include"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "vg-renderer",  "src/**.h"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer",  "src/**.c"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer",  "src/**.cpp"),
        path.join(MUD_SRC_DIR, "3rdparty", "vg.cpp"),
    }
    
    removefiles {
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src/vg.cpp"),
    }
    

--nanovg = mud_dep(nil, "nanovg")
--    cxxmodule("vg")
--    kind "StaticLib"
--    
--    files {
--        path.join(MUD_NANOVG_DIR, "src/nanovg.c"),
--        path.join(MUD_NANOVG_DIR, "src/nanovg_bgfx.cpp"),
--    }
