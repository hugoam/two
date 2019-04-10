$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal
#include <encode.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>
#define BRDF_BLINN_PHONG
#include <pbr/light_brdf_three.sh>
#include <pbr/radiance.sh>

//SAMPLER2D(s_tiles, 7);
//SAMPLER2D(s_lights, 8);
#define s_tiles s_user0
#define s_lights s_user1

void main()
{
#include <pbr/fs_fragment.sh>
#include <pbr/fs_phong_material.sh>
PhongMaterial material = matphong;
#include <pbr/fs_phong.sh>

//#define ALL_LIGHTS
#ifndef ALL_LIGHTS
ivec2 iuv = ivec2(gl_FragCoord.xy) / 32;
vec4 tile = texelFetch(s_tiles, iuv, 0);
#endif
for (int i = 0; i < 4; i++)
{
#ifndef ALL_LIGHTS
	float tileVal = tile.x * 255.0;
  	tile.xyzw = tile.yzwx;
	if(tileVal == 0.0) { continue; }
  	float tileDiv = 128.0;
#endif
	for (int j = 0; j < 8; j++)
	{
#ifndef ALL_LIGHTS
  		if (tileVal < tileDiv) { tileDiv *= 0.5; continue; }
		tileVal -= tileDiv;
		tileDiv *= 0.5;
#endif

		int uvx = 8 * i + j;

  		vec4 light_p0 = texelFetch(s_lights, ivec2(uvx, 0), 0);
  		vec3 position = light_p0.xyz;
  		float range = light_p0.w;

  		vec4 light_p1 = texelFetch(s_lights, ivec2(uvx, 1.0), 0);
  		vec3 energy = light_p1.xyz;
  		float decay = light_p1.w;

		vec3 l = position - fragment.position;
		float a = point_light_decay(length(l), range, decay);
		direct_brdf(energy * a, normalize(l), fragment, material, diffuse, specular);
	}
}

#include <pbr/fs_out_pbr.sh>
}
