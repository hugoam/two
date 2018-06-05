-- mud library
-- mud gfx module

dofile(path.join(MUD_DIR, "scripts/mud_bgfx.lua"))

function uses_mud_gfx()
    uses_bgfx()
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "FastNoise"),
    }
    
    links { "mud_gfx" }
end

os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/filter"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/pbr"))

function mud_bgfx(as_project)
    mud_module(as_project, "mud", "bgfx", MUD_SRC_DIR, "bgfx")
end

function mud_gfx(as_project)
    mud_module(as_project, "mud", "gfx", MUD_SRC_DIR, "gfx", { "obj", "math", "geom", "bgfx" })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }
    
    mud_ctx_backend()
    mud_ui_backend()
    
    uses_bgfx()
end

function mud_gfx_obj(as_project)
    mud_module(as_project, "mud", "gfx-obj", MUD_SRC_DIR, "gfx-obj")
end

function mud_gfx_pbr(as_project)
    mud_module(as_project, "mud", "gfx-pbr", MUD_SRC_DIR, "gfx-pbr")
end

function mud_gfx_gltf(as_project)
    mud_module(as_project, "mud", "gfx-gltf", MUD_SRC_DIR, "gfx-gltf")
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "base64"),
    }

    files {
        path.join(MUD_3RDPARTY_DIR, "base64", "**.h"),
        path.join(MUD_3RDPARTY_DIR, "base64", "**.cpp"),
    }
end

function mud_edit(as_project)
    mud_module(as_project, "mud", "edit", MUD_SRC_DIR, "edit")
end

function mud_gen(as_project)
    mud_module(as_project, "mud", "gen", MUD_SRC_DIR, "gen")
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
        path.join(MUD_3RDPARTY_DIR, "FastNoise"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "FastNoise", "**.h"),
        path.join(MUD_3RDPARTY_DIR, "FastNoise", "**.cpp"),
    }
end

if _OPTIONS["as-libs"] then
    group "lib/mud"
        mud_bgfx(true)
        mud_gfx(true)
        mud_gfx_obj(true)
        mud_gfx_pbr(true)
        mud_gfx_gltf(true)
        mud_edit(true)
        mud_gen(true)
    group "lib"
else
    project "mud_gfx"
        kind "SharedLib"

        mud_bgfx(false)
        mud_gfx(false)
        mud_gfx_obj(false)
        mud_gfx_pbr(false)
        mud_gfx_gltf(false)
        mud_edit(false)
        mud_gen(false)

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
end
