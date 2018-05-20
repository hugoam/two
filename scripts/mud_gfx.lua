-- mud library
-- mud gfx module

dofile(path.join(MUD_DIR, "scripts/mud_bgfx.lua"))

function uses_mud_gfx()
    uses_bgfx()
    
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
    
    mud_ctx_backend()
    mud_ui_backend()
    
    uses_mud_gfx()
    uses_mud()
        
    configuration { "vs*", "not asmjs", "Release" }
        buildoptions {
            "/bigobj",
        }
        
    configuration { "not asmjs" }
        links {
            "glfw",
        }
        
    configuration {}
