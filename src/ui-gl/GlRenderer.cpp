//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <ui/Config.h>
#include <ui/Backend/Gl/GlRenderer.h>

#include <ui/Frame/Layer.h>

#ifdef NANOVG_GLEW
	#include <GL/glew.h>
#elif defined MUD_PLATFORM_EMSCRIPTEN
	#define GL_GLEXT_PROTOTYPES
	#include <GL/gl.h>
	#include <GL/glext.h>
#endif

#ifdef MUD_PLATFORM_EMSCRIPTEN
#define NANOVG_GLES2_IMPLEMENTATION
#else
#define NANOVG_GL3_IMPLEMENTATION
#endif

#include <nanovg_gl.h>

namespace mud
{
	GlRenderer::GlRenderer(const string& resourcePath, bool clear)
		: NanoRenderer(resourcePath)
		, m_clear(clear)
	{}

	void GlRenderer::setupContext()
	{
		this->initGlew();

#if NANOVG_GL2
		m_ctx = nvgCreateGL2(NVG_ANTIALIAS);
#elif NANOVG_GL3
		m_ctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
#elif NANOVG_GLES2
		m_ctx = nvgCreateGLES2(NVG_STENCIL_STROKES);
#endif

		if(m_ctx == nullptr)
		{
			printf("ERROR: Could not init nanovg.\n");
			return;
		}
	}

	void GlRenderer::releaseContext()
	{
#if NANOVG_GL2
		nvgDeleteGL2(m_ctx);
#elif NANOVG_GL3
		nvgDeleteGL3(m_ctx);
#elif NANOVG_GLES2
		nvgDeleteGLES2(m_ctx);
#endif

		m_ctx = nullptr;
	}

	void GlRenderer::initGlew()
	{
#ifdef NANOVG_GLEW
		glewExperimental = true;

		if(glewInit() != GLEW_OK) {
			printf("ERROR: Could not init glew.\n");
			return;
		}
#endif
	}

	void GlRenderer::render(RenderTarget& target)
	{
		if(target.m_gammaCorrected)
			glDisable(GL_FRAMEBUFFER_SRGB);

		// Update and render
		glViewport(0, 0, target.m_layer.m_size.x, target.m_layer.m_size.y);

		if(m_clear)
		{
			glClearColor(0.f, 0.f, 0.f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		Renderer::render(target);

		if(target.m_gammaCorrected)
			glEnable(GL_FRAMEBUFFER_SRGB);
	}
}
