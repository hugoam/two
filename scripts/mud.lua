-- mud library

if _OPTIONS["cpp-modules"] and _ACTION == "gmake" then
    dofile(path.join(MUD_DIR, "scripts/3rdparty/std.lua"))
end

if not _OPTIONS["compile-only"] then
    group "3rdparty"
    dofile(path.join(MUD_DIR, "scripts/3rdparty/json11.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/base64.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/stb.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/tracy.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/lua.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/wren.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/mikktspace.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/vg.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/bgfx/bgfx.lua"))
    group "3rdparty"
    dofile(path.join(MUD_DIR, "scripts/3rdparty/meshoptimizer.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/xatlas.lua"))
    dofile(path.join(MUD_DIR, "scripts/3rdparty/fastnoise.lua"))

    if _OPTIONS["culling"] then
        dofile(path.join(MUD_DIR, "scripts/3rdparty/culling.lua"))
    else
        culling = null
    end

    if _OPTIONS["context-glfw"] then
        dofile(path.join(MUD_DIR, "scripts/3rdparty/glfw.lua"))
    end

    if _OPTIONS["sound"] then
        dofile(path.join(MUD_DIR, "scripts/3rdparty/ogg/ogg.lua"))
        dofile(path.join(MUD_DIR, "scripts/3rdparty/vorbis/vorbis.lua"))
        dofile(path.join(MUD_DIR, "scripts/3rdparty/vorbis/vorbisfile.lua"))
    end
else
    stb = {}
    json11 = null
    base64 = null
    stb.image = null
    stb.rect_pack = null
    tracy = null
    lua = null
    wren = null
    fastnoise = null
    mikktspace = null
    vg = null
    bx = null
    bimg = null
    bgfx = null
    meshoptimizer = null
    culling = null
    glfw = null
    ogg = null
    vorbis = null
    vorbisfile = null
end

os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/filter"))
os.mkdir(path.join(PROJECT_DIR, "data/shaders/compiled/pbr"))

group "lib"

mud = {}

function uses_mud()
    mud_defines()
    
    includedirs {
        path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "tinystl", "include"),
    }
    
    if not _OPTIONS["use-stl"] then
        configuration { "Debug" }
            defines { "MUD_NO_STL" }
            
        configuration {}
    end
    
    if _OPTIONS["profile"] then
        defines { "TRACY_ENABLE" }
    end
end

function mud_infra()
    files {
        path.join(MUD_SRC_DIR, "stl", "**.h"),
        path.join(MUD_SRC_DIR, "stl", "**.hpp"),
        path.join(MUD_SRC_DIR, "stl", "**.cpp"),
    }
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

function uses_mud_bgfx()
    uses_mud()
    
    includedirs {
        path.join(BX_DIR,    "include"),
        path.join(BIMG_DIR,  "include"),
        path.join(BGFX_DIR,  "include"),
    }
    
    configuration { "vs*", "not orbis", "not asmjs" }
        includedirs { path.join(BX_DIR, "include/compat/msvc") }
    
    configuration {}
end

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
    
    if _OPTIONS["culling"] then
        includedirs {
            path.join(MUD_3RDPARTY_DIR, "culling"),
        }
    else
        defines { "NO_OCCLUSION_CULLING" }
    end
end

function mud_gfx_pbr()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "xatlas"),
    }
end

function mud_gltf()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "base64"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
end

-- @todo deactivate reflection for infra, tree, srlz, bgfx, gfx.obj, gfx.gltf, gfx.edit
--       and make reflection generator generate empty modules in those cases
--                       base   name        root path       sub path    self decl   usage decl      reflect     dependencies
-- core
mud.infra   = mud_module("mud", "infra",    MUD_SRC_DIR,    "infra",    mud_infra,  uses_mud,       true,       { })
mud.jobs    = mud_module("mud", "jobs",     MUD_SRC_DIR,    "jobs",     mud_jobs,   uses_mud,       true,       { tracy, mud.infra })
mud.type    = mud_module("mud", "type",     MUD_SRC_DIR,    "type",     nil,        uses_mud,       true,       { mud.infra })
mud.tree    = mud_module("mud", "tree",     MUD_SRC_DIR,    "tree",     nil,        nil,            true,       { mud.infra })
mud.pool    = mud_module("mud", "pool",     MUD_SRC_DIR,    "pool",     nil,        nil,            true,       { mud.infra, mud.type })
-- refl
mud.refl    = mud_module("mud", "refl",     MUD_SRC_DIR,    "refl",     nil,        nil,            true,       { mud.infra, mud.type, mud.pool })
-- ecs
mud.ecs     = mud_module("mud", "ecs",      MUD_SRC_DIR,    "ecs",      nil,        uses_mud,       true,       { mud.infra, mud.pool, mud.type, mud.refl })
-- srlz
mud.srlz    = mud_module("mud", "srlz",     MUD_SRC_DIR,    "srlz",     mud_srlz,   nil,            true,       { json11, mud.infra, mud.type, mud.refl })
-- math
if MUD_STATIC then      
  mud.math  = mud_module("mud", "math",     MUD_SRC_DIR,    "math",     mud_math,   uses_mud_math,  true,       { stb.rect_pack, mud.infra, mud.type })
