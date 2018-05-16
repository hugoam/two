//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ctx/Context.h>

namespace mud
{
	RenderSystem::RenderSystem(cstring resource_path, bool manual_render)
		: m_resource_path(resource_path)
		, m_manual_render(manual_render)
	{}

	Context::Context(RenderSystem& render_system, cstring title, int width, int height, bool full_screen)
		: m_render_system(render_system)
		, m_resource_path(render_system.m_resource_path)
		, m_title(title)
		, m_width(width)
		, m_height(height)
		, m_full_screen(full_screen)
	{}

	Context::~Context()
	{}

}
