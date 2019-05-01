//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/map.h>
#include <stl/memory.h>
#include <math/Timer.h>
#include <math/ImageAtlas.h>
#endif
#include <ui/Forward.h>
#include <ui/UiRenderer.h>

namespace mud
{
	export_ struct refl_ MUD_UI_EXPORT Clipboard
	{
		Clipboard() {}
		Clipboard(const string& text, bool line_mode) : m_text(text), m_line_mode(line_mode) {}
		attr_ string m_text = "";
		attr_ bool m_line_mode = false;
		attr_ vector<string> m_pasted = {};
	};

	export_ class refl_ MUD_UI_EXPORT UiWindow
	{
	public:
		UiWindow(Context& context, Vg& vg, User* user = nullptr);
		~UiWindow();

		void init();
		bool input_frame();
		void render_frame(uint16_t view);
		void shutdown();

		func_ void reset_styles();

		void resize(const uvec2& size, const uvec2& fb_size);

		Image& create_image(cstring image, const uvec2& size, span<uint8_t> data, bool filtering = true);
		void remove_image(Image& image);
		Image* find_image(cstring name);

	protected:
		void init_resources();
		void load_resources();

	public:
		attr_ const string m_resource_path;

		attr_ Context& m_context;
		attr_ Vg& m_vg;

		UiRenderer m_renderer;

		vector<unique<Image>> m_images;
		ImageAtlas m_atlas;

		attr_ uvec2 m_size;
		attr_ Colour m_colour = Colour(0.f);
		attr_ bool m_shutdown = false;

		Clipboard m_clipboard;

		unique<Ui> m_ui;

		User* m_user = nullptr;
	};
}
