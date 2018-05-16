//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/NonCopy.h>
#include <obj/Unique.h>
#include <obj/Strung.h>
#include <math/Vec.h>
#include <ctx/Generated/Forward.h>

namespace mud
{
	class VgRenderer;

	class _refl_ MUD_CTX_EXPORT RenderSystem
	{
	public:
		RenderSystem(cstring resource_path, bool manual_render);

		virtual object_ptr<Context> create_context(cstring name, int width, int height, bool fullScreen) = 0;
		virtual object_ptr<VgRenderer> create_renderer(Context& context) = 0;

		const strung m_resource_path;
		const bool m_manual_render;
	};

	class _refl_ MUD_CTX_EXPORT Context : public NonCopy
	{
	public:
		Context(RenderSystem& render_system, cstring title, int width, int height, bool full_screen = false);
		virtual ~Context();

		RenderSystem& m_render_system;
		const strung m_resource_path;

		strung m_title;
		unsigned int m_width;
		unsigned int m_height;
		bool m_full_screen;

		size_t m_handle = 0;
		void* m_native_handle = nullptr;
		void* m_native_target = nullptr;

		bool m_active = true;
		bool m_shutdown = false;

		vec2 m_cursor;

		virtual void reset(uint16_t width, uint16_t height) = 0;
		virtual void init_input(Mouse& mouse, Keyboard& keyboard) = 0;

		virtual bool next_frame() = 0;
	};

}
