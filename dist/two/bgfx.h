#pragma once

#include <two/infra.h>
#include <two/type.h>



#ifndef TWO_BGFX_EXPORT
#define TWO_BGFX_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ class BgfxContext;
    export_ class BgfxSystem;
}



namespace two
{
	export_ class BgfxSystem;

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



#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_BGFX_EXPORT Type& type<two::BgfxSystem>();
}
