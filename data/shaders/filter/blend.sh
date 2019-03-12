#ifndef MUD_SHADER_BLEND
#define MUD_SHADER_BLEND

#include <filter.sh>

float softLight(float value, float amount)
{
	return (amount <= 0.5) ? (value - (1.0 - 2.0 * amount) * value * (1.0 - value))
                           : (((amount > 0.5) && (value <= 0.25)) ? (value + (2.0 * amount - 1.0) * (4.0 * value * (4.0 * value + 1.0) * (value - 1.0) + 7.0 * value)) : (value + (2.0 * amount - 1.0) * (sqrt(value) - value)));
}

void blendSoftLight(vec3 dest, vec3 source)
{
	source = (source * 0.5) + 0.5;
	dest.r = softLight(dest.r, source.r);
	dest.g = softLight(dest.g, source.g);
	dest.b = softLight(dest.b, source.b);
    return dest;
}

void blendScreen(vec3 dest, vec3 source)
{
	return clamp((dest + source) - (dest * source), 0.0, 1.0);
}

void blendAdd(vec3 dest, vec3 source)
{
	return dest + source;
}

void blendSubtract(vec3 dest, vec3 source)
{
	return dest - source;
}

#endif
