#pragma once

#include <mud/ctx.wasm.h>
#include <mud/ctx.glfw.h>
#include <mud/ctx.win.h>
#include <mud/math.h>
#include <mud/ctx.h>
#include <mud/infra.h>
#include <mud/type.h>





#ifndef MUD_BGFX_EXPORT
#define MUD_BGFX_EXPORT MUD_IMPORT
#endif

#ifndef MUD_MODULES
	#if defined MUD_CONTEXT_GLFW
	#elif defined MUD_CONTEXT_WASM
	#elif defined MUD_CONTEXT_WINDOWS
	#else
	#endif
#endif

#include <bx/allocator.h>

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	class BgfxSystem;

#if defined MUD_CONTEXT_GLFW
	export_ class MUD_BGFX_EXPORT BgfxContext : public GlfwContext
#elif defined MUD_CONTEXT_WASM
	export_ class MUD_BGFX_EXPORT BgfxContext : public EmContext
#elif defined MUD_CONTEXT_WINDOWS
	export_ class MUD_BGFX_EXPORT BgfxContext : public WinContext
#else
	export_ class MUD_BGFX_EXPORT BgfxContext : public Context
#endif
	{
	public:
		BgfxContext(BgfxSystem& gfx_system, const string& name, int width, int height, bool fullScreen, bool init);

		virtual void reset(uint16_t width, uint16_t height) override;
	};

	export_ struct MUD_BGFX_EXPORT TimerBx
	{
		int64_t m_start = 0;

		void begin();
		float end();
	};

	export_ class MUD_BGFX_EXPORT BgfxSystem : public NonCopy, public RenderSystem
	{
	public:
		BgfxSystem(const string& resource_path);
		~BgfxSystem();

		virtual void begin_frame() override;
		virtual bool next_frame() override;

		virtual object<Context> create_context(const string& name, int width, int height, bool fullScreen) override;
		
		void init(BgfxContext& context);
		void advance();

	public:
		bx::DefaultAllocator m_allocator;
		bool m_initialized = false;

		uint32_t m_frame = 1;
		double m_start_counter = 0.0;

		float m_time = 0.f;
		float m_frame_time = 0.f;
		float m_delta_time = 0.f;

		bool m_capture = false;
		size_t m_capture_every = 0;
	};
}





#ifndef MUD_BGFX_EXPORT
#define MUD_BGFX_EXPORT MUD_IMPORT
#endif

namespace mud
{
    class BgfxContext;
    class BgfxSystem;
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    
    
}
