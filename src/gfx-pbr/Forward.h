#pragma once

#include <infra/Config.h>

#ifndef TWO_MODULES
#include <infra/Forward.h>
#include <type/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>
#include <gfx/Forward.h>
#endif

#ifndef TWO_GFX_PBR_EXPORT
#define TWO_GFX_PBR_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum ShaderOptionLight : unsigned int;
    export_ enum ShaderOptionRadiance : unsigned int;
    export_ enum ShaderOptionShadow : unsigned int;
    export_ enum ShaderModeShadow : unsigned int;
    export_ enum ShadowFilterMode : unsigned int;
    export_ enum ShaderOptionBlur : unsigned int;
    export_ enum ShaderOptionDofBlur : unsigned int;
    export_ enum ShaderOptionGlow : unsigned int;
    export_ enum TonemapShaderOption : unsigned int;
    export_ enum TonemapShaderMode : unsigned int;
    export_ enum class TonemapMode : unsigned int;
    
    
	export_ class BlockGeometry;
    export_ class BlockLight;
    export_ struct ReflectionRenderer;
    export_ struct ForwardRenderer;
	export_ struct DeferredRenderer;
    export_ class BlockRadiance;
    export_ class CubeTarget;
	export_ class CubeCamera;
    export_ class ReflectionAtlas;
    export_ class ReflectionProbe;
	export_ class PassGeometry;
	export_ class PassLights;
	export_ class PassOpaque;
	export_ class PassAlpha;
    export_ class PassProbes;
    export_ class BlockReflection;
    export_ struct ShadowmapCube;
    export_ class ShadowAtlas;
    export_ struct CSMShadow;
	export_ struct CSMSlice;
    export_ class PassShadow;
    export_ class PassShadowmap;
    export_ struct ShadowRenderer;
    export_ struct LightBounds;
    export_ struct LightShadow;
    export_ class BlockShadow;
    export_ struct EffectBlurUniform;
    export_ struct BlurKernel;
    export_ class BlockBlur;
	export_ struct DofParams;
    export_ struct DofBlur;
    export_ struct DofBlurUniform;
    export_ class BlockDofBlur;
    export_ struct Glow;
    export_ struct GlowUniform;
	export_ class BlockGI;
	export_ class BlockGIBake;
	export_ class BlockGITrace;
	export_ class BlockLightmap;
    export_ class BlockGlow;
    export_ struct BCS;
    export_ struct Tonemap;
    export_ struct TonemapUniform;
    export_ class BlockTonemap;
    export_ class GIProbe;
    export_ class ReflectionProbe;
    export_ class Lightmap;
    export_ class LightmapAtlas;
    export_ class LightmapItem;
    export_ class PBRShot;
}
