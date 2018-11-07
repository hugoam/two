#ifndef MUD_SHADER_ENCODE
#define MUD_SHADER_ENCODE

#include <common.sh>

CONST(float) hdrRange = 10.0;

#if BGFX_SHADER_LANGUAGE_GLSL == 0 || BGFX_SHADER_LANGUAGE_GLSL > 120
uint encodeRGBA8(vec4 val)
{
  return (uint(val.w) & 0x000000FFu) << 24u
       | (uint(val.z) & 0x000000FFu) << 16u
       | (uint(val.y) & 0x000000FFu) << 8u
       | (uint(val.x) & 0x000000FFu);
}

vec4 decodeRGBA8(uint val)
{
  return vec4(float((val & 0x000000FFu)),
              float((val & 0x0000FF00u) >> 8u),
              float((val & 0x00FF0000u) >> 16u),
              float((val & 0xFF000000u) >> 24u));
}
#endif

vec4 encodeRE8(float _r)
{
	float exponent = ceil(log2(_r) );
	return vec4(_r / exp2(exponent)
			, 0.0
			, 0.0
			, (exponent + 128.0) / 255.0
			);
}

float decodeRE8(vec4 _re8)
{
	float exponent = _re8.w * 255.0 - 128.0;
	return _re8.x * exp2(exponent);
}

vec4 encodeRGBE8(vec3 _rgb)
{
	vec4 rgbe8;
	float maxComponent = max(max(_rgb.x, _rgb.y), _rgb.z);
	float exponent = ceil(log2(maxComponent) );
	rgbe8.xyz = _rgb / exp2(exponent);
	rgbe8.w = (exponent + 128.0) / 255.0;
	return rgbe8;
}

vec3 decodeRGBE8(vec4 _rgbe8)
{
	float exponent = _rgbe8.w * 255.0 - 128.0;
	vec3 rgb = _rgbe8.xyz * exp2(exponent);
	return rgb;
}

vec3 encodeNormalUint(vec3 _normal)
{
	return _normal * 0.5 + 0.5;
}

vec3 decodeNormalUint(vec3 _encodedNormal)
{
	return _encodedNormal * 2.0 - 1.0;
}

vec2 encodeNormalSphereMap(vec3 _normal)
{
	return normalize(_normal.xy) * sqrt(_normal.z * 0.5 + 0.5);
}

vec3 decodeNormalSphereMap(vec2 _encodedNormal)
{
	float zz = dot(_encodedNormal, _encodedNormal) * 2.0 - 1.0;
	return vec3(normalize(_encodedNormal.xy) * sqrt(1.0 - zz*zz), zz);
}

vec2 octahedronWrap(vec2 _val)
{
	// Reference:
	// Octahedron normal vector encoding
	// http://kriscg.blogspot.com/2014/04/octahedron-normal-vector-encoding.html
	return (1.0 - abs(_val.yx) )
		 * mix(vec2_splat(-1.0), vec2_splat(1.0), vec2(greaterThanEqual(_val.xy, vec2_splat(0.0) ) ) );
}

vec2 encodeNormalOctahedron(vec3 _normal)
{
	_normal /= abs(_normal.x) + abs(_normal.y) + abs(_normal.z);
	_normal.xy = _normal.z >= 0.0 ? _normal.xy : octahedronWrap(_normal.xy);
	_normal.xy = _normal.xy * 0.5 + 0.5;
	return _normal.xy;
}

vec3 decodeNormalOctahedron(vec2 _encodedNormal)
{
	_encodedNormal = _encodedNormal * 2.0 - 1.0;

	vec3 normal;
	normal.z  = 1.0 - abs(_encodedNormal.x) - abs(_encodedNormal.y);
	normal.xy = normal.z >= 0.0 ? _encodedNormal.xy : octahedronWrap(_encodedNormal.xy);
	return normalize(normal);
}

vec4 packFloatToRgba(float _value)
{
	const vec4 shift = vec4(256 * 256 * 256, 256 * 256, 256, 1.0);
	const vec4 mask = vec4(0, 1.0 / 256.0, 1.0 / 256.0, 1.0 / 256.0);
	vec4 comp = fract(_value * shift);
	comp -= comp.xxyz * mask;
	return comp;
}

