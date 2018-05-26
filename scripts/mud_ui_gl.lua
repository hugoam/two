-- mud library
-- mud ui gl renderer module

function mud_ui_backend()
	includedirs {
		path.join(MUD_NANOVG_DIR, "src"),
	}

    mud_module("ui-nanovg",     MUD_SRC_DIR, "ui-nanovg",       "MUD_UI_NANOVG")
    mud_module("ui-nanovg-gl",  MUD_SRC_DIR, "ui-nanovg-gl",    "MUD_UI_NANOVG_GL")
    
    files {
        path.join(MUD_NANOVG_DIR, "src/nanovg.c"),
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