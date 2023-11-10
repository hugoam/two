$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

#include <encode.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>
#define BRDF_STANDARD
#include <pbr/light_brdf_three.sh>
#include <pbr/radiance.sh>
#include <fog.sh>

#ifdef GI_CONETRACE
#include <gi/conetrace.sh>
#endif

void main()
{
#include "fs_fragment.sh"

#include "fs_pbr_material.sh"

#ifdef DEFERRED
    #include "fs_out_gbuffer.sh"
#else
    #include "fs_three.sh"
    #include "fs_out_pbr.sh"
    #include "fs_fog_simple.sh"
#endif
}
