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
        flags {
            "CppLatest",
        }
        
        defines { "_CRT_NO_VA_START_VALIDATION" }
        
        defines {
            "MUD_NO_GLM",
            "MUD_CPP_20",
        }
        
    configuration { "cpp-modules", "*-clang*" }
        buildoptions {
            "-fmodules-ts",
        }
        
        defines {
            "MUD_MODULES",
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

function mud_module(as_project, root, name, root_path, subpath, deps)
    if as_project then 
        project(root .. "_" .. name)
        cxxmodule(root .. "." .. name)
        kind "SharedLib"
    
        if deps then
            for _, depname in ipairs(deps) do
                links(root .. "_" .. depname)
                uses(root .. "_" .. depname)
                --links { root .. "_" .. depname }
            end
        end
    end
    
    local module_path = path.join(root_path, subpath)
    local clean_name = string.gsub(name, "-", "_")
    local preproc_name = root:upper() .. "_" .. clean_name:upper()
    
    includedirs {
        root_path,
    }
    
    files {
        path.join(module_path, "**.h"),
        path.join(module_path, "**.cpp"),
    }
    
    defines { preproc_name .. "_REFLECT" }
    defines { preproc_name .. "_LIB" }
    
    --vpaths { [name] = { "**.h", "**.cpp" } }
        
    if file_exists(path.join(module_path, "module.py")) then
        local module = {
            root = root_path,
            path = module_path,
            py = path.join(module_path, "module.py")
        }
        table.insert(MODULES, module)
        table.insert(MODULES_PY, path.join(module_path, "module.py"))
    end
    
    mud_defines()
    
    configuration { "cpp-modules" }
        defines { preproc_name .. "_EXPORT=" }
    
    configuration { "cpp-modules", "vs*" }
        files {
            path.join(module_path, "Generated/Module.ixx"),
        }
            
    configuration { "cpp-modules", "*-clang*" }
        files {
            path.join(module_path, "Generated/" .. root .. "." .. name .. ".cppm"),
        }
        
        links {
            "std_core",
            "std_io",
            "std_threading",
            "std_regex",
        }
        
    configuration {}
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
