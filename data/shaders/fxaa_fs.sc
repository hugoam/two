$input v_uv0
#include <filter.sh>
#include <tonemap.sh>
#define s_diffuse s_source_0
// FXAA 3.11 implementation by NVIDIA, ported to WebGL by Agost Biro (biro@archilogic.com)
//----------------------------------------------------------------------------------
#define FXAA_QUALITY_PRESET 12
#ifndef FXAA_DISCARD
    //
    // Only valid for PC OpenGL currently.
    //
    // 1 = Use discard on pixels which don't need AA.
    //     For APIs which enable concurrent TEX+ROP from same surface.
    // 0 = Return unchanged color on pixels which don't need AA.
    //
    #define FXAA_DISCARD 0
#endif
#ifndef FXAA_FAST_PIXEL_OFFSET
    //
    // Used for GLSL 120 only.
    //
    // 1 = GL API supports fast pixel offsets
    // 0 = do not use fast pixel offsets
    //
    #ifdef GL_EXT_gpu_shader4
        #define FXAA_FAST_PIXEL_OFFSET 1
    #endif
    #ifdef GL_NV_gpu_shader5
        #define FXAA_FAST_PIXEL_OFFSET 1
    #endif
    #ifdef GL_ARB_gpu_shader5
        #define FXAA_FAST_PIXEL_OFFSET 1
    #endif
    #ifndef FXAA_FAST_PIXEL_OFFSET
        #define FXAA_FAST_PIXEL_OFFSET 0
    #endif
#endif
#ifndef FXAA_GATHER4_ALPHA
    //
    // 1 = API supports gather4 on alpha channel.
    // 0 = API does not support gather4 on alpha channel.
    //
    #if (FXAA_HLSL_5 == 1)
        #define FXAA_GATHER4_ALPHA 1
    #endif
    #ifdef GL_ARB_gpu_shader5
        #define FXAA_GATHER4_ALPHA 1
    #endif
    #ifdef GL_NV_gpu_shader5
        #define FXAA_GATHER4_ALPHA 1
    #endif
    #ifndef FXAA_GATHER4_ALPHA
        #define FXAA_GATHER4_ALPHA 0
    #endif
#endif
// FXAA QUALITY - TUNING KNOBS
//
// OPTIONS
// -----------------------------------------------------------------------
// 10 to 15 - default medium dither (10=fastest, 15=highest quality)
// 20 to 29 - less dither, more expensive (20=fastest, 29=highest quality)
// 39       - no dither, very expensive
//
// NOTES
// -----------------------------------------------------------------------
// 12 = slightly faster then FXAA 3.9 and higher edge quality (default)
// 13 = about same speed as FXAA 3.9 and better than 12
// 23 = closest to FXAA 3.9 visually and performance wise
//  _ = the lowest digit is directly related to performance
// _  = the highest digit is directly related to style
//
#ifndef FXAA_QUALITY_PRESET
    #define FXAA_QUALITY_PRESET 12
