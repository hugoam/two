#include <mud/gfx.h>
#include <mud/bgfx.h>
#include <mud/type.h>
#include <mud/infra.h>

#include <cstdio>

#include <bx/allocator.h>
#include <bx/timer.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#ifdef MUD_MODULES
module mud.bgfx;
#else
#endif

namespace mud
{
	BgfxContext::BgfxContext(BgfxSystem& gfx_system, const string& name, int width, int height, bool fullScreen, bool init)
#if defined MUD_CONTEXT_GLFW
		: GlfwContext(gfx_system, name, width, height, fullScreen, false)
#elif defined MUD_CONTEXT_WASM
		: EmContext(gfx_system, name, width, height, fullScreen)
#elif defined MUD_CONTEXT_WINDOWS
		: WinContext(gfx_system, name, width, height, fullScreen)
#endif
	{
		if(init)
			gfx_system.init(*this);
	}

	void BgfxContext::reset(uint16_t width, uint16_t height)
	{
		bgfx::reset(width, height, BGFX_RESET_NONE);
	}

	BgfxSystem::BgfxSystem(const string& resource_path)
		: RenderSystem(resource_path, true)
		//, m_capture_every(100)
	{
		printf("INFO: Init Gfx System\n");
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

	object<Context> BgfxSystem::create_context(const string& name, int width, int height, bool fullScreen)
	{
		return oconstruct<BgfxContext>(*this, name, width, height, fullScreen, !m_initialized);
	}

	void BgfxSystem::init(BgfxContext& context)
	{
		printf("GfxSystem: Native Handle = %p\n", context.m_native_handle);
		bgfx::PlatformData pd = {};
		pd.nwh = context.m_native_handle;
		pd.ndt = context.m_native_target;
		bgfx::setPlatformData(pd);

		printf("GfxSystem: bgfx::init\n");
		bgfx::Init params = {};
		params.type = bgfx::RendererType::OpenGL;
		//params.type = bgfx::RendererType::Direct3D11;
		params.resolution.width = uint32_t(context.m_width);
		params.resolution.height = uint32_t(context.m_height);
		params.resolution.reset = BGFX_RESET_NONE;
		bgfx::init(params);

		//bgfx::reset(uint32_t(context.m_width), uint32_t(context.m_height), BGFX_RESET_NONE);

#ifdef _DEBUG
		bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_PROFILER);
#endif

		bgfx::setViewRect(0, 0, 0, uint16_t(context.m_width), uint16_t(context.m_height));
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);

		m_start_counter = double(bx::getHPCounter());
		m_initialized = true;
	}

	void BgfxSystem::begin_frame()
	{}

	bool BgfxSystem::next_frame()
	{
#ifdef _DEBUG
		m_capture |= m_capture_every && (m_frame % m_capture_every) == 0;
		m_frame = bgfx::frame(m_capture);
		m_capture = false;
#else
		m_frame = bgfx::frame();
#endif

		this->advance();
		return true;
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

#ifdef MUD_MODULES
module mud.bgfx;
#else
#endif

namespace mud
{
    // Exported types
    
}
