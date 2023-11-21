#pragma once

#include <gfx-obj/Forward.h>

namespace two
{
	export_ class refl_ TWO_GFX_OBJ_EXPORT ImporterOBJ : public Importer
	{
	public:
		constr_ ImporterOBJ(GfxSystem& gfx);

		GfxSystem& m_gfx;

		meth_ virtual void import(Import& import, const string& filepath, const ImportConfig& config) override;
		meth_ virtual void import_model(Model& model, const string& filepath, const ImportConfig& config) override;
		meth_ virtual void import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config) override;
		meth_ virtual void repack(const string& filepath, const ImportConfig& config) override;
	};
}
