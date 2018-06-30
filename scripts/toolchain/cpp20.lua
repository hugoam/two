-- mud toolchain
-- cpp20 modules

function mud_modules(m)
    if not _OPTIONS["cpp-modules"] then
        return
    end
    
    removeflags { "Cpp14" }
    flags {
        "CppLatest",
        "CppModules",
    }
    
    defines { "_CRT_NO_VA_START_VALIDATION" }

    configuration { "*-clang*" }
        links {
            "std_core",
            "std_io",
            "std_threading",
            "std_regex",
        }
        
    configuration { "vs*" }
        files {
            --path.join(m.path, m.dotname .. ".ixx"),
        }
            
    configuration { "*-clang*" }
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
