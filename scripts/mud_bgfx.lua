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

mud.ctxbackend  = mud_ctx_backend()
mud.uibackend   = mud_ui_backend()

mud.bgfx        = mud_module("mud", "bgfx", MUD_SRC_DIR, "bgfx", nil, nil, nil, { bx, bimg, bimg.decode, bgfx, mud.infra, mud.obj, mud.math, mud.ctx, mud.ui, mud.ctxbackend, mud.uibackend })
