-- mud toolchain

MUD_STATIC = true
FORCE_REFL_PROJECTS = false

MODULES = {}

if not MUD_DIR then
    MUD_DIR = path.getabsolute("..")
end
MUD_SRC_DIR    = path.join(MUD_DIR, "src")

MUD_3RDPARTY_DIR = path.join(MUD_DIR, "3rdparty")

BX_DIR   = path.join(MUD_3RDPARTY_DIR, "bx")
BGFX_DIR = path.join(MUD_3RDPARTY_DIR, "bgfx")
BIMG_DIR = path.join(MUD_3RDPARTY_DIR, "bimg")

json = dofile(path.join(MUD_3RDPARTY_DIR, "jsonlua/json.lua"))
    
function file_exists(name)
    local f = io.open(name, "r")
    if f ~= nil then
        io.close(f)
        return true
    else
        return false
    end
end

function table.extend(dest, source)
    for _, v in ipairs(source) do
        table.insert(dest, v)
    end
end

function table.inverse(source)
    result = {}
    for i = #source, 1, -1 do
        table.insert(result, source[i])
    end
    return result
end

function table.traverse(tables, children, callback)
    local queue = tables
    local visited = {}
    while next(queue) ~= nil do
        local n = table.remove(queue, 1)
        callback(n)
        table.insert(visited, n)
        
        for _, c in ipairs(n[children] or {}) do
            if not table.contains(queue, c) and not table.contains(visited, c) then
                table.insert(queue, c)
            end
        end
    end
end

function mud_defines()
    if MUD_STATIC then
        defines {
            "MUD_STATIC",
        }
    end
    
    configuration { "cpp-modules" }
        defines {
            "MUD_NO_GLM",
            "MUD_CPP_20",
        }
        
    configuration { "cpp-modules", "*-clang*" }
        defines {
            "MUD_MODULES",
        }
    
    configuration { "cpp-modules", "vs*" }
        defines { 
            "MUD_STD_HAS_CLAMP",
        }
        
    configuration { "windows", "not asmjs" }
        defines { "MUD_PLATFORM_WINDOWS" }
        
    configuration { "linux" }
        defines { "MUD_PLATFORM_LINUX" }

    configuration { "osx" }
        defines { "MUD_PLATFORM_OSX" }
        
    configuration { "asmjs" }
        defines { "MUD_PLATFORM_EMSCRIPTEN" }
        
    configuration {}
  
    configuration { "renderer-gl" }
        defines { "MUD_RENDERER_GL" }
        
    configuration { "renderer-bgfx" }
        defines { "MUD_RENDERER_BGFX" }
        
    configuration { "context-glfw" }
        defines { "MUD_CONTEXT_GLFW" }
            
    configuration { "context-wasm" }
        defines { "MUD_CONTEXT_WASM" }
        
    configuration { "context-native" }
        defines { "MUD_CONTEXT_NATIVE" }
        
    configuration { "windows and context-native" }
        defines { "MUD_CONTEXT_WINDOWS" }
        
    configuration { "context-ogre" }
        defines { "MUD_CONTEXT_OGRE" }
        
    configuration {}
        
    configuration { "webgl2" }
        defines { "MUD_WEBGL2" }
            
    configuration {}
end

function mud_binary(name)
    targetprefix ""
    
    mud_defines()
    
    defines { "_" .. name:upper() .. "_EXE" }
        
    configuration { "asmjs" }
        linkoptions {
            "--separate-asm",
            "--memory-init-file 1",
            --"--llvm-lto 3",
        }
        
        linkoptions {
            "--preload-file ../../../data/interface",
            "--preload-file ../../../data/shaders",
            "--preload-file ../../../data/textures",
            "--shell-file ../../../scripts/emshell.html",
        }
            
    configuration { "asmjs", "webgl2" }
        linkoptions {
            "-s USE_WEBGL2=1",
        }
        
    configuration { "asmjs", "Debug" }
        linkoptions {
            "-s TOTAL_MEMORY=536870912",
            --"-s ALLOW_MEMORY_GROWTH=1",
        }
        
    configuration { "asmjs", "Release" }
        linkoptions {
            "-s WASM=1",
            "-s ALLOW_MEMORY_GROWTH=1",
            "-s ALIASING_FUNCTION_POINTERS=0",
        }
        
    configuration { "not linux", "not asmjs" }
        defines {
            "MUD_RESOURCE_PATH=\"" .. path.join(PROJECT_DIR, "data") .. "/\"",
        }

    configuration { "linux", "not asmjs" }
        defines {
            "MUD_RESOURCE_PATH=\\\"" .. path.join(PROJECT_DIR, "data") .. "/\\\"",
        }

    configuration {}