else        
  mud.math  = mud_module("mud", "math",     MUD_SRC_DIR,    "math",     mud_math,   uses_mud_math,  true,       { stb.image, stb.rect_pack, mud.infra, mud.type })
end     
-- geom
mud.geom    = mud_module("mud", "geom",     MUD_SRC_DIR,    "geom",     mud_geom,   nil,            true,       { mikktspace, mud.type, mud.math })
-- procgen
mud.noise   = mud_module("mud", "noise",    MUD_SRC_DIR,    "noise",    mud_noise,  uses_mud_noise, true,       { fastnoise, mud.infra, mud.type, mud.math, mud.geom })
mud.wfc     = mud_module("mud", "wfc",      MUD_SRC_DIR,    "wfc",      mud_wfc,    nil,            true,       { json11, mud.infra, mud.type, mud.srlz, mud.math, mud.geom })
mud.fract   = mud_module("mud", "fract",    MUD_SRC_DIR,    "fract",    nil,        nil,            true,       { json11, mud.infra, mud.type, mud.math, mud.geom })
-- lang
mud.lang    = mud_module("mud", "lang",     MUD_SRC_DIR,    "lang",     mud_lang,   nil,            true,       { lua, wren, mud.infra, mud.type, mud.pool, mud.refl })
-- ui
mud.ctx     = mud_module("mud", "ctx",      MUD_SRC_DIR,    "ctx",      nil,        nil,            true,       { mud.infra, mud.type, mud.math })
mud.ui      = mud_module("mud", "ui",       MUD_SRC_DIR,    "ui",       mud_ui,     uses_mud_ui,    true,       { mud.infra, mud.type, mud.math, mud.ctx })
mud.uio     = mud_module("mud", "uio",      MUD_SRC_DIR,    "uio",      nil,        nil,            true,       { mud.infra, mud.tree, mud.type, mud.ecs, mud.pool, mud.refl, mud.math, mud.lang, mud.ctx, mud.ui })
-- snd
mud.snd     = mud_module("mud", "snd",      MUD_SRC_DIR,    "snd",      mud_snd,    uses_mud_snd,   true,       { ogg, vorbis, vorbisfile, mud.type, mud.math })

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

--                       base   name        root path       sub path    self decl   usage decl      reflect     dependencies
-- gfx
mud.bgfx    = mud_module("mud", "bgfx",     MUD_SRC_DIR,    "bgfx",     nil,        uses_mud_bgfx,  true,       { bx, bimg, bimg.decode, bimg.encode, bgfx, mud.infra, mud.type, mud.math, mud.ctx })
mud.gfx     = mud_module("mud", "gfx",      MUD_SRC_DIR,    "gfx",      mud_gfx,    uses_mud_gfx,   true,       { tracy, json11, meshopt, culling, bgfx, shaderc, mud.infra, mud.jobs, mud.type, mud.pool, mud.ecs, mud.math, mud.geom, mud.ctx, mud.bgfx })
-- gltf                                                     
mud.gltf    = mud_module("mud", "gltf",     MUD_SRC_DIR,    "gltf",     mud_gltf,   nil,            true,       { json11, base64, mud.infra, mud.type, mud.refl, mud.srlz, mud.math })
-- gfx exts                                                 
mud.gfx.pbr = mud_module("mud", "gfx-pbr",  MUD_SRC_DIR,    "gfx-pbr",  mud_gfx_pbr,nil,            true,       { xatlas, mud.infra, mud.type, mud.math, mud.geom, mud.gfx })
mud.gfx.obj = mud_module("mud", "gfx-obj",  MUD_SRC_DIR,    "gfx-obj",  nil,        nil,            true,       { mud.infra, mud.type, mud.srlz, mud.math, mud.geom, mud.gfx })
mud.gfx.gltf= mud_module("mud", "gfx-gltf", MUD_SRC_DIR,    "gfx-gltf", mud_gltf,   nil,            true,       { json11, mud.infra, mud.type, mud.refl, mud.srlz, mud.math, mud.geom, mud.gfx, mud.gltf, mud.gltf.refl })
mud.gfx.ui  = mud_module("mud", "gfx-ui",   MUD_SRC_DIR,    "gfx-ui",   nil,        nil,            true,       { mud.infra, mud.tree, mud.type, mud.math, mud.geom, mud.ctx, mud.ui, mud.gfx })
mud.gfx.edit= mud_module("mud", "gfx-edit", MUD_SRC_DIR,    "gfx-edit", nil,        nil,            true,       { mud.infra, mud.type, mud.refl, mud.srlz, mud.math, mud.geom, mud.ui, mud.uio, mud.gfx, mud.gfx.pbr })
-- tool                                                     
mud.tool    = mud_module("mud", "tool",     MUD_SRC_DIR,    "tool",     nil,        nil,            true,       { mud.infra, mud.tree, mud.type, mud.refl, mud.srlz, mud.lang, mud.math, mud.geom, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.gfx.pbr, mud.gfx.ui, mud.gfx.edit })
-- wfc                                                      
mud.wfc.gfx = mud_module("mud", "wfc-gfx",  MUD_SRC_DIR,    "wfc-gfx",  nil,        nil,            true,       { json11, mud.infra, mud.tree, mud.type, mud.srlz, mud.math, mud.geom, mud.wfc, mud.ctx, mud.ui, mud.uio, mud.gfx, mud.gfx.ui })
-- frame                                                    
mud.frame   = mud_module("mud", "frame",    MUD_SRC_DIR,    "frame",    nil,        nil,            true,       { mud.gfx, mud.gfx.ui, mud.ctxbackend, mud.uibackend })

