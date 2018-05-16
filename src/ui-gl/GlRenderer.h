//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MUD_GL_UI_RENDERER_H
#define MUD_GL_UI_RENDERER_H

/* mud */
#include <ui/Types.h>
#include <ui/Backend/Nano/NanoRenderer.h>

namespace mud
{
	class MUD_UI_GL_EXPORT GlRenderer : public NanoRenderer
	{
	public:
		GlRenderer(const string& resourcePath, bool clear);

		// init
		virtual void setupContext();
		virtual void releaseContext();

		virtual void render(RenderTarget& target);

		void initGlew();

	protected:
		bool m_clear;
	};
}

#endif
