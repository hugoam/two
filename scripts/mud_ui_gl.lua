-- mud library
-- mud ui gl renderer module

function mud_ui_backend()
	includedirs {
		path.join(MUD_NANOVG_DIR, "src"),
	}

    mud_module(false, "mud", "ui-nanovg",     MUD_SRC_DIR, "ui-nanovg")
    mud_module(false, "mud", "ui-nanovg-gl",  MUD_SRC_DIR, "ui-nanovg-gl")
    
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