end

function mud_modules(m)
    configuration { "cpp-modules" }
        removeflags { "Cpp14" }
        flags {
            "CppLatest",
            "CppModules",
        }
        
        defines { "_CRT_NO_VA_START_VALIDATION" }

    configuration { "cpp-modules", "*-clang*" }
        links {
            "std_core",
            "std_io",
            "std_threading",
            "std_regex",
        }
        
    configuration { "cpp-modules", "vs*" }
        files {
            --path.join(m.path, m.dotname .. ".ixx"),
        }
            
    configuration { "cpp-modules", "*-clang*" }
        files {
            path.join(m.path, m.dotname .. ".mxx"),
        }
        
    configuration {}
end

function mud_mxx(cpps, m)
    if not _OPTIONS["cpp-modules"] then
        return
    end
    
    local cxxmodules = {}

    for _, cpp in ipairs(cpps) do
        local relcpp = path.getrelative(MUD_DIR, cpp)
        print("module for " .. relcpp .. " = " .. m.dotname)
        cxxmodules[relcpp] = m.dotname
    end

    cxxmodule(cxxmodules)
end

function mud_dep(namespace, name, cppmodule, usage_decl, deps)
    local m = {
        project = nil,
        cppmodule = cppmodule,
        namespace = namespace,
        name = name,
        dotname = string.gsub(name, "-", "."),
        idname = string.gsub(name, "-", "_"),
        usage_decl = usage_decl,
        deps = deps,
    }
    
    if namespace then
        m.dotname = namespace .. "." .. m.dotname
        m.idname = namespace .. "_" .. m.idname
    end
    
    m.project = project(m.idname)
    m.lib = project().name
    
    mud_defines()
    if cppmodule then
        mud_modules(m)
    end
    
    return m
end

function mud_module(namespace, name, rootpath, subpath, decl, self_decl, usage_decl, deps, nomodule, noreflect)
    local m = {
        project = nil,
        cppmodule = true,
        namespace = namespace,
        name = name,
        dotname = string.gsub(name, "-", "."),
        idname = string.gsub(name, "-", "_"),
        root = rootpath,
        subdir = subpath,
        path = path.join(rootpath, subpath),
        decl = decl,
        self_decl = self_decl,
        usage_decl = usage_decl,
        deps = deps or {},
        invdeps = table.inverse(deps or {}),
        nomodule = nomodule,
        noreflect = noreflect,
    }
    
    if not m.decl then
        m.decl = mud_module_decl
    end
    
    if namespace then
        m.dotname = namespace .. "." .. m.dotname
        m.idname = namespace .. "_" .. m.idname
    end
    
    if not nomodule then
        table.insert(MODULES, m)
    end
    
    return m
end

function mud_refl(m, force_project)
    deps = { mud.infra, mud.obj, mud.pool, mud.refl }
    table.extend(deps, m.deps)
    table.extend(deps, { m })
    m.refl = mud_module(m.namespace, m.name .. "-refl", m.root, path.join("meta", m.subdir), mud_refl_decl, m.self_decl, m.usage_decl, deps)
    m.refl.force_project = force_project
    return m.refl
end

function mud_refls(modules, force_project)
    refls = {}
    for _, m in ipairs(modules) do
        table.insert(refls, mud_refl(m, force_project))
    end
    return refls
end

function mud_depend(m)
    --print(project().name .. " depends on " .. m.idname)
    if m.usage_decl then
        m.usage_decl()
    end
    if m.lib and project().name ~= m.lib then
        --print(project().name .. " links " .. m.lib)
        links(m.lib)
    end
end

function mud_depends(modules)
    -- dependencies are inverted so that linking order is correct : from higher level to lower level
    list = table.inverse(modules)
    if MUD_STATIC then
        table.traverse(list, 'invdeps', mud_depend)
    else
        for _, m in ipairs(list) do
            mud_depend(modules[i])
        end
    end
end

function mud_project(m)
    print ("project " .. m.idname)
    m.project = project(m.idname)
    if MUD_STATIC then
        kind "StaticLib"
    else
        kind "SharedLib"
    end
    
end

