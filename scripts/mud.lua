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

function uses_mud()
    includedirs {
        path.join(MUD_SRC_DIR),
    }
end

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

--                       base   name        root path    sub path   decl        self decl       decl transitive     dependencies
mud.infra   = mud_module("mud", "infra",    MUD_SRC_DIR, "infra",   nil,        nil,            nil,                {})
mud.obj     = mud_module("mud", "obj",      MUD_SRC_DIR, "obj",     nil,        nil,            nil,                { mud.infra })
mud.pool    = mud_module("mud", "pool",     MUD_SRC_DIR, "pool",    nil,        nil,            nil,                { mud.infra, mud.obj })
mud.refl    = mud_module("mud", "refl",     MUD_SRC_DIR, "refl",    nil,        nil,            nil,                { mud.infra, mud.obj, mud.pool })
mud.tree    = mud_module("mud", "tree",     MUD_SRC_DIR, "tree",    nil,        nil,            nil,                { mud.infra })
mud.srlz    = mud_module("mud", "srlz",     MUD_SRC_DIR, "srlz",    nil,        mud_srlz,       nil,                { json11, mud.infra, mud.obj, mud.refl })
mud.math    = mud_module("mud", "math",     MUD_SRC_DIR, "math",    nil,        mud_math,       uses_mud_math,      { json11, mud.infra, mud.obj, mud.refl, mud.srlz })
mud.geom    = mud_module("mud", "geom",     MUD_SRC_DIR, "geom",    nil,        mud_geom,       nil,                { mud.obj, mud.math })
mud.lang    = mud_module("mud", "lang",     MUD_SRC_DIR, "lang",    nil,        mud_lang,       nil,                { lua, mud.infra, mud.obj, mud.pool, mud.refl })
mud.ctx     = mud_module("mud", "ctx",      MUD_SRC_DIR, "ctx",     nil,        nil,            nil,                { mud.infra, mud.obj, mud.math })
if MUD_STATIC then
    mud.ui  = mud_module("mud", "ui",       MUD_SRC_DIR, "ui",      nil,        mud_ui,         nil,                { json11, stb.rect_pack, mud.infra, mud.obj, mud.refl, mud.srlz, mud.math, mud.ctx })
else
    mud.ui  = mud_module("mud", "ui",       MUD_SRC_DIR, "ui",      nil,        mud_ui,         nil,                { json11, stb.image, stb.rect_pack, mud.infra, mud.obj, mud.refl, mud.srlz, mud.math, mud.ctx })
end
mud.uio     = mud_module("mud", "uio",      MUD_SRC_DIR, "uio",     nil,        nil,            nil,                { mud.infra, mud.tree, mud.obj, mud.pool, mud.refl, mud.math, mud.lang, mud.ctx, mud.ui })
--mud_sys(true)
--mud_vec(true)
--mud.db = mud_module(as_project, "mud", "db", MUD_SRC_DIR, "db", { mud.obj, mud.util })

if _OPTIONS["sound"] then
    mud.snd = mud_module("mud", "snd",      MUD_SRC_DIR, "snd",     nil,        mud_snd,        nil,                { mud.obj })
end

mud.modules = { mud.infra, mud.obj, mud.pool, mud.refl, mud.tree, mud.srlz, mud.math, mud.geom, mud.lang, mud.ctx, mud.ui, mud.uio }
mud.usage_decl = uses_mud

table.extend(mud.modules, mud_refls({ mud.infra, mud.obj, mud.pool, mud.refl, mud.srlz, mud.math, mud.geom, mud.lang, mud.ctx, mud.ui, mud.uio }))

if _OPTIONS["as-libs"] then
    group "lib/mud"
        for _, m  in ipairs(mud.modules) do
            m.decl(m, true)
        end
    group "lib"
else
    project "mud"
        if MUD_STATIC then
            kind "StaticLib"
        else
            kind "SharedLib"
        end
        
        for _, m  in ipairs(mud.modules) do
            m.decl(m, false)
        end
        
        files {
            path.join(MUD_SRC_DIR, "mud", "**.h"),
        }
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
