#include <xx_three/xx_three.h>
#include <gfx-pbr/Api.h>

#include <stl/vector.hpp>

static string fxaa_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"
			
	"#include <filter.sh>\n"
			
	"void main() {\n"
	"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";


static string fxaa_fragment =

	"$input v_uv0\n"
		
	"#include <filter.sh>\n"
	"#include <tonemap.sh>\n"
		
	"#define s_diffuse s_source_0\n"
		
	"// FXAA 3.11 implementation by NVIDIA, ported to WebGL by Agost Biro (biro@archilogic.com)\n"
	"//----------------------------------------------------------------------------------\n"
		
	"#define FXAA_QUALITY_PRESET 12\n"
		
	"#ifndef FXAA_DISCARD\n"
	"    //\n"
	"    // Only valid for PC OpenGL currently.\n"
	"    //\n"
	"    // 1 = Use discard on pixels which don't need AA.\n"
	"    //     For APIs which enable concurrent TEX+ROP from same surface.\n"
	"    // 0 = Return unchanged color on pixels which don't need AA.\n"
	"    //\n"
	"    #define FXAA_DISCARD 0\n"
	"#endif\n"
		
	"#ifndef FXAA_FAST_PIXEL_OFFSET\n"
	"    //\n"
	"    // Used for GLSL 120 only.\n"
	"    //\n"
	"    // 1 = GL API supports fast pixel offsets\n"
	"    // 0 = do not use fast pixel offsets\n"
	"    //\n"
	"    #ifdef GL_EXT_gpu_shader4\n"
	"        #define FXAA_FAST_PIXEL_OFFSET 1\n"
	"    #endif\n"
	"    #ifdef GL_NV_gpu_shader5\n"
	"        #define FXAA_FAST_PIXEL_OFFSET 1\n"
	"    #endif\n"
	"    #ifdef GL_ARB_gpu_shader5\n"
	"        #define FXAA_FAST_PIXEL_OFFSET 1\n"
	"    #endif\n"
	"    #ifndef FXAA_FAST_PIXEL_OFFSET\n"
	"        #define FXAA_FAST_PIXEL_OFFSET 0\n"
	"    #endif\n"
	"#endif\n"
		
	"#ifndef FXAA_GATHER4_ALPHA\n"
	"    //\n"
	"    // 1 = API supports gather4 on alpha channel.\n"
	"    // 0 = API does not support gather4 on alpha channel.\n"
	"    //\n"
	"    #if (FXAA_HLSL_5 == 1)\n"
	"        #define FXAA_GATHER4_ALPHA 1\n"
	"    #endif\n"
	"    #ifdef GL_ARB_gpu_shader5\n"
	"        #define FXAA_GATHER4_ALPHA 1\n"
	"    #endif\n"
	"    #ifdef GL_NV_gpu_shader5\n"
	"        #define FXAA_GATHER4_ALPHA 1\n"
	"    #endif\n"
	"    #ifndef FXAA_GATHER4_ALPHA\n"
	"        #define FXAA_GATHER4_ALPHA 0\n"
	"    #endif\n"
	"#endif\n"
		
		
	"// FXAA QUALITY - TUNING KNOBS\n"
	"//\n"
	"// OPTIONS\n"
	"// -----------------------------------------------------------------------\n"
	"// 10 to 15 - default medium dither (10=fastest, 15=highest quality)\n"
	"// 20 to 29 - less dither, more expensive (20=fastest, 29=highest quality)\n"
	"// 39       - no dither, very expensive\n"
	"//\n"
	"// NOTES\n"
	"// -----------------------------------------------------------------------\n"
	"// 12 = slightly faster then FXAA 3.9 and higher edge quality (default)\n"
	"// 13 = about same speed as FXAA 3.9 and better than 12\n"
	"// 23 = closest to FXAA 3.9 visually and performance wise\n"
	"//  _ = the lowest digit is directly related to performance\n"
	"// _  = the highest digit is directly related to style\n"
	"//\n"
	"#ifndef FXAA_QUALITY_PRESET\n"
	"    #define FXAA_QUALITY_PRESET 12\n"
	"#endif\n"
		
		
	"// FXAA QUALITY - PRESETS\n"
		
	"// FXAA QUALITY - MEDIUM DITHER PRESETS\n"
		
	"#if (FXAA_QUALITY_PRESET == 10)\n"
	"    #define FXAA_QUALITY_PS 3\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 3)) 1.5, 3.0, 12.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 11)\n"
	"    #define FXAA_QUALITY_PS 4\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 4)) 1.0, 1.5, 3.0, 12.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 12)\n"
	"    #define FXAA_QUALITY_PS 5\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 5)) 1.0, 1.5, 2.0, 4.0, 12.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 13)\n"
	"    #define FXAA_QUALITY_PS 6\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 6)) 1.0, 1.5, 2.0, 2.0, 4.0, 12.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 14)\n"
	"    #define FXAA_QUALITY_PS 7\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 7)) 1.0, 1.5, 2.0, 2.0, 2.0, 4.0, 12.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 15)\n"
	"    #define FXAA_QUALITY_PS 8\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 8)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 4.0, 12.0 ARRAY_END();\n"
		
	"// FXAA QUALITY - LOW DITHER PRESETS\n"
	"#elif (FXAA_QUALITY_PRESET == 20)\n"
	"    #define FXAA_QUALITY_PS 3\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 3)) 1.5, 2.0, 8.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 21)\n"
	"    #define FXAA_QUALITY_PS 4\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 4)) 1.0, 1.5, 2.0, 8.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 22)\n"
	"    #define FXAA_QUALITY_PS 5\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 5)) 1.0, 1.5, 2.0, 2.0, 8.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 23)\n"
	"    #define FXAA_QUALITY_PS 6\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 6)) 1.0, 1.5, 2.0, 2.0, 2.0, 8.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 24)\n"
	"    #define FXAA_QUALITY_PS 7\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 7)) 1.0, 1.5, 2.0, 2.0, 2.0, 3.0, 8.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 25)\n"
	"    #define FXAA_QUALITY_PS 8\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 8)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 26)\n"
	"    #define FXAA_QUALITY_PS 9\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 9)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 27)\n"
	"    #define FXAA_QUALITY_PS 10\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 10)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 28)\n"
	"    #define FXAA_QUALITY_PS 11\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 11)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();\n"
	"#elif (FXAA_QUALITY_PRESET == 29)\n"
	"    #define FXAA_QUALITY_PS 12\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 12)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();\n"
		
	"// FXAA QUALITY - EXTREME QUALITY\n"
		
	"#elif (FXAA_QUALITY_PRESET == 39)\n"
	"    #define FXAA_QUALITY_PS 12\n"
	"    CONST(ARRAY_BEGIN(float, c_kernel, 12)) 1.0, 1.0, 1.0, 1.0, 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();\n"
	"#endif\n"
		
		
	//"#if GLSL\n"
	//"    #define FxaaDiscard discard\n"
	//"#else\n"
	//"    #define FxaaDiscard clip(-1)\n"
	//"#endif\n"
	//
	// GLSL
	//"#define FxaaTexAlpha4(t, p) textureGather(t, p, 3)\n"
	//"#define FxaaTexOffAlpha4(t, p, o) textureGatherOffset(t, p, o, 3)\n"
	// HLSL
	//"#define FxaaTexAlpha4(t, p) t.tex.GatherAlpha(t.smpl, p)\n"
	//"#define FxaaTexOffAlpha4(t, p, o) t.tex.GatherAlpha(t.smpl, p, o)\n"
		
	"#if (FXAA_FAST_PIXEL_OFFSET == 1)\n"
	"    #define FxaaTexOff(t, p, o, r) texture2DLodOffset(t, p, 0.0, o)\n"
	"#else\n"
	"    #define FxaaTexOff(t, p, o, r) texture2DLod(t, p + (o * r), 0.0)\n"
	"#endif\n"
		
	//"float FxaaLuma(vec4 rgba) { return rgba.w; }\n"
	"float FxaaLuma(vec4 rgba) { return luma(rgba.rgb); }\n"
		
	"// FXAA3 QUALITY - PC\n"
		
	"vec4 FxaaPixelShader(\n"
	"    //\n"
	"    // Use noperspective interpolation here (turn off perspective interpolation).\n"
	"    // {xy} = center of pixel\n"
	"    vec2 pos,\n"
	"    //\n"
	"    // Input color texture.\n"
	"    // {rgb_} = color in linear or perceptual color space\n"
	"    // {___a} = luma in perceptual color space (not linear)\n"
	"    sampler2D tex,\n"
	"    //\n"
	"    // Only used on FXAA Quality.\n"
	"    // This must be from a constant/uniform.\n"
	"    // {x_} = 1.0/screenWidthInPixels\n"
	"    // {_y} = 1.0/screenHeightInPixels\n"
	"    vec2 fxaaQualityRcpFrame,\n"
	"    //\n"
	"    // Only used on FXAA Quality.\n"
	"    // Choose the amount of sub-pixel aliasing removal.\n"
	"    // This can effect sharpness.\n"
	"    //   1.00 - upper limit (softer)\n"
	"    //   0.75 - default amount of filtering\n"
	"    //   0.50 - lower limit (sharper, less sub-pixel aliasing removal)\n"
	"    //   0.25 - almost off\n"
	"    //   0.00 - completely off\n"
	"    float fxaaQualitySubpix,\n"
	"    //\n"
	"    // Only used on FXAA Quality.\n"
	"    // The minimum amount of local contrast required to apply algorithm.\n"
	"    //   0.333 - too little (faster)\n"
	"    //   0.250 - low quality\n"
	"    //   0.166 - default\n"
	"    //   0.125 - high quality\n"
	"    //   0.063 - overkill (slower)\n"
	"    float fxaaQualityEdgeThreshold,\n"
	"    //\n"
	"    // Only used on FXAA Quality.\n"
	"    // Trims the algorithm from processing darks.\n"
	"    //   0.0833 - upper limit (default, the start of visible unfiltered edges)\n"
	"    //   0.0625 - high quality (faster)\n"
	"    //   0.0312 - visible limit (slower)\n"
	"    float fxaaQualityEdgeThresholdMin\n"
	"    //\n"
	") {\n"
		
	"    vec2 posM = pos;\n"
	"    #if (FXAA_GATHER4_ALPHA == 1)\n"
	"        #if (FXAA_DISCARD == 0)\n"
	"            vec4 rgbyM = texture2DLod(tex, posM, 0.0);\n"
	"            #define lumaM rgbyM.w\n"
	"        #endif\n"
	"            vec4 luma4A = FxaaTexAlpha4(tex, posM);\n"
	"            vec4 luma4B = FxaaTexOffAlpha4(tex, posM, ivec2(-1, -1));\n"
	"        #if (FXAA_DISCARD == 1)\n"
	"            #define lumaM luma4A.w\n"
	"        #endif\n"
	"        #define lumaE luma4A.z\n"
	"        #define lumaS luma4A.x\n"
	"        #define lumaSE luma4A.y\n"
	"        #define lumaNW luma4B.w\n"
	"        #define lumaN luma4B.z\n"
	"        #define lumaW luma4B.x\n"
	"    #else\n"
	"        vec4 rgbyM = texture2DLod(tex, posM, 0.0);\n"
	"        #define lumaM rgbyM.w\n"
	"        float lumaS = FxaaLuma(FxaaTexOff(tex, posM, ivec2(0, 1), fxaaQualityRcpFrame.xy));\n"
	"        float lumaE = FxaaLuma(FxaaTexOff(tex, posM, ivec2(1, 0), fxaaQualityRcpFrame.xy));\n"
	"        float lumaN = FxaaLuma(FxaaTexOff(tex, posM, ivec2(0,-1), fxaaQualityRcpFrame.xy));\n"
	"        float lumaW = FxaaLuma(FxaaTexOff(tex, posM, ivec2(-1, 0), fxaaQualityRcpFrame.xy));\n"
	"    #endif\n"
		
	"    float maxSM = max(lumaS, lumaM);\n"
	"    float minSM = min(lumaS, lumaM);\n"
	"    float maxESM = max(lumaE, maxSM);\n"
	"    float minESM = min(lumaE, minSM);\n"
	"    float maxWN = max(lumaN, lumaW);\n"
	"    float minWN = min(lumaN, lumaW);\n"
	"    float rangeMax = max(maxWN, maxESM);\n"
	"    float rangeMin = min(minWN, minESM);\n"
	"    float rangeMaxScaled = rangeMax * fxaaQualityEdgeThreshold;\n"
	"    float range = rangeMax - rangeMin;\n"
	"    float rangeMaxClamped = max(fxaaQualityEdgeThresholdMin, rangeMaxScaled);\n"
	"    bool earlyExit = range < rangeMaxClamped;\n"
		
	"    if(earlyExit)\n"
	"        #if (FXAA_DISCARD == 1)\n"
	"            FxaaDiscard;\n"
	"        #else\n"
	"            return rgbyM;\n"
	"        #endif\n"
		
	"    #if (FXAA_GATHER4_ALPHA == 0)\n"
	"        float lumaNW = FxaaLuma(FxaaTexOff(tex, posM, ivec2(-1,-1), fxaaQualityRcpFrame.xy));\n"
	"        float lumaSE = FxaaLuma(FxaaTexOff(tex, posM, ivec2(1, 1), fxaaQualityRcpFrame.xy));\n"
	"        float lumaNE = FxaaLuma(FxaaTexOff(tex, posM, ivec2(1,-1), fxaaQualityRcpFrame.xy));\n"
	"        float lumaSW = FxaaLuma(FxaaTexOff(tex, posM, ivec2(-1, 1), fxaaQualityRcpFrame.xy));\n"
	"    #else\n"
	"        float lumaNE = FxaaLuma(FxaaTexOff(tex, posM, ivec2(1, -1), fxaaQualityRcpFrame.xy));\n"
	"        float lumaSW = FxaaLuma(FxaaTexOff(tex, posM, ivec2(-1,  1), fxaaQualityRcpFrame.xy));\n"
	"    #endif\n"
		
	"    float lumaNS = lumaN + lumaS;\n"
	"    float lumaWE = lumaW + lumaE;\n"
	"    float subpixRcpRange = 1.0/range;\n"
	"    float subpixNSWE = lumaNS + lumaWE;\n"
	"    float edgeHorz1 = (-2.0 * lumaM) + lumaNS;\n"
	"    float edgeVert1 = (-2.0 * lumaM) + lumaWE;\n"
		
	"    float lumaNESE = lumaNE + lumaSE;\n"
	"    float lumaNWNE = lumaNW + lumaNE;\n"
	"    float edgeHorz2 = (-2.0 * lumaE) + lumaNESE;\n"
	"    float edgeVert2 = (-2.0 * lumaN) + lumaNWNE;\n"
		
	"    float lumaNWSW = lumaNW + lumaSW;\n"
	"    float lumaSWSE = lumaSW + lumaSE;\n"
	"    float edgeHorz4 = (abs(edgeHorz1) * 2.0) + abs(edgeHorz2);\n"
	"    float edgeVert4 = (abs(edgeVert1) * 2.0) + abs(edgeVert2);\n"
	"    float edgeHorz3 = (-2.0 * lumaW) + lumaNWSW;\n"
	"    float edgeVert3 = (-2.0 * lumaS) + lumaSWSE;\n"
	"    float edgeHorz = abs(edgeHorz3) + edgeHorz4;\n"
	"    float edgeVert = abs(edgeVert3) + edgeVert4;\n"
		
	"    float subpixNWSWNESE = lumaNWSW + lumaNESE;\n"
	"    float lengthSign = fxaaQualityRcpFrame.x;\n"
	"    bool horzSpan = edgeHorz >= edgeVert;\n"
	"    float subpixA = subpixNSWE * 2.0 + subpixNWSWNESE;\n"
		
	"    if(!horzSpan) lumaN = lumaW;\n"
	"    if(!horzSpan) lumaS = lumaE;\n"
	"    if(horzSpan) lengthSign = fxaaQualityRcpFrame.y;\n"
	"    float subpixB = (subpixA * (1.0/12.0)) - lumaM;\n"
		
	"    float gradientN = lumaN - lumaM;\n"
	"    float gradientS = lumaS - lumaM;\n"
	"    float lumaNN = lumaN + lumaM;\n"
	"    float lumaSS = lumaS + lumaM;\n"
	"    bool pairN = abs(gradientN) >= abs(gradientS);\n"
	"    float gradient = max(abs(gradientN), abs(gradientS));\n"
	"    if(pairN) lengthSign = -lengthSign;\n"
	"    float subpixC = saturate(abs(subpixB) * subpixRcpRange);\n"
		
	"    vec2 posB = posM;\n"
	"    vec2 offNP;\n"
	"    offNP.x = (!horzSpan) ? 0.0 : fxaaQualityRcpFrame.x;\n"
	"    offNP.y = (horzSpan) ? 0.0 : fxaaQualityRcpFrame.y;\n"
	"    if(!horzSpan) posB.x += lengthSign * 0.5;\n"
	"    if(horzSpan) posB.y += lengthSign * 0.5;\n"
		
	"    vec2 posN;\n"
	"    posN.x = posB.x - offNP.x * c_kernel[0];\n"
	"    posN.y = posB.y - offNP.y * c_kernel[0];\n"
	"    vec2 posP;\n"
	"    posP.x = posB.x + offNP.x * c_kernel[0];\n"
	"    posP.y = posB.y + offNP.y * c_kernel[0];\n"
	"    float subpixD = ((-2.0)*subpixC) + 3.0;\n"
	"    float lumaEndN = FxaaLuma(texture2DLod(tex, posN, 0.0));\n"
	"    float subpixE = subpixC * subpixC;\n"
	"    float lumaEndP = FxaaLuma(texture2DLod(tex, posP, 0.0));\n"
		
	"    if(!pairN) lumaNN = lumaSS;\n"
	"    float gradientScaled = gradient * 1.0/4.0;\n"
	"    float lumaMM = lumaM - lumaNN * 0.5;\n"
	"    float subpixF = subpixD * subpixE;\n"
	"    bool lumaMLTZero = lumaMM < 0.0;\n"
		
	"    lumaEndN -= lumaNN * 0.5;\n"
	"    lumaEndP -= lumaNN * 0.5;\n"
	"    bool doneN = abs(lumaEndN) >= gradientScaled;\n"
	"    bool doneP = abs(lumaEndP) >= gradientScaled;\n"
	"    if(!doneN) posN.x -= offNP.x * c_kernel[1];\n"
	"    if(!doneN) posN.y -= offNP.y * c_kernel[1];\n"
	"    bool doneNP = (!doneN) || (!doneP);\n"
	"    if(!doneP) posP.x += offNP.x * c_kernel[1];\n"
	"    if(!doneP) posP.y += offNP.y * c_kernel[1];\n"
		
	"	 for(int i = 1; i < int(FXAA_QUALITY_PS); i++)\n"
	"    {\n"
	"        if(!doneNP) break;\n"
	"        if(!doneN) lumaEndN = FxaaLuma(texture2DLod(tex, posN.xy, 0.0));\n"
	"        if(!doneP) lumaEndP = FxaaLuma(texture2DLod(tex, posP.xy, 0.0));\n"
	"        if(!doneN) lumaEndN = lumaEndN - lumaNN * 0.5;\n"
	"        if(!doneP) lumaEndP = lumaEndP - lumaNN * 0.5;\n"
	"        doneN = abs(lumaEndN) >= gradientScaled;\n"
	"        doneP = abs(lumaEndP) >= gradientScaled;\n"
	"        if(!doneN) posN.x -= offNP.x * c_kernel[i];\n"
	"        if(!doneN) posN.y -= offNP.y * c_kernel[i];\n"
	"        doneNP = (!doneN) || (!doneP);\n"
	"        if(!doneP) posP.x += offNP.x * c_kernel[i];\n"
	"        if(!doneP) posP.y += offNP.y * c_kernel[i];\n"
	"    }\n"
		
	"    float dstN = posM.x - posN.x;\n"
	"    float dstP = posP.x - posM.x;\n"
	"    if(!horzSpan) dstN = posM.y - posN.y;\n"
	"    if(!horzSpan) dstP = posP.y - posM.y;\n"
		
	"    bool goodSpanN = (lumaEndN < 0.0) != lumaMLTZero;\n"
	"    float spanLength = (dstP + dstN);\n"
	"    bool goodSpanP = (lumaEndP < 0.0) != lumaMLTZero;\n"
	"    float spanLengthRcp = 1.0/spanLength;\n"
		
	"    bool directionN = dstN < dstP;\n"
	"    float dst = min(dstN, dstP);\n"
	"    bool goodSpan = directionN ? goodSpanN : goodSpanP;\n"
	"    float subpixG = subpixF * subpixF;\n"
	"    float pixelOffset = (dst * (-spanLengthRcp)) + 0.5;\n"
	"    float subpixH = subpixG * fxaaQualitySubpix;\n"
		
	"    float pixelOffsetGood = goodSpan ? pixelOffset : 0.0;\n"
	"    float pixelOffsetSubpix = max(pixelOffsetGood, subpixH);\n"
	"    if(!horzSpan) posM.x += pixelOffsetSubpix * lengthSign;\n"
	"    if(horzSpan) posM.y += pixelOffsetSubpix * lengthSign;\n"
	"    #if (FXAA_DISCARD == 1)\n"
	"        return texture2DLod(tex, posM, 0.0);\n"
	"    #else\n"
	"        return vec4(texture2DLod(tex, posM, 0.0).xyz, lumaM);\n"
	"    #endif\n"
	"}\n"
		
	"void main() {\n"
	"    gl_FragColor = FxaaPixelShader(\n"
	"        v_uv0,\n"
	"        s_diffuse,\n"
	"        u_pixel_size,\n"
	"        0.75,\n"
	"        0.166,\n"
	"        0.0833\n"
	"  );\n"
		
	"    // TODO avoid querying texture twice for same texel\n"
	"    gl_FragColor.a = texture2D(s_diffuse, v_uv0).a;\n"
	"}\n";

