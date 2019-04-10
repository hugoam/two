#pragma once

#include <mud/gfx.h>
#include <mud/geom.h>
#include <mud/srlz.h>
#include <mud/gltf.h>
#include <mud/math.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>




#ifndef MUD_GFX_GLTF_EXPORT
#define MUD_GFX_GLTF_EXPORT MUD_IMPORT
#endif

namespace mud
{
	class ImporterGltf;
}

#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ class refl_ MUD_GFX_GLTF_EXPORT ImporterGltf : public Importer
	{
	public:
		constr_ ImporterGltf(GfxSystem& gfx);

		GfxSystem& m_gfx;

		meth_ virtual void import(Import& import, const string& filepath, const ImportConfig& config) override;
		meth_ virtual void import_model(Model& model, const string& filepath, const ImportConfig& config) override;
		meth_ virtual void import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config) override;
		meth_ virtual void repack(const string& filepath, const ImportConfig& config) override;
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
    
    
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<mud::ImporterGltf>();
}
