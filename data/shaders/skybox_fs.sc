$input v_dir, v_color

#include <common.sh>
#include <spherical.sh>
#include <filter.sh>

#define s_skybox s_source_0
#define u_skybox_level u_source_0_level

void main()
{
    vec3 dir = normalize(v_dir);
    //dir = fixCubeLookup(dir, lod, 256.0);

#ifdef SOURCE_0_CUBE
    // cubemaps are left-handed, but we are right-handed
    vec4 color = textureCubeLod(s_skybox, vec3(-dir.x, dir.y, dir.z), u_skybox_level);
#else
    vec4 color = textureSpherical2D(s_skybox, dir, u_skybox_level);
#endif

    gl_FragColor = color;
    //gl_FragColor = vec4(dir, 1.0);
    //gl_FragColor = v_color;
}
