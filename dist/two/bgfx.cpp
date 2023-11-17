#include <two/gfx.h>
#include <two/infra.h>

module;
module two.bgfx;

namespace two
{
    // Exported types
    
    
    template <> TWO_BGFX_EXPORT Type& type<two::BgfxSystem>() { static Type ty("BgfxSystem", type<two::RenderSystem>(), sizeof(two::BgfxSystem)); return ty; }
}

module;
#include <cassert>
#include <cstdio>
#include <bx/allocator.h>
#include <bx/timer.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
module two.bgfx;

namespace two
{
	BgfxContext::BgfxContext(BgfxSystem& gfx, const string& name, const uvec2& size, bool fullscreen, bool main, bool init)
#if defined TWO_CONTEXT_GLFW
		: GlfwContext(gfx, name, size, fullscreen, main, false)
#elif defined TWO_CONTEXT_WASM
		: EmContext(gfx, name, size, fullscreen, main)
#elif defined TWO_CONTEXT_WINDOWS
		: WinContext(gfx, name, size, fullscreen, main)
#endif
	{
		if(main && init)
			gfx.init(*this);
	}

	void BgfxContext::render_frame()
	{
		// @todo this won't do for multiple contexts
		bgfx::setViewRect(0, 0, 0, uint16_t(m_fb_size.x), uint16_t(m_fb_size.y));
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, to_rgba(Colour(0.f)), 1.0f, 0);
	}

	void BgfxContext::reset_fb(const uvec2& size)
	{
		bgfx::reset(uint16_t(size.x), uint16_t(size.y), BGFX_RESET_NONE);
	}

	BgfxSystem::BgfxSystem(const string& resource_path)
		: RenderSystem(resource_path, true)
		//, m_capture_every(100)
	{
		init_console();
		info("gfx - init gfx system");
	}

	BgfxSystem::~BgfxSystem()
	{
		// we would need to do that after all resources are destroyed
		// bgfx::shutdown();
	}

	bx::AllocatorI& BgfxSystem::allocator()
	{
		static bx::DefaultAllocator alloc;
		return alloc;
	}

	void BgfxSystem::init(BgfxContext& context)
	{
		info("gfx - native handle = %p", context.m_native_handle);
		bgfx::PlatformData pd = {};
		pd.nwh = context.m_native_handle;
		pd.ndt = context.m_native_target;
		bgfx::setPlatformData(pd);

		info("gfx - bgfx::init");
		bgfx::Init params = {};
		params.type = bgfx::RendererType::OpenGL;
		params.type = bgfx::RendererType::Direct3D11;
		//params.type = bgfx::RendererType::Direct3D12;
		params.type = bgfx::RendererType::WebGPU;
		params.resolution.width = uint32_t(context.m_size.x);
		params.resolution.height = uint32_t(context.m_size.y);
		params.resolution.reset = BGFX_RESET_NONE;
		params.debug = false;
		bgfx::init(params);

		//bgfx::reset(uint32_t(context.m_width), uint32_t(context.m_height), BGFX_RESET_NONE);

#ifdef _DEBUG
		bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_PROFILER);
#endif

		m_start_counter = double(bx::getHPCounter());
		m_initialized = true;
	}

	bool BgfxSystem::begin_frame()
	{
		return true;
	}

	void BgfxSystem::end_frame()
	{
#ifdef _DEBUG
		m_capture |= m_capture_every && (m_frame % m_capture_every) == 0;
		m_frame = bgfx::frame(m_capture);
		m_capture = false;
#else
		m_frame = bgfx::frame();
#endif

		this->advance();
	}

	void TimerBx::begin()
	{
		m_start = bx::getHPCounter();
	}

	float TimerBx::end()
	{
		float time = float((bx::getHPCounter() - m_start) / double(bx::getHPFrequency()));
		return time;
	}

	void BgfxSystem::advance()
	{
		float time = float((bx::getHPCounter() - m_start_counter) / double(bx::getHPFrequency()));
		m_frame_time = time - m_time;
		m_time = time;
		m_delta_time = m_frame_time;
	}
}
