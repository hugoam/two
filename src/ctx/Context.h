//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ctx/Forward.h>

namespace two
{
#ifdef TWO_MODULES
	using stl::string;
#endif
	using cstring = const char*;

	export_ class refl_ TWO_CTX_EXPORT RenderSystem
	{
	public:
		RenderSystem(const string& resource_path, bool manual_render);
		virtual ~RenderSystem() {}

		virtual bool begin_frame() = 0;
		virtual void end_frame() = 0;

		const string m_resource_path;
		const bool m_manual_render;
	};

	export_ class refl_ TWO_CTX_EXPORT Context
	{
	public:
		Context(RenderSystem& render_system, const string& title, const uvec2& size, bool fullscreen = false, bool main = true);
		virtual ~Context();

		RenderSystem& m_render_system;
		attr_ const string m_resource_path;

		attr_ string m_title;
		attr_ uvec2 m_size;
		attr_ uvec2 m_fb_size;
		attr_ bool m_fullscreen = false;
		attr_ bool m_is_main = true;

		attr_ float m_pixel_ratio = 1.f;

		size_t m_handle = 0;
		void* m_native_handle = nullptr;
		void* m_native_target = nullptr;

		attr_ bool m_active = true;
		attr_ bool m_shutdown = false;

		attr_ vec2 m_cursor;
		attr_ bool m_mouse_lock = false;

		meth_ virtual void reset_fb(const uvec2& size) = 0;
		meth_ virtual void init_input(Mouse& mouse, Keyboard& keyboard) = 0;

		meth_ virtual bool begin_frame() = 0;
		meth_ virtual void render_frame() = 0;
		meth_ virtual void end_frame() = 0;

		meth_ virtual void lock_mouse(bool locked) = 0;
	};

}
