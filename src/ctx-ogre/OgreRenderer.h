//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifdef TWO_CTX_OGRE

#include <ui/Generated/Types.h>
#include <ui/Render/Renderer.h>
#include <ui/Gl/GlRenderer.h>

#include <Ogre.h>

namespace two
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

#endif // TWO_GFXRERENDERER_H
