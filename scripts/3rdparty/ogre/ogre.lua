-- toy engine
-- ogre library

os.mkdir(path.join(BUILD_DIR, "ogre"))
os.copyfile(path.join(TOY_DIR, "scripts/OgreBuildSettings.h"), path.join(BUILD_DIR, "ogre/OgreBuildSettings.h"))

project "OgreMain"
	kind "SharedLib"
        
    removeflags {
        "NoPCH",
        "NoRTTI",
        "NoExceptions",
    }
    
	includedirs {
        path.join(BUILD_DIR, "ogre"),
        path.join(OGRE_DIR, "OgreMain", "include"),
        path.join(OGRE_DIR, "OgreMain", "src/nedmalloc"),
        path.join(BUILD_DIR, "zlib"),
        path.join(TOY_3RDPARTY_DIR, "zlib"),
        path.join(TOY_3RDPARTY_DIR, "rapidjson/include"),
	}

	files {
        path.join(OGRE_DIR, "OgreMain", "include",                       "*.h"),
        path.join(OGRE_DIR, "OgreMain", "include", "Animation",          "**.h"),
        path.join(OGRE_DIR, "OgreMain", "include", "CommandBuffer",      "**.h"),
        path.join(OGRE_DIR, "OgreMain", "include", "Compositor",         "**.h"),
        path.join(OGRE_DIR, "OgreMain", "include", "Hash",               "**.h"),
        path.join(OGRE_DIR, "OgreMain", "include", "Math", "Simple",     "**.h"),
        path.join(OGRE_DIR, "OgreMain", "include", "Math", "Array",      "*.h"),
        path.join(OGRE_DIR, "OgreMain", "include", "Math", "Array", "C", "**.h"),
        path.join(OGRE_DIR, "OgreMain", "include", "Vao",                "**.h"),
        path.join(OGRE_DIR, "OgreMain", "src",                           "*.cpp"),
        path.join(OGRE_DIR, "OgreMain", "src",     "Animation",          "**.cpp"),
        path.join(OGRE_DIR, "OgreMain", "src",     "CommandBuffer",      "**.cpp"),
        path.join(OGRE_DIR, "OgreMain", "src",     "Compositor",         "**.cpp"),
        path.join(OGRE_DIR, "OgreMain", "src",     "Hash",               "**.cpp"),
        path.join(OGRE_DIR, "OgreMain", "src",     "Math", "Simple",     "**.cpp"),
        path.join(OGRE_DIR, "OgreMain", "src",     "Math", "Array",      "*.cpp"),
        path.join(OGRE_DIR, "OgreMain", "src",     "Math", "Array", "SSE2", "Single", "*.cpp"), -- if OGRE_USE_SIMD
        --path.join(OGRE_DIR, "OgreMain", "src",     "Math", "Array", "C", "**.cpp"),
        path.join(OGRE_DIR, "OgreMain", "src",     "Vao",                "**.cpp"),
		path.join(OGRE_DIR, "OgreMain", "include", "Threading",          "OgreThreadDefinesSTD.h"),
		path.join(OGRE_DIR, "OgreMain", "include", "Threading",          "OgreThreadHeadersSTD.h"),
		path.join(OGRE_DIR, "OgreMain", "include", "Threading",          "OgreDefaultWorkQueueStandard.h"),
		path.join(OGRE_DIR, "OgreMain", "src",     "Threading",          "OgreDefaultWorkQueueStandard.cpp"),
	}
    
    pchheader("OgreStableHeaders.h")
    pchsource(path.join(OGRE_DIR, "OgreMain/src/OgrePrecompiledHeaders.cpp"))
    
    removefiles {
        path.join(OGRE_DIR, "OgreMain/include/OgreFreeImageCodec.h"), 
        path.join(OGRE_DIR, "OgreMain/src/OgreFreeImageCodec.cpp"), 
        path.join(OGRE_DIR, "OgreMain/include/OgreDDSCodec.h"), 
        path.join(OGRE_DIR, "OgreMain/src/OgreDDSCodec.cpp"), 
        path.join(OGRE_DIR, "OgreMain/include/OgrePVRTCCodec.h"), 
        path.join(OGRE_DIR, "OgreMain/src/OgrePVRTCCodec.cpp"), 
        path.join(OGRE_DIR, "OgreMain/include/OgreETCCodec.h"), 
        path.join(OGRE_DIR, "OgreMain/src/OgreETCCodec.cpp"), 
        path.join(OGRE_DIR, "OgreMain/include/OgreZip.h"),
        path.join(OGRE_DIR, "OgreMain/src/OgreZip.cpp"),
        path.join(OGRE_DIR, "OgreMain/include/OgreAPKZipArchive.h"),
        path.join(OGRE_DIR, "OgreMain/src/OgreAPKZipArchive.cpp"),
        path.join(OGRE_DIR, "OgreMain/include/OgreSearchOps.h"),
        path.join(OGRE_DIR, "OgreMain/src/OgreSearchOps.cpp"),
    }
    
    defines {
        "OGRE_NONCLIENT_BUILD",
        "OGRE_NO_ZIP_ARCHIVE=1",
        "OGRE_NO_MESHLOD=1",
        "OGRE_NO_FREEIMAGE=1",
        "OGRE_NO_JSON=1",
        "OGRE_NO_DDS_CODEC=1",
        "OGRE_NO_PVRTC_CODEC=1",
        "OGRE_NO_ETC_CODEC=1",
        "OGRE_NO_ZIP_ARCHIVE=1",
        "OGRE_NO_VIEWPORT_ORIENTATIONMODE=1",
        "OGRE_NO_GLES2_CG_SUPPORT=1",
        "OGRE_NO_GLES2_GLSL_OPTIMISER=1",
        "OGRE_NO_GLES2_VAO_SUPPORT=1",
        "OGRE_NO_GL_STATE_CACHE_SUPPORT=1",
        "OGRE_NO_GLES3_SUPPORT=1",
        "OGRE_NO_TBB_SCHEDULER=1",
        "_MT",
        "_USRDLL",
    }
    
    configuration { "windows" }
        files {
            path.join(OGRE_DIR, "OgreMain", "include", "WIN32",     "**.h"),
            path.join(OGRE_DIR, "OgreMain", "src",     "WIN32",     "**.cpp"),
            path.join(OGRE_DIR, "OgreMain", "src",     "Threading", "OgreThreadsWin.cpp"),
            path.join(OGRE_DIR, "OgreMain", "src",     "Threading", "OgreBarrierWin.cpp"),
            path.join(OGRE_DIR, "OgreMain", "src",     "Threading", "OgreLightweightMutexWin.cpp"),
        }

        removefiles {
            path.join(OGRE_DIR, "OgreMain", "src",     "WIN32",     "OgreConfigDialogWinRT.cpp"),
            path.join(OGRE_DIR, "OgreMain", "src",     "WIN32",     "OgreErrorDialogWinRT.cpp"),
            path.join(OGRE_DIR, "OgreMain", "src",     "WIN32",     "OgreMinGWSupport.cpp"),
        }
        
    configuration { "unix" }
        files {
            path.join(OGRE_DIR, "OgreMain", "include", "GLX",     "**.h"),
            path.join(OGRE_DIR, "OgreMain", "src",     "GLX",     "**.cpp"),
            path.join(OGRE_DIR, "OgreMain", "src",     "Threading", "OgreThreadsPThreads.cpp"),
            path.join(OGRE_DIR, "OgreMain", "src",     "Threading", "OgreBarrierPThreads.cpp"),
            path.join(OGRE_DIR, "OgreMain", "src",     "Threading", "OgreLightweightMutexPThreads.cpp"),
        }
        
	configuration {}
    
    
