//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.ctx;
#else
#include <ctx/Context.h>
#endif

namespace two
{
	RenderSystem::RenderSystem(const string& resource_path, bool manual_render)
		: m_resource_path(resource_path)
		, m_manual_render(manual_render)
	{}

	Context::Context(RenderSystem& render_system, const string& title, const uvec2& size, bool fullscreen, bool main)
		: m_render_system(render_system)
		, m_resource_path(render_system.m_resource_path)
		, m_title(title)
		, m_size(size)
		, m_fb_size(size)
		, m_fullscreen(fullscreen)
		, m_is_main(main)
	{}

	Context::~Context()
	{}

}