if _OPTIONS["tools"] then
  mud.clrefl = mud_module("mud", "clrefl",  MUD_SRC_DIR,    "clrefl",   mud_clrefl, nil,            false,      { json11, mud.infra })
  mud.amalg  = mud_module("mud", "amalg",   MUD_SRC_DIR,    "amalg",    nil,        nil,            false,      { json11, mud.infra })
end

--mud_sys(true)
--mud_vec(true)
--mud.db = mud_module("mud", "db", MUD_SRC_DIR, "db", { mud.type, mud.util })

mud.mud = { mud.infra, mud.jobs, mud.type, mud.tree, mud.pool, mud.refl, mud.ecs, mud.srlz, mud.math, mud.geom, mud.lang, mud.ctx, mud.ui, mud.uio, mud.bgfx, mud.gfx, mud.gfx.ui, mud.frame,
            mud.ctxbackend, mud.uibackend }
mud.opts = { mud.noise, mud.wfc, mud.fract, mud.gfx.pbr, mud.gfx.obj, mud.gltf, mud.gfx.gltf, mud.gfx.edit, mud.tool, mud.wfc.gfx }

if _OPTIONS["tools"] then
    table.insert(mud.opts, mud.clrefl)
    table.insert(mud.opts, mud.amalg)
end

if _OPTIONS["sound"] then
    table.insert(mud.mud, mud.snd)
end

mud.all = table.union(mud.mud, mud.opts)

for _, m in pairs(mud.all) do
    print("    module " .. m.dotname)
end

if _OPTIONS["as-libs"] then
    FORCE_REFL_PROJECTS = true
end

mud.type.basetypes = { 'void', 'void*', 'bool', 'short', 'int', 'long', 'long long', 'float', 'double', 'char', 'unsigned char', 'unsigned short', 'unsigned int', 'unsigned long', 'unsigned long long', 'string', 'const char*' }
mud.type.aliases = { ['mud::string'] = 'string', ['mud::cstring'] = 'const char*' }

local lgfx = {}

if _OPTIONS["renderer-gl"] then
    lgfx = { mud.gl, mud.uibackend }
elseif _OPTIONS["renderer-bgfx"] then
    lgfx = { mud.bgfx, mud.uibackend }
end

table.insert(lgfx, mud.frame)

if _OPTIONS["unity"] then
    for _, m in pairs(mud.all) do
        m.unity = true
        if m.refl then
            m.refl.unity = true
        end
    end
end

if _OPTIONS["as-libs"] then
    group "lib/mud"
        mud_libs(mud.all, "StaticLib")
    group "lib"
else
    mud.lib = mud_lib("mud", mud.all, "StaticLib")
    
        --files {
        --    path.join(MUD_SRC_DIR, "mud", "**.h"),
        --}
        
        configuration { "vs*", "not asmjs", "Release" }
            buildoptions {
                "/bigobj",
            }
            
        configuration {}
end

--group "lib/mud-opts"
--mud_libs(mud.opts, "StaticLib")

function mud_binary(name, modules, deps)
    mud_lib(name, modules, "ConsoleApp", deps)
    defines { "_" .. name:upper() .. "_EXE" }
    mud_binary_config()
end

function mud_js(name, modules)
    local lib = mud_lib(name, {}, "ConsoleApp", modules)
    mud_glue_js(table.inverse(lib.deps))
    linkoptions {
        "-s EXPORT_NAME=\"'" .. name .. "'\"",
        "-s MODULARIZE=1",
    }
    mud_binary_config()
end
