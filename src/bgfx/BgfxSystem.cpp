//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#define BX_COMPILER_MSVC_CONFORMANCE
#include <cassert>
#include <gfx/Cpp20.h>
#include <cstdio>
#include <bx/allocator.h>
#include <bx/timer.h>
#include <bx/platform.h>
#include <bgfx/bgfx.h>
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
		m_swapChain.nwh = m_native_handle;
		m_swapChain.ndt = m_native_target;
		m_swapChain.width = uint32_t(m_size.x);
		m_swapChain.height = uint32_t(m_size.y);
		m_swapChain.formatColor = bgfx::TextureFormat::BGRA8;
		m_swapChain.formatDepthStencil = bgfx::TextureFormat::D24S8;
		m_swapChain.numBackBuffers = 2;

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
		m_size = size;
		m_swapChain.width = size.x;
		m_swapChain.height = size.y;
		bgfx::reset(BGFX_RESET_NONE, &m_swapChain);
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
		info("gfx - bgfx::init");
		bgfx::Init params = {};
		params.type = bgfx::RendererType::OpenGL;
		params.type = bgfx::RendererType::Direct3D11;
	  //params.type = bgfx::RendererType::Direct3D12;
		params.type = bgfx::RendererType::WebGPU;
		params.swapChain = context.m_swapChain;
		params.platformData.type = bgfx::NativeWindowHandleType::Default;
		params.reset = BGFX_RESET_NONE;
		params.debug = false;
		bgfx::init(params);

		//bgfx::reset(BGFX_RESET_NONE, &context.m_swapChain);

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
