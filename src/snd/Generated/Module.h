
#pragma once

#include <obj/System/System.h>

#include <obj/Generated/Module.h>
        
#include <snd/Generated/Forward.h>
#include <snd/Generated/Types.h>

#include <snd/Generator.h>
#include <snd/OggFileBuffer.h>
#include <snd/SharedBuffer.h>
#include <snd/Sound.h>
#include <snd/SoundFileBuffer.h>
#include <snd/SoundImplementer.h>
#include <snd/SoundListener.h>
#include <snd/SoundManager.h>
#include <snd/StaticSound.h>
#include <snd/StreamSound.h>

namespace mud
{
	class MUD_SND_EXPORT mudsnd : public Module
	{
	private:
		mudsnd();

	public:
		static mudsnd& module() { static mudsnd instance; return instance; }
	};
}

#ifdef MUD_SND_MODULE
extern "C"
MUD_SND_EXPORT Module& getModule();
#endif
