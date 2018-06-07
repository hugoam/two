//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <stb_image.h>

#include <obj/Vector.h>
#include <obj/String/String.h>
#include <obj/System/System.h>
#include <obj/Reflect/Class.h> // @kludge
#include <ctx/Context.h>
#include <ui/UiWindow.h>
#include <ui/Generated/Types.h> // @kludge
#include <ui/Style/9Sprite.h> // @kludge
#include <ui/Style/Styler.h>
#include <ui/Style/Styles.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Frame/Frame.h>
#include <ui/Render/Renderer.h>
#include <ui/Controller/Controller.h>
#endif

namespace mud
{
	static void load_folder_images(std::vector<Image>& images, const string& path, const string& subfolder)
	{
		auto visit_file = [&](cstring path, cstring file)
		{
			string fullpath = string(path) + file;
			string name = subfolder + replace_all(file, ".png", "");

			int width, height, n;
			unsigned char* img = stbi_load(fullpath.c_str(), &width, &height, &n, 4);
			stbi_image_free(img);
			images.push_back({ name.c_str(), fullpath.c_str(),{ uint(width), uint(height) } });
		};

		system().visit_files(path.c_str(), visit_file);
	}

	UiWindow::UiWindow(RenderSystem& system, cstring name, int width, int height, bool fullScreen, User* user)
		: m_render_system(system)
		, m_resource_path(system.m_resource_path)
		, m_context(system.create_context(name, width, height, fullScreen))
		, m_renderer(system.create_renderer(*m_context))
		, m_atlas(uvec2(1024U))
		, m_width(float(width))
		, m_height(float(height))
		, m_styler(make_object<Styler>(*this))
		, m_user(user)
	{
		// @kludge until reflection properly supports Enum default parameters
		cls<ImageSkin>().m_constructors[0].m_arguments.back() = var(DIM_NONE);

		this->init();
	}

	UiWindow::~UiWindow()
	{
		for(auto& image : m_images)
			if(image->d_handle != -1)
			{
				m_renderer->unload_image(*image);
			}
	}

	void UiWindow::init()
	{
		printf("INFO: Initializing UiWindow: resource path %s\n", m_resource_path.c_str());
		m_renderer->setup_context();

		this->init_resources();
		this->load_resources();

		styles().setup(*this);

		m_root_sheet = make_object<RootSheet>(*this);

		m_context->init_input(m_root_sheet->m_mouse, m_root_sheet->m_keyboard);

		this->resize(uint16_t(m_width), uint16_t(m_height));
	}

	void UiWindow::init_resources()
	{
		string sprite_path = string(m_resource_path) + "interface/uisprites/";

		printf("INFO: Loading Images in path %s\n", sprite_path.c_str());

		std::vector<Image> images;
		load_folder_images(images, sprite_path, "");

		auto visit_folder = [&](cstring path, cstring folder)
		{
			load_folder_images(images, sprite_path + folder + "/", string(folder) + "/");
		};

		system().visit_folders(sprite_path.c_str(), visit_folder);

		m_images = vector_convert<object_ptr<Image>>(images, [](const Image& image) { return make_object<Image>(image); });
	}

	void UiWindow::load_resources()
	{
		m_renderer->load_default_font();

		std::vector<Image*> images;
		for(auto& image : m_images) images.push_back(image.get());

		std::vector<unsigned char> atlas = m_atlas.generate_atlas(images);
		m_renderer->load_image_RGBA(m_atlas.m_image, atlas.data());
	}

	Image& UiWindow::create_image(cstring name, uvec2 size, uint8_t* data, bool filtering)
	{
		m_images.emplace_back(make_object<Image>(name, name, size));
		Image& image = *m_images.back();
		image.d_filtering = filtering;
		m_renderer->load_image_RGBA(image, data);
		return image;
	}

	void UiWindow::remove_image(Image& image)
	{
		vector_remove_if(m_images, [&](object_ptr<Image>& current) { return current.get() == &image; });
		m_renderer->unload_image(image);
	}

	Image& UiWindow::find_image(cstring name)
	{
		for(auto& image : m_images)
			if(image->d_name == name)
				return *image;
		static Image null; return null;
	}

	void UiWindow::resize(uint16_t width, uint16_t height)
	{
		m_width = float(width);
		m_height = float(height);

		//m_context->m_input_window->resize(width, height);
		m_context->reset(width, height);

		printf("UiWindow :: resize %i, %i\n", int(width), int(height));
		m_root_sheet->m_frame.set_size({ m_width, m_height });
	}

	bool UiWindow::next_frame()
	{
		if(m_context->m_width != uint(m_width) || m_context->m_height != uint(m_height))
			this->resize(uint16_t(m_context->m_width), uint16_t(m_context->m_height));

		if(m_context->m_render_system.m_manual_render)
		{
			m_root_sheet->m_target->render();
			// add sub layers
		}

		size_t tick = m_clock.readTick();
		size_t delta = m_clock.stepTick();

		m_root_sheet->clear_events();

		bool pursue = !m_shutdown;
		pursue &= m_context->next_frame();

		m_root_sheet->next_frame(tick, delta);

		return pursue;
	}
	
	void UiWindow::shutdown()
	{
		m_shutdown = true;
	}
}
