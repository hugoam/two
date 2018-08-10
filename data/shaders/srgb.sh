#ifndef MUD_SHADER_SRGB
#define MUD_SHADER_SRGB

vec3 toLinear(vec3 _rgb)
{
	return pow(abs(_rgb), vec3_splat(2.2) );
}

vec4 toLinear(vec4 _rgba)
{
	return vec4(toLinear(_rgba.xyz), _rgba.w);
}

vec3 toLinearAccurate(vec3 _rgb)
{
	vec3 lo = _rgb / 12.92;
	vec3 hi = pow( (_rgb + 0.055) / 1.055, vec3_splat(2.4) );
	vec3 rgb = mix(hi, lo, vec3(lessThanEqual(_rgb, vec3_splat(0.04045) ) ) );
	return rgb;
}

vec4 toLinearAccurate(vec4 _rgba)
{
	return vec4(toLinearAccurate(_rgba.xyz), _rgba.w);
}

float toGamma(float _r)
{
	return pow(abs(_r), 1.0/2.2);
}

vec3 toGamma(vec3 _rgb)
{
	return pow(abs(_rgb), vec3_splat(1.0/2.2) );
}

vec4 toGamma(vec4 _rgba)
{
	return vec4(toGamma(_rgba.xyz), _rgba.w);
}

vec3 toGammaAccurate(vec3 _rgb)
{
	vec3 lo  = _rgb * 12.92;
	vec3 hi  = pow(abs(_rgb), vec3_splat(1.0/2.4) ) * 1.055 - 0.055;
	vec3 rgb = mix(hi, lo, vec3(lessThanEqual(_rgb, vec3_splat(0.0031308) ) ) );
	return rgb;
}

vec4 toGammaAccurate(vec4 _rgba)
{
	return vec4(toGammaAccurate(_rgba.xyz), _rgba.w);
}

#endif // MUD_SHADER_SRGB
