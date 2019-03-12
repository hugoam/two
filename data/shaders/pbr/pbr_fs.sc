$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

#include <encode.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>
#include <pbr/radiance.sh>

#ifdef FOG
#include <pbr/fog.sh>
#endif

#ifdef GI_CONETRACE
#include <gi/conetrace.sh>
#endif

void main()
{
#include "fs_fragment.sh"

#include "fs_material.sh"

#ifdef DEFERRED
    #include "fs_out_gbuffer.sh"
#else
    #include "fs_pbr.sh"
    #include "fs_out_pbr.sh"
#endif
}
