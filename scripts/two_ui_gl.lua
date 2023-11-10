-- two library
-- two ui gl renderer module

function two_ui_gl()
	includedirs {
		path.join(TWO_NANOVG_DIR, "src"),
	}

    files {
        path.join(TWO_NANOVG_DIR, "src/nanovg.c"),
    }
    
    defines {
        --"TWO_UI_DRAW_CACHE",
        "TWO_VG_NANOVG",
    }
    
    links {
        "glew32",
        "OpenGL32"
	}
    
    configuration { "not wasm*" }
        defines { "NANOVG_GLEW" }

	configuration {}
end

two.ui.nvg = module("two", "ui-nvg", TWO_SRC_DIR, "ui-nvg", nil, nil, false, {})
    
function two_ui_backend()
    return module("two", "ui-nvg-gl",  TWO_SRC_DIR, "ui-nvg-gl", two_ui_gl, nil, false, { two.type, two.math, two.ui })
end