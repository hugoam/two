#ifndef MUD_SHADERLIB
#define MUD_SHADERLIB

vec3 fixCubeLookup(vec3 _v, float _lod, float _topLevelCubeSize)
{
	// Reference:
	// Seamless cube-map filtering
	// http://the-witness.net/news/2012/02/seamless-cube-map-filtering/
	float ax = abs(_v.x);
	float ay = abs(_v.y);
	float az = abs(_v.z);
	float vmax = max(max(ax, ay), az);
	float scale = 1.0 - exp2(_lod) / _topLevelCubeSize;
	if (ax != vmax) { _v.x *= scale; }
	if (ay != vmax) { _v.y *= scale; }
	if (az != vmax) { _v.z *= scale; }
	return _v;
}

vec2 texture2DBc5(sampler2D _sampler, vec2 _uv)
{
#if BGFX_SHADER_LANGUAGE_HLSL && BGFX_SHADER_LANGUAGE_HLSL <= 3
	return texture2D(_sampler, _uv).yx;
#else
	return texture2D(_sampler, _uv).xy;
#endif
}

#endif // MUD_SHADERLIB
