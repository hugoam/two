-- mud library
-- mud ui gl renderer module

function mud_ui_gl()
	includedirs {
		path.join(MUD_NANOVG_DIR, "src"),
	}

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

mud.ui.nanovg = mud_module("mud", "ui-nanovg", MUD_SRC_DIR, "ui-nanovg", nil, nil, nil, {})
    
function mud_ui_backend()
    return mud_module("mud", "ui-nanovg-gl",  MUD_SRC_DIR, "ui-nanovg-gl", nil, mud_ui_gl, nil, { mud.obj, mud.math, mud.ui })
end