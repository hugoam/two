-- mud toolchain

MUD_STATIC = true
FORCE_REFL_PROJECTS = false

MODULES = {}

if not MUD_DIR then
    MUD_DIR = path.getabsolute("..")
end
MUD_SRC_DIR  = path.join(MUD_DIR, "src")
MUD_DIST_DIR = path.join(MUD_DIR, "dist")

MUD_3RDPARTY_DIR = path.join(MUD_DIR, "3rdparty")

BX_DIR   = path.join(MUD_3RDPARTY_DIR, "bx")
BGFX_DIR = path.join(MUD_3RDPARTY_DIR, "bgfx")
BIMG_DIR = path.join(MUD_3RDPARTY_DIR, "bimg")

json = dofile(path.join(MUD_3RDPARTY_DIR, "jsonlua/json.lua"))

dofile("toolchain/table.lua")
dofile("toolchain/defines.lua")

dofile("toolchain/cpp20.lua")
dofile("toolchain/module.lua")

dofile("toolchain/actions.lua")
dofile("toolchain/options.lua")

dofile("toolchain/toolchain.lua")

default_options()

toolchain(BUILD_DIR)

dofile("toolchain/global.lua")
