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

if _OPTIONS["sound"] then
    dofile(path.join(MUD_DIR, "scripts/3rdparty/ogg/ogg.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/vorbis/vorbis.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/vorbis/vorbisfile.lua"))
end

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
        path.join(MUD_3RDPARTY_DIR, "stb"),
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
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
end

function uses_mud_ui()
    defines { "MUD_UI_DRAW_CACHE" }
end

function mud_geom()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "mikkt"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "mikkt", "mikktspace.c"),
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
end

function uses_mud_snd()
    links {
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
mud.infra   = mud_module("mud", "infra",    MUD_SRC_DIR, "infra",   nil,        nil,            uses_mud,           {})
mud.obj     = mud_module("mud", "obj",      MUD_SRC_DIR, "obj",     nil,        nil,            uses_mud,           { mud.infra })
mud.pool    = mud_module("mud", "pool",     MUD_SRC_DIR, "pool",    nil,        nil,            nil,                { mud.infra, mud.obj })
mud.refl    = mud_module("mud", "refl",     MUD_SRC_DIR, "refl",    nil,        nil,            nil,                { mud.infra, mud.obj, mud.pool })
mud.proto   = mud_module("mud", "proto",    MUD_SRC_DIR, "proto",   nil,        nil,            uses_mud,           { mud.infra, mud.obj, mud.refl })
mud.tree    = mud_module("mud", "tree",     MUD_SRC_DIR, "tree",    nil,        nil,            nil,                { mud.infra })
mud.srlz    = mud_module("mud", "srlz",     MUD_SRC_DIR, "srlz",    nil,        mud_srlz,       nil,                { json11, mud.infra, mud.obj, mud.refl })
if MUD_STATIC then
    mud.math = mud_module("mud", "math",    MUD_SRC_DIR, "math",    nil,        mud_math,       uses_mud_math,      { json11, stb.rect_pack, mud.infra, mud.obj, mud.refl, mud.srlz })
else
    mud.math = mud_module("mud", "math",    MUD_SRC_DIR, "math",    nil,        mud_math,       uses_mud_math,      { json11, stb.image, stb.rect_pack, mud.infra, mud.obj, mud.refl, mud.srlz })
end
mud.geom    = mud_module("mud", "geom",     MUD_SRC_DIR, "geom",    nil,        mud_geom,       nil,                { mud.obj, mud.math })
mud.procgen = mud_module("mud", "procgen",  MUD_SRC_DIR, "procgen", nil,        mud_procgen,    uses_mud_procgen,   { json11, mud.infra, mud.obj, mud.srlz, mud.math, mud.geom })
mud.lang    = mud_module("mud", "lang",     MUD_SRC_DIR, "lang",    nil,        mud_lang,       nil,                { lua, mud.infra, mud.obj, mud.pool, mud.refl })
mud.ctx     = mud_module("mud", "ctx",      MUD_SRC_DIR, "ctx",     nil,        nil,            nil,                { mud.infra, mud.obj, mud.math })
mud.ui      = mud_module("mud", "ui",       MUD_SRC_DIR, "ui",      nil,        mud_ui,         uses_mud_ui,        { json11, mud.infra, mud.obj, mud.refl, mud.srlz, mud.math, mud.ctx })
mud.uio     = mud_module("mud", "uio",      MUD_SRC_DIR, "uio",     nil,        nil,            nil,                { mud.infra, mud.tree, mud.obj, mud.pool, mud.refl, mud.math, mud.lang, mud.ctx, mud.ui })
mud.snd     = mud_module("mud", "snd",      MUD_SRC_DIR, "snd",     nil,        mud_snd,        uses_mud_snd,       { ogg, vorbis, vorbisfile, mud.obj, mud.math })
--mud_sys(true)
--mud_vec(true)
--mud.db = mud_module(as_project, "mud", "db", MUD_SRC_DIR, "db", { mud.obj, mud.util })

mud.mud = { mud.infra, mud.obj, mud.pool, mud.refl, mud.proto, mud.tree, mud.srlz, mud.math, mud.geom, mud.procgen, mud.lang, mud.ctx, mud.ui, mud.uio, mud.snd }

--mud.usage_decl = uses_mud

if _OPTIONS["as-libs"] then
    FORCE_REFL_PROJECTS = true
end

mud.obj.basetypes = { 'void', 'bool', 'short', 'int', 'long', 'long long', 'float', 'double', 'char', 'unsigned char', 'unsigned short', 'unsigned int', 'unsigned long', 'unsigned long long', 'std::string', 'cstring' }
mud.obj.aliases = { ['mud::string'] = 'std::string', ['string'] = 'std::string', ['mud::cstring'] = 'cstring' }

if _OPTIONS["renderer-gl"] then
    dofile(path.join(MUD_DIR, "scripts/mud_gl.lua"))
elseif _OPTIONS["renderer-bgfx"] then
    dofile(path.join(MUD_DIR, "scripts/mud_gfx.lua"))
end

if _OPTIONS["as-libs"] then
    group "lib/mud"
        mud_libs(mud.mud, "StaticLib")
    group "lib"
else
    mud.lib = mud_lib("mud", mud.mud, "StaticLib")
    
        files {
            path.join(MUD_SRC_DIR, "mud", "**.h"),
        }
        
        configuration { "vs*", "not asmjs", "Release" }
            buildoptions {
                "/bigobj",
            }
            
        configuration {}
end

function mud_binary(name, modules, deps)
    mud_lib(name, modules, "ConsoleApp")
    defines { "_" .. name:upper() .. "_EXE" }
    mud_binary_config()
end

function mud_shell(name, modules, deps)
    mud_binary(name, modules, deps)
    
    files {
        path.join(MUD_DIR, "src", "mud", "Shell.cpp"),
    }
end
