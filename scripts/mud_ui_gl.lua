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

mud.ui.nvg = mud_module("mud", "ui-nvg", MUD_SRC_DIR, "ui-nvg", nil, nil, false, {})
    
function mud_ui_backend()
    return mud_module("mud", "ui-nvg-gl",  MUD_SRC_DIR, "ui-nvg-gl", mud_ui_gl, nil, false, { mud.type, mud.math, mud.ui })
end