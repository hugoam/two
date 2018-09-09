-- mud library
-- fiber 3rdparty module

local canary = ""
if FTL_CANARY_BYTES then
    canary = "canary_"
end

local arch_table = {
    x32 = "i386",
    x64 = "x86_64",
    ARM = "arm"
}

local os_table = {
    windows = "ms",
    linux = "sysv",
    osx = "sysv",
}

local abi_table = {
    windows = "pe",
    linux = "elf",
    osx = "macho",
}

local asm_table = {
    windows = "masm.asm",
    linux = "gas.S",
    osx = "gas.S",
}

fcontext = mud_dep(nil, "fcontext")
    kind "StaticLib"

    files {
        path.join(MUD_3RDPARTY_DIR, "fiber", "third_party", "boost_context", "include/**.h"),
        path.join(MUD_3RDPARTY_DIR, "fiber", "third_party", "boost_context", "src/**.cpp"),
    }
    
    for _, os in ipairs({ "windows", "linux", "osx" }) do
    for _, arch in ipairs({ "x32", "x64", "ARM" }) do
        --print("configuration { " .. os .. ", " .. arch .. " })")
        --print("files {")
        --print("    asm/jump_" .. canary .. arch_table[arch] .. "_" .. os_table[os] .. "_" .. abi_table[os] .. "_" .. asm_table[os])
        --print("    asm/make_" .. canary .. arch_table[arch] .. "_" .. os_table[os] .. "_" .. abi_table[os] .. "_" .. asm_table[os])
        --print("}")
        
        configuration { os, arch }
            files {
                path.join(MUD_3RDPARTY_DIR, "fiber", "third_party", "boost_context", "asm/jump_" .. canary .. arch_table[arch] .. "_" .. os_table[os] .. "_" .. abi_table[os] .. "_" .. asm_table[os]),
                path.join(MUD_3RDPARTY_DIR, "fiber", "third_party", "boost_context", "asm/make_" .. canary .. arch_table[arch] .. "_" .. os_table[os] .. "_" .. abi_table[os] .. "_" .. asm_table[os]),
            }
    end
    end
    
    configuration { "windows", "x32" }
        buildoptions {
            "/safeseh"
        }
        
    configuration {}

function uses_ftl()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "fiber", "include"),
        path.join(MUD_3RDPARTY_DIR, "fiber", "third_party", "boost_context", "include"),
    }
end

ftl = mud_dep(nil, "ftl", false, uses_ftl)
    kind "StaticLib"
    
    includedirs {
        path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "fiber", "include"),
        path.join(MUD_3RDPARTY_DIR, "fiber", "source"),
        path.join(MUD_3RDPARTY_DIR, "fiber", "third_party", "boost_context", "include"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "fiber",  "include/**.h"),
        path.join(MUD_3RDPARTY_DIR, "fiber",  "source/**.cpp"),
    }
    
    defines {
        --"FTL_VALGRIND=1",
        --"FTL_FIBER_STACK_GUARD_PAGES=1",
    }
    
    links {
        "fcontext",
    }
