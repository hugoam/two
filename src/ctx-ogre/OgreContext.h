//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifdef MUD_CTX_OGRE

/* mud */
#include <ui/Generated/Types.h>
#include <ui/UiWindow.h>

namespace Ogre
{
	class Root;
	class RenderWindow;
	class RenderSystem;

	class HlmsManager;
	class HlmsTextureManager;
	class HlmsUnlit;
	class HlmsPbs;
}

namespace mud
{
	class OgreContext : public Context
	{
	public:
		OgreContext(OgreRenderSystem& renderSystem, const string& name, int width, int height, bool fullScreen);
	};

	class OgreRenderSystem : public RenderSystem
	{
	public:
		OgreRenderSystem(const string& resourcePath);
		~OgreRenderSystem();

		unique_ptr<Ogre::Root> m_ogreRoot;
		bool m_contextActive;

		bool nextFrame();

		void init();
		void setupRenderer(const string& name);
		void setupHiddenWindow();
		void setupUiWorkspace();

		void focusChange() { m_contextActive = !m_contextActive; }

		virtual object_ptr<Context> createContext(const string& name, int width, int height, bool fullScreen);
		virtual object_ptr<Renderer> createRenderer(Context& context);

	protected:
		Ogre::RenderWindow* m_hiddenWindow;
		Ogre::RenderSystem* m_renderSystem;
	};
}

#endif
