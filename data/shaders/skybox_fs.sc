$input v_dir, v_uv0

#include <common.sh>
#include <spherical.sh>

#ifdef SKYBOX_CUBE
SAMPLERCUBE(s_skybox_map, 0);
#else
SAMPLER2D(s_skybox_map, 0);
#endif

uniform vec4 u_skybox_p0;
#define u_skybox_level u_skybox_p0.x

void main()
{
    vec3 dir = normalize(v_dir);
    //dir = fixCubeLookup(dir, lod, 256.0);

#ifdef SKYBOX_CUBE
    // cubemaps are left-handed, but we are right-handed
    vec4 color = textureCubeLod(s_skybox_map, vec3(-dir.x, dir.y, dir.z), u_skybox_level);
#else
    vec4 color = textureSpherical2D(s_skybox_map, dir, u_skybox_level);
#endif
    //color = toLinear(color);
    //color *= exp2(u_exposure);

    gl_FragColor = color;
    //gl_FragColor = vec4(dir, 1.0);
    //gl_FragColor = toFilmic(color);
}
