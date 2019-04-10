#ifndef MUD_SHADER_TONEMAP
#define MUD_SHADER_TONEMAP

#include <srgb.sh>

vec3 toReinhard(vec3 _rgb)
{
	return toGamma(_rgb/(_rgb+vec3_splat(1.0) ) );
}

vec4 toReinhard(vec4 _rgba)
{
	return vec4(toReinhard(_rgba.xyz), _rgba.w);
}

vec3 toFilmic(vec3 _rgb)
{
	_rgb = max(vec3_splat(0.0), _rgb - 0.004);
	_rgb = (_rgb*(6.2*_rgb + 0.5) ) / (_rgb*(6.2*_rgb + 1.7) + 0.06);
	return _rgb;
}

vec4 toFilmic(vec4 _rgba)
{
	return vec4(toFilmic(_rgba.xyz), _rgba.w);
}

vec3 toAcesFilmic(vec3 _rgb)
{
    // Reference:
    // ACES Filmic Tone Mapping Curve
    // https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
    float aa = 2.51f;
    float bb = 0.03f;
    float cc = 2.43f;
    float dd = 0.59f;
    float ee = 0.14f;
    return saturate( (_rgb*(aa*_rgb + bb) )/(_rgb*(cc*_rgb + dd) + ee) );
}

vec4 toAcesFilmic(vec4 _rgba)
{
    return vec4(toAcesFilmic(_rgba.xyz), _rgba.w);
}

float luma(vec3 _rgb)
{
    float yy = dot(vec3(0.2126729, 0.7151522, 0.0721750), _rgb);
    return yy;
}

vec3 luma3(vec3 _rgb)
{
	return vec3_splat(luma(_rgb));
}

vec4 luma(vec4 _rgba)
{
	return vec4(luma3(_rgba.xyz), _rgba.w);
}

vec3 conSatBri(vec3 _rgb, vec3 _csb)
{
	vec3 rgb = _rgb * _csb.z;
	rgb = mix(luma3(rgb), rgb, _csb.y);
	rgb = mix(vec3_splat(0.5), rgb, _csb.x);
	return rgb;
}

vec4 conSatBri(vec4 _rgba, vec3 _csb)
{
	return vec4(conSatBri(_rgba.xyz, _csb), _rgba.w);
}

vec3 posterize(vec3 _rgb, float _numColors)
{
	return floor(_rgb*_numColors) / _numColors;
}

vec4 posterize(vec4 _rgba, float _numColors)
{
	return vec4(posterize(_rgba.xyz, _numColors), _rgba.w);
}

vec3 sepia(vec3 _rgb)
{
	vec3 color;
	color.x = dot(_rgb, vec3(0.393, 0.769, 0.189) );
	color.y = dot(_rgb, vec3(0.349, 0.686, 0.168) );
	color.z = dot(_rgb, vec3(0.272, 0.534, 0.131) );
	return color;
}

vec4 sepia(vec4 _rgba)
{
	return vec4(sepia(_rgba.xyz), _rgba.w);
}

vec3 blendOverlay(vec3 _base, vec3 _blend)
{
	vec3 lt = 2.0 * _base * _blend;
	vec3 gte = 1.0 - 2.0 * (1.0 - _base) * (1.0 - _blend);
	return mix(lt, gte, step(vec3_splat(0.5), _base) );
}

vec4 blendOverlay(vec4 _base, vec4 _blend)
{
	return vec4(blendOverlay(_base.xyz, _blend.xyz), _base.w);
}

vec3 to_reindhart(vec3 color, float white)
{
    return color * (1.0 + (color / white)) / (1.0 + color);
}

vec3 to_filmic(vec3 color, float white)
{
    float A = 0.15;
    float B = 0.50;
    float C = 0.10;
    float D = 0.20;
    float E = 0.02;
    float F = 0.30;
    float W = 11.2;

    vec3 coltn = ((color*(A*color+C*B)+D*E)/(color*(A*color+B)+D*F))-E/F;
    float whitetn = ((white*(A*white+C*B)+D*E)/(white*(A*white+B)+D*F))-E/F;

    return coltn / whitetn;
}

#endif // MUD_SHADER_TONEMAP
