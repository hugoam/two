
#pragma once

#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
        
#include <ctx/Generated/Forward.h>
#include <ctx/Generated/Types.h>

#include <ctx/Context.h>
#include <ctx/ControlNode.h>
#include <ctx/InputDevice.h>
#include <ctx/InputDispatcher.h>
#include <ctx/InputEvent.h>
#include <ctx/KeyCode.h>

namespace mud
{
	class MUD_CTX_EXPORT mudctx : public Module
	{
	private:
		mudctx();

	public:
		static mudctx& module() { static mudctx instance; return instance; }
	};
}

#ifdef MUD_CTX_MODULE
extern "C"
MUD_CTX_EXPORT Module& getModule();
#endif
