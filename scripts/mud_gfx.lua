-- mud library
-- mud gfx module

dofile(path.join(MUD_DIR, "scripts/mud_bgfx.lua"))

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

--                           base   name            root path    sub path       decl    self decl       decl transitive     dependencies
mud.gfx         = mud_module("mud", "gfx",          MUD_SRC_DIR, "gfx",         nil,    nil,            uses_mud_gfx,       { json11, mud.infra, mud.obj, mud.pool, mud.refl, mud.srlz, mud.math, mud.geom, mud.ctx, mud.ui, mud.ctxbackend, mud.uibackend, mud.bgfx })

mud.gfx.pbr     = mud_module("mud", "gfx-pbr",      MUD_SRC_DIR, "gfx-pbr",     nil,    nil,            nil,                { mud.infra, mud.obj, mud.srlz, mud.math, mud.geom, mud.gfx })
mud.gfx.obj     = mud_module("mud", "gfx-obj",      MUD_SRC_DIR, "gfx-obj",     nil,    nil,            nil,                { mud.infra, mud.obj, mud.srlz, mud.math, mud.geom, mud.gfx })
mud.gfx.gltf    = mud_module("mud", "gfx-gltf",     MUD_SRC_DIR, "gfx-gltf",    nil,    mud_gfx_gltf,   nil,                { json11, mud.infra, mud.obj, mud.refl, mud.srlz, mud.math, mud.geom, mud.gfx })

mud.edit        = mud_module("mud", "edit",         MUD_SRC_DIR, "edit",        nil,    nil,            nil,                { mud.infra, mud.tree, mud.obj, mud.refl, mud.srlz, mud.lang, mud.math, mud.geom, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.gfx.pbr })

mud.procgen     = mud_module("mud", "procgen",      MUD_SRC_DIR, "procgen",     nil,    mud_procgen,    uses_mud_procgen,   { json11, mud.infra, mud.obj, mud.srlz, mud.math, mud.geom })
mud.procgen.gfx = mud_module("mud", "procgen-gfx",  MUD_SRC_DIR, "procgen-gfx", nil,    nil,            nil,                { json11, mud.infra, mud.tree, mud.obj, mud.srlz, mud.math, mud.geom, mud.procgen, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.edit })

mudgfx = {}

mudgfx.modules = { mud.ctxbackend, mud.uibackend, mud.bgfx, mud.gfx, mud.gfx.obj, mud.gfx.pbr, mud.gfx.gltf, mud.edit, mud.procgen, mud.procgen.gfx }

table.extend(mudgfx.modules, mud_refls({ mud.gfx, mud.gfx.obj, mud.gfx.pbr, mud.gfx.gltf, mud.edit, mud.procgen, mud.procgen.gfx }))

mud.all = {}

table.extend(mud.all, mud.modules)
table.extend(mud.all, mudgfx.modules)

if _OPTIONS["as-libs"] then
    group "lib/mud"
        for _, m  in ipairs(mudgfx.modules) do
            m.decl(m, true)
        end
    group "lib"
else
    project "mud_gfx"
        if MUD_STATIC then
            kind "StaticLib"
        else
            kind "SharedLib"
        end

        for _, m  in ipairs(mudgfx.modules) do
            m.decl(m, false)
        end
        
        configuration { "vs*", "not asmjs", "Release" }
            buildoptions {
                "/bigobj",
            }
            
        configuration {}
end

