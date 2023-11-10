#pragma once

#include <two/gfx.h>
#include <two/geom.h>
#include <two/srlz.h>
#include <two/math.h>
#include <two/infra.h>
#include <two/type.h>




#ifndef TWO_GFX_OBJ_EXPORT
#define TWO_GFX_OBJ_EXPORT TWO_IMPORT
#endif

namespace two
{
    class ImporterOBJ;
	class ImporterPLY;
}

#ifndef TWO_MODULES
#endif

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

#ifndef TWO_MODULES
#endif

namespace two
{
	export_ class refl_ TWO_GFX_OBJ_EXPORT ImporterPLY : public Importer
	{
	public:
		constr_ ImporterPLY(GfxSystem& gfx);

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

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_MODULES
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_GFX_OBJ_EXPORT Type& type<two::ImporterOBJ>();
    export_ template <> TWO_GFX_OBJ_EXPORT Type& type<two::ImporterPLY>();
}

