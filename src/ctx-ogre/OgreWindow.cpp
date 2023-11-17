//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <ui/Config.h>
#include <ui/Context/Ogre/OgreWindow.h>

#include <ui/Context/Ogre/OgreContext.h>

#include <ui/Input/InputDevice.h>

#include <Ogre.h>
#include <OgreRoot.h>

#include <Compositor/OgreCompositorManager2.h>
#include <Compositor/OgreCompositorNodeDef.h>
#include <Compositor/OgreCompositorWorkspaceDef.h>

namespace two
{
	OgreRenderWindow::OgreRenderWindow(OgreRenderSystem& renderSystem, const string& name, int width, int height, bool fullScreen)
		: RenderWindow(name, width, height, fullScreen)
		, m_renderSystem(renderSystem)
		, m_context(nullptr)
	{
		this->initContext();
	}

	OgreRenderWindow::~OgreRenderWindow()
	{
		Ogre::WindowEventUtilities::removeWindowEventListener(m_context, this);

		m_renderSystem.m_ogreRoot->destroyRenderTarget(m_context);
	}

	void OgreRenderWindow::initContext()
	{
		Ogre::NameValuePairList params;
		//params["border"] = "none";

		HGLRC context = wglGetCurrentContext();
		params["externalGLContext"] = Ogre::StringConverter::toString((size_t)(context));
		params["vsync"] = "No";
		params["gamma"] = "true";

		m_context = m_renderSystem.m_ogreRoot->createRenderWindow(m_title, m_width, m_height, m_fullScreen, &params);

		m_context->getCustomAttribute("WINDOW", &m_handle);

		Ogre::WindowEventUtilities::addWindowEventListener(m_context, this);
	}

	bool OgreRenderWindow::nextFrame()
	{
		return !m_shutdown;
	}

	void OgreRenderWindow::updateSize()
	{
		unsigned int depth;
		int left, top;
		m_context->getMetrics(m_width, m_height, depth, left, top);
	}

	void OgreRenderWindow::windowResized(Ogre::RenderWindow* renderWindow)
	{
		this->updateSize();
	}

	void OgreRenderWindow::windowFocusChange(Ogre::RenderWindow* renderWindow)
	{
		m_active = !m_active;
		m_renderSystem.focusChange();
	}

	void OgreRenderWindow::windowClosed(Ogre::RenderWindow* renderWindow)
	{
		m_shutdown = true;
	}

	MouseButtonCode convertOISButton(int buttonID)
	{
		switch(buttonID)
		{
		case OIS::MB_Left:
			return LEFT_BUTTON;
		case OIS::MB_Right:
			return RIGHT_BUTTON;
		case OIS::MB_Middle:
			return MIDDLE_BUTTON;
		default:
			return LEFT_BUTTON;
		}
	}

	OISInputWindow::OISInputWindow()
		: m_inputManager(nullptr)
		, m_mouse(nullptr)
		, m_keyboard(nullptr)
		, m_uiMouse(nullptr)
		, m_uiKeyboard(nullptr)
		, m_shutdownRequested(false)
	{}

	OISInputWindow::~OISInputWindow()
	{
		destroyInput();
	}

	void OISInputWindow::initInput(RenderWindow& renderWindow, Mouse& mouse, Keyboard& keyboard)
	{
		this->setupInput(renderWindow.m_handle);

		m_uiMouse = &mouse;
		m_uiKeyboard = &keyboard;
	}

	void OISInputWindow::setupInput(size_t windowHnd)
	{
		std::ostringstream windowHndStr;
		OIS::ParamList paramList;

		windowHndStr << (unsigned int)windowHnd;
		paramList.insert(std::make_pair("WINDOW", windowHndStr.str()));
		paramList.insert(std::make_pair("w32_mouse", "DISCL_FOREGROUND"));
		paramList.insert(std::make_pair("w32_mouse", "DISCL_NONEXCLUSIVE"));

		m_inputManager = OIS::InputManager::createInputSystem(paramList);

		m_mouse = static_cast<OIS::Mouse*>(m_inputManager->createInputObject(OIS::OISMouse, true));
		m_keyboard = static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));

		m_keyboard->setEventCallback(this);
		m_mouse->setEventCallback(this);
	}

	bool OISInputWindow::nextFrame()
	{
		m_mouse->capture();
		m_keyboard->capture();

		return !m_shutdownRequested;
	}

	void OISInputWindow::resize(size_t width, size_t height)
	{
		const OIS::MouseState& mouseState = m_mouse->getMouseState();
		mouseState.width = width;
		mouseState.height = height;
	}

	void OISInputWindow::destroyInput()
	{
		if(m_inputManager != 0)
		{
			m_inputManager->destroyInputObject(m_mouse);
			m_inputManager->destroyInputObject(m_keyboard);

			OIS::InputManager::destroyInputSystem(m_inputManager);
			m_inputManager = 0;
		}
	}

	bool OISInputWindow::mouseMoved(const OIS::MouseEvent &arg)
	{
		m_uiMouse->dispatchMouseMoved(DimFloat(arg.state.X.abs, arg.state.Y.abs));

		if(arg.state.Z.rel != 0)
			m_uiMouse->dispatchMouseWheeled(DimFloat(arg.state.X.abs, arg.state.Y.abs), float(arg.state.Z.rel));

		return true;
	}

	bool OISInputWindow::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
	{
		if(m_pressed[id])
			this->mouseReleased(arg, id);

		m_pressed[id] = true;
		m_uiMouse->dispatchMousePressed(DimFloat(arg.state.X.abs, arg.state.Y.abs), convertOISButton(id));
		return true;
	}

	bool OISInputWindow::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
	{
		if(!m_pressed[id])
			return true;

		m_pressed[id] = false;
		m_uiMouse->dispatchMouseReleased(DimFloat(arg.state.X.abs, arg.state.Y.abs), convertOISButton(id));
		return true;
	}

	char OISInputWindow::getChar(const OIS::KeyEvent &arg)
	{
		switch(arg.key)
		{
		case KC_NUMPAD0: return '0';
		case KC_NUMPAD1: return '1';
		case KC_NUMPAD2: return '2';
		case KC_NUMPAD3: return '3';
		case KC_NUMPAD4: return '4';
		case KC_NUMPAD5: return '5';
		case KC_NUMPAD6: return '6';
		case KC_NUMPAD7: return '7';
		case KC_NUMPAD8: return '8';
		case KC_NUMPAD9: return '9';
		}

		return arg.text;
	}

	bool OISInputWindow::keyPressed(const OIS::KeyEvent &arg)
	{
		if(arg.key == OIS::KC_ESCAPE)
			m_shutdownRequested = true;

		m_uiKeyboard->dispatchKeyPressed(static_cast<KeyCode>(arg.key), getChar(arg));
		return true;
	}

	bool OISInputWindow::keyReleased(const OIS::KeyEvent &arg)
	{
		m_uiKeyboard->dispatchKeyReleased(static_cast<KeyCode>(arg.key), getChar(arg));
		return true;
	}
}
