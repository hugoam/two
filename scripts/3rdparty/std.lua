-- two library
-- std module

project("std")
    kind "StaticLib"

    removeflags { "Cpp17" }
    flags {
        "CppLatest",
        "CppModules",
    }

    includedirs {
        path.join(TWO_SRC_DIR),
        path.join(TWO_SRC_DIR, "3rdparty"),
    }

    cxxheaderunits {
        --"cmath",
        "initializer_list",
        "atomic",
        "memory",
        "tuple",
        "vector",
        "string",
        "set",
        "map",
        "unordered_set",
        "unordered_map",
        "algorithm",
        "random",
        "functional",
        "thread",
        "condition_variable",
        "mutex",
        "fstream",
        "iostream",
        "regex", -- @todo use re2
    }

    files {
        path.join(TWO_SRC_DIR, "3rdparty/std", "std.cxxm"),
    }

    cxxmodules {
        std = path.join(TWO_SRC_DIR, "3rdparty/std", "std.cxxm"),
    }

    buildoptions { "-Wno-pragma-system-header-outside-header" }

printf("std")
std = dep(nil, "std", false)
