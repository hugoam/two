
#pragma once

#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
#include <ui/Generated/Module.h>
        
#include <gfx/Generated/Forward.h>
#include <gfx/Generated/Types.h>

#include <gfx/Animated.h>
#include <gfx/Animation.h>
#include <gfx/Camera.h>
#include <gfx/Draw.h>
#include <gfx/Filter.h>
#include <gfx/Frustum.h>
#include <gfx/Generator.h>
#include <gfx/Gfx.h>
#include <gfx/GfxSystem.h>
#include <gfx/Graph.h>
#include <gfx/Item.h>
#include <gfx/Light.h>
#include <gfx/ManualRender.h>
#include <gfx/Material.h>
#include <gfx/Mesh.h>
#include <gfx/Node3.h>
#include <gfx/Particles.h>
#include <gfx/Picker.h>
#include <gfx/Pipeline.h>
#include <gfx/Prefab.h>
#include <gfx/Program.h>
#include <gfx/Renderer.h>
#include <gfx/RenderTarget.h>
#include <gfx/Scene.h>
#include <gfx/Shader.h>
#include <gfx/Shot.h>
#include <gfx/Skeleton.h>
#include <gfx/Texture.h>
#include <gfx/Uniform.h>
#include <gfx/Viewport.h>
#include <gfx/Blocks/Depth.h>
#include <gfx/Blocks/Light.h>
#include <gfx/Blocks/Particles.h>
#include <gfx/Blocks/Radiance.h>
#include <gfx/Blocks/Reflection.h>
#include <gfx/Blocks/ReflectionAtlas.h>
#include <gfx/Blocks/Shadow.h>
#include <gfx/Blocks/ShadowAtlas.h>
#include <gfx/Blocks/ShadowCSM.h>
#include <gfx/Blocks/Sky.h>
#include <gfx/Filters/Blur.h>
#include <gfx/Filters/DofBlur.h>
#include <gfx/Filters/EffectBlock.h>
#include <gfx/Filters/Glow.h>
#include <gfx/Filters/Tonemap.h>
#include <gfx/Import/ImporterGltf.h>
#include <gfx/Import/ImporterObj.h>
#include <gfx/Ui/GfxEdit.h>
#include <gfx/Ui/ParticleEdit.h>
#include <gfx/Ui/PrefabEdit.h>
#include <gfx/Widget/SpaceSheet.h>
#include <gfx/Widget/SpaceViewer.h>
#include <gfx/Widget/Viewer.h>

namespace mud
{
	class MUD_GFX_EXPORT mudgfx : public Module
	{
	private:
		mudgfx();

	public:
		static mudgfx& module() { static mudgfx instance; return instance; }
	};
}

#ifdef MUD_GFX_MODULE
extern "C"
MUD_GFX_EXPORT Module& getModule();
#endif
