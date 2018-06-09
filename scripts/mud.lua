-- mud library

if _OPTIONS["cpp-modules"] then
    dofile(path.join(MUD_DIR, "scripts/3rdparty/std.lua"))
end

group "3rdparty"
dofile(path.join(MUD_DIR, "scripts/3rdparty/json11.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/stb.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/lua.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/glfw.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/vg.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/bgfx/bgfx.lua"))

group "lib"

mud = {}

function mud_srlz()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
end

function mud_math()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
end

function uses_mud_math()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }
end

function mud_ui()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "stb"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
    
    --defines { "MUD_UI_DRAW_CACHE" }    
end

function mud_geom()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "mikkt"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "mikkt", "mikktspace.c"),
    }
end

function mud_lang()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "lua"),
    }
end

function mud_snd()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "vorbis", "include"),
        path.join(MUD_3RDPARTY_DIR, "ogg", "include"),
        path.join(MUD_DIR, "scripts/3rdparty/ogg/"),
    }
    
    links {
        "vorbis",
        "vorbisfile",
        "ogg",
        "OpenAL32",
    }
end

function mud_db()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "sqlite3"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "sqlite3", "*.c"),
    }
end

--                                        base   name       root path    sub path   decl        decl transitive     dependencies
mud.infra   = mud_module(mud_module_decl, "mud", "infra",   MUD_SRC_DIR, "infra",   nil,        nil,                {})
mud.obj     = mud_module(mud_module_decl, "mud", "obj",     MUD_SRC_DIR, "obj",     nil,        nil,                { mud.infra })
mud.pool    = mud_module(mud_module_decl, "mud", "pool",    MUD_SRC_DIR, "pool",    nil,        nil,                { mud.infra, mud.obj })
mud.refl    = mud_module(mud_module_decl, "mud", "refl",    MUD_SRC_DIR, "refl",    nil,        nil,                { mud.infra, mud.obj, mud.pool })
mud.tree    = mud_module(mud_module_decl, "mud", "tree",    MUD_SRC_DIR, "tree",    nil,        nil,                { mud.infra })
mud.srlz    = mud_module(mud_module_decl, "mud", "srlz",    MUD_SRC_DIR, "srlz",    mud_srlz,   nil,                { json11, mud.infra, mud.obj, mud.refl })
mud.math    = mud_module(mud_module_decl, "mud", "math",    MUD_SRC_DIR, "math",    mud_math,   uses_mud_math,      { json11, mud.infra, mud.obj, mud.refl, mud.srlz })
mud.geom    = mud_module(mud_module_decl, "mud", "geom",    MUD_SRC_DIR, "geom",    mud_geom,   nil,                { mud.obj, mud.math })
mud.lang    = mud_module(mud_module_decl, "mud", "lang",    MUD_SRC_DIR, "lang",    mud_lang,   nil,                { lua, mud.infra, mud.obj, mud.pool, mud.refl })
mud.ctx     = mud_module(mud_module_decl, "mud", "ctx",     MUD_SRC_DIR, "ctx",     nil,        nil,                { mud.infra, mud.obj, mud.math })
mud.ui      = mud_module(mud_module_decl, "mud", "ui",      MUD_SRC_DIR, "ui",      mud_ui,     nil,                { json11, stb.image, stb.rect_pack, mud.infra, mud.obj, mud.refl, mud.srlz, mud.math, mud.ctx })
mud.uio     = mud_module(mud_module_decl, "mud", "uio",     MUD_SRC_DIR, "uio",     nil,        nil,                { mud.infra, mud.tree, mud.obj, mud.pool, mud.refl, mud.math, mud.lang, mud.ctx, mud.ui })
--mud_sys(true)
--mud_vec(true)
--mud.db = mud_module(as_project, "mud", "db", MUD_SRC_DIR, "db", { mud.obj, mud.util })

if _OPTIONS["sound"] then
    mud.snd = mud_module(mud_module_decl, "mud", "snd",     MUD_SRC_DIR, "snd",     mud_snd,    nil,                { mud.obj })
end

mud.core = { mud.infra, mud.obj, mud.pool, mud.refl, mud.tree, mud.srlz, mud.math, mud.geom, mud.lang, mud.ctx, mud.ui, mud.uio }

if _OPTIONS["as-libs"] then
    group "lib/mud"
        for _, m  in ipairs(mud.core) do
            m.decl(m, true)
        end
    group "lib"
else
    project "mud"
        kind "SharedLib"
        
        for _, m  in ipairs(mud.core) do
            m.decl(m, false)
        end
        
        files {
            path.join(MUD_SRC_DIR, "mud", "**.h"),
        }
end
    
function uses_mud()
    includedirs {
        path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }
    
    if _OPTIONS["as-libs"] then
        links { "mud_infra", "mud_obj", "mud_refl", "mud_srlz", "mud_math", "mud_geom", "mud_lang", "mud_ctx", "mud_ui", "mud_uio" }
        links { "mud_obj_refl", "mud_refl_refl", "mud_srlz_refl", "mud_math_refl", "mud_geom_refl", "mud_lang_refl", "mud_ctx_refl", "mud_ui_refl", "mud_uio_refl" }
    else
        links { "mud" }
        links { "mud_refl" }
    end
end

function mud_shell(name)
    mud_defines()
    mud_binary(name)
    
    files {
        path.join(MUD_DIR, "src", "mud", "Shell.cpp"),
    }
end

if _OPTIONS["renderer-gl"] then
    dofile(path.join(MUD_DIR, "scripts/mud_gl.lua"))
elseif _OPTIONS["renderer-bgfx"] then
    dofile(path.join(MUD_DIR, "scripts/mud_gfx.lua"))
end
