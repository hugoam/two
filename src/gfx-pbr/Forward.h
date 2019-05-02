#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>
#include <gfx/Forward.h>

#ifndef TWO_GFX_PBR_EXPORT
#define TWO_GFX_PBR_EXPORT TWO_IMPORT
#endif

namespace two
{
    enum ShaderOptionLight : unsigned int;
    enum ShaderOptionRadiance : unsigned int;
    enum ShaderOptionShadow : unsigned int;
    enum ShaderModeShadow : unsigned int;
    enum ShadowFilterMode : unsigned int;
    enum ShaderOptionBlur : unsigned int;
    enum ShaderOptionDofBlur : unsigned int;
    enum ShaderOptionGlow : unsigned int;
    enum TonemapShaderOption : unsigned int;
    enum TonemapShaderMode : unsigned int;
    enum class TonemapMode : unsigned int;
    
    
	class BlockGeometry;
    class BlockLight;
    struct ReflectionRenderer;
    struct ForwardRenderer;
	struct DeferredRenderer;
    class BlockRadiance;
    class CubeTarget;
	class CubeCamera;
    class ReflectionAtlas;
    class ReflectionProbe;
	class PassGeometry;
	class PassLights;
	class PassOpaque;
	class PassAlpha;
    class PassProbes;
    class BlockReflection;
    struct ShadowmapCube;
    class ShadowAtlas;
    struct CSMShadow;
	struct CSMSlice;
    class PassShadow;
    class PassShadowmap;
    struct ShadowRenderer;
    struct LightBounds;
    struct LightShadow;
    class BlockShadow;
    struct EffectBlurUniform;
    struct BlurKernel;
    class BlockBlur;
	struct DofParams;
    struct DofBlur;
    struct DofBlurUniform;
    class BlockDofBlur;
    struct Glow;
    struct GlowUniform;
	class BlockGI;
	class BlockGIBake;
	class BlockGITrace;
	class BlockLightmap;
    class BlockGlow;
    struct BCS;
    struct Tonemap;
    struct TonemapUniform;
    class BlockTonemap;
}
