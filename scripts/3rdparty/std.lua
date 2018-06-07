-- mud library
-- std module

function std_module(name)
project("std_" .. name)
    cxxmodule("std." .. name)
    kind "StaticLib"
    
    includedirs {
        path.join(MUD_SRC_DIR),
        path.join(MUD_SRC_DIR, "3rdparty"),
    }
    
    files {
        path.join(MUD_SRC_DIR, "3rdparty/std", "**.h"),
        path.join(MUD_SRC_DIR, "3rdparty/std", "std.cpp"),
        path.join(MUD_SRC_DIR, "3rdparty/std", "std." .. name  .. ".mxx"),
    }
    
    return mud_dep("std", name, true)
end

std = {}
std.core      = std_module("core")
std.io        = std_module("io")
std.regex     = std_module("regex")
std.threading = std_module("threading")