function mud_module_decl(m, as_project)
    local previous = project().name
    if as_project then
        mud_project(m)
        defines { m.idname:upper() .. "_LIB" }
    end

    m.lib = project().name
    
    mud_depends(m.deps)
    
    includedirs {
        m.root,
    }
    
    files {
        path.join(m.path, "**.h"),
        path.join(m.path, "**.cpp"),
    }
    
    local cpps = os.matchfiles(path.join(m.path, "**.cpp"))
    mud_mxx(cpps, m)
    
    defines { m.idname:upper() .. "_EXPORT=MUD_EXPORT" }
    
    --vpaths { [name] = { "**.h", "**.cpp" } }
    
    mud_defines()
    mud_modules(m)
    
    if m.self_decl then
        m.self_decl()
    end
    if m.usage_decl then
        m.usage_decl()
    end
    
    if as_project then
        project(previous)
    end
end

function mud_refl_decl(m)
    mud_module_decl(m, m.force_project)
end

function mud_amalgamate(modules)
    for _, m in ipairs(modules) do
        local dir = os.getcwd()
        os.chdir(m.root)
        os.execute(path.join(MUD_DIR, "3rdparty/amalgamate/amalgamate.py") .. " -c " .. m.path .. "/Refl/amalgam.h.json" .. " -s " .. MUD_SRC_DIR)
        os.execute(path.join(MUD_DIR, "3rdparty/amalgamate/amalgamate.py") .. " -c " .. m.path .. "/Refl/amalgam.cpp.json" .. " -s " .. MUD_SRC_DIR)
        os.chdir(dir)
    end
end

function mud_write_api(m)
    headers = os.matchfiles(path.join(m.path, "**.h"))
    --table.insert(headers, os.matchfiles(path.join(m.path, "**.hpp")))
    
    local f, err = io.open(path.join(m.path, "Api.h"), "wb")
    io.output(f)
    for _, h in ipairs(headers) do
        if not string.find(h, "Api.h") then
            io.printf("#include <" .. path.getrelative(m.root, h) .. ">")
        end
    end
    io.printf("")
    f:close()
end

function mud_write_mxx(m)
	local f, err = io.open(path.join(m.path, m.dotname .. ".mxx"), "wb")
    io.output(f)
    
    local p = io.printf
    p("#include <cpp/preimport.h>")
    p("")
    p("#include <obj/Config.h>")
    p("")
    p("export module " .. m.dotname .. ";")
    p("export import std.core;")
    p("export import std.io;")
    p("export import std.threading;")
    p("export import std.regex;")
    p("")
    for _, dep in ipairs(m.deps or {}) do
        if dep.cppmodule then
            p("export import " .. dep.dotname .. ";")
        end
    end
    p("")
    p("#include <" .. m.subdir .. "/Api.h>")
    if m.reflect then
        p("#include <meta/" .. m.subdir .. "/Module.h>")
        p("#include <meta/" .. m.subdir .. "/Convert.h>")
    end
    p("")
    
    f:close()
end

function mud_bootstrap(modules)
    for _, m in ipairs(modules) do
        mud_write_api(m)
        mud_write_mxx(m)
    end
end

function mud_reflect(modules)
    local current = {}
    includedirs = function(dirs)
        for _, dir in ipairs(dirs) do
            if not table.contains(current.includedirs, dir) then
                --print("includedir " .. dir)
                table.insert(current.includedirs, dir)
            end
        end
    end
    
    local temp_refl_path = path.join(BUILD_DIR, "refl")
    local jsons = {}
    for _, m in ipairs(modules) do
        if m.refl then
            --print('mud reflect ' .. m.idname)
            current = {
                namespace = iif(m.namespace, m.namespace, ''),
                name = m.name,
                dotname = m.dotname,
                idname = m.idname,
                root = m.root,
                subdir = m.subdir,
                path = m.path,
                basetypes = m.basetypes,
                aliases = m.aliases,
                dependencies = {},
                includedirs = {},
            }
            
            for i, dep in ipairs(m.deps or {}) do
                if dep.refl then
                    table.insert(current.dependencies, dep.idname)
                end
            end
            
            -- trick to collect the includes
            m.refl.decl(m.refl, true)
            
            local json_path = path.join(temp_refl_path, m.idname .. "_refl.json")
            local f, err = io.open(json_path, "wb")
            io.output(f)
            io.printf(json.encode(current))
            f:close()
            
            table.insert(jsons, json_path)
        end
    end
    
    os.execute(path.join(MUD_DIR, "src/refl/Metagen", "generator.py") .. " " .. table.concat(jsons, " "))
