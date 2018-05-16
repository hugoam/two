//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifdef MUD_CTX_OGRE

/* mud */
#include <ui/Generated/Types.h>
#include <ui/Render/Renderer.h>
#include <ui/Gl/GlRenderer.h>

/* Ogre */
#include <Ogre.h>

namespace mud
{
	class OgreRenderTarget : public RenderTarget
	{
	public:
		OgreRenderTarget(Renderer& renderer, Layer& masterLayer);
		~OgreRenderTarget();

	protected:
		Ogre::SceneManager& m_scene;
		Ogre::SceneNode& m_node;
		Ogre::Camera& m_camera;
	};

	class OgreRenderer : public GlRenderer
	{
	public:
		OgreRenderer(const string& resourcePath);

		virtual object_ptr<RenderTarget> createRenderTarget(Layer& masterLayer);
	};
}

#endif // MUD_GFXRERENDERER_H
