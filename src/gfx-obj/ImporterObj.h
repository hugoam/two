#pragma once

#ifndef MUD_MODULES
#include <type/Type.h>
#include <gfx/Importer.h>
#endif
#include <gfx-obj/Forward.h>

#ifndef MUD_CPP_20
#include <string>
#include <map>
#include <vector>
#endif

namespace mud
{
	using string = std::string;
	using MaterialMap = std::map<string, Material*>;

	export_ class MUD_GFX_OBJ_EXPORT ImporterOBJ : public Importer
	{
	public:
		ImporterOBJ(GfxSystem& gfx_system);

		GfxSystem& m_gfx_system;

		virtual void import(Import& import, const string& path, const ImportConfig& config) override;
		virtual void import_model(Model& model, const string& path, const ImportConfig& config) override;
		virtual void import_prefab(Prefab& prefab, const string& path, const ImportConfig& config) override;
	};
}
