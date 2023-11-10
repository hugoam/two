#pragma once

#ifndef TWO_MODULES
#include <gfx/Importer.h>
#endif
#include <gfx-gltf/Forward.h>

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
