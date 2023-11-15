//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#include <ctx/Forward.h>
#endif
#include <bgfx/Forward.h>

#ifndef TWO_MODULES
	#if defined TWO_CONTEXT_GLFW
		#include <ctx-glfw/GlfwContext.h>
	#elif defined TWO_CONTEXT_WASM
		#include <ctx-wasm/EmscriptenContext.h>
	#elif defined TWO_CONTEXT_WINDOWS
		#include <ctx-win/WindowsContext.h>
	#else
		#include <ctx/Context.h>
	#endif
#endif

#ifndef TWO_MODULES
namespace bx
{
	struct AllocatorI;
}
#endif

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

