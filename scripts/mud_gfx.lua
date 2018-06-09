-- mud library
-- mud gfx module

dofile(path.join(MUD_DIR, "scripts/mud_bgfx.lua"))

function uses_mud_coregfx()
    uses_bgfx()
    
    if _OPTIONS["as-libs"] then
        links { "mud_gfx", "mud_gfx_obj", "mud_gfx_pbr", "mud_gfx_gltf", "mud_edit", "mud_procgen", "mud_procgen_gfx" }
        links { "mud_gfx_refl", "mud_gfx_obj_refl", "mud_gfx_pbr_refl", "mud_gfx_gltf_refl", "mud_edit_refl", "mud_procgen_refl", "mud_procgen_gfx_refl" }
    else
        links { "mud_gfx" }
        links { "mud_gfx_refl" }
    end
end

os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/filter"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/pbr"))

function uses_mud_gfx()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }
    
    uses_bgfx()
end

function mud_gfx()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
    
    uses_bgfx()
end

function mud_gfx_gltf()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "base64"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }

    files {
        path.join(MUD_3RDPARTY_DIR, "base64", "**.h"),
        path.join(MUD_3RDPARTY_DIR, "base64", "**.cpp"),
    }
end

function uses_mud_procgen()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "FastNoise"),
    }
end

function mud_procgen()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
        path.join(MUD_3RDPARTY_DIR, "FastNoise"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "FastNoise", "**.h"),
        path.join(MUD_3RDPARTY_DIR, "FastNoise", "**.cpp"),
    }
end

mud.gfx         = mud_module(mud_module_decl, "mud", "gfx",         MUD_SRC_DIR, "gfx",         nil,            uses_mud_gfx,       { json11, mud.infra, mud.obj, mud.pool, mud.refl, mud.srlz, mud.math, mud.geom, mud.ctx, mud.ui, mud.ctxbackend, mud.uibackend, mud.bgfx })

mud.gfx.pbr     = mud_module(mud_module_decl, "mud", "gfx-pbr",     MUD_SRC_DIR, "gfx-pbr",     nil,            nil,                { mud.infra, mud.obj, mud.srlz, mud.math, mud.geom, mud.gfx })
mud.gfx.obj     = mud_module(mud_module_decl, "mud", "gfx-obj",     MUD_SRC_DIR, "gfx-obj",     nil,            nil,                { mud.infra, mud.obj, mud.srlz, mud.math, mud.geom, mud.gfx })
mud.gfx.gltf    = mud_module(mud_module_decl, "mud", "gfx-gltf",    MUD_SRC_DIR, "gfx-gltf",    mud_gfx_gltf,   nil,                { json11, mud.infra, mud.obj, mud.refl, mud.srlz, mud.math, mud.geom, mud.gfx })

mud.edit        = mud_module(mud_module_decl, "mud", "edit",        MUD_SRC_DIR, "edit",        nil,            nil,                { mud.infra, mud.tree, mud.obj, mud.refl, mud.srlz, mud.lang, mud.math, mud.geom, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.gfx.pbr })

mud.procgen     = mud_module(mud_module_decl, "mud", "procgen",     MUD_SRC_DIR, "procgen",     mud_procgen,    uses_mud_procgen,   { json11, mud.infra, mud.obj, mud.srlz, mud.math, mud.geom })
mud.procgen.gfx = mud_module(mud_module_decl, "mud", "procgen-gfx", MUD_SRC_DIR, "procgen-gfx", nil,            nil,                { json11, mud.infra, mud.tree, mud.obj, mud.srlz, mud.math, mud.geom, mud.procgen, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.edit })

mud.coregfx = { mud.ctxbackend, mud.uibackend, mud.bgfx, mud.gfx, mud.gfx.obj, mud.gfx.pbr, mud.gfx.gltf, mud.edit, mud.procgen, mud.procgen.gfx }

mud.all = {
    mud.infra, mud.obj, mud.pool, mud.refl, mud.tree, mud.srlz, mud.math, mud.geom, mud.lang, mud.ctx, mud.ui, mud.uio,
    mud.ctxbackend, mud.uibackend, mud.bgfx, mud.gfx, mud.gfx.obj, mud.gfx.pbr, mud.gfx.gltf, mud.edit, mud.procgen, mud.procgen.gfx
}

if _OPTIONS["as-libs"] then
    group "lib/mud"
        for _, m  in ipairs(mud.coregfx) do
            m.decl(m, true)
        end
    group "lib"
else
    project "mud_gfx"
        kind "SharedLib"

        for _, m  in ipairs(mud.coregfx) do
            m.decl(m, false)
        end
        
        uses_mud()
            
        configuration { "vs*", "not asmjs", "Release" }
            buildoptions {
                "/bigobj",
            }
            
        configuration {}
end

mud_bgfx()
