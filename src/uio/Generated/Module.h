
#pragma once

#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <lang/Generated/Module.h>
#include <ui/Generated/Module.h>
        
#include <uio/Generated/Forward.h>
#include <uio/Generated/Types.h>

#include <uio/Dropper.h>
#include <uio/Unode.h>
#include <uio/Edit/Canvas.h>
#include <uio/Edit/Indexer.h>
#include <uio/Edit/Injector.h>
#include <uio/Edit/Inspector.h>
#include <uio/Edit/Method.h>
#include <uio/Edit/Reflection.h>
#include <uio/Edit/Script.h>
#include <uio/Edit/Section.h>
#include <uio/Edit/Structure.h>
#include <uio/Edit/UiEdit.h>
#include <uio/Edit/Value.h>

namespace mud
{
	class MUD_UIO_EXPORT muduio : public Module
	{
	private:
		muduio();

	public:
		static muduio& module() { static muduio instance; return instance; }
	};
}

#ifdef MUD_UIO_MODULE
extern "C"
MUD_UIO_EXPORT Module& getModule();
#endif
