-- mud library

if _OPTIONS["cpp-modules"] and _ACTION == "gmake" then
    dofile(path.join(MUD_DIR, "scripts/3rdparty/std.lua"))
end

group "3rdparty"
dofile(path.join(MUD_DIR, "scripts/3rdparty/json11.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/stb.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/tracy.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/lua.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/wren.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/vg.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/bgfx/bgfx.lua"))

if _OPTIONS["context-glfw"] then
    dofile(path.join(MUD_DIR, "scripts/3rdparty/glfw.lua"))
end

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
    
    if _OPTIONS["profile"] then
        defines { "TRACY_ENABLE" }
    end
end

function mud_jobs()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "tracy"),
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

function uses_mud_noise()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "FastNoise"),
    }
end

function mud_noise()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "FastNoise"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "FastNoise", "**.h"),
        path.join(MUD_3RDPARTY_DIR, "FastNoise", "**.cpp"),
    }
end

function mud_wfc()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
end

function mud_lang()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "lua"),
        path.join(MUD_3RDPARTY_DIR, "wren", "src", "include"),
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
    configuration { "asmjs" }
        --links { "openal" }
        
    configuration { "not asmjs" }
        links { "OpenAL32" }
        
    configuration {}
end

function mud_db()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "sqlite3"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "sqlite3", "*.c"),
    }
end

function mud_clrefl()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
    
    links { "libclang" }
    
    configuration { "windows" }
        includedirs {
            "C:/Program Files (x86)/LLVM/include",
            "C:/Program Files/LLVM/include",
        }

    configuration { "windows", "x32" }
        libdirs {
            "C:/Program Files (x86)/LLVM/lib",
        }

    configuration { "windows", "x64" }
        libdirs {
            "C:/Program Files/LLVM/lib",
        }
        
    configuration {}
end

--                       base   name        root path       sub path    self decl   usage decl      reflect     dependencies
-- core
mud.infra   = mud_module("mud", "infra",    MUD_SRC_DIR,    "infra",    nil,        uses_mud,       true,       { })
mud.jobs    = mud_module("mud", "jobs",     MUD_SRC_DIR,    "jobs",     mud_jobs,   uses_mud,       true,       { tracy, mud.infra })
mud.type    = mud_module("mud", "type",     MUD_SRC_DIR,    "type",     nil,        uses_mud,       true,       { mud.infra })
mud.tree    = mud_module("mud", "tree",     MUD_SRC_DIR,    "tree",     nil,        nil,            true,       { mud.infra })
mud.pool    = mud_module("mud", "pool",     MUD_SRC_DIR,    "pool",     nil,        nil,            true,       { mud.infra, mud.type })
-- refl
mud.refl    = mud_module("mud", "refl",     MUD_SRC_DIR,    "refl",     nil,        nil,            true,       { mud.infra, mud.type, mud.pool })
-- ecs
mud.ecs     = mud_module("mud", "ecs",      MUD_SRC_DIR,    "ecs",      nil,        uses_mud,       true,       { mud.infra, mud.type, mud.refl })
-- srlz
mud.srlz    = mud_module("mud", "srlz",     MUD_SRC_DIR,    "srlz",     mud_srlz,   nil,            true,       { json11, mud.infra, mud.type, mud.refl })
-- math
if MUD_STATIC then      
  mud.math  = mud_module("mud", "math",     MUD_SRC_DIR,    "math",     mud_math,   uses_mud_math,  true,       { json11, stb.rect_pack, mud.infra, mud.type })
else        
  mud.math  = mud_module("mud", "math",     MUD_SRC_DIR,    "math",     mud_math,   uses_mud_math,  true,       { json11, stb.image, stb.rect_pack, mud.infra, mud.type })
end     
-- geom
mud.geom    = mud_module("mud", "geom",     MUD_SRC_DIR,    "geom",     mud_geom,   nil,            true,       { mud.type, mud.math })
-- procgen
mud.noise   = mud_module("mud", "noise",    MUD_SRC_DIR,    "noise",    mud_noise,  uses_mud_noise, true,       { json11, mud.infra, mud.type, mud.math, mud.geom })
mud.wfc     = mud_module("mud", "wfc",      MUD_SRC_DIR,    "wfc",      mud_wfc,    nil,            true,       { json11, mud.infra, mud.type, mud.srlz, mud.math, mud.geom })
mud.fract   = mud_module("mud", "fract",    MUD_SRC_DIR,    "fract",    nil,        nil,            true,       { json11, mud.infra, mud.type, mud.math, mud.geom })
-- lang
mud.lang    = mud_module("mud", "lang",     MUD_SRC_DIR,    "lang",     mud_lang,   nil,            true,       { lua, wren, mud.infra, mud.type, mud.pool, mud.refl })
-- ui
mud.ctx     = mud_module("mud", "ctx",      MUD_SRC_DIR,    "ctx",      nil,        nil,            true,       { mud.infra, mud.type, mud.math })
mud.ui      = mud_module("mud", "ui",       MUD_SRC_DIR,    "ui",       mud_ui,     uses_mud_ui,    true,       { json11, mud.infra, mud.type, mud.math, mud.ctx })
mud.uio     = mud_module("mud", "uio",      MUD_SRC_DIR,    "uio",      nil,        nil,            true,       { mud.infra, mud.tree, mud.type, mud.ecs, mud.pool, mud.refl, mud.math, mud.lang, mud.ctx, mud.ui })
-- snd
mud.snd     = mud_module("mud", "snd",      MUD_SRC_DIR,    "snd",      mud_snd,    uses_mud_snd,   true,       { ogg, vorbis, vorbisfile, mud.type, mud.math })

if _OPTIONS["metagen"] then
  mud.clrefl = mud_module("mud", "clrefl",  MUD_SRC_DIR,    "clrefl",   mud_clrefl, nil,            false,      { json11, mud.infra, mud.type, mud.pool, mud.refl })
end

--mud_sys(true)
--mud_vec(true)
--mud.db = mud_module("mud", "db", MUD_SRC_DIR, "db", { mud.type, mud.util })

mud.mud = { mud.infra, mud.jobs, mud.type, mud.tree, mud.pool, mud.refl, mud.ecs, mud.srlz, mud.math, mud.geom, mud.noise, mud.wfc, mud.fract, mud.lang, mud.ctx, mud.ui, mud.uio }

if _OPTIONS["metagen"] then
    table.insert(mud.mud, mud.clrefl)
end

if _OPTIONS["sound"] then
    table.insert(mud.mud, mud.snd)
end

if _OPTIONS["as-libs"] then
    FORCE_REFL_PROJECTS = true
end

mud.type.basetypes = { 'void', 'bool', 'short', 'int', 'long', 'long long', 'float', 'double', 'char', 'unsigned char', 'unsigned short', 'unsigned int', 'unsigned long', 'unsigned long long', 'std::string', 'const char*' }
mud.type.aliases = { ['mud::string'] = 'std::string', ['string'] = 'std::string', ['mud::cstring'] = 'const char*' }

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
    mud_lib(name, modules, "ConsoleApp", deps)
    defines { "_" .. name:upper() .. "_EXE" }
    mud_binary_config()
end

function mud_js(name, modules)
    local lib = mud_lib(name, {}, "ConsoleApp", modules)
    mud_glue_js(table.inverse(lib.deps))
    mud_binary_config()
end
