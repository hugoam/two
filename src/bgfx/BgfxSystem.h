//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ctx/Forward.h>
#include <bgfx/Config.h>

#ifndef MUD_MODULES
	#if defined MUD_CONTEXT_GLFW
		#include <ctx-glfw/GlfwContext.h>
	#elif defined MUD_CONTEXT_WASM
		#include <ctx-wasm/EmscriptenContext.h>
	#elif defined MUD_CONTEXT_WINDOWS
		#include <ctx-win/WindowsContext.h>
	#else
		#include <ctx/Context.h>
	#endif
#endif

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace bx
{
	struct AllocatorI;
}

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

		bx::AllocatorI& allocator();

	public:
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

