-- mud library

solution "mud"
	configurations {
		"Debug",
		"Release",
	}

	platforms {
		"x32",
		"x64"
	}

	language "C++"
    
    
BUILD_DIR = path.join(path.getabsolute(".."), "build")

dofile "toolchain_mud.lua"

dofile "mud.lua"
