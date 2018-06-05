-- mud library
-- mud ui bgfx renderer module

function mud_ui_backend()
	includedirs {
		path.join(MUD_NANOVG_DIR, "src"),
        path.join(MUD_3RDPARTY_DIR),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "include"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src"),
	}

    defines {
        --"MUD_UI_DRAW_CACHE",
    }
        
    if _OPTIONS["vg-vg"] then
        mud_module(false, "mud", "ui-vg", MUD_SRC_DIR, "ui-vg")
        
        files {
            path.join(MUD_3RDPARTY_DIR, "vg-renderer",  "src/**.h"),
            path.join(MUD_3RDPARTY_DIR, "vg-renderer",  "src/**.c"),
            path.join(MUD_3RDPARTY_DIR, "vg-renderer",  "src/**.cpp"),
        }
        
        removefiles {
            path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src/vg.cpp"),
        }
        
        defines {
            "MUD_VG_VG",
        }
    end
        
    if _OPTIONS["vg-nanovg"] then
        mud_module(false, "mud", "ui-nanovg",      MUD_SRC_DIR, "ui-nanovg")
        mud_module(false, "mud", "ui-nanovg-bgfx", MUD_SRC_DIR, "ui-nanovg-bgfx")
        
        files {
            path.join(MUD_NANOVG_DIR, "src/nanovg.c"),
            path.join(MUD_NANOVG_DIR, "src/nanovg_bgfx.cpp"),
        }
    
        defines {
            "MUD_VG_NANOVG",
        }
    end
end
