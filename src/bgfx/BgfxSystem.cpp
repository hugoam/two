//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bx/allocator.h>
#include <bx/timer.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#ifdef MUD_MODULES
module mud.bgfx;
#else
#include <obj/Type.h>
#include <bgfx/Config.h>
#include <bgfx/BgfxSystem.h>
#endif

namespace mud
{
	BgfxContext::BgfxContext(BgfxSystem& gfx_system, cstring name, int width, int height, bool fullScreen, bool init)
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

	BgfxSystem::BgfxSystem(cstring resource_path)
		: RenderSystem(resource_path, true)
	{
		printf("INFO: Init Gfx System\n");
	}

	BgfxSystem::~BgfxSystem()
	{
		// we would need to do that after all ressources are destroyed
		// bgfx::shutdown();
	}

	object_ptr<Context> BgfxSystem::create_context(cstring name, int width, int height, bool fullScreen)
	{
		return make_object<BgfxContext>(*this, name, width, height, fullScreen, !m_initialized);
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
		params.resolution.width = uint32_t(context.m_width);
		params.resolution.height = uint32_t(context.m_height);
		params.resolution.reset = BGFX_RESET_NONE;
		bgfx::init(params);

		//bgfx::reset(uint32_t(context.m_width), uint32_t(context.m_height), BGFX_RESET_NONE);

		bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_PROFILER);

		bgfx::setViewRect(0, 0, 0, uint16_t(context.m_width), uint16_t(context.m_height));
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);

		m_start_counter = double(bx::getHPCounter());
		m_initialized = true;
	}

	bool BgfxSystem::next_frame()
	{
		bgfx::touch(0);

		size_t capture_every = 100;
		bool capture = (m_frame % capture_every) == 0;
		//bool capture = false;
		capture = false;

		m_frame = bgfx::frame(capture);
		this->advance();

		return true;
	}

	void BgfxSystem::advance()
	{
		float time = float((bx::getHPCounter() - m_start_counter) / double(bx::getHPFrequency()));
		m_frame_time = time - m_time;
		m_time = time;
		m_delta_time = m_frame_time;//;float(m_frame_time / double(bx::getHPFrequency()));
	}
}
