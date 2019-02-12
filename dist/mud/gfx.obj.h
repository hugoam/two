#pragma once

#include <mud/gfx.h>
#include <mud/geom.h>
#include <mud/srlz.h>
#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>




#ifndef MUD_GFX_OBJ_EXPORT
#define MUD_GFX_OBJ_EXPORT MUD_IMPORT
#endif

namespace mud
{
    class ImporterOBJ;
}

#ifndef MUD_MODULES
#endif

namespace mud
{

	export_ class MUD_GFX_OBJ_EXPORT ImporterOBJ : public Importer
	{
	public:
		ImporterOBJ(GfxSystem& gfx_system);

		GfxSystem& m_gfx_system;

		virtual void import(Import& import, const string& filepath, const ImportConfig& config) override;
		virtual void import_model(Model& model, const string& filepath, const ImportConfig& config) override;
		virtual void import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config) override;
		virtual void repack(const string& filepath, const ImportConfig& config) override;
	};
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif


namespace mud
{
    // Exported types
    
    
}

