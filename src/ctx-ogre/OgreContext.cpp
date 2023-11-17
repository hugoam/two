 //  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <ui/Config.h>
#include <ui/Context/Ogre/OgreContext.h>

#include <ui/Context/Ogre/OgreWindow.h>
#include <ui/Context/Ogre/OgreRenderer.h>

#include <ui/UiWindow.h>

#include <ui/Gl/GlRenderer.h>
#include <ui/Render/Renderer.h>

#include <OgreRoot.h>
#include <Compositor/OgreCompositorManager2.h>
#include <Compositor/OgreCompositorNodeDef.h>
#include <Compositor/OgreCompositorWorkspaceDef.h>
#include <Compositor/RenderPass/OgreCompositorPass.h>
#include <Compositor/RenderPass/OgreCompositorPassProvider.h>

#include <OgreBuildSettings.h>

namespace two
{
	class UiPassProvider : public Ogre::CompositorPassProvider
	{
	public:
		virtual Ogre::CompositorPassDef* addPassDef(Ogre::CompositorPassType passType, Ogre::IdString customId, Ogre::CompositorTargetDef* parentTargetDef, Ogre::CompositorNodeDef* parentNodeDef);
		virtual Ogre::CompositorPass* addPass(const Ogre::CompositorPassDef* definition, Ogre::Camera* camera, Ogre::CompositorNode* parentNode, const Ogre::CompositorChannel& target, Ogre::SceneManager* sceneManager);

		static Ogre::IdString m_passId;
	};

	class UiPassDef : public Ogre::CompositorPassDef
	{
	public:
		UiPassDef(Ogre::CompositorTargetDef* parentTargetDef)
			: Ogre::CompositorPassDef(Ogre::PASS_CUSTOM, parentTargetDef)
		{}
	};

	class UiPass : public Ogre::CompositorPass
	{
	public:
		UiPass(const Ogre::CompositorPassDef* definition, const Ogre::CompositorChannel& target, Ogre::CompositorNode* parentNode, Ogre::Camera* camera)
			: Ogre::CompositorPass(definition, target, parentNode)
			, m_camera(camera)
		{}

		virtual void execute(const Ogre::Camera* lodCameraconst)
		{
			m_camera->getSceneManager()->_setViewport(mViewport); // @kludge : investigate, ask on the forums ?
			RenderTarget* renderer = Ogre::any_cast<RenderTarget*>(m_camera->getUserAny());
			renderer->render();
		}

	protected:
		Ogre::Camera* m_camera;
	};

	Ogre::CompositorPassDef* UiPassProvider::addPassDef(Ogre::CompositorPassType passType, Ogre::IdString customId, Ogre::CompositorTargetDef* parentTargetDef, Ogre::CompositorNodeDef* parentNodeDef)
	{
		if(customId == m_passId)
			return OGRE_NEW UiPassDef(parentTargetDef);
		return nullptr;
	}

	Ogre::CompositorPass* UiPassProvider::addPass(const Ogre::CompositorPassDef* definition, Ogre::Camera* camera, Ogre::CompositorNode* parentNode
		, const Ogre::CompositorChannel& target, Ogre::SceneManager* sceneManager)
	{
		return OGRE_NEW UiPass(definition, target, parentNode, camera);
	}

	Ogre::IdString UiPassProvider::m_passId("Ui");

	OgreContext::OgreContext(OgreRenderSystem& renderSystem, const string& name, int width, int height, bool fullScreen)
		: Context(renderSystem, make_object<OgreRenderWindow>(renderSystem, name, width, height, fullScreen), make_object<OISInputWindow>())
	{}

	OgreRenderSystem::OgreRenderSystem(const string& resourcePath)
		: RenderSystem(resourcePath, false)
		, m_ogreRoot(make_unique<Ogre::Root>())
		, m_contextActive(true)
	{}
	
	OgreRenderSystem::~OgreRenderSystem()
	{}

	object_ptr<Context> OgreRenderSystem::createContext(const string& name, int width, int height, bool fullScreen)
	{
		return make_object<OgreContext>(*this, name, width, height, fullScreen);
	}

	object_ptr<Renderer> OgreRenderSystem::createRenderer(Context& context)
	{
		return make_object<OgreRenderer>(m_resourcePath);
	}

	bool OgreRenderSystem::nextFrame()
	{
		Ogre::WindowEventUtilities::messagePump();

		if(m_contextActive)
			m_ogreRoot->renderOneFrame();
		else
			m_ogreRoot->clearEventTimes();

		return true;
	}

	void OgreRenderSystem::init()
	{
		this->setupRenderer("OpenGL 3+ Rendering Subsystem");
		//this->setupRenderer("Direct3D11 Rendering Subsystem");

		m_ogreRoot->initialise(false);

		this->setupHiddenWindow();
		this->setupUiWorkspace();
	}

	void OgreRenderSystem::setupRenderer(const string& name)
	{
		m_renderSystem = m_ogreRoot->getRenderSystemByName(name);
		if(!m_renderSystem)
			m_renderSystem = m_ogreRoot->getAvailableRenderers().at(0);

		m_ogreRoot->setRenderSystem(m_renderSystem);
	}

	void OgreRenderSystem::setupHiddenWindow()
	{
		Ogre::NameValuePairList params;
		params["hidden"] = "true";
		params["gamma"] = "true";

		m_hiddenWindow = m_ogreRoot->createRenderWindow("twoHidden", 1, 1, false, &params);
	}

	void OgreRenderSystem::setupUiWorkspace()
	{
		Ogre::CompositorManager2* compositorManager = m_ogreRoot->getCompositorManager2();

		static UiPassProvider m_passProvider;
		compositorManager->setCompositorPassProvider(&m_passProvider);

		Ogre::CompositorNodeDef* nodeDef = compositorManager->addNodeDefinition("AutoGen " + (Ogre::IdString("Ui Workspace") + Ogre::IdString("/Node")).getReleaseText());
		nodeDef->addTextureSourceName("WindowRT", 0, Ogre::TextureDefinitionBase::TEXTURE_INPUT);
		nodeDef->setNumTargetPass(1);

		Ogre::CompositorTargetDef* targetDef = nodeDef->addTargetPass("WindowRT");
		targetDef->setNumPasses(1);
		targetDef->addPass(Ogre::PASS_CUSTOM, UiPassProvider::m_passId);

		Ogre::CompositorWorkspaceDef* workDef = compositorManager->addWorkspaceDefinition("Ui Workspace");
		workDef->connectExternal(0, nodeDef->getName(), 0);

		compositorManager->createBasicWorkspaceDef("Clear Workspace", Ogre::ColourValue::Black);
	}
}
