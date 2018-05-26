//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

/* mud */
#include <ctx/Context.h>
#include <ui-nanovg/VgNano.h>

#ifdef MUD_GL_LIB
#define MUD_GL_EXPORT MUD_EXPORT
#else
#define MUD_GL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	class MUD_GL_EXPORT GlSystem : public RenderSystem
	{
	public:
		GlSystem(cstring resource_path);
		
		virtual bool next_frame() final;

		virtual object_ptr<Context> create_context(cstring name, int width, int height, bool full_screen) final;
		virtual object_ptr<VgRenderer> create_renderer(Context& context) final;

		void init_glew();
	};
}
