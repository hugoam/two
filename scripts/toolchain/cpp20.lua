-- two toolchain
-- cpp20 modules

function modules(m)
    removeflags { "Cpp20" }
    flags {
        "CppLatest",
        --"CppModules",
    }

    defines { "_CRT_NO_VA_START_VALIDATION" }

    if _ACTION == "vs2026" then
        if m.cppmodule then
            files {
            --path.join(m.path, m.dotname .. ".ixx"),
                path.join(m.path, m.dotname2 .. ".ixx"),
            }

            buildoptions {
                "/wd5244",
            }
        end
    else
        if m.cppmodule then
            files {
                path.join(m.path, m.dotname2 .. ".cppm"),
            }

            configuration { "*-clang*" }
                buildoptions {
                    -- the module headers are included in the module purview
                    "-Wno-include-angled-in-module-purview",
                }
            configuration {}
        end

        links { "std" }
    end
end