#endif
// FXAA QUALITY - PRESETS
// FXAA QUALITY - MEDIUM DITHER PRESETS
#if (FXAA_QUALITY_PRESET == 10)
    #define FXAA_QUALITY_PS 3
    CONST(ARRAY_BEGIN(float, c_kernel, 3)) 1.5, 3.0, 12.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 11)
    #define FXAA_QUALITY_PS 4
    CONST(ARRAY_BEGIN(float, c_kernel, 4)) 1.0, 1.5, 3.0, 12.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 12)
    #define FXAA_QUALITY_PS 5
    CONST(ARRAY_BEGIN(float, c_kernel, 5)) 1.0, 1.5, 2.0, 4.0, 12.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 13)
    #define FXAA_QUALITY_PS 6
    CONST(ARRAY_BEGIN(float, c_kernel, 6)) 1.0, 1.5, 2.0, 2.0, 4.0, 12.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 14)
    #define FXAA_QUALITY_PS 7
    CONST(ARRAY_BEGIN(float, c_kernel, 7)) 1.0, 1.5, 2.0, 2.0, 2.0, 4.0, 12.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 15)
    #define FXAA_QUALITY_PS 8
    CONST(ARRAY_BEGIN(float, c_kernel, 8)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 4.0, 12.0 ARRAY_END();
// FXAA QUALITY - LOW DITHER PRESETS
#elif (FXAA_QUALITY_PRESET == 20)
    #define FXAA_QUALITY_PS 3
    CONST(ARRAY_BEGIN(float, c_kernel, 3)) 1.5, 2.0, 8.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 21)
    #define FXAA_QUALITY_PS 4
    CONST(ARRAY_BEGIN(float, c_kernel, 4)) 1.0, 1.5, 2.0, 8.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 22)
    #define FXAA_QUALITY_PS 5
    CONST(ARRAY_BEGIN(float, c_kernel, 5)) 1.0, 1.5, 2.0, 2.0, 8.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 23)
    #define FXAA_QUALITY_PS 6
    CONST(ARRAY_BEGIN(float, c_kernel, 6)) 1.0, 1.5, 2.0, 2.0, 2.0, 8.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 24)
    #define FXAA_QUALITY_PS 7
    CONST(ARRAY_BEGIN(float, c_kernel, 7)) 1.0, 1.5, 2.0, 2.0, 2.0, 3.0, 8.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 25)
    #define FXAA_QUALITY_PS 8
    CONST(ARRAY_BEGIN(float, c_kernel, 8)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 26)
    #define FXAA_QUALITY_PS 9
    CONST(ARRAY_BEGIN(float, c_kernel, 9)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 27)
    #define FXAA_QUALITY_PS 10
    CONST(ARRAY_BEGIN(float, c_kernel, 10)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 28)
    #define FXAA_QUALITY_PS 11
    CONST(ARRAY_BEGIN(float, c_kernel, 11)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();
#elif (FXAA_QUALITY_PRESET == 29)
    #define FXAA_QUALITY_PS 12
    CONST(ARRAY_BEGIN(float, c_kernel, 12)) 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();
// FXAA QUALITY - EXTREME QUALITY
#elif (FXAA_QUALITY_PRESET == 39)
    #define FXAA_QUALITY_PS 12
    CONST(ARRAY_BEGIN(float, c_kernel, 12)) 1.0, 1.0, 1.0, 1.0, 1.0, 1.5, 2.0, 2.0, 2.0, 2.0, 4.0, 8.0 ARRAY_END();
#endif
#if (FXAA_FAST_PIXEL_OFFSET == 1)
    #define FxaaTexOff(t, p, o, r) texture2DLodOffset(t, p, 0.0, o)
#else
    #define FxaaTexOff(t, p, o, r) texture2DLod(t, p + (o * r), 0.0)
#endif
float FxaaLuma(vec4 rgba) { return luma(rgba.rgb); }
// FXAA3 QUALITY - PC
vec4 FxaaPixelShader(
    //
    // Use noperspective interpolation here (turn off perspective interpolation).
    // {xy} = center of pixel
    vec2 pos,
    //
    // Input color texture.
    // {rgb_} = color in linear or perceptual color space
    // {___a} = luma in perceptual color space (not linear)
    sampler2D tex,
    //
    // Only used on FXAA Quality.
    // This must be from a constant/uniform.
    // {x_} = 1.0/screenWidthInPixels
    // {_y} = 1.0/screenHeightInPixels
    vec2 fxaaQualityRcpFrame,
    //
    // Only used on FXAA Quality.
    // Choose the amount of sub-pixel aliasing removal.
    // This can effect sharpness.
    //   1.00 - upper limit (softer)
    //   0.75 - default amount of filtering
    //   0.50 - lower limit (sharper, less sub-pixel aliasing removal)
    //   0.25 - almost off
    //   0.00 - completely off
    float fxaaQualitySubpix,
    //
    // Only used on FXAA Quality.
    // The minimum amount of local contrast required to apply algorithm.
    //   0.333 - too little (faster)
    //   0.250 - low quality
    //   0.166 - default
    //   0.125 - high quality
    //   0.063 - overkill (slower)
    float fxaaQualityEdgeThreshold,
    //
    // Only used on FXAA Quality.
    // Trims the algorithm from processing darks.
    //   0.0833 - upper limit (default, the start of visible unfiltered edges)
    //   0.0625 - high quality (faster)
    //   0.0312 - visible limit (slower)
    float fxaaQualityEdgeThresholdMin
    //
) {
    vec2 posM = pos;
    #if (FXAA_GATHER4_ALPHA == 1)
        #if (FXAA_DISCARD == 0)
            vec4 rgbyM = texture2DLod(tex, posM, 0.0);
            #define lumaM rgbyM.w
        #endif
            vec4 luma4A = FxaaTexAlpha4(tex, posM);
            vec4 luma4B = FxaaTexOffAlpha4(tex, posM, ivec2(-1, -1));
        #if (FXAA_DISCARD == 1)
            #define lumaM luma4A.w
        #endif
        #define lumaE luma4A.z
        #define lumaS luma4A.x
        #define lumaSE luma4A.y
        #define lumaNW luma4B.w
        #define lumaN luma4B.z
        #define lumaW luma4B.x
    #else
        vec4 rgbyM = texture2DLod(tex, posM, 0.0);
        #define lumaM rgbyM.w
        float lumaS = FxaaLuma(FxaaTexOff(tex, posM, ivec2(0, 1), fxaaQualityRcpFrame.xy));
        float lumaE = FxaaLuma(FxaaTexOff(tex, posM, ivec2(1, 0), fxaaQualityRcpFrame.xy));
        float lumaN = FxaaLuma(FxaaTexOff(tex, posM, ivec2(0,-1), fxaaQualityRcpFrame.xy));
        float lumaW = FxaaLuma(FxaaTexOff(tex, posM, ivec2(-1, 0), fxaaQualityRcpFrame.xy));
    #endif
    float maxSM = max(lumaS, lumaM);
    float minSM = min(lumaS, lumaM);
    float maxESM = max(lumaE, maxSM);
    float minESM = min(lumaE, minSM);
    float maxWN = max(lumaN, lumaW);
    float minWN = min(lumaN, lumaW);
    float rangeMax = max(maxWN, maxESM);
    float rangeMin = min(minWN, minESM);
    float rangeMaxScaled = rangeMax * fxaaQualityEdgeThreshold;
    float range = rangeMax - rangeMin;
    float rangeMaxClamped = max(fxaaQualityEdgeThresholdMin, rangeMaxScaled);
    bool earlyExit = range < rangeMaxClamped;
    if(earlyExit)
        #if (FXAA_DISCARD == 1)
            FxaaDiscard;
        #else
            return rgbyM;
        #endif
    #if (FXAA_GATHER4_ALPHA == 0)
        float lumaNW = FxaaLuma(FxaaTexOff(tex, posM, ivec2(-1,-1), fxaaQualityRcpFrame.xy));
        float lumaSE = FxaaLuma(FxaaTexOff(tex, posM, ivec2(1, 1), fxaaQualityRcpFrame.xy));
        float lumaNE = FxaaLuma(FxaaTexOff(tex, posM, ivec2(1,-1), fxaaQualityRcpFrame.xy));
        float lumaSW = FxaaLuma(FxaaTexOff(tex, posM, ivec2(-1, 1), fxaaQualityRcpFrame.xy));
    #else
        float lumaNE = FxaaLuma(FxaaTexOff(tex, posM, ivec2(1, -1), fxaaQualityRcpFrame.xy));
        float lumaSW = FxaaLuma(FxaaTexOff(tex, posM, ivec2(-1,  1), fxaaQualityRcpFrame.xy));
    #endif
    float lumaNS = lumaN + lumaS;
    float lumaWE = lumaW + lumaE;
    float subpixRcpRange = 1.0/range;
    float subpixNSWE = lumaNS + lumaWE;
    float edgeHorz1 = (-2.0 * lumaM) + lumaNS;
    float edgeVert1 = (-2.0 * lumaM) + lumaWE;
    float lumaNESE = lumaNE + lumaSE;
    float lumaNWNE = lumaNW + lumaNE;
    float edgeHorz2 = (-2.0 * lumaE) + lumaNESE;
    float edgeVert2 = (-2.0 * lumaN) + lumaNWNE;
    float lumaNWSW = lumaNW + lumaSW;
    float lumaSWSE = lumaSW + lumaSE;
    float edgeHorz4 = (abs(edgeHorz1) * 2.0) + abs(edgeHorz2);
    float edgeVert4 = (abs(edgeVert1) * 2.0) + abs(edgeVert2);
    float edgeHorz3 = (-2.0 * lumaW) + lumaNWSW;
    float edgeVert3 = (-2.0 * lumaS) + lumaSWSE;
    float edgeHorz = abs(edgeHorz3) + edgeHorz4;
    float edgeVert = abs(edgeVert3) + edgeVert4;
    float subpixNWSWNESE = lumaNWSW + lumaNESE;
    float lengthSign = fxaaQualityRcpFrame.x;
    bool horzSpan = edgeHorz >= edgeVert;
    float subpixA = subpixNSWE * 2.0 + subpixNWSWNESE;
    if(!horzSpan) lumaN = lumaW;
    if(!horzSpan) lumaS = lumaE;
    if(horzSpan) lengthSign = fxaaQualityRcpFrame.y;
    float subpixB = (subpixA * (1.0/12.0)) - lumaM;
    float gradientN = lumaN - lumaM;
    float gradientS = lumaS - lumaM;
    float lumaNN = lumaN + lumaM;
    float lumaSS = lumaS + lumaM;
    bool pairN = abs(gradientN) >= abs(gradientS);
    float gradient = max(abs(gradientN), abs(gradientS));
    if(pairN) lengthSign = -lengthSign;
    float subpixC = saturate(abs(subpixB) * subpixRcpRange);
    vec2 posB = posM;
    vec2 offNP;
    offNP.x = (!horzSpan) ? 0.0 : fxaaQualityRcpFrame.x;
    offNP.y = (horzSpan) ? 0.0 : fxaaQualityRcpFrame.y;
    if(!horzSpan) posB.x += lengthSign * 0.5;
    if(horzSpan) posB.y += lengthSign * 0.5;
    vec2 posN;
    posN.x = posB.x - offNP.x * c_kernel[0];
    posN.y = posB.y - offNP.y * c_kernel[0];
    vec2 posP;
    posP.x = posB.x + offNP.x * c_kernel[0];
    posP.y = posB.y + offNP.y * c_kernel[0];
    float subpixD = ((-2.0)*subpixC) + 3.0;
    float lumaEndN = FxaaLuma(texture2DLod(tex, posN, 0.0));
    float subpixE = subpixC * subpixC;
    float lumaEndP = FxaaLuma(texture2DLod(tex, posP, 0.0));
    if(!pairN) lumaNN = lumaSS;
    float gradientScaled = gradient * 1.0/4.0;
    float lumaMM = lumaM - lumaNN * 0.5;
    float subpixF = subpixD * subpixE;
    bool lumaMLTZero = lumaMM < 0.0;
    lumaEndN -= lumaNN * 0.5;
    lumaEndP -= lumaNN * 0.5;
    bool doneN = abs(lumaEndN) >= gradientScaled;
    bool doneP = abs(lumaEndP) >= gradientScaled;
    if(!doneN) posN.x -= offNP.x * c_kernel[1];
    if(!doneN) posN.y -= offNP.y * c_kernel[1];
    bool doneNP = (!doneN) || (!doneP);
    if(!doneP) posP.x += offNP.x * c_kernel[1];
    if(!doneP) posP.y += offNP.y * c_kernel[1];
	 for(int i = 1; i < int(FXAA_QUALITY_PS); i++)
    {
        if(!doneNP) break;
        if(!doneN) lumaEndN = FxaaLuma(texture2DLod(tex, posN.xy, 0.0));
        if(!doneP) lumaEndP = FxaaLuma(texture2DLod(tex, posP.xy, 0.0));
        if(!doneN) lumaEndN = lumaEndN - lumaNN * 0.5;
        if(!doneP) lumaEndP = lumaEndP - lumaNN * 0.5;
        doneN = abs(lumaEndN) >= gradientScaled;
        doneP = abs(lumaEndP) >= gradientScaled;
        if(!doneN) posN.x -= offNP.x * c_kernel[i];
        if(!doneN) posN.y -= offNP.y * c_kernel[i];
        doneNP = (!doneN) || (!doneP);
        if(!doneP) posP.x += offNP.x * c_kernel[i];
        if(!doneP) posP.y += offNP.y * c_kernel[i];
    }
    float dstN = posM.x - posN.x;
    float dstP = posP.x - posM.x;
    if(!horzSpan) dstN = posM.y - posN.y;
    if(!horzSpan) dstP = posP.y - posM.y;
    bool goodSpanN = (lumaEndN < 0.0) != lumaMLTZero;
    float spanLength = (dstP + dstN);
    bool goodSpanP = (lumaEndP < 0.0) != lumaMLTZero;
    float spanLengthRcp = 1.0/spanLength;
    bool directionN = dstN < dstP;
    float dst = min(dstN, dstP);
    bool goodSpan = directionN ? goodSpanN : goodSpanP;
    float subpixG = subpixF * subpixF;
    float pixelOffset = (dst * (-spanLengthRcp)) + 0.5;
    float subpixH = subpixG * fxaaQualitySubpix;
    float pixelOffsetGood = goodSpan ? pixelOffset : 0.0;
    float pixelOffsetSubpix = max(pixelOffsetGood, subpixH);
    if(!horzSpan) posM.x += pixelOffsetSubpix * lengthSign;
    if(horzSpan) posM.y += pixelOffsetSubpix * lengthSign;
    #if (FXAA_DISCARD == 1)
        return texture2DLod(tex, posM, 0.0);
    #else
        return vec4(texture2DLod(tex, posM, 0.0).xyz, lumaM);
    #endif
}
void main() {
    gl_FragColor = FxaaPixelShader(
        v_uv0,
        s_diffuse,
        u_pixel_size,
        0.75,
        0.166,
        0.0833
  );
    // TODO avoid querying texture twice for same texel
    gl_FragColor.a = texture2D(s_diffuse, v_uv0).a;
}
