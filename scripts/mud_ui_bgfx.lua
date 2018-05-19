-- mud library
-- mud ui bgfx renderer module

function mud_ui_backend()
	includedirs {
		path.join(MUD_NANOVG_DIR, "src"),
        path.join(MUD_3RDPARTY_DIR),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "include"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src"),
	}

    configuration { "vg-vg" }
        files {
            path.join(MUD_SRC_DIR,      "ui-vg",        "**.h"),
            path.join(MUD_SRC_DIR,      "ui-vg",        "**.cpp"),
            path.join(MUD_3RDPARTY_DIR, "vg-renderer",  "src/**.h"),
            path.join(MUD_3RDPARTY_DIR, "vg-renderer",  "src/**.c"),
            path.join(MUD_3RDPARTY_DIR, "vg-renderer",  "src/**.cpp"),
        }
        
        removefiles {
            path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src/vg.cpp"),
        }
        
        defines {
            --"MUD_UI_DRAW_CACHE",
            "MUD_VG_VG",
        }
        
    configuration { "vg-nanovg" }
        files {
            path.join(MUD_SRC_DIR,    "ui-nanovg",        "**.cpp"),
            path.join(MUD_SRC_DIR,    "ui-nanovg",        "**.cpp"),
            path.join(MUD_NANOVG_DIR, "src/nanovg.c"),
            path.join(MUD_NANOVG_DIR, "src/nanovg_bgfx.cpp"),
        }
    
        defines {
            --"MUD_UI_DRAW_CACHE",
            "MUD_VG_NANOVG",
        }
        
    configuration {}
end