project "OgreHlmsUnlit"
	kind "SharedLib"
    
    removeflags {
        "NoRTTI",
        "NoExceptions",
    }
    
    includedirs {
        path.join(BUILD_DIR, "ogre"),
        path.join(OGRE_DIR, "OgreMain", "include"),
        path.join(OGRE_DIR, "Components/Hlms/Common", "include"),
        path.join(OGRE_DIR, "Components/Hlms/Unlit",  "include"),
    }
    
    files {
        path.join(OGRE_DIR, "Components/Hlms/Common", "include",  "**.h"),
        path.join(OGRE_DIR, "Components/Hlms/Unlit",  "include",  "**.h"),
        path.join(OGRE_DIR, "Components/Hlms/Common", "src",      "**.cpp"),
        path.join(OGRE_DIR, "Components/Hlms/Unlit",  "src",      "**.cpp"),
    }
    
    defines {
        "OgreHlmsUnlit_EXPORTS",
    }
    
    links {
        "OgreMain",
    }

project "OgreHlmsPbs"
	kind "SharedLib"

    removeflags {
        "NoRTTI",
        "NoExceptions",
    }
    
    includedirs {
        path.join(BUILD_DIR, "ogre"),
        path.join(OGRE_DIR, "OgreMain", "include"),
        path.join(OGRE_DIR, "Components/Hlms/Common", "include"),
        path.join(OGRE_DIR, "Components/Hlms/Pbs",    "include"),
    }
    
    files {
        path.join(OGRE_DIR, "Components/Hlms/Common", "include",  "**.h"),
        path.join(OGRE_DIR, "Components/Hlms/Pbs",    "include",  "**.h"),
        path.join(OGRE_DIR, "Components/Hlms/Common", "src",      "**.cpp"),
        path.join(OGRE_DIR, "Components/Hlms/Pbs",    "src",      "**.cpp"),
    }

    defines {
        "OgreHlmsPbs_EXPORTS",
    }
    
    links {
        "OgreMain",
    }
    
