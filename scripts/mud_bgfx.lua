-- mud library
-- mud ctx bgfx module

project "mud_bgfx"
	kind "SharedLib"
    
    includedirs {
		path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "glfw", "include"),
        path.join(BX_DIR,    "include"),
        path.join(BGFX_DIR,  "include"),
    }
    
    files {
        path.join(MUD_SRC_DIR, "bgfx/**.h"),
        path.join(MUD_SRC_DIR, "bgfx/**.cpp"),
    }
    
    defines { "MUD_CTX_GLFW_EXPORT=MUD_EXPORT" }
    defines { "MUD_BGFX_LIB" }
    
    links {
        "mud",
        MUD_UI_BACKEND,
        MUD_CTX_BACKEND,
        "bx",
        "bimg",
        "bgfx",
        "glfw3",
    }
    
	configuration { "vs20*" }
		links {
			"psapi",
		}
        
	configuration {}
    