float unpackRgbaToFloat(vec4 _rgba)
{
	const vec4 shift = vec4(1.0 / (256.0 * 256.0 * 256.0), 1.0 / (256.0 * 256.0), 1.0 / 256.0, 1.0);
	return dot(_rgba, shift);
}

vec2 packHalfFloat(float _value)
{
	const vec2 shift = vec2(256, 1.0);
	const vec2 mask = vec2(0, 1.0 / 256.0);
	vec2 comp = fract(_value * shift);
	comp -= comp.xx * mask;
	return comp;
}

float unpackHalfFloat(vec2 _rg)
{
	const vec2 shift = vec2(1.0 / 256.0, 1.0);
	return dot(_rg, shift);
}

vec4 encodeRGBM(vec3 rgb)
{
    float maxRGB = max(rgb.x, max(rgb.g, max(rgb.b, 1e-6)));
    float M =      maxRGB / hdrRange;
    M =            ceil(M * 255.0) / 255.0;
    return vec4(rgb / (M * hdrRange), M);
}

vec3 decodeRGBM(vec4 rgbm)
{
    return rgbm.rgb * (rgbm.a * hdrRange);
}

vec4 encodeHDR(vec3 color)
{
    return encodeRGBM(color);
    //return encodeRGBE8(color);
	float hdr = length(color);
    return vec4(color / hdr, hdr / hdrRange);
}

vec3 decodeHDR(vec4 color)
{
    return decodeRGBM(color);
    //return decodeRGBE8(color);
    float hdr = color.a * hdrRange;
	return vec3(color.rgb * hdr);
}

#if BGFX_SHADER_LANGUAGE_GLSL == 0 || BGFX_SHADER_LANGUAGE_GLSL > 120
// Encode HDR color to a 32 bit uint
// Alpha is 1 bit + 7 bit HDR remapping
uint encodeColor(vec4 color)
{
	// normalize color to LDR
	float hdr = length(color.rgb);
	color.rgb /= hdr;

	// encode LDR color and HDR range
	uvec3 iColor = uvec3(color.rgb * 255.0);
	uint iHDR = uint(saturate(hdr / hdrRange) * 127);
	uint colorMask = (iHDR << 24u) | (iColor.r << 16u) | (iColor.g << 8u) | iColor.b;

	// encode alpha into highest bit
	uint iAlpha = (color.a > 0 ? 1u : 0u);
	colorMask |= iAlpha << 31u;

	return colorMask;
}

// Decode 32 bit uint into HDR color with 1 bit alpha
vec4 decodeColor(uint colorMask)
{
	float hdr;
	vec4 color;

	hdr = (colorMask >> 24u) & 0x0000007f;
	color.r = (colorMask >> 16u) & 0x000000ff;
	color.g = (colorMask >> 8u) & 0x000000ff;
	color.b = colorMask & 0x000000ff;

	hdr /= 127.0;
	color.rgb /= 255.0;

	color.rgb *= hdr * hdrRange;

	color.a = (colorMask >> 31u) & 0x00000001;

	return color;
}

uint encodeNormal(vec3 n)
{
	ivec3 inor = ivec3(n * 255.0);
	uvec3 signs;
	signs.x = uint((inor.x >> 5) & 0x04000000);
	signs.y = uint((inor.y >> 14) & 0x00020000);
	signs.z = uint((inor.z >> 23) & 0x00000100);
	inor = abs(inor);
	uint val = int(signs.x) | (inor.x << 18) | int(signs.y) | (inor.y << 9) | int(signs.z) | inor.z;
	//uint val = signs.x | uint(inor.x << 18) | signs.y | uint(inor.y << 9) | signs.z | uint(inor.z);
	return val;
}

vec3 decodeNormal(uint val)
{
	ivec3 nor;
	nor.x = (int(val) >> 18) & 0x000000FF;
	nor.y = (int(val) >> 9) & 0x000000FF;
	nor.z = int(val) & 0x000000FF;
	ivec3 signs;
	signs.x = (int(val) >> 25) & 0x00000002;
	signs.y = (int(val) >> 16) & 0x00000002;
	signs.z = (int(val) >> 7) & 0x00000002;
	signs = ivec3(1,1,1) - signs;
	vec3 normal = vec3(nor) / 255.0;
	normal *= vec3(signs);
	return normal;
}
#endif

#endif // MUD_SHADER_ENCODE
