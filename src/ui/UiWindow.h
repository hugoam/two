//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/NonCopy.h>
#include <infra/Strung.h>
#include <type/Unique.h>
#include <math/Timer.h>
#include <math/ImageAtlas.h>
#endif
#include <ui/Forward.h>
#include <ui/Render/Renderer.h>

#ifndef MUD_CPP_20
#include <vector>
#include <map>
#endif

namespace mud
{
	export_ struct refl_ MUD_UI_EXPORT Clipboard
	{
		Clipboard() {}
		Clipboard(const string& text, bool line_mode) : m_text(text), m_line_mode(line_mode) {}
		attr_ string m_text = "";
		attr_ bool m_line_mode = false;
		attr_ std::vector<string> m_pasted = {};
	};

	export_ class refl_ MUD_UI_EXPORT UiWindow : public NonCopy
	{
	public:
		UiWindow(Context& context, Vg& vg, User* user = nullptr);
		~UiWindow();

		void init();
		bool input_frame();
		void render_frame();
		void shutdown();

		void init_styles();
		void reset_styles();

		void resize(uint16_t width, uint16_t height);

		Image& create_image(cstring image, uvec2 size, uint8_t* data, bool filtering = true);
		void remove_image(Image& image);
		Image* find_image(cstring name);

	protected:
		void init_resources();
		void load_resources();

	public:
		const string m_resource_path;

		Context& m_context;
		Vg& m_vg;

		UiRenderer m_renderer;

		std::vector<object_ptr<Image>> m_images;
		ImageAtlas m_atlas;

		float m_width;
		float m_height;

		Clipboard m_clipboard;

		object_ptr<Ui> m_root_sheet;

		bool m_shutdown = false;

		User* m_user = nullptr;

		static std::map<string, Style*> s_styles;
	};
}
