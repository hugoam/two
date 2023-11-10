-- two toolchain
-- options

newoption {
    trigger = "cpp-modules",
    description = "Use C++ experimental modules",
}

newoption {
    trigger = "use-stl",
    description = "Use STL containers",
}

newoption {
    trigger = "compile-only",
    description = "Compile library code only",
}

newoption {
    trigger = "as-libs",
    description = "Generate separate two libraries",
}

newoption {
    trigger = "unity",
    description = "Unity build (use amalgamated)",
}

newoption {
    trigger = "webgpu",
    description = "Experimental WebGPU (dawn) renderer",
}

newoption {
    trigger = "culling",
    description = "Enable Occlusion Culling",
}

newoption {
    trigger = "webshaderc",
    description = "Use shaderc compiler on web",
}

newoption {
    trigger = "sound",
    description = "Build two library with Sound",
}

newoption {
    trigger = "profile",
    description = "Integrated profiling",
}

newoption {
    trigger = "jsbind",
    description = "Use JS bindings",
}

newoption {
    trigger = "tools",
    description = "Build tools",
}

newoption {
    trigger = "webcompile",
    description = "Create dummy projects for webcompile",
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

newoption {
    trigger = "with-webgpu",
    description = "Experimental WebGPU (dawn) renderer",
}

function default_options()
    _OPTIONS["with-windows"] = "10.0"

    if _OPTIONS["cpp-modules"] then
        _OPTIONS["as-libs"] = ""
    end

    if not _OPTIONS["renderer-gl"] and not _OPTIONS["renderer-bgfx"] then
        _OPTIONS["renderer-bgfx"] = ""
    end

    if not _OPTIONS["context-native"] and not _OPTIONS["context-glfw"] and not _OPTIONS["context-ogre"] then
        if _OPTIONS["vs"] ~= "wasm" and _OPTIONS["gcc"] ~= "wasm" then
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
    
    NO_SHARED_LIBS = false
    if _OPTIONS["vs"] == "wasm" or _OPTIONS["gcc"] == "wasm" then
        NO_SHARED_LIBS = true
    end
end
