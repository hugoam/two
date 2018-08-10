$input v_texcoord0,

#include <common.sh>
#include <spherical.sh>

//#define SOURCE_0_ARRAY
#include <filter/filter.sh>

#define s_radiance_source s_source_0

uniform vec4 u_prefilter_envmap_params;
#define u_roughness u_prefilter_envmap_params.x
#define u_num_samples u_prefilter_envmap_params.y

// reference : Real Shading in Unreal Engine 4
// also : https://learnopengl.com/PBR/IBL/Specular-IBL
vec3 ImportanceSampleGGX(vec2 Xi, float Roughness, vec3 N)
{
	float a = Roughness * Roughness;

	// Compute distribution direction
	float Phi = 2.0 * M_PI * Xi.x;
	float CosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
	float SinTheta = sqrt(1.0 - CosTheta * CosTheta);

	// Convert to spherical direction
	vec3 H;
	H.x = SinTheta * cos(Phi);
	H.y = SinTheta * sin(Phi);
	H.z = CosTheta;

	vec3 UpVector = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
	vec3 TangentX = normalize(cross(UpVector, N));
	vec3 TangentY = cross(N, TangentX);

	// Tangent to world space
	return TangentX * H.x + TangentY * H.y + N * H.z;
}

#if BGFX_SHADER_LANGUAGE_GLSL <= 120
float VanDerCorpus(int n, int base)
{
    float invBase = 1.0 / float(base);
    float denom   = 1.0;
    float result  = 0.0;

    for(int i = 0; i < 32; ++i)
    {
        if(n > 0)
        {
            denom   = mod(float(n), 2.0);
            result += denom * invBase;
            invBase = invBase / 2.0;
            n       = int(float(n) / 2.0);
        }
    }

    return result;
}
vec2 Hammersley(int i, int N)
{
    return vec2(float(i)/float(N), VanDerCorpus(i, 2));
}
#else
float RadicalInverseVdC(uint bits)
{
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

vec2 Hammersley(uint i, uint N)
{
     return vec2(float(i) / float(N), RadicalInverseVdC(i));
}
#endif

void main()
{
	vec3 N = invertedSphericalUV(v_texcoord0.xy);
    vec3 V = N;

	vec4 color = vec4_splat(0.0);

#if BGFX_SHADER_LANGUAGE_GLSL <= 120
    int num_samples = int(u_num_samples);
	for(int i = 0; i < num_samples; i++)
#else
    uint num_samples = uint(u_num_samples);
	for(uint i = 0u; i < num_samples; i++)
#endif
    {
		vec2 Xi = Hammersley(i, num_samples);

		vec3 H = ImportanceSampleGGX(Xi, u_roughness, N);
		vec3 L = 2.0 * dot(V, H) * H - V;

		float NoL = saturate(dot(N, L));

		if (NoL > 0.0)
        {
#ifdef SOURCE_0_ARRAY
			color.rgb += textureSpherical2DArray(s_radiance_source, L, float(u_source_0_level)).rgb * NoL;
#else
			color.rgb += textureSpherical2D(s_radiance_source, L, float(u_source_0_level)).rgb * NoL;
#endif
			color.a += NoL;
		}
	}

	color /= color.a;

	gl_FragColor = vec4(color.rgb, 1.0);
	//gl_FragColor = vec4(N, 1.0);
}

