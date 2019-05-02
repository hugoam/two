-- two library

solution "two"
	configurations {
		"Debug",
		"Release",
	}

	platforms {
		"x32",
		"x64"
	}

	language "C++"
    
    
PROJECT_DIR = path.getabsolute("..")
BUILD_DIR = path.join(path.getabsolute(".."), "build")

dofile "toolchain.lua"

dofile "two.lua"
dofile "two_example.lua"