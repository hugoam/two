-- mud library
-- mud gfx module

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

os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/filter"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/pbr"))

function uses_mud_gfx()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }
end

function mud_gfx()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
        path.join(MUD_3RDPARTY_DIR, "meshoptimizer", "src"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "meshoptimizer", "src/**.cpp"),
    }

    if _OPTIONS["culling"] then
        includedirs {
            path.join(MUD_3RDPARTY_DIR, "culling"),
        }
        
        files {
            path.join(MUD_3RDPARTY_DIR, "culling", "*.cpp"),
        }
    else
        defines { "NO_OCCLUSION_CULLING" }
    end
end

function mud_gfx_pbr()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "xatlas"),
    }

    files {
        path.join(MUD_3RDPARTY_DIR, "xatlas", "xatlas.cpp"),
    }
end

function mud_gltf()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "base64"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }

    files {
        path.join(MUD_3RDPARTY_DIR, "base64", "**.h"),
        path.join(MUD_3RDPARTY_DIR, "base64", "**.cpp"),
    }
end

mud.ctxbackend  = mud_ctx_backend()
mud.uibackend   = mud_ui_backend()

--                           base   name            root path    sub path       self decl       decl transitive     reflect     dependencies
-- gfx
mud.bgfx        = mud_module("mud", "bgfx",         MUD_SRC_DIR, "bgfx",        nil,            nil,                true,       { bx, bimg, bimg.decode, bimg.encode, bgfx, mud.infra, mud.type, mud.math, mud.ctx })
mud.gfx         = mud_module("mud", "gfx",          MUD_SRC_DIR, "gfx",         mud_gfx,        uses_mud_gfx,       true,       { tracy, json11, bgfx, shaderc, mud.infra, mud.jobs, mud.type, mud.pool, mud.math, mud.geom, mud.ctx, mud.bgfx })
-- gltf
mud.gltf        = mud_module("mud", "gltf",         MUD_SRC_DIR, "gltf",        mud_gltf,       nil,                true,       { json11, mud.infra, mud.type, mud.refl, mud.srlz, mud.math })
-- gfx exts
mud.gfx.pbr     = mud_module("mud", "gfx-pbr",      MUD_SRC_DIR, "gfx-pbr",     mud_gfx_pbr,    nil,                true,       { mud.infra, mud.type, mud.math, mud.geom, mud.gfx })
mud.gfx.obj     = mud_module("mud", "gfx-obj",      MUD_SRC_DIR, "gfx-obj",     nil,            nil,                true,       { mud.infra, mud.type, mud.srlz, mud.math, mud.geom, mud.gfx })
mud.gfx.gltf    = mud_module("mud", "gfx-gltf",     MUD_SRC_DIR, "gfx-gltf",    mud_gltf,       nil,                true,       { json11, mud.infra, mud.type, mud.refl, mud.srlz, mud.math, mud.geom, mud.gfx, mud.gltf, mud.gltf.refl })
mud.gfx.ui      = mud_module("mud", "gfx-ui",       MUD_SRC_DIR, "gfx-ui",      nil,            nil,                true,       { mud.infra, mud.tree, mud.type, mud.math, mud.geom, mud.ctx, mud.ui, mud.gfx })
mud.gfx.edit    = mud_module("mud", "gfx-edit",     MUD_SRC_DIR, "gfx-edit",    nil,            nil,                true,       { mud.infra, mud.type, mud.refl, mud.srlz, mud.math, mud.geom, mud.ui, mud.uio, mud.gfx, mud.gfx.pbr })
-- tool
mud.tool        = mud_module("mud", "tool",         MUD_SRC_DIR, "tool",        nil,            nil,                true,       { mud.infra, mud.tree, mud.type, mud.refl, mud.srlz, mud.lang, mud.math, mud.geom, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.gfx.pbr, mud.gfx.ui, mud.gfx.edit })
-- wfc
mud.wfc.gfx     = mud_module("mud", "wfc-gfx",      MUD_SRC_DIR, "wfc-gfx",     nil,            nil,                true,       { json11, mud.infra, mud.tree, mud.type, mud.srlz, mud.math, mud.geom, mud.wfc, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.gfx.ui })
-- core
mud.core        = mud_module("mud", "core",         MUD_SRC_DIR, "core",        nil,            nil,                false,      { mud.gfx, mud.gfx.ui, mud.ctxbackend, mud.uibackend })

table.extend(mud.mud, { mud.ctxbackend, mud.uibackend, mud.bgfx, mud.gfx, mud.gfx.pbr, mud.gfx.obj, mud.gltf, mud.gfx.gltf, mud.gfx.ui, mud.gfx.edit, mud.tool, mud.wfc.gfx, mud.core })

local lgfx = {}

if _OPTIONS["renderer-gl"] then
    lgfx = { mud.gl, mud.uibackend }
elseif _OPTIONS["renderer-bgfx"] then
    lgfx = { mud.bgfx, mud.uibackend }
end

table.insert(lgfx, mud.core)

