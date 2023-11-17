#pragma once

#include <two/infra.h>
#include <two/type.h>



#ifndef TWO_GFX_GLTF_EXPORT
#define TWO_GFX_GLTF_EXPORT TWO_IMPORT
#endif

namespace two
{
	class ImporterGltf;
}


namespace two
{
	export_ class refl_ TWO_GFX_GLTF_EXPORT ImporterGltf : public Importer
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


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_GFX_GLTF_EXPORT Type& type<two::ImporterGltf>();
}