project "RenderSystem_GL3Plus"
	kind "SharedLib"

    removeflags {
        "NoRTTI",
        "NoExceptions",
    }
    
	includedirs {
        path.join(BUILD_DIR, "ogre"),
        path.join(OGRE_DIR, "OgreMain", "include"),
        path.join(OGRE_DIR, "OgreMain", "src/nedmalloc"),
        path.join(OGRE_DIR, "RenderSystems/GL3Plus", "include"),
        path.join(OGRE_DIR, "RenderSystems/GL3Plus", "include/GLSL"),
	}

	files {
        path.join(OGRE_DIR, "RenderSystems/GL3Plus", "include",         "*.h"),
        path.join(OGRE_DIR, "RenderSystems/GL3Plus", "include", "Vao",  "*.h"),
        path.join(OGRE_DIR, "RenderSystems/GL3Plus", "include", "GLSL", "*.h"),
        path.join(OGRE_DIR, "RenderSystems/GL3Plus", "src",             "*.cpp"),
        path.join(OGRE_DIR, "RenderSystems/GL3Plus", "src",     "Vao",  "*.cpp"),
        path.join(OGRE_DIR, "RenderSystems/GL3Plus", "src",     "GLSL", "*.cpp"),
	}
 
    defines {
        "RenderSystem_GL3Plus_EXPORTS",
    }
    
    links {
        "OgreMain",
        "OpenGL32",
	}
    
    configuration { "windows" }
        includedirs {
            path.join(OGRE_DIR, "RenderSystems/GL3Plus", "include", "windowing/win32"),
            path.join(OGRE_DIR, "RenderSystems/GL3Plus", "src",     "windowing/win32"),
        }
    
        files {
            path.join(OGRE_DIR, "RenderSystems/GL3Plus", "include", "windowing/win32/*.h"),
            path.join(OGRE_DIR, "RenderSystems/GL3Plus", "src",     "windowing/win32/*.cpp"),
        }
    configuration { "apple" }
        files {
            path.join(OGRE_DIR, "RenderSystems/GL3Plus", "include", "windowing/OSX/*.h"),
            path.join(OGRE_DIR, "RenderSystems/GL3Plus", "src",     "windowing/OSX/*.mm"),
        }
    configuration { "unix" }
        files {
            path.join(OGRE_DIR, "RenderSystems/GL3Plus", "include", "windowing/GLX/*.h"),
            path.join(OGRE_DIR, "RenderSystems/GL3Plus", "src",     "windowing/GLX/*.cpp"),
        }

	configuration {}

