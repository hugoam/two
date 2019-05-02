//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gl/GlSystem.h>
#include <ui-nanovg-gl/VgNanoGl.h>

#ifdef TWO_CONTEXT_GLFW
#include <ctx-glfw/GlfwContext.h>
#elif defined TWO_CONTEXT_WASM
#include <ctx-wasm/EmscriptenContext.h>
#endif

#include <ui/Frame/Layer.h>

#ifdef NANOVG_GLEW
	#include <GL/glew.h>
#elif defined TWO_PLATFORM_EMSCRIPTEN
	#define GL_GLEXT_PROTOTYPES
	#include <GL/gl.h>
	#include <GL/glext.h>
#endif

namespace two
{
	GlSystem::GlSystem(cstring resource_path)
		: RenderSystem(resource_path, true)
	{}

	void GlSystem::init_glew()
	{
#ifdef NANOVG_GLEW
		glewExperimental = true;

		if(glewInit() != GLEW_OK)
		{
			printf("ERROR: Could not init glew.\n");
			return;
		}
#endif
	}
	
	bool GlSystem::next_frame()
	{
		return true;
	}

	object_ptr<Context> GlSystem::create_context(cstring name, int width, int height, bool full_screen)
	{
#ifdef TWO_CONTEXT_GLFW
		object_ptr<Context> context = make_object<GlfwContext>(*this, name, width, height, full_screen, true);
#elif defined TWO_CONTEXT_WASM
		object_ptr<Context> context = make_object<EmContext>(*this, name, width, height, full_screen);
#endif
		this->init_glew();
		return std::move(context);
	}

	object_ptr<VgRenderer> GlSystem::create_renderer(Context& context)
	{
		return make_object<VgNanoGl>(m_resource_path.c_str());
	}
}
