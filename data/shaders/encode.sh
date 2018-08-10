#ifndef MUD_SHADER_ENCODE
#define MUD_SHADER_ENCODE

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

#endif // MUD_SHADER_ENCODE
