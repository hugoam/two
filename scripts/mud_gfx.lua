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
    }
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

mud.ctxbackend  = mud_ctx_backend()
mud.uibackend   = mud_ui_backend()

--                           base   name            root path    sub path       decl    self decl       decl transitive     dependencies
mud.bgfx        = mud_module("mud", "bgfx",         MUD_SRC_DIR, "bgfx",        nil,    nil,            nil,                { bx, bimg, bimg.decode, bgfx, mud.infra, mud.obj, mud.math, mud.ctx, mud.ctxbackend })
mud.gfx         = mud_module("mud", "gfx",          MUD_SRC_DIR, "gfx",         nil,    nil,            uses_mud_gfx,       { json11, bgfx, shaderc, mud.infra, mud.obj, mud.pool, mud.refl, mud.srlz, mud.math, mud.geom, mud.ctx, mud.ctxbackend, mud.bgfx })

mud.gfx.pbr     = mud_module("mud", "gfx-pbr",      MUD_SRC_DIR, "gfx-pbr",     nil,    nil,            nil,                { mud.infra, mud.obj, mud.srlz, mud.math, mud.geom, mud.gfx })
mud.gfx.obj     = mud_module("mud", "gfx-obj",      MUD_SRC_DIR, "gfx-obj",     nil,    nil,            nil,                { mud.infra, mud.obj, mud.srlz, mud.math, mud.geom, mud.gfx })
mud.gfx.gltf    = mud_module("mud", "gfx-gltf",     MUD_SRC_DIR, "gfx-gltf",    nil,    mud_gfx_gltf,   nil,                { json11, mud.infra, mud.obj, mud.refl, mud.srlz, mud.math, mud.geom, mud.gfx })
mud.gfx.ui      = mud_module("mud", "gfx-ui",       MUD_SRC_DIR, "gfx-ui",      nil,    nil,            nil,                { mud.infra, mud.tree, mud.obj, mud.refl, mud.srlz, mud.lang, mud.math, mud.geom, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.gfx.pbr })

mud.tool        = mud_module("mud", "tool",         MUD_SRC_DIR, "tool",        nil,    nil,            nil,                { mud.infra, mud.tree, mud.obj, mud.refl, mud.srlz, mud.lang, mud.math, mud.geom, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.gfx.pbr, mud.gfx.ui })

mud.procgen.gfx = mud_module("mud", "procgen-gfx",  MUD_SRC_DIR, "procgen-gfx", nil,    nil,            nil,                { json11, mud.infra, mud.tree, mud.obj, mud.srlz, mud.math, mud.geom, mud.procgen, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.gfx.ui })

table.extend(mud.mud, { mud.ctxbackend, mud.uibackend, mud.bgfx, mud.gfx, mud.gfx.pbr, mud.gfx.obj, mud.gfx.gltf, mud.gfx.ui, mud.tool, mud.procgen.gfx })

local lgfx = {}

if _OPTIONS["renderer-gl"] then
    lgfx = { mud.gl, mud.uibackend }
elseif _OPTIONS["renderer-bgfx"] then
    lgfx = { mud.bgfx, mud.uibackend }
end

table.insert(lgfx, mud.core)