end

newaction {
    trigger     = "bootstrap",
    description = "Bootstrap c++ modules",
    execute     = function()
        mud_bootstrap(MODULES)
    end
}

newaction {
    trigger     = "reflect",
    description = "Generate reflection",
    execute     = function()
        mud_reflect(MODULES)
    end
}

newaction {
    trigger     = "amalgamate",
    description = "Generate amalgamation files",
    execute     = function()
        mud_amalgamate(MODULES)
    end
}

newoption {
    trigger = "cpp-modules",
    description = "Use C++ experimental modules",
}

newoption {
    trigger = "as-libs",
    description = "Generate separate mud libraries",
}

newoption {
    trigger = "webgl2",
    description = "Use WebGL 2.0",
}

newoption {
    trigger = "webshaderc",
    description = "Use shaderc compiler on web",
}

newoption {
    trigger = "sound",
    description = "Build mud library with Sound.",
}

--newoption {
--    trigger = "renderer",
--    --value = "toolset",
--    description = "UI renderer",
--    allowed = {
--        { "bgfx",   "bgfx UI renderer"      },
--        { "gl",     "OpenGL UI renderer"    },
--    },
--}

newoption {
    trigger = "renderer-bgfx",
    description = "Use bgfx UI renderer",
}

newoption {
    trigger = "renderer-gl",
    description = "Use ",
}

newoption {
    trigger = "context-native",
    description = "Use native context",
}

newoption {
    trigger = "context-glfw",
    description = "Use GLFW context",
}

newoption {
    trigger = "context-wasm",
    description = "Use html5 context",
}

newoption {
    trigger = "context-ogre",
    description = "Use Ogre context",
}

newoption {
    trigger = "vg-vg",
    description = "Use vg-renderer",
}

newoption {
    trigger = "vg-nanovg",
    description = "Use NanoVG",
}

dofile("toolchain.lua")

if _OPTIONS["cpp-modules"] then
    _OPTIONS["as-libs"] = ""
end

if not _OPTIONS["renderer-gl"] and not _OPTIONS["renderer-bgfx"] then
    _OPTIONS["renderer-bgfx"] = ""
end

if not _OPTIONS["context-native"] and not _OPTIONS["context-glfw"] and not _OPTIONS["context-ogre"] then
    if _OPTIONS["vs"] ~= "asmjs" then
        _OPTIONS["context-glfw"] = ""
    else
        _OPTIONS["context-wasm"] = ""
    end
end

if _OPTIONS["renderer-gl"] then
    _OPTIONS["vg-nanovg"] = ""
end

if not _OPTIONS["vg-vg"] and not _OPTIONS["vg-nanovg"] then
    _OPTIONS["vg-vg"] = ""
end

toolchain(BUILD_DIR)

flags {
    "Cpp14",
}

removeflags {
    "StaticRuntime",
    "NoFramePointer",
}

configuration { "Debug" }
    targetsuffix "_d"

    removeflags {
        --"NoExceptions",
    }

configuration { "Release" }
    targetsuffix ""
    
    removeflags {
        "Symbols",
    }

configuration {}

configuration { "asmjs", "Release" }
    --flags { "Optimize" }
    --flags { "OptimizeSize" }
    flags { "OptimizeSpeed" }

configuration { "asmjs", "Debug" }
    removeflags {
        --"NoExceptions",
    }
    
    buildoptions {
        --"-s SAFE_HEAP=1"
    }
    
    linkoptions {
        --"-s SAFE_HEAP=1",
    }


configuration { "linux-*" }
    buildoptions {
        "-fPIC",
    }

configuration { "*-gcc* or osx" }
    buildoptions {
        "-Wno-shadow",
        "-Wno-undef",
    }
        
configuration {}


MUD_NANOVG_DIR = path.join(MUD_3RDPARTY_DIR, "nanovg-layers")

function copyLib()
end

configuration { "windows"}
    libdirs {
        "C:/Program Files (x86)/GLEW/lib/Release/Win32",
        "C:/Program Files/GLEW/lib/Release/Win32",
    }
    
    includedirs {
        "C:/Program Files (x86)/GLEW/include",
        "C:/Program Files/GLEW/include",
    }
    
configuration {} 
