//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifdef MUD_CTX_OGRE

/* mud */
#include <ui/Types.h>
#include <ui/Render/RenderWindow.h>
#include <ui/Input/InputDispatcher.h>

/* Ogre */
#include <OgreWindowEventUtilities.h>

/* OIS */
#include <OIS.h>

namespace mud
{
	class OgreRenderWindow : public RenderWindow, Ogre::WindowEventListener
	{
	public:
		OgreRenderWindow(OgreRenderSystem& renderSystem, const string& name, int width, int height, bool fullScreen);
		~OgreRenderWindow();

		Ogre::RenderWindow& context() { return *m_context; }

		void initContext();

		bool nextFrame();
		void resize();

		void updateSize();

		void windowResized(Ogre::RenderWindow* renderWindow);
		void windowFocusChange(Ogre::RenderWindow* renderWindow);
		void windowClosed(Ogre::RenderWindow* renderWindow);

	protected:
		OgreRenderSystem& m_renderSystem;

		Ogre::RenderWindow* m_context;
	};

	class OISInputWindow : public InputWindow, public OIS::KeyListener, public OIS::MouseListener
	{
	public:
		OISInputWindow();
		~OISInputWindow();

		void initInput(RenderWindow& renderWindow, Mouse& mouse, Keyboard& keyboard);
		void setupInput(size_t windowHnd);
		void destroyInput();

		bool nextFrame();
		void resize(size_t width, size_t height);

		// OISInput::InputListener
		bool mouseMoved(const OIS::MouseEvent &arg);
		bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
		bool keyPressed(const OIS::KeyEvent &arg);
		bool keyReleased(const OIS::KeyEvent &arg);

		char getChar(const OIS::KeyEvent &arg);

	protected:
		OIS::InputManager* m_inputManager;
		OIS::Mouse* m_mouse;
		OIS::Keyboard* m_keyboard;

		Mouse* m_uiMouse;
		Keyboard* m_uiKeyboard;

		map<OIS::MouseButtonID, bool> m_pressed;
		bool m_shutdownRequested;
	};
}

#endif // MUD_GFXREWINDOW_H
