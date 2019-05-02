-- two library
-- two ctx native module

two.ctx.win = two_module("two", "ctx-win", TWO_SRC_DIR, "ctx-win", nil, nil, false, { two.math, two.ctx })

function two_ctx_backend()
    return two.ctx.win
end
