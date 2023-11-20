-- two toolchain
-- cpp20 modules

if not cxxmodules then
    cxxmodules = function(m)
    end
end

function modules(m)
    if not _OPTIONS["cpp-modules"] then
        return
    end
    
    removeflags { "Cpp17" }
    flags {
        "CppLatest",
        "CppModules",
    }

    defines { "_CRT_NO_VA_START_VALIDATION" }

    if _ACTION == "vs2017"
	or _ACTION == "vs2019"
	or _ACTION == "vs2022" then
        if not m.nomodule then
            files {
            --path.join(m.path, m.dotname .. ".ixx"),
                path.join(m.path, m.dotname2 .. ".ixx"),
            }

            buildoptions {
                "/wd5244",
            }
        end
    else
        if not m.nomodule then
            local cxxmodule = path.join(m.path, m.dotname2 .. ".cxxm")
            files { cxxmodule }
            local modules = {}
            modules[m.dotname] = cxxmodule
            cxxmodules(modules)

            --cxxmodules {
            --    path.join(m.path, m.dotname2 .. ".cxxm"),
            --}

            buildoptions {
                "-Wno-include-angled-in-module-purview",
                "-Wno-experimental-header-units",
            }
        end

        links { "std" }
    end
end
