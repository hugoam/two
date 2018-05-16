-- mud library
-- mud ui bgfx renderer module

project "mud_ui_bgfx"
	kind "StaticLib"

	includedirs {
		path.join(MUD_NANOVG_DIR, "src"),
        path.join(MUD_3RDPARTY_DIR),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "include"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src"),
        path.join(BX_DIR,    "include"),
        path.join(BGFX_DIR,  "include"),
	}

    mud_module("ui-bgfx",  MUD_SRC_DIR, "ui-bgfx",      "MUD_UI_BGFX")
    mud_module("ui-vg",    MUD_SRC_DIR, "ui-nanovg",    "MUD_UI_VG")
    
    files {
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src/**.c"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src/**.cpp"),
        --path.join(MUD_NANOVG_DIR, "src/nanovg.c"),
        --path.join(MUD_NANOVG_DIR, "src/nanovg_bgfx.cpp"),
    }
    
    removefiles {
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src/vg.cpp"),
    }
    
    defines {
        --"MUD_UI_DRAW_CACHE",
        "MUD_VG_RENDERER",
    }
    links {
        "bx",
        "bimg",
        "bgfx",
    }

    uses_mud()
    
	configuration { "vs20*" }
		links {
			"psapi",
		}
        
    configuration {}