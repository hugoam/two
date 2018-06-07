-- mud library
-- mud gfx module

dofile(path.join(MUD_DIR, "scripts/mud_bgfx.lua"))

function uses_mud_gfx()
    uses_bgfx()
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "FastNoise"),
    }
    
    if _OPTIONS["as-libs"] then
        links { "mud_gfx", "mud_gfx_obj", "mud_gfx_pbr", "mud_gfx_gltf", "mud_edit", "mud_procgen", "mud_procgen_gfx" }
    else
        links { "mud_gfx" }
    end
end

os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/filter"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/pbr"))

function mud_gfx(as_project)
    print("mud_gfx()")
    mud.gfx = mud_module(as_project, "mud", "gfx", MUD_SRC_DIR, "gfx", { json11, mud.obj, mud.srlz, mud.math, mud.geom, mud.ctx, mud.ui, mud.ctxbackend, mud.uibackend })
    
    mud_module(false, "mud", "bgfx", MUD_SRC_DIR, "bgfx", { mud.obj, mud.math, mud.ctx, mud.ui, mud.ctxbackend, mud.uibackend })
    
    mud_ctx_backend(mud.gfx)
    mud_ui_backend(mud.gfx)
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
    
    uses_bgfx()
end

function mud_gfx_obj(as_project)
    mud.gfx.obj = mud_module(as_project, "mud", "gfx-obj", MUD_SRC_DIR, "gfx-obj", { mud.obj, mud.srlz, mud.math, mud.geom, mud.gfx })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }
    
    uses_bgfx()
end

function mud_gfx_pbr(as_project)
    mud.gfx.pbr = mud_module(as_project, "mud", "gfx-pbr", MUD_SRC_DIR, "gfx-pbr", { mud.obj, mud.srlz, mud.math, mud.geom, mud.gfx })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }
    
    uses_bgfx()
end

function mud_gfx_gltf(as_project)
    mud.gfx.gltf = mud_module(as_project, "mud", "gfx-gltf", MUD_SRC_DIR, "gfx-gltf", { json11, mud.obj, mud.srlz, mud.math, mud.geom, mud.gfx })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "base64"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }

    files {
        path.join(MUD_3RDPARTY_DIR, "base64", "**.h"),
        path.join(MUD_3RDPARTY_DIR, "base64", "**.cpp"),
    }
    
    uses_bgfx()
end

function mud_edit(as_project)
    mud.edit = mud_module(as_project, "mud", "edit", MUD_SRC_DIR, "edit", { mud.obj, mud.srlz, mud.lang, mud.math, mud.geom, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.gfx.pbr })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
    
    uses_bgfx()
end

function mud_procgen(as_project)
    mud.procgen = mud_module(as_project, "mud", "procgen", MUD_SRC_DIR, "procgen", { json11, mud.obj, mud.srlz, mud.math, mud.geom })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "stb"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
        path.join(MUD_3RDPARTY_DIR, "FastNoise"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "FastNoise", "**.h"),
        path.join(MUD_3RDPARTY_DIR, "FastNoise", "**.cpp"),
    }
    
    if _OPTIONS["as-libs"] then
        table.insert(mud.procgen.deps, stb.image)
    end
end

function mud_procgen_gfx(as_project)
    mud.procgen.gfx = mud_module(as_project, "mud", "procgen-gfx", MUD_SRC_DIR, "procgen-gfx", { json11, mud.obj, mud.srlz, mud.math, mud.geom, mud.procgen, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.edit })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "FastNoise"),
    }
    
    uses_bgfx()
end

if _OPTIONS["as-libs"] then
    group "lib/mud"
        mud_gfx(true)
        mud_gfx_obj(true)
        mud_gfx_pbr(true)
        mud_gfx_gltf(true)
        mud_edit(true)
        mud_procgen(true)
        mud_procgen_gfx(true)
    group "lib"
else
    project "mud_gfx"
        kind "SharedLib"

        mud_gfx(false)
        mud_gfx_obj(false)
        mud_gfx_pbr(false)
        mud_gfx_gltf(false)
        mud_edit(false)
        mud_procgen(false)
        mud_procgen_gfx(false)

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

mud_bgfx()
