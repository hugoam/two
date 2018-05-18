$input v_dir, v_texcoord0

#include "common.sh"
#include "spherical.sh"

SAMPLER2D(s_skybox_map, 0);

uniform vec4 u_skybox_params;
#define u_skybox_level u_skybox_params.x

void main()
{
	vec3 dir = normalize(v_dir);
	//dir = fixCubeLookup(dir, lod, 256.0);
    
	vec4 color = textureSpherical2D(s_skybox_map, dir, u_skybox_level);
	//vec4 color = toLinear(textureSpherical2D(s_skybox_map, dir, u_skybox_level));
	//color *= exp2(u_exposure);
    
	gl_FragColor = color; // vec4(v_dir, 1.0);
	//gl_FragColor = toFilmic(color);
}
