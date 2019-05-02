//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <ui/Config.h>
#include <ui/Context/Ogre/OgreRenderer.h>

#include <ui/Context/Ogre/OgreWindow.h>

#include <ui/Widget/RootSheet.h>
#include <ui/Frame/Layer.h>
#include <ui/UiWindow.h>

#include <Ogre.h>
#include <Compositor/OgreCompositorManager2.h>

namespace two
{
	OgreRenderTarget::OgreRenderTarget(Renderer& renderer, Layer& masterLayer)
		: RenderTarget(renderer, masterLayer, true)
		, m_scene(*Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC, 1, Ogre::INSTANCING_CULLING_SINGLETHREAD))
		, m_node(*m_scene.getRootSceneNode()->createChildSceneNode())
		, m_camera(*m_scene.createCamera("Ui Camera"))
	{
		m_camera.detachFromParent();
		m_node.attachObject(&m_camera);

		OgreRenderWindow& renderWindow = static_cast<OgreRenderWindow&>(masterLayer.d_widget.uiWindow().m_renderWindow);

		Ogre::CompositorManager2& compositorManager = *Ogre::Root::getSingleton().getCompositorManager2();
		compositorManager.addWorkspace(&m_scene, &renderWindow.context(), &m_camera, "Clear Workspace", true);
		compositorManager.addWorkspace(&m_scene, &renderWindow.context(), &m_camera, "Ui Workspace", true);

		m_camera.setUserAny(Ogre::Any(static_cast<RenderTarget*>(this)));
	}

	OgreRenderTarget::~OgreRenderTarget()
	{}

	OgreRenderer::OgreRenderer(const string& resourcePath)
		: GlRenderer(resourcePath, false)
	{}

	object_ptr<RenderTarget> OgreRenderer::createRenderTarget(Layer& masterLayer)
	{
		return make_object<OgreRenderTarget>(*this, masterLayer);
	}
}