void pass_fxaa(GfxSystem& gfx, Render& render)
{
	static Program& program = gfx.programs().fetch("fxaa");

	Pass pass = render.next_pass("bokeh", PassType::PostProcess);

	gfx.m_filter->source0(render.m_target->m_diffuse);

	gfx.m_filter->quad(pass, render.m_target->m_post.swap(), program);

	gfx.m_copy->quad(render.composite_pass("flip"), *render.m_fbo, render.m_target->m_post.last());
}

EX(xx_post_fxaa)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	static Program& program = app.m_gfx.programs().create("fxaa");
	if(init)
	{
		program.set_source(ShaderType::Vertex, fxaa_vertex);
		program.set_source(ShaderType::Fragment, fxaa_fragment);
	}

	static Node3* node = nullptr;
	struct Node { vec3 p; vec3 a; vec3 s; Node3* node; };
	static vector<Node> nodes;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 45.f; camera.m_near = 1.f; camera.m_far = 2000.f;
		camera.m_eye.z = 500.f;

		viewer.m_viewport.m_clear_colour = Colour(1.f);
		//scene.background = new THREE.Color(0xffffff);

		Zone& env = scene.m_env;
		env.m_fog = { true, 1.f, rgb(0xcccccc), true, 100.f, 1500.f };
		env.m_skylight = { true, 1.f / c_pi, vec3(0.f, 1000.f, 0.f), vec3(0.f), rgb(0x444444), rgb(0xffffff) };

		quat dir = look_dir(vec3(-3.f, 1.f, -1.f)); // -3000, 1000, -1000
		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f), dir));
		gfx::lights(scene).add(Light(n, LightType::Direct, false, rgb(0xffffff), 0.8f));

		Node3& group = gfx::nodes(scene).add(Node3());
		node = &group;

		//Model& geometry = app.m_gfx.shape(Sphere(10.f));
		Model& geometry = app.m_gfx.shape(Tetraedr(10.f));

		Program& three = *app.m_gfx.programs().file("pbr/three");

		Material& material = app.m_gfx.materials().create("fxaa", [&](Material& m) {
			m.m_program = &three;
			m.m_base.m_flat_shaded = true;
			m.m_pbr.m_albedo = rgb(0xee0808);
		});

		nodes.clear();
		for(size_t i = 0; i < 100; i++)
		{
			vec3 p = vec3(randf(), randf(), randf()) * 500.f - 250.f;
			vec3 a = vec3(randf(), randf(), randf()) * c_pi;
			vec3 s = vec3(randf()) * 2.f + 1.f;

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a), s));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
			nodes.push_back({ p, a, s, &n });
		}

		auto render = [](GfxSystem& gfx, Render& render)
		{
			begin_pbr_render(gfx, render);

			pass_clear(gfx, render);
			pass_opaque(gfx, render);
			pass_fxaa(gfx, render);
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);
	}

	// viewport 0 : use fxaa render
	// viewport 1 : use normal render

	static vec3 angles = vec3(0.f);
	angles.y += app.m_gfx.m_delta_time * 0.1f;

	node->apply(vec3(0.f), quat(angles));
	for(Node& n : nodes)
	{
		n.node->derive(*node, n.p, quat(n.a), n.s);
	}
}
