#pragma once

#ifndef MUD_MODULES
#include <gfx/Importer.h>
#endif
#include <gfx-gltf/Forward.h>

namespace mud
{
	export_ class MUD_GFX_GLTF_EXPORT ImporterGltf : public Importer
	{
	public:
		ImporterGltf(GfxSystem& gfx);

		GfxSystem& m_gfx;

		virtual void import(Import& import, const string& filepath, const ImportConfig& config) override;
		virtual void import_model(Model& model, const string& filepath, const ImportConfig& config) override;
		virtual void import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config) override;
		virtual void repack(const string& filepath, const ImportConfig& config) override;
	};
}
