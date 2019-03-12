$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

#include <encode.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>
#include <pbr/radiance.sh>

void main()
{
#include "fs_fragment.sh"

    vec2 uv = fragment.uv;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

    int zone_index = int(u_state_zone);
    Zone zone = read_zone(zone_index);
    
#ifdef RADIANCE_ENVMAP
    vec3 env = radiance_reflection(zone, fragment.view, fragment.normal, 0.0);
#else
    vec3 env = vec3_splat(1.0);
#endif
    
    int material_index = int(u_state_material);
    PbrMaterial pbr = read_pbr_material(material_index);

    gl_FragColor = vec4(pbr.albedo * env, pbr.alpha);
}
