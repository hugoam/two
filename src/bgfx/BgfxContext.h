//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>

#if defined MUD_CONTEXT_GLFW
#define MUD_GLFW_EXPORT MUD_BGFX_EXPORT
#include <ctx-glfw/GlfwContext.h>
#elif defined MUD_CONTEXT_WASM
#define MUD_WASM_EXPORT MUD_BGFX_EXPORT
#include <ctx-wasm/EmscriptenContext.h>
#elif defined MUD_CONTEXT_WINDOWS
#define MUD_WIN_EXPORT MUD_BGFX_EXPORT
#include <ctx-win/WindowsContext.h>
#endif

#ifndef MUD_META_GENERATOR
#include <bx/allocator.h>
#endif

#include <vector>

namespace mud
{
	class BgfxSystem;

#if defined MUD_CONTEXT_GLFW
	class MUD_BGFX_EXPORT BgfxContext : public GlfwContext
#elif defined MUD_CONTEXT_WASM
	class MUD_BGFX_EXPORT BgfxContext : public EmContext
#elif defined MUD_CONTEXT_WINDOWS
	class MUD_BGFX_EXPORT BgfxContext : public WinContext
#endif
	{
	public:
		BgfxContext(BgfxSystem& gfx_system, cstring name, int width, int height, bool fullScreen, bool init);

		virtual void reset(uint16_t width, uint16_t height) override;
	};

	class MUD_BGFX_EXPORT BgfxSystem : public NonCopy, public RenderSystem
	{
	public:
		BgfxSystem(cstring resource_path);
		~BgfxSystem();

		virtual object_ptr<Context> create_context(cstring name, int width, int height, bool fullScreen);
		virtual object_ptr<VgRenderer> create_renderer(Context& context);

		void init(BgfxContext& context);
		bool next_frame();
		void advance();

		UiWindow& create_window(cstring name, int width, int height, bool fullScreen, User* user = nullptr);

	public:
#ifndef MUD_META_GENERATOR
		bx::DefaultAllocator m_allocator;
#endif
		bool m_initialized = false;

		std::vector<object_ptr<UiWindow>> m_windows;
		VgRenderer* m_vg_renderer = nullptr;

		uint32_t m_frame = 1;
		double m_start_counter = 0.0;

		float m_time = 0.f;
		float m_frame_time = 0.f;
		float m_delta_time = 0.f;
	};
}

