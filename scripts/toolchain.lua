-- two toolchain

TWO_STATIC = true
FORCE_REFL_PROJECTS = false
NO_REFL = false

MODULES = {}

BASE_DIR = path.getabsolute("../..")

if not TWO_DIR then
    TWO_DIR = path.getabsolute("..")
end
TWO_SRC_DIR  = path.join(TWO_DIR, "src")
TWO_DIST_DIR = path.join(TWO_DIR, "dist")

TWO_3RDPARTY_DIR = path.join(TWO_DIR, "3rdparty")

BX_DIR   = path.join(BASE_DIR, "bx")
BGFX_DIR = path.join(BASE_DIR, "bgfx")
BIMG_DIR = path.join(BASE_DIR, "bimg")

DAWN_DIR = path.join(BASE_DIR, "dawn")

json = dofile(path.join(TWO_3RDPARTY_DIR, "jsonlua/json.lua"))

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
