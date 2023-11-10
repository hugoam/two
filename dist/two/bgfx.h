#pragma once

#include <two/ctx.wasm.h>
#include <two/ctx.glfw.h>
#include <two/ctx.win.h>
#include <two/math.h>
#include <two/ctx.h>
#include <two/infra.h>
#include <two/type.h>




#ifndef TWO_BGFX_EXPORT
#define TWO_BGFX_EXPORT TWO_IMPORT
#endif

namespace two
{
    class BgfxContext;
    class BgfxSystem;
}


#include <stl/vector.h>

#ifndef TWO_MODULES
	#if defined TWO_CONTEXT_GLFW
	#elif defined TWO_CONTEXT_WASM
	#elif defined TWO_CONTEXT_WINDOWS
	#else
	#endif
#endif

namespace bx
{
	struct AllocatorI;
}

namespace two
{
	class BgfxSystem;

#if defined TWO_CONTEXT_GLFW
	export_ class TWO_BGFX_EXPORT BgfxContext : public GlfwContext
#elif defined TWO_CONTEXT_WASM
	export_ class TWO_BGFX_EXPORT BgfxContext : public EmContext
#elif defined TWO_CONTEXT_WINDOWS
	export_ class TWO_BGFX_EXPORT BgfxContext : public WinContext
#else
	export_ class TWO_BGFX_EXPORT BgfxContext : public Context
#endif
	{
	public:
		BgfxContext(BgfxSystem& gfx, const string& name, const uvec2& size, bool fullscreen, bool main, bool init = true);

		virtual void render_frame() override;

		virtual void reset_fb(const uvec2& size) override;
	};

	export_ struct TWO_BGFX_EXPORT TimerBx
	{
		int64_t m_start = 0;

		void begin();
		float end();
	};

	export_ class refl_ TWO_BGFX_EXPORT BgfxSystem : public RenderSystem
	{
	public:
		BgfxSystem(const string& resource_path);
		~BgfxSystem();

		virtual bool begin_frame() override;
		virtual void end_frame() override;

		void init(BgfxContext& context);
		void advance();

		bx::AllocatorI& allocator();

	public:
		bool m_initialized = false;

		attr_ uint32_t m_frame = 1;
		double m_start_counter = 0.0;

		attr_ float m_time = 0.f;
		attr_ float m_frame_time = 0.f;
		attr_ float m_delta_time = 0.f;

		bool m_capture = false;
		size_t m_capture_every = 0;
	};
}


#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_MODULES
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_BGFX_EXPORT Type& type<two::BgfxSystem>();
}
