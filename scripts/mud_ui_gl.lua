-- mud library
-- mud ui gl renderer module

function mud_ui_backend()
	includedirs {
		path.join(MUD_NANOVG_DIR, "src"),
	}

    mud_module("ui-gl", MUD_SRC_DIR, "ui-gl", "MUD_UI_GL")
    
    files {
        path.join(MUD_UI_DIR, "ui-vg/NanoRenderer.h"),
        path.join(MUD_UI_DIR, "ui-vg/NanoRenderer.cpp"),
        path.join(MUD_NANOVG_DIR, "src/nanovg.c"),
        path.join(MUD_NANOVG_DIR, "src/nanovg_bgfx.cpp"),
    }
    
    defines {
        --"MUD_UI_DRAW_CACHE",
        "MUD_VG_NANOVG",
    }
    
    links {
        "glew32",
        "OpenGL32"
	}
    
    configuration { "not asmjs" }
        defines { "NANOVG_GLEW" }

	configuration {}
end