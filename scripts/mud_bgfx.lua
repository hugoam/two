-- mud library
-- mud ctx bgfx module

if _OPTIONS["context-glfw"] then
dofile(path.join(MUD_DIR, "scripts/mud_ctx_glfw.lua"))
elseif _OPTIONS["context-wasm"] then
dofile(path.join(MUD_DIR, "scripts/mud_ctx_wasm.lua"))
end

if _OPTIONS["renderer-bgfx"] then
dofile(path.join(MUD_DIR, "scripts/mud_ui_bgfx.lua"))
else
dofile(path.join(MUD_DIR, "scripts/mud_ui_gl.lua"))
end

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

project "mud_bgfx"
	kind "SharedLib"
    
    mud_module(false, "mud", "bgfx", MUD_SRC_DIR, "bgfx")
    
    mud_ctx_backend()
    mud_ui_backend()

    uses_mud()
    uses_bgfx()
    
function uses_mud_bgfx()
    links {
        "mud_bgfx",
    }
    
    uses_mud()
    uses_bgfx()
end
