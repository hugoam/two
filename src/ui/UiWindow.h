//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/NonCopy.h>
#include <infra/Strung.h>
#include <obj/Unique.h>
#include <math/Timer.h>
#endif
#include <ui/Forward.h>
#include <ui/ImageAtlas.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ class refl_ MUD_UI_EXPORT UiWindow : public NonCopy
	{
	public:
		UiWindow(RenderSystem& system, cstring name, int width, int height, bool fullScreen, User* user = nullptr);
		~UiWindow();

		void init();
		bool next_frame();
		void shutdown();

		void resize(uint16_t width, uint16_t height);

		void handle_resize(uint16_t width, uint16_t height);

		Image& create_image(cstring image, uvec2 size, uint8_t* data, bool filtering = true);
		void remove_image(Image& image);
		Image& find_image(cstring name);

	protected:
		void init_resources();
		void load_resources();

	public:
		RenderSystem& m_render_system;
		const string m_resource_path;

		object_ptr<Context> m_context;
		object_ptr<VgRenderer> m_renderer;

		std::vector<object_ptr<Image>> m_images;
		ImageAtlas m_atlas;

		float m_width;
		float m_height;

		object_ptr<Styler> m_styler;

		object_ptr<RootSheet> m_root_sheet;

		bool m_shutdown = false;

		Clock m_clock;

		User* m_user = nullptr;
	};
}
