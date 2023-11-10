-- two library
-- zeromq 3rdparty module

function uses_zeromq()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "libzmq", "include"),
        path.join(TWO_3RDPARTY_DIR, "cppzmq"),
    }
    
	removeflags {
		"NoExceptions",
	}

    configuration { "linux or osx or wasm*" }
        links {
            "pthread",
        }

    configuration { "vs*" }
        links {
            "ws2_32",
            "rpcrt4",
            "iphlpapi",
        }
        
    configuration {}
end

zeromq = dep(nil, "zeromq", true, uses_zeromq)
    kind "StaticLib"
    
    defines {
        "ZMQ_STATIC",
    }

	removeflags {
		"NoExceptions",
	}

	removedefines {
		"__STDC_LIMIT_MACROS",
    }
    
    includedirs {
        path.join(TWO_SRC_DIR),
        path.join(TWO_DIR, "scripts", "3rdparty", "zeromq"),
        path.join(TWO_3RDPARTY_DIR, "libzmq"),
    }
    
    files {
        path.join(TWO_3RDPARTY_DIR, "libzmq", "include", "**.h"),
        path.join(TWO_3RDPARTY_DIR, "libzmq", "src", "**.hpp"),
        path.join(TWO_3RDPARTY_DIR, "libzmq", "src", "**.cpp"),
    }

    removefiles {
        path.join(TWO_3RDPARTY_DIR, "libzmq", "src", "wss_engine.hpp"),
        path.join(TWO_3RDPARTY_DIR, "libzmq", "src", "wss_engine.cpp"),
        path.join(TWO_3RDPARTY_DIR, "libzmq", "src", "ws_engine.cpp"),
        path.join(TWO_3RDPARTY_DIR, "libzmq", "src", "ws_address.cpp"),
        path.join(TWO_3RDPARTY_DIR, "libzmq", "src", "ws_connecter.cpp"),
    }

    configuration { "linux or wasm*" }
        defines {
            "ZMQ_IOTHREAD_POLLER_USE_EPOLL",
            "ZMQ_POLL_BASED_ON_POLL",
            "ZMQ_USE_EPOLL",
            "HAVE_POSIX_MEMALIGN",
            "ZMQ_HAVE_EVENTFD",
            "ZMQ_HAVE_IFADDRS",
            "ZMQ_HAVE_SOCK_CLOEXEC",
            "ZMQ_HAVE_SO_BINDTODEVICE",
            "ZMQ_HAVE_SO_KEEPALIVE",
            "ZMQ_HAVE_SO_PEERCRED",
            "ZMQ_HAVE_TCP_KEEPCNT",
            "ZMQ_HAVE_TCP_KEEPIDLE",
            "ZMQ_HAVE_TCP_KEEPINTVL",
            "ZMQ_HAVE_UIO",
            "HAVE_CLOCK_GETTIME",
            "HAVE_FORK",
            "HAVE_ACCEPT4",
        }

        defines {
            "ZMQ_CACHELINE_SIZE=64",
        }

        links {
            "pthread",
        }

    configuration { "osx" }
        defines {
            "ZMQ_IOTHREAD_POLLER_USE_KQUEUE",
            "ZMQ_POLL_BASED_ON_POLL",
            "ZMQ_USE_KQUEUE",
            "HAVE_POSIX_MEMALIGN",
            "ZMQ_HAVE_IFADDRS",
            "ZMQ_HAVE_SO_KEEPALIVE",
            "ZMQ_HAVE_TCP_KEEPALIVE",
            "ZMQ_HAVE_TCP_KEEPCNT",
            "ZMQ_HAVE_TCP_KEEPINTVL",
            "ZMQ_HAVE_UIO",
            "HAVE_FORK",
        }

        defines {
            "ZMQ_CACHELINE_SIZE=64",
        }

        links {
            "pthread",
        }

    configuration { "vs*" }
        defines {
            "ZMQ_HAVE_WINDOWS",
            "ZMQ_IOTHREAD_POLLER_USE_SELECT",
            "ZMQ_POLL_BASED_ON_SELECT",
        }

        links {
            "ws2_32",
            "rpcrt4",
            "iphlpapi",
        }

        buildoptions {
            "/wd4005", -- warning C4204: 'xxx': macro redefinition
            "/wd4100", -- warning C4100: 'xxx': unreferenced formal parameter
            "/wd4245", -- warning C4245: 'return': conversion from 'xxx' to 'yyy', signed/unsigned mismatch
            "/wd4244", -- warning C4244: '+=': conversion from 'xxx' to 'yyy', possible loss of data
            "/wd4701", -- warning C4701: potentially uninitialized local variable 'xxx' used
        }
        
    configuration {}
