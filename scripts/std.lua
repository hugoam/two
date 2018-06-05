-- mud library
-- std module

function std_module(name)
project("std_" .. name)
    cxxmodule("std." .. name)
    kind "StaticLib"
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "std"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "std", "**.h"),
        path.join(MUD_3RDPARTY_DIR, "std", "std.cpp"),
        path.join(MUD_3RDPARTY_DIR, "std", "std." .. name  .. ".cppm"),
    }
    
    mud_defines()
end

std_module("core")
std_module("io")
std_module("regex")
std_module("threading")
