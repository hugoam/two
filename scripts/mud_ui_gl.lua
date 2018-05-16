-- mud library
-- mud ui gl renderer module

project "mud_ui_gl"
	kind "StaticLib"

	includedirs {
		path.join(MUD_NANOVG_DIR, "src"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src"),
	}

    files {
        path.join(MUD_UI_DIR, "Backend/Gl/**.h"),
        path.join(MUD_UI_DIR, "Backend/Gl/**.cpp"),
        path.join(MUD_UI_DIR, "Backend/Nano/**.h"),
        path.join(MUD_UI_DIR, "Backend/Nano/**.cpp"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src/vg/**.c"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src/vg/**.cpp"),
        --path.join(MUD_NANOVG_DIR, "src/nanovg.c"),
    }
    
    removefiles {
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src/vg/svg_renderer.cpp"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src/vg/nanovg_renderer.cpp"),
    }
    
    links {
        "glew32",
        "OpenGL32"
	}
    
    uses_mud()
    
    configuration { "not asmjs" }
        defines { "NANOVG_GLEW" }

	configuration {}