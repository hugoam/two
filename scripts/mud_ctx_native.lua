-- mud library
-- mud ctx native module

function mud_ctx_backend(parent)
    mud.ctxbackend = mud_module(false, "ctx-win", MUD_SRC_DIR, "ctx-win") 
    table.insert(parent.deps, mud.ctxbackend)
end
