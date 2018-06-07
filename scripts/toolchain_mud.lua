-- mud toolchain

function file_exists(name)
    local f = io.open(name, "r")
    if f ~= nil then
        io.close(f)
        return true
    else
        return false
    end
end

function mud_defines()
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

function mud_modules()
    configuration { "cpp-modules" }
        removeflags { "Cpp14" }
        flags {
            "CppLatest",
            "CppModules",
        }
        
        defines { "_CRT_NO_VA_START_VALIDATION" }

    configuration {}
end

function mud_mxx(cpps, m)
    local cxxmodules = {}

    for _, cpp in ipairs(cpps) do
        local relcpp = path.getrelative(MUD_DIR, cpp)
        print("module for " .. relcpp .. " = " .. m.dotname)
        cxxmodules[relcpp] = m.dotname
    end

    cxxmodule(cxxmodules)
end

function mud_dep(namespace, name, cppmodule)
    local m = {
        project = nil,
        cppmodule = cppmodule,
        namespace = namespace,
        name = name,
        dotname = string.gsub(name, "-", "."),
        idname = string.gsub(name, "-", "_"),
    }
    
    if namespace then
        m.dotname = namespace .. "." .. m.dotname
        m.idname = namespace .. "_" .. m.idname
    end
    
    m.project = project(m.idname)
    m.lib = project().name
    
    mud_defines()
    if cppmodule then
        mud_modules()
    end
    
    return m
end

function mud_module(as_project, namespace, name, root_path, subpath, deps, nomodule)
    local m = {
        project = nil,
        cppmodule = true,
        reflect = false,
        namespace = namespace,
        name = name,
        dotname = string.gsub(name, "-", "."),
        idname = string.gsub(name, "-", "_"),
        root = root_path,
        subdir = subpath,
        path = path.join(root_path, subpath),
        deps = deps,
    }
    
    if namespace then
        m.dotname = namespace .. "." .. m.dotname
        m.idname = namespace .. "_" .. m.idname
    end
    
    m.reflect = file_exists(path.join(m.path, "module.py"))
    
    if as_project then
        m.project = project(m.idname)
        kind "SharedLib"
        
        defines { m.idname:upper() .. "_LIB" }
    end

    m.lib = project().name
    
    for _, dep in ipairs(deps or {}) do
        if dep.lib ~= m.lib then
            links(dep.lib)
            print (m.lib .. " links " .. dep.lib)
            --uses(dep.idname)
        end
    end
    
    includedirs {
        root_path,
    }
    
    files {
        path.join(m.path, "**.h"),
        path.join(m.path, "**.cpp"),
    }
    
    local cpps = os.matchfiles(path.join(m.path, "**.cpp"))
    mud_mxx(cpps, m)

    defines { m.idname:upper() .. "_REFLECT" }
    defines { m.idname:upper() .. "_EXPORT=MUD_EXPORT" }
    
    --vpaths { [name] = { "**.h", "**.cpp" } }
    
    mud_defines()
    mud_modules()
    
    if m.reflect then
        table.insert(MODULES_PY, path.join(m.path, "module.py"))
    end
    
    if not nomodule then
        table.insert(MODULES, m)
        
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
    
    configuration { "cpp-modules", "*-clang*" }
        links {
            "std_core",
            "std_io",
            "std_threading",
            "std_regex",
        }
        
    configuration {}
    
    return m
end

function mud_amalgamate(modules)
    for _, m in ipairs(modules) do
        local dir = os.getcwd()
        os.chdir(m.root)
        os.execute(path.join(MUD_DIR, "3rdparty/amalgamate/amalgamate.py") .. " -c " .. m.path .. "/Generated/amalgam.h.json" .. " -s " .. MUD_SRC_DIR)
        os.execute(path.join(MUD_DIR, "3rdparty/amalgamate/amalgamate.py") .. " -c " .. m.path .. "/Generated/amalgam.cpp.json" .. " -s " .. MUD_SRC_DIR)
        os.chdir(dir)
    end
end

function mud_write_api(m)
    headers = os.matchfiles(path.join(m.path, "**.h"))
    --table.insert(headers, os.matchfiles(path.join(m.path, "**.hpp")))
    
    local f, err = io.open(path.join(m.path, "Api.h"), "wb")
    io.output(f)
    for _, h in ipairs(headers) do
        if not string.find(h, "Api.h") and not string.find(h, "Generated/") then
            io.printf("#include <" .. path.getrelative(m.root, h) .. ">")
        end
    end
    io.printf("")
    f:close()
end

function mud_write_mxx(m)
	local f, err = io.open(path.join(m.path, m.dotname .. ".mxx"), "wb")
    io.output(f)
        
    io.printf("#include <cpp/preimport.h>")
    io.printf("")
    io.printf("#include <obj/Config.h>")
    io.printf("")
    io.printf("export module " .. m.dotname .. ";")
    io.printf("export import std.core;")
    io.printf("export import std.io;")
    io.printf("export import std.threading;")
    io.printf("export import std.regex;")
    io.printf("")
    for _, dep in ipairs(m.deps or {}) do
        if dep.cppmodule then
            io.printf("export import " .. dep.dotname .. ";")
        end
    end
    io.printf("")
    io.printf("#include <" .. m.subdir .. "/Api.h>")
    if m.reflect then
        io.printf("#include <" .. m.subdir .. "/Generated/Types.h>")
        io.printf("#include <" .. m.subdir .. "/Generated/Module.h>")
        io.printf("#include <" .. m.subdir .. "/Generated/Convert.h>")
    end
    io.printf("")
    f:close()
end

function mud_bootstrap(modules)
    for _, m in ipairs(modules) do
        mud_write_api(m)
        mud_write_mxx(m)
    end
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
        os.execute(path.join(MUD_DIR, "src/obj/Metagen", "generator.py") .. " " .. table.concat(MODULES_PY, " "))
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

newoption {
    trigger = "renderer-bgfx",
    description = "Use bgfx UI renderer",
}

newoption {
    trigger = "renderer-gl",
    description = "Use OpenGL UI renderer",
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

MODULES = {}
MODULES_PY = {}

if not MUD_DIR then
    MUD_DIR = path.getabsolute("..")
end
MUD_SRC_DIR    = path.join(MUD_DIR, "src")

MUD_3RDPARTY_DIR = path.join(MUD_DIR, "3rdparty")

BX_DIR   = path.join(MUD_3RDPARTY_DIR, "bx")
BGFX_DIR = path.join(MUD_3RDPARTY_DIR, "bgfx")
BIMG_DIR = path.join(MUD_3RDPARTY_DIR, "bimg")

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
