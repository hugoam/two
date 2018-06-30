-- mud library
-- mud ctx native module

mud.ctx.win = mud_module("mud", "ctx-win", MUD_SRC_DIR, "ctx-win", nil, nil, nil, { mud.math, mud.ctx })

function mud_ctx_backend()
    return mud.ctx.win
end
