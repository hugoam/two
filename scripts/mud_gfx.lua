-- mud library
-- mud gfx module

function uses_shaderc()
    defines { "MUD_LIVE_SHADER_COMPILER" }
        
    links {
        "shaderc",
        "fcpp",
        "glslang",
        "glsl-optimizer",
        "spirv-opt",
    }
end

function uses_bgfx()
    includedirs {
        path.join(BX_DIR,    "include"),
        path.join(BIMG_DIR,  "include"),
        path.join(BGFX_DIR,  "include"),
    }
    
    configuration { "not asmjs" }
        uses_shaderc()
    configuration { "webshaderc" }
        uses_shaderc()
        
    configuration {}
    
    links {
        "bgfx",
        "bimg_decode",
        "bimg",
        "bx",
    }

    configuration { "linux" }
        links {
            "X11",
            "GLU",
            "GL",
            "Xext",
        }
    
    configuration { "vs20*", "not asmjs" }
        links {
            "psapi",
        }
    
    configuration { "osx or linux*" }
        links {
            "pthread",
        }
    
    configuration {}
end

function uses_mud_gfx()
    uses_bgfx()
    
    defines { "MUD_VG_RENDERER" }
    
    if project().name ~= "mud_gfx" then
        links { "mud_gfx" }
    end
end

os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/filter"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/pbr"))

project "mud_gfx"
    kind "SharedLib"

    includedirs {
        path.join(MUD_NANOVG_DIR, "src"),
        path.join(MUD_3RDPARTY_DIR, "base64"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "include"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src"),
    }

    mud_module("bgfx", MUD_SRC_DIR, "bgfx",  "MUD_BGFX")
    mud_module("gfx",  MUD_SRC_DIR, "gfx",   "MUD_GFX")
    mud_module("gen",  MUD_SRC_DIR, "gen",   "MUD_GEN")
    mud_module("edit", MUD_SRC_DIR, "edit",  "MUD_EDIT")
        
    files {
        path.join(MUD_3RDPARTY_DIR, "FastNoise", "**.h"),
        path.join(MUD_3RDPARTY_DIR, "FastNoise", "**.cpp"),
        path.join(MUD_3RDPARTY_DIR, "base64", "**.h"),
        path.join(MUD_3RDPARTY_DIR, "base64", "**.cpp"),
    }
    
    defines { "MUD_BGFX_LIB" }
    defines { "MUD_GFX_LIB", "MUD_GEN_LIB", "MUD_EDIT_LIB" }
    
    --uses(MUD_CTX_BACKEND)
    
    links {
        MUD_CTX_BACKEND,
        MUD_UI_BACKEND,
    }
    
    uses_mud_gfx()
    uses_mud()
    
    configuration { "vs*", "Release" }
        buildoptions {
            "/bigobj",
        }
        
    configuration { "not asmjs" }
        links {
            "glfw",
        }
        
    configuration {}