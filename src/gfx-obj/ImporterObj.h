#pragma once

#include <obj/Type.h>
#include <gfx/Generated/Forward.h>

#include <string>
#include <map>
#include <vector>

namespace mud
{
	using string = std::string;
	using MaterialMap = std::map<string, Material*>;

	class ImporterOBJ
	{
	public:
		ImporterOBJ(GfxSystem& gfx_system);

		GfxSystem& m_gfx_system;

		void import_material_library(const string& path, MaterialMap& materials);
		void import_model(Model& model, const string& path, const ModelConfig& config);
	};
}
